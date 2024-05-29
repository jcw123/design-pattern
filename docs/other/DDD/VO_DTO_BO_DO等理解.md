# 数据模型


## 基本模型
1. DO(data object)

2. DTO(data transfer object)

3. BO(business object)

4. AO(applicaton object)

5. VO(value object)

6. DAO(data access obejct)

7. PO(persistent object)

## 应用分层

## 参考文档
[不同对象的定义](https://www.cnblogs.com/EasonJim/p/7967999.html)
[object 使用介绍](https://zhuanlan.zhihu.com/p/102389552)

## 使用方式
基于目前的代码和理解，一个dao对象用于对数据库进行交互，出入参都是DO对象，表示数据库对象。
一个BO对象，用于业务的处理，出入参都是DTO对象
一个展示层对象，对外的可以用VO或者DTO对象表示