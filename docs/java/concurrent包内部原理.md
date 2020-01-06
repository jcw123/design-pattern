1、atomic内部的类
AtomicBoolean、AtomicInteger、AtomicReference等等，通过借助于Unsafe类来实现原子性。
实现原子性主要是借助于CAS（Compare And Swap），在底层抱枕CAS是一个原子操作。
参考文档：https://blog.csdn.net/zyzzxycj/article/details/89877863


其他：
（1）volatile通过内存屏障技术防止指令重排序和可见性，但如果没有线程安全的问题，可以不需要加volatile修饰，
使用内存屏障本身就花费时间。
