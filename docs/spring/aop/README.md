# aop

## 表达式语法
execution(modifiers-pattern? ret-type-pattern declaring-type-pattern?name-pattern(param-pattern) throws-pattern?)
execution: 关键字，表示这是一个执行点切入表达式。
modifiers-pattern: 方法修饰符模式（可选），比如 public、private 等。
ret-type-pattern: 返回值类型模式，例如 int、void、* 等。
declaring-type-pattern: 声明类型模式，指定要拦截的类。
name-pattern: 方法名模式，可以使用通配符。
param-pattern: 参数类型模式，可以使用通配符。
throws-pattern: 异常抛出类型模式（可选）。

## aop的入口

### 入口一
通过spring的配置文件
```xml
<aop:config proxy-target-class="false">
        <aop:aspect id="aspect1" ref="advice">
            <aop:pointcut id="p1" expression="execution(* com.im.sky.spring.bean.IPeople.say(..))" />
            <aop:before pointcut-ref="p1" method="before" />
        </aop:aspect>
        <aop:aspect id="aspect2" ref="advice">
            <aop:pointcut expression="execution(* com.im.sky.spring.bean.IPeople.*(..))" id="p2" />
            <aop:around method="around" pointcut-ref="p2" />
            <aop:after pointcut-ref="p2" method="after" />
        </aop:aspect>
    </aop:config>
```

### 入口二
通过注解@Aspect，如果需要识别这个注解，需要配置<aop:aspectj-autoproxy />这个属性

## 关键类介绍

### AspectJExpressionPointcut
在解析aop配置时，会将pointcut的表达式映射到这个实现类

### AspectJAwareAdvisorAutoProxyCreator
这个是BeanPostProcesser处理器，利用applyBeanPostProcessorsAfterInitialization这个方法生成bean的代理对象，进行aop代理

```java
protected Object wrapIfNecessary(Object bean, String beanName, Object cacheKey) {
    if (StringUtils.hasLength(beanName) && this.targetSourcedBeans.contains(beanName)) {
        return bean;
    }
    if (Boolean.FALSE.equals(this.advisedBeans.get(cacheKey))) {
        return bean;
    }
    if (isInfrastructureClass(bean.getClass()) || shouldSkip(bean.getClass(), beanName)) {
        this.advisedBeans.put(cacheKey, Boolean.FALSE);
        return bean;
    }

    // Create proxy if we have advice.
    Object[] specificInterceptors = getAdvicesAndAdvisorsForBean(bean.getClass(), beanName, null);
    if (specificInterceptors != DO_NOT_PROXY) {
        this.advisedBeans.put(cacheKey, Boolean.TRUE);
        Object proxy = createProxy(
                bean.getClass(), beanName, specificInterceptors, new SingletonTargetSource(bean));
        this.proxyTypes.put(cacheKey, proxy.getClass());
        return proxy;
    }
```

利用AbstractAutoProxyCreator#createProxy这个方法创建代理对象。


#### 参考文章
[网上学些](https://zhuanlan.zhihu.com/p/25892085)
[表达式学习](https://docs.spring.io/spring-framework/reference/core/aop/ataspectj/pointcuts.html)
