#### Shared and Exclusive Locks
- A shared (S) lock permits the transaction that holds the lock to read a row
- An exclusive (X) lock permits the transaction that holds the lock to update or delete a row
> 同一行的共享锁可以由多个事务占有，但是如果以存在共享锁，获取排他锁是阻塞的；如果存在排他锁，共享锁和排它锁都无法再次获取；
这是一个行级别的锁；

#### Intention Locks(意向锁)
- An intention shared lock (IS) indicates that a transaction intends to set a shared lock on individual rows in a table
- An intention exclusive lock (IX) indicates that a transaction intends to set an exclusive lock on individual rows in a table.

#### gap Lock
```sql
-- 导致，记录10到20之前存在间隙锁，在此区间不能进行插入操作；
SELECT c1 FROM t WHERE c1 BETWEEN 10 and 20 FOR UPDATE;
```

#### record Lock
- A lock on an index record. For example, SELECT c1 FROM t WHERE c1 = 10 FOR UPDATE; prevents any other transaction from inserting, updating, or deleting rows where the value of t.c1 is 10. Contrast with gap lock and next-key lock

#### next-key Lock
- A next-key lock is a combination of a record lock on the index record and a gap lock on the gap before the index record

#### Insert Intention Locks
- An insert intention lock is a type of gap lock set by INSERT operations prior to row insertion. This lock signals the intent to insert in such a way that multiple transactions inserting into the same index gap need not wait for each other if they are not inserting at the same position within the gap

#### AUTO-INC Locks
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

参考文章：
1. https://dev.mysql.com/doc/refman/5.7/en/innodb-locking.html
