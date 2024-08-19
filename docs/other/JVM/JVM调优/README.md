# JVM调优

## 观察

### 日志打印参数

1. -verbose:gc  或者 -XX:+PrintGC
打印简化的GC日志信息
```
[GC pause (G1 Evacuation Pause) (young) 6144K->1404K(10M), 0.0039584 secs]
[GC pause (G1 Humongous Allocation) (young) (initial-mark) 3868K->2375K(10M), 0.0050467 secs]
[GC concurrent-root-region-scan-start]
[GC pause (G1 Humongous Allocation) (young)[GC concurrent-root-region-scan-end, 0.0005994 secs]
[GC concurrent-mark-start]
 2375K->1811K(10M), 0.0044939 secs]
[GC concurrent-mark-end, 0.0068249 secs]
[GC cleanup 7053K->7053K(10M), 0.0007168 secs]    
```

2. -XX:+PrintGCDetails
打印比较详细的日志信息
```
[GC pause (G1 Evacuation Pause) (young), 0.0043297 secs]
   [Parallel Time: 2.1 ms, GC Workers: 10]
      [GC Worker Start (ms): Min: 343.2, Avg: 343.4, Max: 344.0, Diff: 0.7]
      [Ext Root Scanning (ms): Min: 0.0, Avg: 0.3, Max: 1.0, Diff: 1.0, Sum: 2.9]
      [Update RS (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.0]
         [Processed Buffers: Min: 0, Avg: 0.0, Max: 0, Diff: 0, Sum: 0]
      [Scan RS (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.0]
      [Code Root Scanning (ms): Min: 0.0, Avg: 0.0, Max: 0.1, Diff: 0.1, Sum: 0.2]
      [Object Copy (ms): Min: 0.2, Avg: 0.8, Max: 1.3, Diff: 1.1, Sum: 8.3]
      [Termination (ms): Min: 0.0, Avg: 0.6, Max: 0.7, Diff: 0.7, Sum: 5.5]
         [Termination Attempts: Min: 1, Avg: 2.4, Max: 4, Diff: 3, Sum: 24]
      [GC Worker Other (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.2]
      [GC Worker Total (ms): Min: 1.1, Avg: 1.7, Max: 1.9, Diff: 0.8, Sum: 17.1]
      [GC Worker End (ms): Min: 345.0, Avg: 345.1, Max: 345.2, Diff: 0.2]
   [Code Root Fixup: 0.0 ms]
   [Code Root Purge: 0.0 ms]
   [Clear CT: 0.2 ms]
   [Other: 2.0 ms]
      [Choose CSet: 0.0 ms]
      [Ref Proc: 1.7 ms]
      [Ref Enq: 0.0 ms]
      [Redirty Cards: 0.3 ms]
      [Humongous Register: 0.0 ms]
      [Humongous Reclaim: 0.0 ms]
      [Free CSet: 0.0 ms]
   [Eden: 6144.0K(6144.0K)->0.0B(5120.0K) Survivors: 0.0B->1024.0K Heap: 6144.0K(10.0M)->1418.0K(10.0M)]
 [Times: user=0.02 sys=0.00, real=0.00 secs] 
[GC pause (G1 Humongous Allocation) (young) (initial-mark), 0.0049914 secs]
   [Parallel Time: 2.6 ms, GC Workers: 10]
      [GC Worker Start (ms): Min: 412.0, Avg: 412.3, Max: 412.5, Diff: 0.4]
      [Ext Root Scanning (ms): Min: 0.2, Avg: 0.7, Max: 2.1, Diff: 1.9, Sum: 7.4]
      [Update RS (ms): Min: 0.0, Avg: 0.0, Max: 0.1, Diff: 0.1, Sum: 0.2]
         [Processed Buffers: Min: 0, Avg: 0.2, Max: 1, Diff: 1, Sum: 2]
      [Scan RS (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.0]
      [Code Root Scanning (ms): Min: 0.0, Avg: 0.1, Max: 0.6, Diff: 0.6, Sum: 0.9]
      [Object Copy (ms): Min: 0.0, Avg: 0.8, Max: 1.8, Diff: 1.8, Sum: 7.7]
      [Termination (ms): Min: 0.0, Avg: 0.7, Max: 1.0, Diff: 1.0, Sum: 6.6]
         [Termination Attempts: Min: 1, Avg: 3.8, Max: 10, Diff: 9, Sum: 38]
      [GC Worker Other (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.1]
      [GC Worker Total (ms): Min: 2.1, Avg: 2.3, Max: 2.6, Diff: 0.5, Sum: 22.8]
      [GC Worker End (ms): Min: 414.5, Avg: 414.6, Max: 414.6, Diff: 0.1]
   [Code Root Fixup: 0.0 ms]
   [Code Root Purge: 0.0 ms]
   [Clear CT: 0.2 ms]
   [Other: 2.2 ms]
      [Choose CSet: 0.0 ms]
      [Ref Proc: 1.9 ms]
      [Ref Enq: 0.0 ms]
      [Redirty Cards: 0.2 ms]
      [Humongous Register: 0.0 ms]
      [Humongous Reclaim: 0.0 ms]
      [Free CSet: 0.0 ms]
   [Eden: 3072.0K(5120.0K)->0.0B(5120.0K) Survivors: 1024.0K->1024.0K Heap: 3905.9K(10.0M)->2214.9K(10.0M)]
 [Times: user=0.03 sys=0.00, real=0.00 secs] 
[GC concurrent-root-region-scan-start]
[GC concurrent-root-region-scan-end, 0.0008311 secs]
[GC concurrent-mark-start]
[GC pause (G1 Humongous Allocation) (young), 0.0077176 secs]
   [Parallel Time: 5.0 ms, GC Workers: 10]
      [GC Worker Start (ms): Min: 418.1, Avg: 419.8, Max: 422.0, Diff: 3.9]
      [Ext Root Scanning (ms): Min: 0.0, Avg: 0.1, Max: 0.3, Diff: 0.3, Sum: 0.6]
      [Update RS (ms): Min: 0.0, Avg: 0.2, Max: 0.7, Diff: 0.7, Sum: 1.8]
         [Processed Buffers: Min: 0, Avg: 1.0, Max: 4, Diff: 4, Sum: 10]
      [Scan RS (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.0]
      [Code Root Scanning (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.0]
      [Object Copy (ms): Min: 0.0, Avg: 0.1, Max: 0.2, Diff: 0.2, Sum: 0.5]
      [Termination (ms): Min: 0.0, Avg: 2.6, Max: 3.3, Diff: 3.3, Sum: 25.8]
         [Termination Attempts: Min: 1, Avg: 1.0, Max: 1, Diff: 0, Sum: 10]
      [GC Worker Other (ms): Min: 0.0, Avg: 0.0, Max: 0.0, Diff: 0.0, Sum: 0.1]
      [GC Worker Total (ms): Min: 0.0, Avg: 2.9, Max: 4.4, Diff: 4.4, Sum: 28.8]
      [GC Worker End (ms): Min: 422.0, Avg: 422.6, Max: 423.0, Diff: 1.0]
   [Code Root Fixup: 0.0 ms]
   [Code Root Purge: 0.0 ms]
   [Clear CT: 0.2 ms]
   [Other: 2.5 ms]
      [Choose CSet: 0.0 ms]
      [Ref Proc: 2.3 ms]
      [Ref Enq: 0.0 ms]
      [Redirty Cards: 0.2 ms]
      [Humongous Register: 0.0 ms]
      [Humongous Reclaim: 0.0 ms]
      [Free CSet: 0.0 ms]
   [Eden: 0.0B(5120.0K)->0.0B(5120.0K) Survivors: 1024.0K->1024.0K Heap: 2214.9K(10.0M)->1663.0K(10.0M)]
 [Times: user=0.03 sys=0.00, real=0.01 secs] 
[GC concurrent-mark-end, 0.0102779 secs]
[GC remark [Finalize Marking, 0.0045368 secs] [GC ref-proc, 0.0001042 secs] [Unloading, 0.0020350 secs], 0.0069370 secs]
 [Times: user=0.02 sys=0.00, real=0.01 secs] 
[GC cleanup 6906K->6906K(10M), 0.0012029 secs]
 [Times: user=0.00 sys=0.00, real=0.00 secs] 
Heap
 garbage-first heap   total 10240K, used 6783K [0x00000007bf600000, 0x00000007bf700050, 0x00000007c0000000)
  region size 1024K, 2 young (2048K), 1 survivors (1024K)
 Metaspace       used 5144K, capacity 5272K, committed 5504K, reserved 1056768K
  class space    used 599K, capacity 627K, committed 640K, reserved 1048576K 
```

## 常见配置
-Xloggc:/Users/jiangchangwei/Documents/gc.log
-XX:+UseGCLogFileRotation
-XX:GCLogFileSize=100M
-XX:NumberOfGCLogFiles=10
-XX:+PrintGCDetails
-XX:+PrintGCDateStamps
-Xms10M
-Xmx10M
-XX:+UseG1GC

[调优汇总](https://blog.csdn.net/shadow_zed/article/details/88047808)
[g1日志解析](https://heapdump.cn/article/233563)
[gc日志分析工具](https://gceasy.ycrash.cn/)