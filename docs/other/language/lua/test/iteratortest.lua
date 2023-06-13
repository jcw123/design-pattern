
array = {"test1", "test2", "test3"}

for key, value in ipairs(array) do
    print(key, value)
end

--[[
d为状态常量
n为状态变量    
--]]
function square(d, n) 
    if n < 100 then
        n = n + 1
        return n, n * n, 1
    end
end

for v, v1, v2 in square, 100, 90 do
    print(v, v1, v2)
end