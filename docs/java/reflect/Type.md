#### 参考文档
https://zhuanlan.zhihu.com/p/64584427

1. Type是java所有类型的父接口，是对java数据类型的一个抽象；
2. Tyep共有4个子接口：GenericArrayType，ParameterizedType，TypeVariable，WildcardType
- TypeVariable 类型变量
> 指的类型是不确定的，比如List<T> m; 其中的T就是类型变量；

- ParameterizedType 参数化类型
> 例如Map<K, V>带参数的类型，其中<K, V>就是带的参数

- GenericArrayType
> 泛型数组类型，比如:List<T>[]

- WildcardType 通配符类型
> 例如：Map<? extends People, ? super People>

- Class
> 这个是Type类型的实现类，是反射的基础；

3. GenericDeclaration的子类有Class、Method、Constructor
> 继承这个接口的接口才可以声明类型变量；

4. AnnotatedElement
> 通过这个接口的api可以获取类型上声明的注解属性；
