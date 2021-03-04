1. 核心包
```xml
<dependency>
  <groupId>org.mybatis</groupId>
  <artifactId>mybatis-spring</artifactId>
</dependency>
```

2. 核心连接组件

- org.mybatis.spring.SqlSessionFactoryBean
用于构建SqlSessionFactory这个对象，是一个核心，需要的核心属性一个是数据源datasource，还有个就是mybatis的配置文件地址变量configLocation；

- SqlSessionTemplate
SqlSession的一个模板类，构建这个类只需要一个SqlSessionFactory对象。是线程安全的（注：线程安全主要是通过代理+ThreadLocal来实现的。SqlSession不是线程安全的），受spring的管理，支持spring的事务管理。通过这个类就不需要我们手动调用openSqlSession创建一个SqlSession对象了。还是挺不错的。
> SqlSessionInterceptor这个类很有意思，是InvocationHandler接口的一个实现，在SqlSessionInterceptor有一个SqlSession的代理类sqlSessionProxy，通过这个类来执行sql的执行。
  sqlSessionProxy这个代理类使用ThreadLocal维护了一个map，而这个map的key就是SqlSessionFactory，而value就是SqlSession本身，如果SqlSession不存在，则调用SqlSessionFactory重新创建一个SqlSession对象。
