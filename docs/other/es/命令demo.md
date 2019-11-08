1、处于包含object类型的数据：
```
PUT object_test/_doc/5
{
  "region" : "CN2",
  "manager" : {
    "age" : 30,
    "name" : {
      "last" : "xr",
      "first" : "jiang"
    }
  }
}
```
2、GET方式查询数据：
```
GET object_test/_search?q=region:CN1
```
