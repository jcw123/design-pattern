1、git的官方参考文档
https://git-scm.com/docs

2、git底层原理介绍
https://zhuanlan.zhihu.com/p/96631135

3、git中的objects中有三种文件类型：blob（存储数据的）、tree（相当于一个文件夹，存储不同文件的内容）、
commit（指向了一个tree）。

一个文件夹对应一个tree，而一个具体文件对应一个BLOB文件，如果一个文件的数据变动了，会导致其上层的文件的
hash值都会变动。

4、默克尔树（Merkle Trees）
一个二叉树，上层节点的hash值是通过底层节点的hash生成的。所以上层节点的hash依赖于下层节点的
hash，如果下层节点的值变了，会直接往上传递影响上层节点的hash。
