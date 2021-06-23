#### IdentityWrapper

1. 路径
org.apache.commons.pool2.impl.BaseGenericObjectPool

2. 作用
通过对一个对象进行包装，比如重写hashCode、equals时可以作为hash key，不需要破坏原有对象
本身，非常不错的方案；