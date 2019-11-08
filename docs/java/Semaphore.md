## 简介

相当于是一个计数信号量，用于控制共享资源的访问，比如实例化时可以用N表示访问共享资源的计数器。每访问一次，都会将访问的剩余次数进行减一。也是通过AQS来实现此功能的。

## 实现原理
（1）借助于AQS来实现，实例化时传入一个许可证的次数，将此值设置为state。
```java
public Semaphore(int permits) {
        sync = new NonfairSync(permits);
    }

public Semaphore(int permits, boolean fair) {
        sync = fair ? new FairSync(permits) : new NonfairSync(permits);
    }

// 这里可以看出就是更改state的值
Sync(int permits) {
    setState(permits);
}
```

(2)获取许可的几个方法
> 下面提供了多个方法都是可以获取许可证，前两个方法是可以被中断的，后两个方法是不可以中断的。无参的acquire方法，调用时，只要state大于0就可以返回，而对于有参的方法，需要保证permits小于等于state的值才可以获取成功。

```java
public void acquire() throws InterruptedException {
    sync.acquireSharedInterruptibly(1);
}

public void acquire(int permits) throws InterruptedException {
    if (permits < 0) throw new IllegalArgumentException();
    sync.acquireSharedInterruptibly(permits);
}

public void acquireUninterruptibly() {
    sync.acquireShared(1);
}

public void acquireUninterruptibly(int permits) {
    if (permits < 0) throw new IllegalArgumentException();
    sync.acquireShared(permits);
}

public boolean tryAcquire() {
    return sync.nonfairTryAcquireShared(1) >= 0;
}

public boolean tryAcquire(int permits) {
    if (permits < 0) throw new IllegalArgumentException();
    return sync.nonfairTryAcquireShared(permits) >= 0;
}

public boolean tryAcquire(int permits, long timeout, TimeUnit unit)
    throws InterruptedException {
    if (permits < 0) throw new IllegalArgumentException();
    return sync.tryAcquireSharedNanos(permits, unit.toNanos(timeout));
}

public boolean tryAcquire(long timeout, TimeUnit unit)
        throws InterruptedException {
    return sync.tryAcquireSharedNanos(1, unit.toNanos(timeout));
}
```

（3）释放许可证的方法
```java
public void release() {
    sync.releaseShared(1);
}

public void release(int permits) {
    if (permits < 0) throw new IllegalArgumentException();
    sync.releaseShared(permits);
}
```

上面acquire时是将state做减法操作，而release操作是将state做加法操作。只要当前的state的值大于等于permits，就可以直接返回，对于阻塞式的获取操作，如果获取不到锁，就会调用LockSupport.park方法等待，当其他线程释放需要证时，重新换新等待的线程重新尝试获取锁，如果获取成功则返回，否则再次等待。

## demo
```java
import java.util.concurrent.Semaphore;

/**
 * @Author: jiangcw
 * @Date: 2019-9-22 下午 12:52
 * @Version 1.0
 */
public class Test {

    public static void main(String[] args) throws Exception {
        Semaphore semaphore = new Semaphore(2);
        new Thread(() -> {
            System.out.println("thread1 start");
            try {
                semaphore.acquire(3);
                System.out.println("thread1 获取到了资源，用完了，释放");
                semaphore.release();
            }catch (InterruptedException e) {}
        }).start();

        new Thread(() -> {
            System.out.println("thread2 start");
            try {
                semaphore.acquireUninterruptibly();
                System.out.println("thread2 获取到了资源，用完了，释放");
                semaphore.release();
                // 这里比较有意思，release两次，第一次relaes时，第一个线程还是会阻塞，但是第二次release时，第一个线程可以运行了，主要是release时将state加一，导致state的值为3，满足第一个线程acquire的入参了，即state>=permits
                semaphore.release();
            }catch (Exception e) {}
        }).start();

    }
}
```

理解原理的最好的方法还是debug，进行代码跟踪。
