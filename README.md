# KD-Tree for Gaussian Process

## 概述
此项目基于[Leo Ma](https://github.com/begeekmyfriend/kdtree)所做的工作, 
为了满足 [高斯过程](https://en.wikipedia.org/wiki/Gaussian_process) 对临近点搜索的需求,
我们做了适配修改并添加了代码注释,方便他人使用和修改.  

## 说明
- `kdtree.c`和`kdtree.h` 为kdtree核心算法的源文件和头文件.  
- `test`目录下`test.cpp`和`eigen_test.cpp` 分别提供了不同数据结构输入的测试样例.
- `lib`目录下`libkdtree.a`和`libkdtree.so` 提供了静态库和动态库.
- 核心算法使用`C`编写, 因此在`C++`程序中调用, 需要注意以下两点:  
  1. 一是, 库文件中需要添加`__cplusplus`声明, 防止编译错误;
  1. 一是, 在`C++`调用程序中需添加`extern "C"`声明, 防止编译错误.

## 使用
使用该项目有两种方法:
- 一是, 直接将源文件和头文件拖进你的工程使用，但需注意编译环节的问题, 防止编译器风格选择错误;
- 一是, 使用Makefile生成静态库或者动态库, 作为库添加进你的工程即可.

关于Makefile:
>`make array` ----------`array` 测试案例  
>`make eigen` ----------`eigen` 测试案例  
>`make static_lib`-------创建静态库`libkdtree.a`   
>`make shared_lib`-----创建动态库`libkdtree.so`   
>`make clear`-------------清楚之前生成的可执行文件

第一种方法使用案例:
```
make array
./array_test
```

## 修改日志
增加了索引输出`coord_index`
增加了搜索结果重置，防止多次搜索时结果累积
