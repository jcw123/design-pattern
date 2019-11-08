# ReentrantLock原理介绍和源码解析

## AQS
讲解ReentrantLock之前还是得先说AQS，AQS全称AbstractQueuedSynchronizer。正如源码的文档所说，这是依赖于FIFO队列提供的一种实现阻塞队列和相关联同步器（信号量、事件等等）的一种框架。像我们平常用的ReentrantLock、Semaphore、CountDownLatch、ThreadPoolExecutor中的Worker类也借助了这个AQS框架。AQS的具体细节就不多讲了，之后会在将每一种实现的时候说说AQS的一些知识。
> AQS中的核心是维护一个双向链表，一个节点可以认为是一个排队的线程。每一个节点用一个Node的实例表示，而每一个节点等待时又分为排他模式和共享模式。Node节点中的waitStatus这个状态表示线程等待时的状态，主要有（SIGNAL、CANCELLED、CONDITION、PROPAGATE、0）

## ReentrantLock
ReentrantLock实现了Lock这个接口，Lock这个接口提供了很多比较灵活的操作锁的方法，比如：lock()、tryLock()等等。

ReentrantLock这个类中有一个内部抽象类Sync就是继承了AbstractQueuedSynchronizer，并且提供了两个实现类，FairSync（公平锁的同步对象）、NonfairSync（非公平锁的同步对象）。

看看这两个构造方法，默认实现的是非公平锁，可以通过入参指定为公平锁机制。
```java
public ReentrantLock() {
        sync = new NonfairSync();
    }

    public ReentrantLock(boolean fair) {
            sync = fair ? new FairSync() : new NonfairSync();
        }
```

**基本例子：**
```java
public class Test {

    private static final ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) throws Exception {
        Test test = new Test();
        new Thread(() -> {
            test.test1("线程中直接调用test1");
            test.test2("线程中直接调用test2");
        }).start();

        new Thread(() -> {
            test.test2("线程中直接调用test2");
            test.test1("线程中直接调用test1");
        }).start();
    }

    public void test1(String str) {
        lock.lock();
        try {
            test2("在test1方法中调用test2");
            System.out.println("ThreadName:" + Thread.currentThread().getName() + ", " + str);
        }finally {
            lock.unlock();
        }
    }

    public void test2(String str) {
        lock.lock();
        try {
            System.out.println("ThreadName:" + Thread.currentThread().getName() + ", " + str);
        }finally {
            lock.unlock();
        }
    }

}
```
**结果：**
> ThreadName:Thread-0, 在test1方法中调用test2
ThreadName:Thread-0, 线程中直接调用test1
ThreadName:Thread-0, 线程中直接调用test2
ThreadName:Thread-1, 线程中直接调用test2
ThreadName:Thread-1, 在test1方法中调用test2
ThreadName:Thread-1, 线程中直接调用test1

因为是可重入的，所有一个线程调用了lock方法之后，调用unlock方法之前，再次调用lock方法还是能够获取的，不会阻塞。

### 详细的api

