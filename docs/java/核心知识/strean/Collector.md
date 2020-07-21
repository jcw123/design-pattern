1. 定义一个Collector
```java
     Collector<Widget, ?, TreeSet<Widget>> intoSet =
         Collector.of(TreeSet::new, TreeSet::add,
                      (left, right) -> { left.addAll(right); return left; });
```

2. 核心组成
- supplier()
creation of a new result container
- accumulator
incorporating a new data element into a result container
- combiner()
combining two result containers into one
- finisher()
performing an optional final transform on the

3. 可以通过Collector.of方法获取Collector类的实现；
