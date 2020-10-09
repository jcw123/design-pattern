#### 常见生成器方式

- UUID
java中的实现类:UUID
 The most significant long consists of the following unsigned fields:
 0xFFFFFFFF00000000 time_low
 0x00000000FFFF0000 time_mid
 0x000000000000F000 version
 0x0000000000000FFF time_hi
 The least significant long consists of the following unsigned fields:
 0xC000000000000000 variant
 0x3FFF000000000000 clock_seq
 0x0000FFFFFFFFFFFF node

 time-based, DCE security, name-based, and randomly generated UUIDs.  These types have a version value of 1, 2, 3 and 4 respectively.

- 数据库自增ID
- 数据库多主模式
- 号段模式
- Redis
- 雪花算法（SnowFlake）
- 滴滴出品（TinyID）
- 百度 （Uidgenerator）
- 美团（Leaf）

#### 生成器满足的一些常见特性
- 全局唯一
- 高性能
- 高可用
- 易接入
- 趋势递增（不知道啥意思。。）

参考文档：
https://zhuanlan.zhihu.com/p/107939861
https://cloud.tencent.com/developer/article/1530850
