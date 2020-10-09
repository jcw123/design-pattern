1. 基于一个表结构后者数据创建另一张表
```sql
create table test1 like test;

create table test1 as select * from test;
```
