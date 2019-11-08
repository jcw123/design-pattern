## SynchronousQueue

#### 特点

- 是阻塞队列BlockingQueue的一种实现，也就是方法具有BlokingQueue的基本性质；

- 和ArrayBlockingQueue区别在于，ArrayBlockingQueue内部会有一个数组用于存放元素，相当于一个缓存区；而对于SynchronousQueue，内部没有这样的数据结构用于存放数据。

- 对于具体的一个线程A，想要插入数据，必须有另一个线程B打算取数据，否则线程A阻塞（底层是调用Unsafe.park导致阻塞的）。这样实现的目的就是希望生产数据的速度和消费数据的速度步调保持一致。

#### 主要的数据结构

1. Transferer
> Shared internal API for dual stacks and queues

上面这个接口保存了数据转移的关键api，上面英文转为中文应该表示为双栈和双队列的共享内部api，“双”主要体检在当取数据时，如果没有线程等待存数据，会创建一个表示取数据的Node节点。如果存数据时，如果没有等待取数据的线程，会创建一个表示存数据的Node节点。对于这两类节点都是用同一个结构表示的。这链表中，同一时刻只能有一个一种类型的节点存在。

Transferer接口的两个实现类：

- TransferStack

    用于实现非公平方式的存取数据。

- TransferQueue

  用于实现公平方式的存取数据。
