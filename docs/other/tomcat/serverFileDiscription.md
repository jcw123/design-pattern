## 配置文件基本结构

```xml
<Server>
  <Service> <!-- 此元素可以有一个或者多个 -->
    <Connector> <!-- 此元素可以有多个 -->
    </Connector>
    <Engine>  <!-- 容器 可以处理服务下的所有请求 -->
      <Host> <!-- 一个主机 -->
        <Context /> <!-- 主机下的一个应用 -->
      </Host>
    </Engine>
  </Service>
</Server>
```

注：Host节点的deployOnStartup和autoDeploy可以启动自动部署

一、如果决定请求由谁处理
1、根据协议和端口号选定Service和Engine
2、根据域名或Ip选定Host
3、根据URL选定Context/Web应用

二、配置多个服务
1、可以实现通过不同的端口号访问同一台机房不同的应用


三、其他组件
1、Listener
监听器组件，可以在特定事件发生时执行特定的操作
2、GlobalNamingResources和Realm
Realm提供了一种用户密码与web应用的映射关系，从而达到角色安全管理的作用；GlobalNamingResources元素定义了全局资源；
3、Valve
代表了请求流水线上的一个组件，可以在流水线上执行特定的操作；

四、Connector架构分析
Connector使用ProtocolHandler来处理请求的，不同的ProtocolHandler代表不同的连接类型；ProtocolHandler
包含Endpoint、Processor、Adapter；Endpoint用于处理底层的Socket连接，
Processor用于将EndPoint接收到的Socket封装成Request,Adapter用于将Request交给Container进行具体处理。

五、webapp三种部署方式
1、通过XML文件描述符

2、WAR包
3、文件目录

六、tomcat启动过程
1、启动入口是Bootstrap的main函数
2、实例化一个Bootstrap
3、调用Bootstrap的init方法，初始化三个类加载器，包括commonLoader、catalinaLoader、sharedLoader，调用的是Bootstrap的createClassLoader方法。通过将Bootstrap所属的线程的类加载器设置为catalinaLoader。使用catalinaLoader加载Catalina类，同时将sharedLoader设置为Catalina的父加载器。
4、调用Bootstrap实例的start方法，设置Catalina的await属性为true，设置参数，在设置参数时，会调用Catalina实例的load方法，会解析server.xml对象，构造Server对象，同时调用Server对象的init方法；接着调用Catalina类的start方法。
5、Catalina.start方法内部电泳Server对象的start方法，内部会根据Server组件的状态调用相应的方法
> Catalina、Server、Engine、Host等都是组件，实现了LifecycleBase抽象类，用于描述组件的生命周期。

6、调用Server的start方法，内部会进行生命周期状态转换，转换过程中，会触发对应的监听器（initialized -》STARTING_PREP -》STARTING -》STARTED），开始准备前会触发事件、配置开始会触发，事件在设置开始状态会触发事件，设置完成后也会触发事件。
7、Server内部startInternal方法会调用每一个Service方法的start方法
8、Service内部的startInternal方法会首先调用Engine对象的start方法，内部会实际调用ContainerBase的startInternal方法；然后调用Executor对象的start方法；最后调用Connector对象的start方法，start方法中会调用startInternal方法，startInternal方法内部调用ProtocolHandler实现类的start方法，start方法内部再调用AbstractEndpoint方法的start方法，内部会使用java自带的nio模式构建Socket连接。
> （1）每个组件内部的startInternal是核心方法，启动时实际做的事情就封装在这里面
（2）Connector的start方法中就是调用ProtocolHandler的start处理request请求，而start方法中会调用AbstractEndpoint的start方法进行底层的Socket连接；
（3）ProtocolHandler调用初始化时就已经初始化了ServerSocket
（4）Poller是其中的NioEndPoint中的轮询器，一直轮询，监听事件（单独启动一个线程）
（5）Acceptor是用于接收新的连接，当接收到连接后，会将其注册到Poller中（也是单独启动一个线程）
（6）启动时是先启动Connector中的端口，对于Server上的端口是最后启动了，主要是为了接收shutdown请求，关闭tomcat。
（7）AbstractEndPoint中excutor表示执行业务的线程池
（8）SocketProcessorBase这个对象的实例就是相当于一个个任务放到线程池中进行执行


七、请求和响应过程
1、首先建立连接，会通过Acceptor类来接收连接，同时注册到Poller对象的中
2、对于Poller，会启动一个线程定时监控请求
3、有请求过来时，会调用Poller中的processKey方法来处理对应的请求，在processKey中会实例化一个SocketProcessorBase对象，将对于的请求关联到这个对象中，然后SocketProcessorBase这个对象就作为一个任务放到线程池中执行；然后会调用SocketProcessorBase这个类的子类中的doRun方法；dnRun方法会调用AbstractEndPoint的具体子类中的Handler对象的process方法执行请求；process方法中会再次刁调用service方法执行，service方法中会再次调用Adapter实例的service方法执行；
4、接下来就会通过责任链的方式执行：
（1）
```java
connector.getService().getContainer().getPipeline().getFirst().invoke(
                        request, response);
```
(2)
```java
host.getPipeline().getFirst().invoke(request, response);
```
(3)
```java
context.getPipeline().getFirst().invoke(request, response);
```
(4)
```java
wrapper.getPipeline().getFirst().invoke(request, response);
```
5、在StandardWrapperValve的invoke方法中，会根据类名构造对应Servlet实例，然后实例化ApplicationFilterChain过滤器链，同时将servlet对象传递给过滤器链，首先执行过滤器链，当过滤器链执行完成后，就执行servlet中的service方法，
执行完service方法后，就会将response返回，最终可以在页面展示。

注：
1、Server对象是通过Digester解析Server.xml文件构造出来的；
2、Catalina.load()是会实例化一个Server，同时调用Server.init()方法
