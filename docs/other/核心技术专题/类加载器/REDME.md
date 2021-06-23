### 类加载器

#### 语义说明

- Class.forName(String)
通过这个方法实现类加载时，会从调用者类的类加载器加载需要的类；也就是调用者类和当前要加载的类会使用相同的类加载器，如果想使用自定义的类加载器加载需要的类，可以使用Class.forName(String, boolean, ClassLoader)指定类加载器；

- Class.getClassLoader()
这个方法是回去加载当前类的类加载器

- Thread.currentThread().getContextClassLoader()
回去当前线上的上下文类加载器，创建一个线程时如果没有指定ClassLoader，会继承父线程的类加载器，初始化应用的上下文类加载器是系统类加载器；

#### 参考文档
- 线程上下文类加载器
https://cloud.tencent.com/developer/article/1481101