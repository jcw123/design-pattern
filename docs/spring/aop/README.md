### aop

#### aop的入口

##### 入口一
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

##### 入口二
通过注解@Aspect，如果需要识别这个注解，需要配置<aop:aspectj-autoproxy />这个属性


#### 参考文章
https://zhuanlan.zhihu.com/p/25892085
