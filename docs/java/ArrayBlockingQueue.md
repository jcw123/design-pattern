# BlockingQueue之ArrayBlockingQueue

ArrayBlockingQueue是一个基于数组实现的有界限的阻塞队列，队列中的元素也是先进先出。

在说ArrayBlockingQueue之前，先来看看其接口BlockingQueue，接口中提供了一些比较有意思的方法，当我们调用其中的方法时，会表现出一下四种行为之一：
- 直接抛出一个异常（Throws Exception）
- 返回一个特殊的值（Special value）
- 一直处于阻塞状态（Blocks）
- 超时等待（Times out）

而对于插入（Insert）和移除操作（Remove）分别用如下几个方法体现上述的行为。

**Insert:**
- add(e) : 当队列空间满时调用这个方法会直接抛出一个异常
- offer(e)：当队列满时调用这个方法会直接返回一个false
- put(e)：当队列满时调用这个方法会一直处于阻塞状态，直到有空的空间可以插入数据
- offer(Object, long, TimeUnit):当队列满时，会等待一段时间，如果这段时间队列还是满的，会返回一个false。

**Remove:**
- remove()：如果没有元素，调用这个方法会抛出异常
- poll()：如果没有元素，调用这个方法会返回null
- take()：如果没有元素，调用这个方法会一直阻塞，知道有元素为止
- poll(long, TimeUnit)：如果没有元素，调用这个方法会阻塞一段时间，如果超时还没有元素，会返回null。

### ArrayBlockingQueue的成员变量

#### final Object[] items
前面说过，元素是放到一个数组中的，items数组就是用来存放数据的

#### int takeIndex
> items index for next take, poll, peek or remove

takeIndex用来取数据的索引，如果调用take、poll等方法就是通过这个索引来定位数据的。

#### int putIndex
>   items index for next put, offer, or add

putIndex是定位下一个用来存放数据的位置，通过上面可以看出，插入数据和写入数据是通过两个不同的索引来定位的。

#### final ReentrantLock lock
> Main lock guarding all access

使用Java中的重入锁ReentrantLock来进行操作过程中的同步机制的，翻看源码的话，大部分操作都会使用这个锁来进行加锁和解锁操作。

#### private final Condition notEmpty
> Condition for waiting takes

当调用take方法时，如果数据为null，会调动notEmpty.await()方法让当前线程处于等待状态（让出CPU资源），当有新的数据入队时，会再次调用notEmpty.singal()方法让阻塞的线程继续运行。

#### private final Condition notFull
> Condition for waiting puts

当调用put方法时，如果队列已满，会调用notFull.await()方法，让当前线程处于等待状态（让出CPU资源），当有新的出队时，会再次调用notFull.singal()方法让阻塞的线程继续运行。

#### transient Itrs itrs = null
> Shared state for currently active iterators

用于记录集合的迭代器状态，迭代器实现这块代码太多了，我也不想看了，用到时再详细看看吧。

#### 核心方法
插入操作：
```java
// 超时等待方式
public boolean offer(E e, long timeout, TimeUnit unit)
        throws InterruptedException {

    checkNotNull(e);
    long nanos = unit.toNanos(timeout);
    final ReentrantLock lock = this.lock;
    // 如果由于获取锁处于阻塞的话，可以被中断信号打断的
    lock.lockInterruptibly();
    try {
        while (count == items.length) {
            if (nanos <= 0)
                return false;
            // 其实这里内部的核心调用的是LockSupport.parkNanos(this, nanosTimeout);这个方法，而这内部调用的又是UNSAFE.park(false, nanos);这个方法
            nanos = notFull.awaitNanos(nanos);
        }
        // 入队操作，内部会调用notEmpty.signal();这个方法
        enqueue(e);
        return true;
    } finally {
        lock.unlock();
    }
}

public void put(E e) throws InterruptedException {
    checkNotNull(e);
    final ReentrantLock lock = this.lock;
    lock.lockInterruptibly();
    try {
        while (count == items.length)
            // 队列满的话调用await方法
            notFull.await();
        enqueue(e);
    } finally {
        lock.unlock();
    }
}
```

移除操作：
```java
public E poll(long timeout, TimeUnit unit) throws InterruptedException {
    long nanos = unit.toNanos(timeout);
    final ReentrantLock lock = this.lock;
    lock.lockInterruptibly();
    try {
        while (count == 0) {
            if (nanos <= 0)
                return null;
            // 队列为null，超时等待
            nanos = notEmpty.awaitNanos(nanos);
        }
        return dequeue();
    } finally {
        lock.unlock();
    }
}

public E take() throws InterruptedException {
    final ReentrantLock lock = this.lock;
    lock.lockInterruptibly();
    try {
        while (count == 0)
            // 为null，进行等待
            notEmpty.await();
        return dequeue();
    } finally {
        lock.unlock();
    }
}
```

### 案例
实现一个简单的生产者和消费者案例
```java
import java.util.Random;
import java.util.concurrent.*;

/**
 * @Author: jiangcw
 * @Date: 2019-9-22 下午 12:52
 * @Version 1.0
 */
public class Test {

    public static void main(String[] args) throws Exception {
        // 消费者线程池
        ThreadPoolExecutor consumerExecutor = new ThreadPoolExecutor(2, 2, 0, TimeUnit.SECONDS,  new ArrayBlockingQueue<Runnable>(1));
        ArrayBlockingQueue<Integer> queue =  new ArrayBlockingQueue<Integer>(1);
        consumerExecutor.execute(()->{
            Consumer consumer = new Consumer(queue);
            while(true) {
                consumer.consume();
            }
        });

        consumerExecutor.execute(()->{
            Consumer consumer = new Consumer(queue);
            while(true) {
                consumer.consume();
            }
        });

        // 生产者线程池
        ThreadPoolExecutor producerExecutor = new ThreadPoolExecutor(1, 1, 0, TimeUnit.SECONDS,  new ArrayBlockingQueue<Runnable>(1));
        producerExecutor.execute(()-> {
            Producer producer = new Producer(queue);
            Random random = new Random();
            while(true) {
                producer.produce(random.nextInt(100));
                try {
                    Thread.sleep(1000);
                }catch (InterruptedException e) {}
            }
        });
    }

    private static class Consumer {

        private BlockingQueue<Integer> queue;

        Consumer(BlockingQueue<Integer> queue) {
            this.queue = queue;
        }

        // 从队列中取数，像生产环境，很多时候用poll(long, TimeUnit)，主要是如果生产者生产慢了，将会导致消费者一直等待，可以选用超时等待模式
        public void consume() {
            try {
                System.out.println("Thread:" + Thread.currentThread().getName() + " 消费了" + queue.take());
            }catch (InterruptedException e) {}
        }
    }

    private static class Producer {
        private BlockingQueue<Integer> queue;

        Producer(BlockingQueue<Integer> queue) {
            this.queue = queue;
        }

        // 往队列中塞数据
        public void produce(Integer i) {
            try {
                queue.put(i);
                System.out.println("Thread:" + Thread.currentThread().getName() + " 生产了 " + i);
            }catch (Exception e) {}
        }
    }
}
```

### 总结：
- 底层是使用数组存储元素的
- 插入数据和取出数据分别用putIndex和takeIndex来定位位置的
- 对于方法的访问是通过ReentrantLock来实现同步的
- 对于取数据和写数据实现阻塞的方式是通过Condition来实现的，而且分别使用不同的Condition
- 对于实现生产者/消费者模式，ArrayBlockingQueue是一个非常好的数据结构
