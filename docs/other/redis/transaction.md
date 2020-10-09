##### COMMON TRANSACTION COMMAND
- MULTI
开启一个事务
- EXEC
执行一个事务命令
- DISCARD
丢弃一个事务
- WATCH
可以用来模仿CAS操作，对key进行监控，其他客户端对监控的key进行修改后，执行在WATCH下执行事务，会抛出异常

##### why not support roll back?
- Redis commands can fail only if called with a wrong syntax (and the problem is not detectable during the command queueing), or against keys holding the wrong data type: this means that in practical terms a failing command is the result of a programming errors, and a kind of error that is very likely to be detected during development, and not in production.

- Redis is internally simplified and faster because it does not need the ability to roll back.

注：目前可以通过脚本实行原子性，可以不用上面提到的命令，使用脚本实现更好；
