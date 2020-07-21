##### eval
用于执行lua脚本，可以将多个命令组装到一个lua脚本中，保证多个命令的原子性；

命令格式：

eval script numKeys key1 key2 arg1 arg2

KEY[i]获取key的值
ARGV[i]获取arg的值


##### 通过lua脚本调用redis命令
- redis.call()
> 会将异常向外抛出

- redis.pcall()
> 会将异常捕获

eval "return redis.call('set','foo','bar')"
eval "return redis.call('set',KEYS[1],'bar')"
