# java线程知识

## 线程核心：锁

对于共享资源，在多线程的环境中，是会存在竞争情况的，由于竞争的存在，导致在使用共享资源的情况，会出现意想不到的情况。如果共享资源仅仅是可读的，不管多少线程来操作，也不会出现线程安全的情况。但如果在使用共享资源的时候，会改变共享资源的状态，那么基本会出现线程安全的问题。
  锁是什么呢？既然资源存在竞争，那么当一个线程在占用了资源后，想办法告知其他想使用其资源的线程当前资源正在占用中，让其等候，相当于把资源锁住了，即每个对象都关联一个锁，且是唯一的。
  **注：核心概念还是锁，需要明白锁在java中是如何体现的**

  ## 线程状态
  一张图

  ## wait()/notify()/notifyAll()使用

  ```java
  public class ThreadTest {

    public static void main(String[] args) {
        Object lockObject = new Object();
        Thread t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (lockObject) {
                    try {
                        System.out.println("t1 start");
                        lockObject.wait();
                        lockObject.notify();
                        System.out.println("t1 end");
                    }catch (Exception e) {

                    }
                }
            }
        });
        Thread t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (lockObject) {
                    try {
                        System.out.println("t2 start");
                        lockObject.wait();
                        lockObject.notify();
                        System.out.println("t2 end");
                    }catch (Exception e) {

                    }
                }
            }
        });
        Thread t3 = new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (lockObject) {
                    try {
                        System.out.println("t3 start");
                        // 限时等待，调用这个方法后会释放锁，处于等待状态，1秒之后会进入
                        //等待获取锁的队列
                        lockObject.wait(1000);
                        System.out.println("t3 notify");
                        // 只要是通知其他调用了wait方法的线程，让这些线程可以重新进入等待获取锁的队列
                        lockObject.notify();
                        System.out.println("t3 end");
                    }catch (Exception e) {

                    }
                }
            }
        });
        t3.start();
        t1.start();
        t2.start();
    }
  ```

执行结果：
t3 start
t1 start
t2 start
t3 notify
t3 end
t1 end
t2 end

分析：t1、t2、t3三个线程开始的顺序是不确定的。t1执行到wait()方法后，t1线程会进入等待状态，并释放lockObject这个锁，同理，t2和t3线程也会进入等待状态，并释放线程锁。但t3线程不同(lockObject.wait(1000))，会在1s后重新进入等待获取线程队列。此时并没有线程持有锁，所有t3在1s之后能够获取此锁继续往下执行，然后调用notify方法，当t1或者t2某一个收到此信号后，也会进入等待获取锁队列（只能有一个进入，如果调用notifyAll方法，两个线程都能进入队列。），此时t3还没有执行完，即锁还没有释放，等t3执行完后，释放锁。则进入等待获取锁队列的线程就有可以获取锁了，继续执行，然后调用notify方法，另一个线程也能按照此步骤继续往下执行了。

## join方法
> 此方法是线程中的一个方法，平常也没怎么用到，这个方法可以控制线程的执行顺序，内部也是wait和notify的机制。

```java
public class ThreadTest {

    public static void main(String[] args) {
        Object lockObject = new Object();
        Thread t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("t1 start");
                System.out.println("t1 end");
            }
        });
        Thread t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    t1.join();
                    System.out.println("t2 start");
                    System.out.println("t2 end");
                }catch (Exception e) {

                }
            }
        });
        Thread t3 = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    t2.join();
                    System.out.println("t3 start");
                    System.out.println("t3 end");
                }catch (Exception e) {

                }
            }
        });
        t3.start();
        t1.start();
        t2.start();
    }
```
通过上面的写法，可以控制t1的线程执行完之后，t2线程的任务再执行，t2线程中的任务执行完之后，t3线程执行。

## synchronized
这个关键字没啥好说的，最常用的保证线程安全的关键字，这个关键字保证了：可见性、防止重排序、原子性。

## ReentrantLock

基本原理：ReentrantLock被称之为重入锁，即如果当前线程获取了此锁，再次获取时，可以获取成功，将获取锁的次数进行加一操作。借助如Unsafe这个类的操作，即常常听到的CAS（Compare And Swap）操作。

**AbstractQueuedSynchronizer**:AQS,这个类非常核心，给一个阻塞锁和同步器提供了一个基本框架，比如ReentrantLock、ContDownLatch、Semaphore等。


```java
public class ThreadTest {

    private static final ReentrantLock lock = new ReentrantLock();

    private static int i = 0;

    public static void increment()  {
        try {
            // 等待获取锁，除非收到中断信号
            lock.lockInterruptibly();
            // 一直等着获取锁
            lock.lock();
            // 尝试获取锁，如果锁被其他线程保持着，直接返回false，否则返回true
            // 这里得进行判断，如果获取锁失败了，调用unlock()方法会抛出异常
            lock.tryLock();
            // 在规定时间范围内获取锁，返回true，如果在固定时间范围内，锁还被其他线程拿着则则返回false。
            // 这里得进行判断，如果获取锁失败了，调用unlock()方法会抛出异常
            lock.tryLock(1, TimeUnit.SECONDS);
            i++;
        }catch (InterruptedException e) {

        }
        try {
            i++;
        }finally {
            lock.unlock();
            lock.unlock();
            lock.unlock();
            lock.unlock();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                Stream.iterate(1, item -> item + 1).limit(1000).forEach(i -> increment());
            }
        });
        Thread t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Stream.iterate(1, item -> item + 1).limit(1000).forEach(i -> increment());
                }catch (Exception e) {

                }
            }
        });
        Thread t3 = new Thread(new Runnable() {
            @Override
            public void run() {
                Stream.iterate(1, item -> item + 1).limit(1000).forEach(i -> increment());
            }
        });
        t3.start();
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        t3.join();
        System.out.println(i);
    }
```
