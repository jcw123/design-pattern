# 单例模式

为什么需要单例吗？实例过多占用空间不用多说，如果多个实例之间没有差异化，就没必要创建过多的实例。

## 单例模式的特点

1. 单例类只能有一个实例
2. 单例类必须自己创建自己的唯一实例。
3. 单例类必须给所有其他对象提供这一实例

饿汉式单例
```java
public class EagerSingleton {
    // 初始化时才会进行分配对象吧？ 需要用final修饰符进行修饰，否则的话对象的指针会被改变，而使用final修饰后，
    // 在类进行加载时就进行了初始化，导致内存提前被占用
    // private static EagerSingleton instance = new EagerSingleton();
    private static final EagerSingleton instance = new EagerSingleton();

    /**
     * 私有默认构造子
     */
    private EagerSingleton(){}
    /**
     * 静态工厂方法
     */
    public static EagerSingleton getInstance(){
        return instance;
    }
}
```

懒汉式单例
```java
public class LazySingleton {
    private static LazySingleton instance = null;
    /**
     * 私有默认构造子
     */
    private LazySingleton(){}
    /**
     * 静态工厂方法
     */
    public static synchronized LazySingleton getInstance(){
        if(instance == null){
            instance = new LazySingleton();
        }
        return instance;
    }
}
```

双重检查锁实现单例
```java
public class Singleton {
    private volatile static Singleton instance = null;
    private Singleton(){}
    public static Singleton getInstance(){
        //先检查实例是否存在，如果不存在才进入下面的同步块
        if(instance == null){
            //同步块，线程安全的创建实例
            synchronized (Singleton.class) {
                //再次检查实例是否存在，如果不存在才真正的创建实例
                if(instance == null){
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
}
```

类级内部类实现单例
```java
public class Singleton {

    private Singleton(){}
    /**
     *    类级的内部类，也就是静态的成员式内部类，该内部类的实例与外部类的实例
     *    没有绑定关系，而且只有被调用到时才会装载，从而实现了延迟加载。
     *    当类进行初始化时，内部类并不会进行初始化
     */
    private static class SingletonHolder{
        /**
         * 静态初始化器，由JVM来保证线程安全
         */
        private static final Singleton instance = new Singleton();
    }

    public static Singleton getInstance(){
        return SingletonHolder.instance;
    }
}
```

枚举实现内部类
```java
public enum Singleton {
    /**
     * 定义一个枚举的元素，它就代表了Singleton的一个实例。
     */

    uniqueInstance;

    /**
     * 单例可以有自己的操作
     */
    public void singletonOperation(){
        //功能处理
    }
}

// 枚举类方式也是一种懒加载吗？
public class SingletonObject7 {


    private SingletonObject7(){

    }

    /**
     * 枚举类型是线程安全的，并且只会装载一次
     */
    private enum Singleton{
        INSTANCE;

        private final SingletonObject7 instance;

        Singleton(){
            instance = new SingletonObject7();
        }

        private SingletonObject7 getInstance(){
            return instance;
        }
    }

    public static SingletonObject7 getInstance(){

        return Singleton.INSTANCE.getInstance();
    }
}
```
