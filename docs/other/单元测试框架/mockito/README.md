## Mockito

### 使用方法

### spring boot
1. 使用SpringBootTest注解和MockBean注解，其中通过MockBean注解声明的bean会注解到spring的上下文中，将正常的依赖进行移除；

参考用例
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class MyTests {

    @MockBean
    private RemoteService remoteService;

    @Autowired
    private Reverser reverser;

    @Test
    public void exampleTest() {
        // RemoteService has been injected into the reverser bean
        given(this.remoteService.someCall()).willReturn("mock");
        String reverse = reverser.reverseSomeCall();
        assertThat(reverse).isEqualTo("kcom");
    }

}
```

### spring
如果使用spring框架，需要做更多的工作，创建一个@Configuration bean，将模拟的bean放入到spring的上下文中，移除外部服务依赖的bean

```java
@Configuration
@Profile("useMocks")
public class MockConfigurer {

    @Bean
    @Primary
    public MyBean myBeanSpy() {
        return mock(MyBean.class);
    }
}
```

### 参考文档
[详细的mockito和spring集成](https://www.codenong.com/2457239/)