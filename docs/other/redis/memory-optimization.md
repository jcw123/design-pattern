##### 内存优化

1. 常用配置
> 少于对应的大小，进行优化操作；当大于对应的阈值后，进行正常的编码操作；

hash-max-ziplist-entries 512
hash-max-ziplist-value 64
zset-max-ziplist-entries 128
zset-max-ziplist-value 64
set-max-intset-entries 512

1. 常用优化操作

- Using 32 bit instances

- Bit and byte level operations

- Use hashes when possible
Small hashes are encoded in a very small space, so you should try representing your data using hashes every time it is possible

- Using hashes to abstract a very memory efficient plain key-value store on top of Redis


参考文档：
https://redis.io/topics/memory-optimization
