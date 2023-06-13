var a = 1;
console.log("a:" + a);

// 声明块级局部变量
let b = 2;
console.log("a + b:" + (a + b));

// 声明常量
const c = 3;
console.log("c:" + c);

console.log(typeof {"a":1, "b":2})

var s = "11"
var ss = parseInt(s)
console.log(typeof s)
console.log(typeof ss)

var arr = new Array();
arr[0] = 10;
arr[100] = 200;
console.log("arr len:" + arr.length)

var dict = new Map([[1, 2], [3, 4]]);
console.log("dict len:" + dict.size)

// map遍历
dict.forEach(function(value, key){
    console.log("key:" + key + ", value:" + value);
});

for(key of dict.keys()) {
    console.log("key:" + key);
}

for(value of dict.values()) {
    console.log("values:" + value)
}

for([key, value] of dict.entries()) {
    console.log("key:" + key + ", value:" + value);
}