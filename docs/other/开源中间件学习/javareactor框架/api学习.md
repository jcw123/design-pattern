# Flux

## combineLatest
进行多个flux元素的合并处理，对于多个发布者，每当一个发布者发布了最新的元素之后，它会通过组合函数进行其他flux中最新的元素的组合。
```java
@Test
public void testCombineLatest() throws Exception {
    Flux<String> flux1 = Flux.interval(Duration.ofSeconds(1)).map(t -> "a" + t).take(3);
    Flux<String> flux2 = Flux.interval(Duration.ofSeconds(2)).map(t -> "b" + t).take(3);
    Flux<String> flux = Flux.combineLatest(flux1, flux2, (o1, o2) -> o1 + o2);
    flux.subscribe(System.out::println);
    Thread.sleep(1000*10);
}
```

## concat
将多个发布者进行连接起来，重点是保证发布者的顺序

## merge
将多个发布者进行连接起来，不保证发布者消息订阅的顺序

## zip
对于多个订阅者，只有所有的发布者都发布一个元素后，才将这些元素合并成元组进行发布出去。


# Mono