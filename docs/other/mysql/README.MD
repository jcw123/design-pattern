## 执行步骤顺序
（1）From：对FROM子句中的left_table和right_table执行
笛卡尔积，产生虚拟表VT1；  
（2）ON:对虚拟表VT1应用ON筛选，执行服务ON后面条件的记录
才会插入到虚拟表VT2中；  
（3）JOIN：如果指定了OUTER JOIN（LEFT OUTER JOIN、RIGHT OUTER JOIN），那么保留
表中未匹配的行作为外部行添加到虚拟表VT2中，产生虚拟表VT3。如果FROM子句包含两个以上
表，则对上一个连接生成的结果表VT3和下一个表重复执行步骤（1）~（3），直到所有的表执行
完为止。
（4）WHERE：对虚拟表VT3应用WHERE过滤条件，只有符合WHERE过滤条件的记录才会插入到
虚拟表VT4中。  
(5)GROUP BY : 根据GROUP BY 中的列，对虚拟表VT4进行分组操作，产生虚拟表VT5；  
（6）CUBE|ROLLUP：对虚拟表VT5   进行CUBE或ROLLUP操作，产生虚拟表VT6；  
（7）HAVING：对虚拟表VT6执行HAVING过滤器，只有符合<having_condition>条件的记录才会
插入到虚拟表VT7中；
（8）SELECT：第二次执行SELECT操作，选择指定的列，插入到虚拟表VT8中。  
（9）DISTINCT：去除重复数据，产生虚拟表VT9；
（10）ORDER BY: 对虚拟表VT9按照指定的列进行排序操作，产生虚拟表VT10
（11）LIMIT：取出指定的行，产生虚拟表VT11，返回给用户。
- having和where的区别：
参考文档：https://blog.csdn.net/HD243608836/article/details/88813269
where是一个约束声明，having是一个过滤声明
having 要和 group by成组使用，having是对已经分好的组进行过滤操作，用的是聚合函数来操作的
where语句对对表中的每一条记录进行操作的，只有满足条件才能返回结果

- on和where的区别：
参考文章：https://zhuanlan.zhihu.com/p/127137604

参考文章：
https://zhuanlan.zhihu.com/p/66352669
查看mysql已有bug的网站：http://bugs.mysql.com/


#当前运行的所有事务
select * from information_schema.innodb_trx;  

#当前出现的锁
select * from information_schema.innodb_locks;

#锁等待的对应关系
select * from information_schema.innodb_lock_waits

## 参考文档
[mysql线程池问题](https://cloud.tencent.com/developer/article/1068832)
[菜鸟教程](https://www.runoob.com/mysql/mysql-tutorial.html)