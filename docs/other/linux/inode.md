参考文档：
https://www.jianshu.com/p/09c476d60dbb
http://www.ruanyifeng.com/blog/2011/12/inode.html

1. stat [OPTION] file
显示文件和文件系统的状态

2. 磁盘格式化时，自动将硬盘格式化为两个区域，一个是数据区，用于存放文件数据，
一个是inode区（inode table）,用于存放node所包含的信息；

3. inode所包含的信息如下：
    - 文件的字节数  
    - 文件拥有者的User ID  
    - 文件的Group ID
    - 文件的读、写、执行权限
    - 文件的时间戳，共有三个：ctime指inode上一次变动的时间，mtime指文件内容上一次变动的时间，atime指文件上一次打开的时间。
    - 链接数，即有多少文件名指向这个inode
    - 文件数据block的位置

4. 目录文件由两部分组成：所包含文件的文件名，以及该文件所对应的inode号码；
