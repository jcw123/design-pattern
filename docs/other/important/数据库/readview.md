1. readview是一个快照视图，快照并不是一个时机的数据快照，而是事务id的快照，核心参数包含如下几个字段：
（1） m_ids
是一个事务id列表，当创建一个快照时，如果发现那些事务已经启动但是还没有提交，就将对应的事务id放到这个列表中；
（2）m_low_limit_id
这是一个高水位标志，当进行读时，是没法看到任务事务id大于等于这个值的提交记录的；
（3）m_up_limit_id
这是一个低水位标志，当进行读时，可以看到事务id小于这个值的记录；

这个有意思了，快照存的并不是实际的数据，不然太浪费空间了，通过一个事务id来标识哪些记录应该读那一条历史数据；

对于历史记录在适当实际可以进行删除，比如当前未提交的事务id最小号为100，则对于一条记录只需要保存最新的一条事务id小于100的记录即可，其他的历史数据都是可以进行删除；

通过借助于MVCC，在进行读操作时就可以不用再加锁，提升了性能；
