初始化过程时，通过调用AbstractApplicationContext类中的refresh方法进行上下文初始化。

refresh方法采用template pattern设计模式，内部执行方法如下：

1. prepareRefresh
2. obtainFreshBeanFactory
3. prepareBeanFactory
4. postProcessBeanFactory
5. invokeBeanFactoryPostProcessors
6. registerBeanPostProcessors
7. initMessageSource
8. initApplicationEventMulticaster
9. onRefresh
10. registerListeners
11. finishBeanFactoryInitialization
12. finishRefresh

上述方法是完整初始化流程，如果抛出异常，会执行如下步骤：
1. destroyBeans
2. cancelRefresh

最后会执行如下方法：
1. resetCommonCaches


对于上述方法，有的提供了实现，有的是空实现，需要清楚每个方法具体做了什么事，能够做什么事。下面给出具体的说明。

##### prepareRefresh()
- 初始化启动时的状态，比如设置启动时间、激活状态、关闭状态等。
- 验证必须存在的properties属性

##### obtainFreshBeanFactory()
> DefaultListableBeanFactory这个bean才是最终的实现类，可以通过这个beanFactory拿到非常多的信息，
比如：bean的所有定义、不同注册类型bean的定义等等。
> DefaultBeanDefinitionDocumentReader这个类的doRegisterBeanDefinitions这个方法才是真正从xml配置中解析
bean的定义的方法。
> NamespaceHandler这个接口和对应的实现类很重要，主要是用来解析xml文件生成最终的BeanDefinition。
>ClassPathBeanDefinitionScanner这个类的doScan这个类扫描component-scan这个配置指定的bean。


执行步骤如下：
- 首先判断是否已经有beanFactory存在，如果有则先销毁原来的所有bean和beanFactory
- 创建一个初始化beanFactory，这一步基本调用createBeanFactory方法实例化一个DefaultListableBeanFactory。
- 调用customizeBeanFactory方法，定制化beanFactory，这一步就是简单设置beanFactory的allowBeanDefinitionOverriding和allowCircularReferences属性而已。
- 调用loadBeanDefinitions这个方法从配置文件和文件在加载所有查找到的bean的定义。

##### prepareBeanFactory()
> 为bean工厂在spring上下文使用做一些基本的准备操作。

执行步骤如下：
- 设置加载bean的类加载器。（使用applicationContext的类加载器）；
- 设置bean的后处理器ApplicationContextAwareProcessor
- 设置需要忽略的依赖接口
- 设置哪些依赖可以解析，工厂实例、资源加载器、应用上下文实例
- 设置bean的后处理器ApplicationListenerDetector
- 注册依赖单例实例，比如：environment、systemProperties、systemEnvironment。

##### postProcessBeanFactory(beanFactory)
> 这个方法是一个空实现，在这一步之前，所有的bean的定义都已经进行加载，但是bean都未实例，所有可以
通过这个方法注入一些bean的后处理器，当进行bean的实例化时调用这些后处理器进行一些特殊的逻辑操作。

##### invokeBeanFactoryPostProcessors(beanFactory)
> 调用beanFactory的后处理器

- 调用PostProcessorRegistrationDelegate这个类的invokeBeanFactoryPostProcessors这个静态方法
- 首先根据局applicationContext中的BeanFactoryPostProcessor列表进行逻辑处理，通常情况下这个列表是空，
但是可以在初始化上下文时注入内容。（这个方法中的内容看着很长，但是逻辑是很简单的，只是在处理bean的顺序上
是存在优先级的。）
- 获取BeanDefinitionRegistryPostProcessor实现这个接口的bean的name，然后按照实现PriorityOrdered、Ordered、其他的执行，每一个Processor只会执行一遍，首先执行postProcessBeanDefinitionRegistry这个方法。全部执行完之后，然后postProcessBeanFactory这个方法。（注：通过这些操作，可以注入新的bean的definition）
- 获取BeanFactoryPostProcessor上线这个接口的bean的name，然后执行过程中排除上面已经执行过得processor，然后按照
PriorityOrdered、Ordered、其他的顺序依次执行各个processor的postProcessBeanFactory这个方法。

##### registerBeanPostProcessors(beanFactory)
> 注册bean的后处理器，当执行bean的创建时会执行对应的后处理器逻辑。
这个方法就是查找BeanPostProcessor进行注册，没有做其他额外的事情。

- 获取所有实现BeanPostProcessor这个接口的bean的name集合；
- 基于这个集合依次获取实现PriorityOrdered、Ordered、其他processor名称，然后依次将这些bean写入beanPostProcessors列表中。

##### initMessageSource
> 初始化消息源，不太清楚做什么事情。
文档中是用来支持消息的参数化和国际化

- 没有定义的话，默认实例化一个单例DelegatingMessageSource，注册到beanFactory。

##### initApplicationEventMulticaster
> 初始化应用事件多播器，也不太清楚有什么用
用于管理一系列的应用事件监听对象，同时给它们发布事件。

- 初始化SimpleApplicationEventMulticaster实例，并注册此单例。

##### onRefresh()
> 默认是空实现，可以被子类重写，然后在类实例化之前，对一些特殊的实例进行一些初始化工作。

##### registerListeners()
> 注册监听器

- 首先从上下文中获取应用监听器列表，然后注册到ApplicationEventMulticaster中。
- 从bean工厂中获取实现了ApplicationListener接口的bean的定义，然后将其注册到ApplicationEventMulticaster中。

##### finishBeanFactoryInitialization(beanFactory)
> 初始化剩余的非懒加载的单例对象。根据定义，这里基本是大部分bean进行初始化的入口点。

- 如果没有PropertyPlaceholderConfigurer值解析器注入，会注入一个默认的值解析器；
- 缓存bean的定义，主要是防止这部分数据变动；
- 逐个进行未实例化的单例bean进行实例化。

##### finishRefresh()
> 最后一个步骤，发布相关的事件。

- 初始化lifecycleProcessor， 给context中的lifecycleProcessor成员变量进行赋值；
