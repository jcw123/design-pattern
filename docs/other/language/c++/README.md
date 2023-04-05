# c++

## 指针和引用
1、指针就是一个变量的地址，通过这个地址可以直接更改元素的值；通过新建一个地址空间存储原有变量的地址值的；
2、引用不用新建一个地址空间，指向的是和原来变量相同的地址；
```c++
int a = 1;
int *p = &a;
int &b = a;
```
## 声明
```c++
// 变量的声明
// 变量声明，变量的声明可以在多个文件声明，但是定义只能在一个文件中，否则进行文件链接时会报错；
extern int a, b;

// 变量的定义
int a, b;
```

## 参考文档
[中文文档](https://www.apiref.com/cpp-zh/index.html)
[官方文档](https://cplusplus.com/reference/)
[菜鸟教程](https://www.runoob.com/cplusplus/cpp-standard-library.html)