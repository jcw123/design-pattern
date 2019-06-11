1. netty三大优势
（1）并发高
（2）传输快
（3）封装好

2. netty的基本组成
（1）Channel：代表了一个套接字或者基本组件，能够执行一个或者多个I/0操作的开放连接。
（2）Netty 的异步编程模型是建立在 future 和 callback 的概念上的。
（3）Netty 通过触发事件从应用程序中抽象出 Selector，从而避免手写调度代码。EventLoop 分配给每个 Channel 来处理所有的事件。
（4）Transport：数据传输可以采用NIO和OIO模式。
（5）一个Channel会与一个ChannelPipeline、一个ChannelConfig关联
（6）ByteBuf和ByteBufHolder：缓存的实现，优化了jdk提供的缓存实现
