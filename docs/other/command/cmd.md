1、查看进程
wmic process get name,executablepath,processid|findstr pid

2、systeminfo
查看系统的信息，比如查看cpu的个数

3、wmic -》 cpu get *
查看核数和线程数
