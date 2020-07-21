1、一个Connector对应一套Acceptor、Poller线程架构

2、tomcat启动时会加载web应用，通过server.xml进行相应的初始化；

3、发起请求时，会通过请求的协议和端口找到对应的Processor，然后进行后续的处理操作；

4、poller线程会定期查询就绪的socket，然后将其交给一个Processor进行处理；

5、通过Poller线程选择好了对应的就绪socket后，对于这个socket的事件处理是放到一个线程池中执行的，可进行相应的配置；

参考文章
https://blog.csdn.net/xlgen157387/article/details/79006434
https://blog.csdn.net/jcw321/article/details/102526747
