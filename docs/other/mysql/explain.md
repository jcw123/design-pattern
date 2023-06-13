# explain
可以进行select性能分析；
参考文章：https://segmentfault.com/a/1190000008131735
https://www.cnblogs.com/xuanzhi201111/p/4175635.html
https://dev.mysql.com/doc/refman/5.7/en/explain-output.html

1. show table status
可以查询表的基本状态，比如总行数、平均数据总长度；

2. 各种show语法
查表、库、索引等等
https://dev.mysql.com/doc/refman/5.7/en/show.html
```sql
show index test;
```

3. 服务端的一些状态变量，可以检索索引的使用情况等
https://dev.mysql.com/doc/refman/5.7/en/server-status-variables.html#statvar_Handler_read_next
例如：
+-----------------------+-------+
| Variable_name         | Value |
+-----------------------+-------+
| Handler_read_first    | 0     |
| Handler_read_key      | 1     |
| Handler_read_last     | 0     |
| Handler_read_next     | 1     |
| Handler_read_prev     | 0     |
| Handler_read_rnd      | 0     |
| Handler_read_rnd_next | 0     |
+-----------------------+-------+

4. explain结果

1. id
> The SELECT identifier

2. select_type
> The SELECT type

- SIMPLE
- PRIMARY
- UNION
- DEPENDENT UNION
- UNION RESULT
- SUBQUERY
- DEPENDENT SUBQUERY
- DERIVED
- MATERIALIZED
- UNACHEABLE SUBQUERY
- UNACHEABLE UNION

3. table
> The table for the output row

4. partitions
> The matching partitions

5. type
> The join type

- system
> 表中就写了一条数据
如果表只有一行，这个是const的一种特例；

- const
> 表中最多只有一条匹配数据，在查询的开始，将主键索引或者唯一索引跟一个常量进行等号匹配。
表示一个表中只有一行匹配，通过主键索引或者唯一索引进行过滤，将这两种索引将一个常量值进行比较；

- eq_ref
对于关联查询，对于当前表中的每一条数据最多在前一个表中最多只有一条进行匹配。这就是通过主键索引或者唯一索引进行匹配的模式。

- ref
使用到了索引，但是join模式，基于前一个表的一行数据，在下一个表中匹配的数据不止一行。如果使用最左前缀，或者
非主键索引或者唯一索引就是这样的匹配结果。

- fulltext
使用全文索引

- ref or null
类似于ref，当多了一些额外的条件，会查询对应的列包含null的情况；

- index_merge
表名join类型存在索引合并优化；

- unique subquery
在一些in类型的子查询中，这个类型替代eq_ref类型方式；

- index subquery
这种类型类似于unique sbuquery,但是in中查询的列不是唯一索引；

- range
用于=,<>,>,>=,<,<=,IS NULL, <=>, BETWEEN,LIKE or IN();

- index
> 命中了覆盖索引的模式
这种方式非常类似于ALL模式，性能很差，有两种场景会用到：（1）如果一个覆盖索引能够包含索要查询的数据；（2）
如果仅仅统计行数；

- ALL
最坏的一种方式，应该避免这种情况出现；

1. possible_keys
> The possible indexes to choose

1. key
> The index actually chosen

1. key_len
> The length of the chosen key

1. ref
> The columns compared to the index

1.  rows
> Estimate of rows to be examined

1.  filtered
> Percentage of rows filtered by table condition

1.  extra
> Additional information
>

## 执行计划的选择过程
```sql
SET optimizer_trace="enabled=on";
select * from t1;
select * from information_schema.OPTIMIZER_TRACE;
SET optimizer_trace="enabled=off";
```


##  参考文档
[官网文档](https://dev.mysql.com/doc/refman/5.7/en/explain-output.html#explain-join-types)
[引擎选择索引过程](https://www.cnblogs.com/jimoer/p/14461051.html)

