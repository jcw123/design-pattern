##### redis支持客户端缓存

1. 客户端缓存的优点：
- Data is available with a very small latency
- The database system receives less queries, allowing to serve the same dataset with a smaller number of nodes.

2. 客户端缓存实现的两种方式：
- In the default mode, the server remembers what keys a given client accessed, and send invalidation messages when the same keys are modified. This costs memory in the server side, but sends invalidation messages only for the set of keys that the client could have in memory
> 服务端记录每一个客户端可能缓存了哪些key，当key发生改变时，通知相应的客户端；

- In the broadcasting mode instead the server does not attempt to remember what keys a given client accessed, so this mode does not cost any memory at all in the server side. Instead clients subscribe to key prefixes such as object: or user:, and will receive a notification message every time a key matching such prefix is touched
> 客户端对一些前缀key进行订阅，然后当相应的key发生改变时就通知对应的客户端；

参考文章：
https://redis.io/topics/client-side-caching
