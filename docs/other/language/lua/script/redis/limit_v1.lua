local key = "redis.limit:" .. KEYS[1] -- 限流key
local limit = tonumber(ARGV[1]) -- 限流大小
local windows = tonumber(ARGV[2]) -- 时间窗口
local val = redis.call('get', key)
if not val then
  redis.call('INCRBY', key, 1)
  redis.call('expire', key, windows)
  return 0 -- 0表示不限流
local current = tonumer(redis.call('get', key) or "0")
if current + 1 > limit then
  return 1 -- 表示限流
else
  redis.call('INCRBY', key, 1)
  return 0
end
