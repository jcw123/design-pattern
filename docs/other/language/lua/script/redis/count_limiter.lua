local key = KEYS[1] -- 限流
-- 在固定时间内最多调用的次数
local maxLimit = tonumber(ARGV[1])
-- 固定的时间间隔，单位是秒
local interval = ARGV[2]

local current = tonumber(redis.call('incr', key))
if current > maxLimit then
  return 0
else
  if current == 1 then
    redis.call('expire', key, interval)
  end
  return tonumber(redis.call('get', key))
end