#### lock()
```java
public void lock() {
        sync.lock();
    }
```
内部调用时Sync这个接口的lock方法，而这个接口提供了两个实现类。
(1)FairSync.lock()
```java
// 加锁的入口，内部调用的是acquire方法，这个方法是在AbstractQueuedSynchronizer这个类中实现
final void lock() {
    acquire(1);
}

// tryAcquire方法对于FairSync和UnFairSync这两个类实现是不一样的。
public final void acquire(int arg) {
        if (!tryAcquire(arg) &&
            acquireQueued(addWaiter(Node.EXCLUSIVE), arg))
            selfInterrupt();
    }

// 尝试获取锁
protected final boolean tryAcquire(int acquires) {
            final Thread current = Thread.currentThread();
            //这个状态很重要，只有值为0时，才表示当前锁没有被任何线程持有，那么当前线程就看看是不是满足能够持有当前锁的条件，如果满足则尝试获取当前锁，获取锁成功的条件就是能够更改state值成功，这是个CAS操作，也可能不成功。
            int c = getState();
            if (c == 0) {
              // hasQueuedPredecessors这个方法是用来进行公平锁和非公平锁区别的一个核心方法。这个方法用来判定队列中是否有一个比当前线程等待获取锁更久的线程，如果有的话，是不能进行获取锁操作的，因为这个锁时公平的，肯定得保证谁先来请求谁先获取锁的公平性嘛。调用compareAndSetState这个方法进行获取锁操作，设置成功的话，调用setExclusiveOwnerThread这个方法表示锁时当前线程独占的。
                if (!hasQueuedPredecessors() &&
                    compareAndSetState(0, acquires)) {
                    setExclusiveOwnerThread(current);
                    return true;
                }
            }
            // 如果锁已经被某一个线程占有的，判断占有锁的线程是不是就是当前线程，如果是的话就好办了，只需要将state的值进行加法操作即可。
            else if (current == getExclusiveOwnerThread()) {
                int nextc = c + acquires;
                if (nextc < 0)
                    throw new Error("Maximum lock count exceeded");
                setState(nextc);
                return true;
            }
            return false;
        }

/**
*当调用tryAcquire方法获取锁失败后，调用addWaiter创建一个新的节点以当前线程和指定的模式进行入队操作。
**/
private Node addWaiter(Node mode) {
        Node node = new Node(Thread.currentThread(), mode);
        // Try the fast path of enq; backup to full enq on failure
        Node pred = tail;
        if (pred != null) {
            node.prev = pred;
            if (compareAndSetTail(pred, node)) {
                pred.next = node;
                return node;
            }
        }
        enq(node);
        return node;
    }

/**
*对于已经入队的当前节点，判断它的前驱节点是不是头节点，如果是就尝试获取锁，如果获取锁成功，退出；如果获取锁失败判断是否将当前线程设为驻留状态，是的话就当前线程设置为驻留状态。
**/
final boolean acquireQueued(final Node node, int arg) {
        boolean failed = true;
        try {
            boolean interrupted = false;
            for (;;) {
                final Node p = node.predecessor();
                if (p == head && tryAcquire(arg)) {
                    setHead(node);
                    p.next = null; // help GC
                    failed = false;
                    return interrupted;
                }
                if (shouldParkAfterFailedAcquire(p, node) &&
                    parkAndCheckInterrupt())
                    interrupted = true;
            }
        } finally {
            if (failed)
                cancelAcquire(node);
        }
    }

```
(2)NonfairSync.lock()
```java
final void lock() {
    //不管前面是否有线程已经处于等待状态，直接进行获取锁，有点像抢占式的。
    if (compareAndSetState(0, 1))
        setExclusiveOwnerThread(Thread.currentThread());
    else
        acquire(1);
}

public final void acquire(int arg) {
    if (!tryAcquire(arg) &&
        acquireQueued(addWaiter(Node.EXCLUSIVE), arg))  //获取锁失败后，后续操作和公平锁类似。
        selfInterrupt();
}

protected final boolean tryAcquire(int acquires) {
    return nonfairTryAcquire(acquires);
}

final boolean nonfairTryAcquire(int acquires) {
    final Thread current = Thread.currentThread();
    int c = getState();
    if (c == 0) {
      // 这里有意思，就是不管是否在当前线程之前是否已有线程等待，直接尝试获取锁，这就是和公平锁的区别
        if (compareAndSetState(0, acquires)) {
            setExclusiveOwnerThread(current);
            return true;
        }
    }
    else if (current == getExclusiveOwnerThread()) {
        int nextc = c + acquires;
        if (nextc < 0) // overflow
            throw new Error("Maximum lock count exceeded");
        setState(nextc);
        return true;
    }
    return false;
}
```

上面就是公平锁和非公平锁获取锁的机制，当然还提供了很多其余的方法。

#### lockInterruptibly()
尝试获取锁，并且在获取锁的过程中，如果收到中断信号，会向外抛出异常，退出当前方法
#### tryLock()
不公平的获取锁的方式，就算实例化ReentrantLock时传入true，也会使用抢占式获取锁的方式。
#### tryLock(long timeout, TimeUnit unit)
有超时设置的获取锁的方式，如果获取锁失败，会调用LockSupport.parkNanos这个方法驻留一段时间，然后再尝试获取锁，如果超时未获取锁，直接返回false。
### unlock
```java
// 每调用一次unlock方法，都会是state的值减一。
public void unlock() {
    sync.release(1);
}

public final boolean release(int arg) {
  if (tryRelease(arg)) {
      Node h = head;
      if (h != null && h.waitStatus != 0)
         // 释放锁成功后，通知后继者来占有锁
          unparkSuccessor(h);
      return true;
  }
  return false;
}

protected final boolean tryRelease(int releases) {
    int c = getState() - releases;
    if (Thread.currentThread() != getExclusiveOwnerThread())
        throw new IllegalMonitorStateException();
    boolean free = false;
    // 状态值为0表示锁完全释放了，否则还持有当前锁。
    if (c == 0) {
        free = true;
        setExclusiveOwnerThread(null);
    }
    setState(c);
    return free;
}

private void unparkSuccessor(Node node) {
    /*
     * If status is negative (i.e., possibly needing signal) try
     * to clear in anticipation of signalling.  It is OK if this
     * fails or if status is changed by waiting thread.
     */
    int ws = node.waitStatus;
    if (ws < 0)
        compareAndSetWaitStatus(node, ws, 0);

    /*
     * Thread to unpark is held in successor, which is normally
     * just the next node.  But if cancelled or apparently null,
     * traverse backwards from tail to find the actual
     * non-cancelled successor.
     */
    Node s = node.next;
    if (s == null || s.waitStatus > 0) {
        s = null;
        for (Node t = tail; t != null && t != node; t = t.prev)
            if (t.waitStatus <= 0)
                s = t;
    }
    if (s != null)
        // 这个方法就是让当入参中的线程重新恢复
        LockSupport.unpark(s.thread);
}
```

总结：
上面基于AQS，基本介绍了ReentrantLock的实现机制，在AQS框架中，每一个线程都会与一个Node节点进行绑定。ReentrantLock提供了公平和不公平两种获取锁的机制，要想明白这种机制的原理，需要明白底层是通过一个FIFO的队列维护的。目前上面是第一遍看代码了解的内容，以后如果有更深入的了解，会进行补充，如果那里写的有不对的地方，麻烦指正。
