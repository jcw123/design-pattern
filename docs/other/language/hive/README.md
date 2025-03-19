# hive

## 常见功能

### 使用外部的jar文件
```sql 
ADD JAR hdfs:///user/hive/your.jar;
CREATE TEMPORARY FUNCTION my_udf AS 'com.example.MyUDF';
SELECT my_udf(column_name) FROM your_table;
```

## 备注

1、通过jar构建UDF函数的缺陷
支持的出入参数据类型太简单，主要是一些基本类型

2、ROW_NUMBER() OVER (PARTITION BY sale_ord_id, sku_uuid ORDER BY ver DESC) AS rn 含义解释
（1）PARTITION BY指定分区的字段，对于sale_ord_id, sku_uuid组合相同的行数据分在同一个分区；
（2）ROW_NUMBER()对于每一个分区中的数据分配一个唯一的编号；

3、LATERAL VIEW explode(process_names(test_list)) mytable AS testinfo_all
将一列的多个值转为数组形式，然后利用LATERAL VIEW转为一个表。

## 参考文档
[官方全量文档](https://hive.apache.org/docs/latest/)
[官方sql文档](https://hive.apache.org/docs/latest/languagemanual-ddl_27362034/#show-create-table)
[hive表内置函数](https://hive.apache.org/docs/latest/languagemanual-udf_27362046/#date-functions)
[学习文档](https://www.hadoopdoc.com/hive/hive-tutorial)