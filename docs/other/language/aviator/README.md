# aviator

## 特殊使用

1. 进行aviator类型和java类型转换
通过AviatorRuntimeJavaType.valueOf()函数可以将java类型转为aviator数据类型

2. 如何定义不同集合
定义set集合：

## 内置函数
函数名	参数类型	返回值类型	功能描述	示例
math.abs	数字类型	同输入类型	绝对值	math.abs(-5) → 5
math.sqrt	数字类型	Double	平方根	math.sqrt(9) → 3.0
math.pow	(底数, 指数)	Double	幂运算	math.pow(2,3) → 8.0
math.log	数字类型	Double	自然对数	math.log(10) → 2.302585
math.log10	数字类型	Double	以10为底对数	math.log10(100) → 2.0
math.sin	弧度值	Double	正弦函数	math.sin(math.PI/2) → 1.0
math.round	(数字, 小数位)	Double	四舍五入	math.round(3.14159, 2) → 3.14

string.length	String	Long	字符串长度	string.length('hello') → 5
string.contains	(主串, 子串)	Boolean	是否包含	string.contains('abc','a') → true
string.join	(分隔符, 集合/数组)	String	连接字符串	string.join(',', [1,2,3]) → “1,2,3”
string.split	(字符串, 分隔符)	字符串数组	分割字符串	string.split('a,b,c', ',') → [“a”,“b”,“c”]
string.replace	(原串, 目标串, 替换串)	String	字符串替换	string.replace('foo','o','a') → “faa”

seq.map	(集合, lambda)	新集合	映射操作	seq.map([1,2,3], lambda(x) -> x+1 ) → [2,3,4]
seq.filter	(集合, lambda)	新集合	过滤操作	seq.filter([1,2,3], lambda(x) -> x>1 ) → [2,3]
seq.reduce	(集合, lambda, 初始值)	任意类型	归约操作	seq.reduce([1,2,3], lambda(a,b)->a+b, 0) → 6
seq.contains	(集合, 元素)	Boolean	是否包含元素	seq.contains([1,2,3], 2) → true
seq.sort	集合	新集合	排序	seq.sort([3,1,2]) → [1,2,3]

date.now	无	Date	当前时间	date.now() → 当前时间对象
date.format	(Date, 格式字符串)	String	日期格式化	date.format(now, 'yyyy-MM-dd') → “2023-07-20”
date.parse	(日期字符串, 格式)	Date	字符串转日期	date.parse('2023-07-20', 'yyyy-MM-dd') → Date对象

long	数字/字符串	Long	转为长整型	long('123') → 123L
double	数字/字符串	Double	转为双精度	double('3.14') → 3.14
str	任意类型	String	转为字符串	str(123) → “123”
boolean	任意类型	Boolean	转为布尔值	boolean(1) → true

lambda	(参数列表, 表达式)	Function	创建匿名函数	filter(list, lambda(x) -> x>0 )
apply	(函数, 参数…)	任意类型	应用函数	apply(lambda(x,y)->x+y, 1, 2) → 3

rand	无/上限值	Double	随机数	rand() → 0.123 / rand(10) → 5.67
if	(条件, 真值, 假值)	任意类型	三元运算	if(1>0, 'yes', 'no') → “yes”
isnil	任意类型	Boolean	判断null	isnil(null) → true
tuple	多个参数	Tuple	创建元组	tuple(1,'a',true) → (1,‘a’,true)

## 参考文档
[掘金用户学习文档](https://juejin.cn/column/6992213452605358117)
[镜像官网参考文档](https://gitee.com/mirrors/aviator/wikis/Home)