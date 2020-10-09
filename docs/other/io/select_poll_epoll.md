参考文章：
https://zhuanlan.zhihu.com/p/55269256
https://blog.csdn.net/qq546770908/article/details/53082870

1. select
- select监控的fd描述符是有限的，默认值是1024；
- 当调用select函数返回时，仅仅返回的是就绪的fd的个数，需要重新遍历所有的描述符，发现
到底是哪些是就绪的；
- 每次调用select时，当需要将监控的文件描述符从用户空间拷贝到内核空闲，经过系统调用；
- 简单，数据结构简单，但是在性能上稍逊一筹；

2. poll
- poll和select很类似，数据结构稍微有些区别，监控的文件描述符没有限制；

3. epoll
- 监控的文件描述符个数没有限制；
- 通过epoll_create()、epoll_ctl()、epoll_wait()完成整个io操作，每次进行epoll_wait调用时不需要
重新拷贝监控的文件描述符；
- 调用epoll_wait返回时，直接可以获取就绪的文件描述符，不需要重新遍历整个文件描述符；
- 借助于红黑树结构进行文件描述符的维护的；
- 每一个fd都注册了一个中断处理程序回调函数，当收到设备的就绪中断事件时，就会将文件描述符加入到就绪链表中；