#### Shared and Exclusive Locks
- A shared (S) lock permits the transaction that holds the lock to read a row
- An exclusive (X) lock permits the transaction that holds the lock to update or delete a row
> 同一行的共享锁可以由多个事务占有，但是如果以存在共享锁，获取排他锁是阻塞的；如果存在排他锁，共享锁和排它锁都无法再次获取；
这是一个行级别的锁；

#### Intention Locks(意向锁)
- An intention shared lock (IS) indicates that a transaction intends to set a shared lock on individual rows in a table
- An intention exclusive lock (IX) indicates that a transaction intends to set an exclusive lock on individual rows in a table.
意向锁的作用：
意向锁主要是解决行锁和表锁之间的冲突，如果打算获取表锁时，第一步得判断是否有其他事务获取了表锁，第二步是判断是否有其他事务占据了行锁，如果直接遍历每一行效率太低，因此通过一个意向锁表名是否有其他事务占据对应的行锁，类似于归一化；
https://www.zhihu.com/question/51513268

#### gap Lock
```sql
-- 导致，记录10到20之前存在间隙锁，在此区间不能进行插入操作；
SELECT c1 FROM t WHERE c1 BETWEEN 10 and 20 FOR UPDATE;

-- 如果id是唯一索引，则使用record lock，如果id不是一个索引或者是一个非唯一索引，则使用的是间隙锁。间隙锁可以被多个事务拥有，间隙锁的主要作用就是在间隙范围内，不需要插入、修改、删除数据。
SELECT * FROM child WHERE id = 100;
```

#### record Lock
> 排它锁是一种概念，record lock是排它锁的一种具体实现。

- A lock on an index record. For example, SELECT c1 FROM t WHERE c1 = 10 FOR UPDATE; prevents any other transaction from inserting, updating, or deleting rows where the value of t.c1 is 10. Contrast with gap lock and next-key lock
> 记录锁是一种行锁，是在对应的记录上加入排他锁，不允许机器事务插入、更新和删除；但是允许查询操作；如果记录上没有索引，会隐式创建一个索引。

#### next-key Locks
- A next-key lock is a combination of a record lock on the index record and a gap lock on the gap before the index record

参考文章：https://zhuanlan.zhihu.com/p/35477890

#### Insert Intention Locks
- An insert intention lock is a type of gap lock set by INSERT operations prior to row insertion. This lock signals the intent to insert in such a way that multiple transactions inserting into the same index gap need not wait for each other if they are not inserting at the same position within the gap

#### AUTO-INC Locks（算是找到一种表锁了）
- An AUTO-INC lock is a special table-level lock taken by transactions inserting into tables with AUTO_INCREMENT columns. In the simplest case, if one transaction is inserting values into the table, any other transactions must wait to do their own inserts into that table, so that rows inserted by the first transaction receive consecutive primary key values

#### Predicate Locks for Spatial Indexes
InnoDB supports SPATIAL indexing of columns containing spatial columns


用读锁锁整张表

```sql
lock table test1 read;
```

用写锁锁整张表
```sql
lock table test1 write;
```

- sql层面加S锁
select * lock in share mode;
- sql层面加X锁
select * for update;

参考文章总结：
- 记录锁、间隙锁、临键锁，都属于排它锁；
- 记录锁就是锁住一行记录；
- 间隙锁只有在事务隔离级别 RR 中才会产生；
- 唯一索引只有锁住多条记录或者一条不存在的记录的时候，才会产生间隙锁，指定给某条存在的记录加锁的时候，只会加记录锁，不会产生间隙锁；
- 普通索引不管是锁住单条，还是多条记录，都会产生间隙锁；
- 间隙锁会封锁该条记录相邻两个键之间的空白区域，防止其它事务在这个区域内插入、修改、删除数据，这是为了防止出现 幻读 现象；
- 普通索引的间隙，优先以普通索引排序，然后再根据主键索引排序（多普通索引情况还未研究）；
- 事务级别是RC（读已提交）级别的话，间隙锁将会失效

参考文章：
1. https://dev.mysql.com/doc/refman/5.7/en/innodb-locking.html
2. https://www.cnblogs.com/rjzheng/p/9950951.html
3. https://zhuanlan.zhihu.com/p/48269420
