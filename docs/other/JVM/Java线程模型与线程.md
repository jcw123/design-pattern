一、Java内存模型
每条线程有自己的工作内存，共享主内存

内存间的8条原子性相互操作：
lock（锁定）：作用于主内存，把一个变量标识为线程独占状态
unlock(解锁)：作用于主内存，把一个锁定的变量解锁
read（读取）：作用于主内存，把一个主内存的变量传入到线程的工作内存，以便随后load操作
load(载入)：作用于工作内存的变量，它把read操作从主内存读取的变量值放入工作内存的变量副本上
use(使用)：作用于工作内存的变量，它把工作内存的一个变量的值传递给执行引擎
assign(赋值)：作用于工作内存的变量，它把一个从执行引擎接收到的值赋值给工作内存的变量
store(存储)：作用于工作内存的变量，它把工作内存中的一个变量的值传送给主内存中，以便随后的write操作使用。
write(写入)：作用于主内存的变量，它把store操作从工作内存得到的变量的值放到主内存的变量中。


volatile型变量的特殊规则
volatile类型的变量在使用之前都要先刷新，执行引擎看不到不一致的情况。

符合下面规则的volatile变量可保证原子性：
运算结果不依赖变量当前的值，或者能够确保只有单一的线程修改变量的值；
变量不需要与其它的状态变量共同参与不变约束。

先行发生原则（happens-before）
含义：如果操作A先行发生于操作B，其实就是说在发生操作B之前，操作A产生的影响都能被操作B观察到，“影响”包括修改内存中共享变量的值、发送了消息、调用了方法等。

天然存在的先行发生关系：
（1）程序次序规则 
> 同一个线程内，操作A在操作B之前，则A操作将在B操作之前完成；
（2）管程锁定规则
> 对于同一个监视器锁，对锁的加锁操作一定在加锁操作之前执行；
（3）volatile变量规则
> 对volatile写入操作在时间上早于读取操作，则写入操作先行发生于读取操作；
（4）线程启动规则
> 在线程上对Thread.start的调用必须在该线程中执行任务操作之前；
（5）线程终止规则
> 线程中的任何操作都必须在其他线程检测到该线程已经结束之前执行，或者从 Thread.join 中成功返回，或者在调用 Thread.isAlive 时返回false
（6）线程中断规则
> 当一个线程在另一个线程上调用 interrupt 时，必须在被中断线程检测到 interrupt 调用之前执行
（7）对象终结规则
> 对象的构造函数必须在启动该对象的终结器之前执行完成
（8）传递性
> 如果操作A在操作B之前执行，并且操作B在操作C之前执行，那么操作A必须在操作C之前执行

java线程的状态转换：
新建（New）：创建后尚未启动的线程
运行（Runable）：包括操作系统中的Running和Ready状态
无期限等待（Waiting）：处于这种状态的线程不会被分配CPU执行时间，它们要等待被其他线程显示地唤醒。例如：Object.wait()、Thread.join()、LockSupport.park()。
限期等待（Timed Waiting）：无需等待被其他线程唤醒，在一段时间后会由系统自动唤醒。例如：Thread.sleep()等
阻塞（Blocked）：线程被阻塞了。“阻塞装态”在等待着获取一个排他锁。"等待状态"则是等待一段时间或者唤醒动作的发生。
结束：已终止的线程状态。


wait方法会释放对象锁，而sleep方法不会释放对象锁。
