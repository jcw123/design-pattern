# OQL

## 常规使用
1. 通过字符串值匹配查找字符串的值
select s from java.lang.String s where s.toString().startsWith("GH")
参考文档:https://stackoverflow.com/questions/11527526/string-search-using-oql

2. 正则表达式匹配
select s.value.toString() from java.lang.String s 
    where /java/.test(s.value.toString())

3. 获取一个对象的唯一标识符，后面可以用这个标识符来定位当前对象
select objectid(o) from java.lang.String o where o.value.length >= 1000

4. 查询一个类的静态属性
select heap.findClass("java.lang.System").statics.props

5. 基于正则匹配定位到类的实例
select filter(heap.classes(), "/java.net./.test(it.name)")

6. 查找某一个类的实例
select c1 from java.lang.Thread c1

7. 查找一个类可达哪些对象(相当于从根从下找)
select reachables(p) from java.util.Properties p

8. 查看哪些对象持有了某一个对象
select referrers(f) from java.io.File f

9. 查询出来多个值
select { name: t.name? t.name.toString() : "null", thread: t } 
    from instanceof java.lang.Thread t

10. 查询最长的字符串对象
select max(heap.objects('java.lang.String'), 'lhs.value.length > rhs.value.length')

11. 排序之后，进行映射结果输出
 select map(sort(heap.objects('[I'), 'rhs.length - lhs.length'), '{ size: it.length, obj: it, id: objectid(it)}')





## 参考文档
[OQL学习文档](http://cr.openjdk.java.net/~sundar/8022483/webrev.01/raw_files/new/src/share/classes/com/sun/tools/hat/resources/oqlhelp.html )  