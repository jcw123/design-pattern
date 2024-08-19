-- local t = {["1"]="2"};

-- print(t['1'])

local m = "t1|t2|t3"

string.gsub(m, '[^|]+', function(w) 
    print(w)
end
);


if 0 then
    print "nihao"
end


print(tonumber(''))


if nil == false then
    print('ok')
end