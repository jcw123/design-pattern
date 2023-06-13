o1 = {
    "test1":1,
    "test2": function(m) {
        console.log("m:" + m)
    }
}
console.log(o1.test1)
console.log(o1.test2)
o1.test2(3)