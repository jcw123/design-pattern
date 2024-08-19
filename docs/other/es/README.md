# ES

## 基本原理

## 架构图

## 基本概念

### Inverted Index（反向索引）

### Document
存储的最基本的单元，一条文档有一个唯一的id。

### Index
具有相似特征的document的记录，类似于关系数据库中的table。

### Cluster
一个集群由多个节点组成，集群的能力依赖于不同节点的存储、搜索、聚合、索引；

### Node
一个Node就是一个服务实例，节点有不同的类型，master node、data node、client node；
- master node
  控制index的创建和删除；控制节点的删除和添加；
- data node
  存储数据和数据相关的操作，比如：搜索和聚合；
- client node
  传递集群请求到master节点，数据相关的请求到数据节点。

### Shards
- 一个index可以被分为多个分片，实现数据得分布式存储，充分利用分布式的能力；

### Replicas
- 主分片的复制分片，防止主分片数据丢失，提升数据查询速度；

## 基本命令

## 核心知识点

## 杂记
1、es的每一个分片都有索引，这个索引是所有索引的一部分，只针对当前分片的数据建立索引；


## 参考文档
[官方首页](https://www.elastic.co/cn/)
[官方文档](https://www.elastic.co/guide/index.html)
[7.15版本之后推荐的java客户端](https://www.elastic.co/guide/en/elasticsearch/client/java-api-client/7.17/installation.html)
[rest-java使用说明](https://juejin.cn/post/7046759829255225351)
[setting配置](https://www.elastic.co/guide/en/elasticsearch/reference/6.8/index-modules.html)
[es客户端使用讨论区](https://discuss.elastic.co/latest)

1. 倒排索引参考文章
https://www.cnblogs.com/candlia/p/11920027.html

2. frame-of-reference and roaring bitmaps
https://www.elastic.co/cn/blog/frame-of-reference-and-roaring-bitmaps

3. lucene算法原理
http://www.blogjava.net/kingpub/archive/2012/07/16/64174.html

4. es分片介绍
https://www.jianshu.com/p/cc06f9adbe82

- 对于频繁出现的值，例如男/女，通过借助于Frame of Reference编码可以极大减少磁盘占用。
