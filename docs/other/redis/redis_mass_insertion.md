##### 批量插入技术

对于大批量的插入操作，可以使用pipe模式；

1. a commands can be represented as fllows:
*<args><cr><lf>
$<len><cr><lf>
<arg0><cr><lf>
<arg1><cr><lf>
...
<argN><cr><lf>

*3<cr><lf>
$3<cr><lf>
SET<cr><lf>
$3<cr><lf>
key<cr><lf>
$5<cr><lf>
value<cr><lf>

注：管道技术非常不错，正常的情况下是发送一个command，然后等待响应结果，采用管道技术，可以发送一批命令，然后只需要响应一次即可。
交互次数少了，消耗在网络上的时间也少了。
