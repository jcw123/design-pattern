function test() {
    var i = 0;
    return function() {
        console.log(i++);
    }
}

var m = test();
for(let i = 0; i < 10; i++) {
    m();
}

// 创建一个匿名函数并立即执行
(function (m) {
    console.log(m)
})(4);

var one = function(f) {
    return function(x) {
        return f(x);
    }
}

one(function(x) {
    console.log("x:" + x);
})(1);


if(Math.random() > 0.5) {
    var x = 1;
}else {
    var x = 2;
}
console.log(x);


function outer() {
    const x = 5;
    const y = 6;
    return () => console.log(x, y);
  }
  
  outer()(); // Logs 5 6