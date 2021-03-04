只针对1.8版本的hashmap
1、底层是数组+链表+红黑树实现的。

2、核心参数
（1）DEFAULT_INITIAL_CAPACITY:默认的初始化容量16.

（2）MAXIMUM_CAPACITY = 1 << 30
最大的容量值，如果设置的值大于此，会使用MAXMUM_CAPACITY作为此时容量

（3）DEFAULT_LOAD_FACTOR = 0.75f
默认的负载因子

（4）threshold
其值等于capacity * loadfactor，当map中元素的个数大于threshold时，会
进行 2 * oldCapacity的容量进行扩容。

（5）transient Node<K,V>[] table
这个数组就是存放元素的地方，其中Node可能是链表结构也可能是红黑树结构。

3、什么时候进行扩容？
（1）初始化时会进行扩容
（2）当打算插入元素时，先判断元素的个数是否超过阈值（capacity * loadfactor），
如果超过其值，进行进行扩容，然后重新进行hash操作。

4、链表结构和红黑树结构什么时候互换？
（1）链表结构转为红黑树结构

（2）红黑树转为链表

5、有趣的tableSizeFor方法
根据传递的capacity方法，计算第一个大于等于capacity的2的整数幂；
```java
static final int tableSizeFor(int cap) {
        int n = cap - 1;
        n |= n >>> 1;  // 假设为1的最高位为m，经过这个操作后，m，m-1为都为1；
        n |= n >>> 2; // 经过这个后，m,...m-3都为1；
        n |= n >>> 4; // 经过这个后，m,... m-7都为1；
        n |= n >>> 8; // 经过这个后，m,...m-15都为1；
        n |= n >>> 16; // 经过这个后， m,...m-31都为1；
        return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
    }
```
