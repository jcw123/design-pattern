#### CopyOnWriteArrayList

COPY ON WRITE, 写时复制思想的应用。当没有修改操作时，操作的是同一个对象，切内部的array不会变，
但都有修改操作时会进行加锁操作，会生成一个新的newarray覆盖内部的array。但不影响未完成的读操作。

优点：
1. 线程安全
2. 写操作不会阻塞读操作

缺点：
1. 耗内存资源


适用场景：
1. 读多写少的情况；
2. 多线程环境；


```java
/** The array, accessed only via getArray/setArray. */
    private transient volatile Object[] array;
```
