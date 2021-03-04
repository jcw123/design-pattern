#### NMT

##### 开启
-XX:NativeMemoryTracking=summary or -XX:NativeMemoryTracking=detail

#### 命令格式
jcmd <pid> VM.native_memory [summary | detail | baseline | summary.diff | detail.diff | shutdown] [scale= KB | MB | GB]
注：baseline相当于创建一个基底快照，用于summary.diff和detail.diff比较

#### 其他
-XX:+UnlockDiagnosticVMOptions -XX:+PrintNMTStatistics 当VM退出时打印最后的内存使用情况；

##### 参考文档
https://docs.oracle.com/javase/8/docs/technotes/guides/vm/nmt-8.html
https://stackoverflow.com/questions/38597965/difference-between-resident-set-size-rss-and-java-total-committed-memory-nmt
