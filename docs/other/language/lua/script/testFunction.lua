function testFun(tab, fun)
  for k, v in pairs(tab) do
    print(fun(k, v));
  end
end

tab = {key1="val1", key2="val2"};
testFun(tab,
function(key, val)
  return key.."="..val;
end
);


x = 1
y = 2
x,y=y,x
print("x".. "="..x)
print("y".."="..y)

local arr = {1,2,3}
print(#arr)

print(arr[0])


if(0)
then
  print("0 is true")
elseif(nil)
then
  print("nil is true")
end

do
  function foo(...)
    for i = 1, select('#', ...) do -->获取参数总数
      local arg = select(i, ...); -->读取参数
      print("arg", arg);
    end
  end

  foo(1, 2, 3, 4);
end

function square(iteratorMaxCount,currentNumber)
   if currentNumber<iteratorMaxCount
   then
      currentNumber = currentNumber+1
   return currentNumber, currentNumber*currentNumber
   end
end

for i,n in square,3,0
do
   print(i,n)
end
