1. 参考文章：
https://www.cnblogs.com/rjzheng/p/10874537.html


2. 监控热key方式：
- 凭着业务经验，评估哪些是热key
- 在proxy层进行监控；
- 在客户端进行监控；
- 用redis自带命令：monitor命令、hotkeys参数
- 自己抓包评估；

3. 解决方式:
- 利用二级缓存；
- 备份热
