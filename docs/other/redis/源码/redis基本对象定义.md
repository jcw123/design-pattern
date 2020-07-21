1. 基本对象结构
```c
typedef struct redisObject {
    unsigned type:4;
    unsigned encoding:4;
    unsigned lru:LRU_BITS; /* LRU time (relative to global lru_clock) or
                            \* LFU data (least significant 8 bits frequency
                            \* and most significant 16 bits access time). \*/
    int refcount;
    void \*ptr;
} robj;
```

2. 
