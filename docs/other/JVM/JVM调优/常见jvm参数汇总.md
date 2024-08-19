# 常见JMV参数汇总

##  -XX:InitiatingHeapOccupancyPercent=30
含义：老年代使用的容量跟堆总容量的比值
功能：如果达到这个阈值，则会触发并发标记，方便后续快速mixed gc;

## -XX:+PrintGCDetails 
含义：可以打印GC的详细日志

## -XX:+UseG1GC
含义：表示垃圾收集器使用G1

## XX:+ParallelRefProcEnabled
含义：启用并行处理引用处理过程
参考：https://stackoverflow.com/questions/56846977/what-is-reference-processing-in-garbage-collection-process

## -XX:G1ReservePercent