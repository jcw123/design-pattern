## spring是什么？为什么需要spring？

spring是一个容器框架，bean的创建和管理都交给spring来管理。spring中几个核心概念。

- IOC（Inversion of Control）:控制反转
传统的代码中对象之间的耦合性太强，通过将对象交于spring容器管理，由容器来控制程序之前的依赖关系。其还有一个名字：DI（依赖
注入），即如果对象之间存在依赖关系，又spring容器将依赖的对象注入进去。

- AOP(Aspect Oriented Programming):面向切面编程
提供一些通用的组件，通过切面的方式注入调用点处，不需要破坏原来的代码结构。不仅降低了耦合性，同时能够使一些组件达到复用性。


## spring的初始化过程

1. 定义一个启动入口点
```java
public class Main {

    public static void main(String[] args) {
        ApplicationContext context = new ClassPathXmlApplicationContext("spring-config.xml");
        People people = context.getBean(People.class);
        people.say();
    }
}
```

当new一个ClassPahtXmlApplicationContext时候，内部会调用AbstractApplicationContext类中的refresh方法，通过这个方法，
会完成上线文的初始化工作，通过配置文件，会完成bean定义结构的转换。对于单例模式，且不是懒加载的类，会完成bean自身的实例化。

refresh方法的内部实现如下：
```java
// 采用的是模板设计模式，其中的一些方法提供了实现，一些方法子类可以重写
public void refresh() throws BeansException, IllegalStateException {
		synchronized (this.startupShutdownMonitor) {
			// Prepare this context for refreshing.
      // 主要是进行一些初始化工作，设置当前上下文被激活，执行一些property源文件的初始化工作
			prepareRefresh();

			// Tell the subclass to refresh the internal bean factory.
      // 这个方法很重要，获取工厂类，这个阶段会加载所有类的bean定义，同时完成一些
      //额外的相关工作
			ConfigurableListableBeanFactory beanFactory = obtainFreshBeanFactory();

			// Prepare the bean factory for use in this context.
      // 为生成的bean工厂做一些基本的工作，比如设置bean表达式的解析器，设置一些bean的后处理器
      // 设置一些依赖忽略的接口，一些依赖需要解析的接口等等。
      // beanFactory.addBeanPostProcessor(new ApplicationContextAwareProcessor(this))这个
      //方法就添加一个后过滤解析器，可以为实现*Aware接口的类做一些额外的事情。
			prepareBeanFactory(beanFactory);

			try {
				// Allows post-processing of the bean factory in context subclasses.
        // 目前是一个空时间，可以重写在bean工厂类中注入新的后处理器
				postProcessBeanFactory(beanFactory);

				// Invoke factory processors registered as beans in the context.
        // 主要是调用bean工厂类的后处理器，做一些事情
				invokeBeanFactoryPostProcessors(beanFactory);

				// Register bean processors that intercept bean creation.
        // 在bean实例的创建过程中，注入一些后处理器，可以在bean创建过程中
        //做一些额外的事情。
				registerBeanPostProcessors(beanFactory);

				// Initialize message source for this context.
        // 初始化MessageSource，可以用来支持消息的参数化和国际化等等。
				initMessageSource();

				// Initialize event multicaster for this context.
        // 初始化事件的多播（没用过，也不清楚什么意思）
				initApplicationEventMulticaster();

				// Initialize other special beans in specific context subclasses.
        // 默认是空实现
				onRefresh();

				// Check for listener beans and register them.
				registerListeners();

				// Instantiate all remaining (non-lazy-init) singletons.
        // 主要是完成一些非懒加载bean的实例化操作。
				finishBeanFactoryInitialization(beanFactory);

				// Last step: publish corresponding event.
				finishRefresh();
			}

			catch (BeansException ex) {
				if (logger.isWarnEnabled()) {
					logger.warn("Exception encountered during context initialization - " +
							"cancelling refresh attempt: " + ex);
				}

				// Destroy already created singletons to avoid dangling resources.
				destroyBeans();

				// Reset 'active' flag.
				cancelRefresh(ex);

				// Propagate exception to caller.
				throw ex;
			}

			finally {
				// Reset common introspection caches in Spring's core, since we
				// might not ever need metadata for singleton beans anymore...
				resetCommonCaches();
			}
		}
	}
```

当完成了refresh操作后，就会完成上下文的初始化工作。之后就会基于这个上下文进行后续的操作。
