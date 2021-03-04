##### 内存屏障方法

- __machine_r_barrier() — This is a read barrier. It ensures that all the load operations before the barrier will be completed before all the load operations after the barrier.

- __machine_w_barrier() — This is a write barrier. It ensures that all the store operations before the barrier will be completed before all the store operations after the barrier.

- __machine_rw_barrier() — This is a read-write barrier. It ensures that all the load and store operations before the barrier will be completed before all the load and store operations after the barrier.

- __machine_acq_barrier() — This is a barrier with acquire semantics. It ensures that all the load operations before the barrier will be completed before all the load and store operations after the barrier.

- __machine_rel_barrier() — This is a barrier with release semantics. It ensures that all the load and store operations before the barrier will be completed before all the store operations after the barrier.

- __compiler_barrier() — Prevents the compiler from moving memory accesses across the barrier.

参考文档：
https://zhuanlan.zhihu.com/p/29881777

##### memory barrier
1. 编译器或者操作系统
