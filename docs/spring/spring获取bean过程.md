### 从上下文中获取bean的过程

以context.getBean(Class<T> cls)为例。

- 调用AbstractApplicationContext中的getBean方法；
- 调用DefaultListableBeanFactory类的getBean方法；
- 调用AbstractBeanFactory类的getBean方法；
- 调用doGetBean方法；
- 首先判断是否工厂已经创建了bean，如果创建了直接返回，否则执行如下步骤；
- 获取bean的definition，然后调用AbstractAutowireCapableBeanFactory进行bean的创建；
- 创建完后首先执行bean的invokeAwareMethods这个方法，执行BeanNameAware、BeanClassLoaderAware、
BeanFactoryAware的自动注入方法；
- 执行bean的postProcessors的postProcessBeforeInitialization这个方法；
- 执行bean的初始化方法，比如实现了InitializingBean这个接口会调afterPropertiesSet这个方法，然后调用
其他的init方法，最后调用postProcesser的postProcessAfterInitialization这个方法。
