## C语言的基础

1. c程序到可执行文件经历的步骤：

- 预编译
  + 将所有的#define删除，并且展开所有的宏定义。说白了就是字符替换
  + 处理所有的条件编译指令，#ifdef #ifndef #endif等，就是带#的那些
  + 处理#include，将#include指向的文件插入到该行处
  + 删除所有注释
  + 添加行号和文件标示，这样的在调试和编译出错的时候才知道是是哪个文件的哪一行
  + 保留#pragma编译器指令，因为编译器需要使用它们。

- 编译
  + 词法分析
  + 语法分析
  + 语义分析
  + 优化后生成相应的汇编代码

- 汇编
将汇编语言转为机器语言

- 链接
将二进制文件和库进行链接，生成可执行程序

- 可执行文件

> -E                       Preprocess only; do not compile,assemble or link
  -S                       Compile only; do not assemble or link
  -c                       Compile and assemble, but do not link
  -o <file>                Place the output into <file>.

  参考文档：
  - https://www.cnblogs.com/liuzhenbo/p/11031052.html
