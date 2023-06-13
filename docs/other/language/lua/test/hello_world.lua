print("Hello World")

mytable = {}
mytable[1] = 2
print(mytable[1])

io.write(mytable[1], "testme", "\n")

for line in io.lines("/Users/jiangchangwei/jd_source/design-pattern/docs/other/language/lua/test/hello_world.lua") do 
        print(line)
end


a = 17
local b = 16

function test()
    c = 16
    print("b:", b)
end

test()

function test1()
    inc = 1
    print("inc:", inc);
    function test2()
        inc = inc + 1
        print("inc:", inc);
    end
    return test2
end

t = test1()
tt = test1()
t()
t()
tt()
tt()