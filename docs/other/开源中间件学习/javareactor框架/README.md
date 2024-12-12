# javareactor

## API学习


## Q&A

1. publishOn 和 subscribeOn区别
publishOn：可以保证onNext, onComplete and onError这些方法运行在一个单独的调度器上。影响调用publishOn后的步骤，知道遇到一个新的publishOn方法。
subscribeOn：可以保证subscribe、onSubscribe和request方法在一个单独的调度器上。不管在哪里运行这个方法都会影响onNext, onComplete and onError这些方法调用链的上下文，直到遇到一个publishOn方法的调用。

2. Subscription的作用
- 控制数据流的请求和传递
- 管理订阅的生命周期
- 解耦生产者和消费者
- 异步数据传输
- 实现响应式流的协议

3. 调用链如何执行的？
首先通过Operator记录每一步上一步的步骤和当前的步骤，然后利用Flux内部提供的subscribe方法反向找到最开始的source，对于每一个元素从初始的源头执行每一个操作，完成整个链的执行。



## 备注
1、Subscription#request这个方法调用才会触发publisher发送数据流事件，可以通过cancel取消事件流的发送

2、通过publisher调用subscribe方法时，首先触发订阅者调用onSubscribe方法，内部会触发Subscrcibtion类调用request方法，内部会反过来调用onNext、onComplete、onError方法。

3、

## 参考文档
[官方文档](https://projectreactor.io/docs/core/release/reference/#_blocking_can_be_wasteful)
[基本使用](https://www.baeldung.com/reactor-core)
[github地址](https://github.com/reactor/reactor-core)