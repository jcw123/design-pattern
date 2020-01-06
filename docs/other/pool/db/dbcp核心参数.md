1、核心的包
```xml
<dependency>
  <groupId>org.apache.commons</groupId>
  <artifactId>commons-pool2</artifactId>
  <version>${commons.pool.version}</version>
</dependency>

<dependency>
  <groupId>org.apache.commons</groupId>
  <artifactId>commons-dbcp2</artifactId>
  <version>${commons.dbcp2.version}</version>
</dependency>
```

2、基本内容介绍

（1）dbcp借助于commons-pool这个jar包，commons-pool是一种对象池的实现，下面给出一些基本的pool中的概念。

**对象生命周期状态枚举**
```java
public enum PooledObjectState {
    // 空闲的对象
    IDLE,
    // 使用中的对象
    ALLOCATED,
    // 正在被驱逐线程测试的对象
    EVICTION,
    // 正在被驱逐线程测试，一单测试完成后，会将
    EVICTION_RETURN_TO_HEAD,
    // 正在被验证的对象
    VALIDATION,
    // 正在被验证的对象，一单验证通过，会直接通过borrow借出。
    VALIDATION_PREALLOCATED,
    // 驱逐线程验证的对象，没问题回将对象放到队列的头部
    VALIDATION_RETURN_TO_HEAD,
    // 不合法的对象，之后会被移出
    INVALID,
    //废弃的对象，之后会被销毁
    ABANDONED,
    //正在返回到池中的对象
    RETURNING
}
```

3、核心参数和代码中的体现

- initialSize
> 当连接池创建时初始化创建连接的数目

当首次获取数据库连接时，这个参数起到作用，会初始化initialSize这个数目的空闲连接数。在BasicDataSource的
createDataSource这个方法中，会有如下代码，进行初始化连接的建立。
```java
// If initialSize > 0, preload the pool
try {
    for (int i = 0; i < initialSize; i++) {
        connectionPool.addObject();
    }
} catch (final Exception e) {
    closeConnectionPool();
    throw new SQLException("Error preloading the connection pool", e);
}
```

- minIdle
> 最小化的空闲连接数目，当空闲驱逐线程进行超时空闲线程驱逐时，驱逐完毕后能够保证空闲连接数目至少达到最小值，这个参数必须在设置timeBetweenEvictionRunsMillis这个参数为正值时才会起作用（就是让驱逐线程运行起来）

在BaseGenericObjectPool.Evictor中，会用到minIdle，Evictor实现了Runnable接口，驱逐线程运行的就是这个实例任务。当完成了
超时连接和基于其他参数的连接后，会调用内部方法ensureMinIdle()保证空闲连接满足minIdle这个值。
```java
private void ensureIdle(final int idleCount, final boolean always) throws Exception {
    if (idleCount < 1 || isClosed() || (!always && !idleObjects.hasTakeWaiters())) {
        return;
    }

    // 空闲连接小于设置的minIdle
    while (idleObjects.size() < idleCount) {
        final PooledObject<T> p = create();
        if (p == null) {
            // Can't create objects, no reason to think another call to
            // create will work. Give up.
            break;
        }
        if (getLifo()) {
            idleObjects.addFirst(p);
        } else {
            idleObjects.addLast(p);
        }
    }
    if (isClosed()) {
        // Pool closed while object was being added to idle objects.
        // Make sure the returned object is destroyed rather than left
        // in the idle object pool (which would effectively be a leak)
        clear();
    }
}
```

- maxIdle
> 最大的空闲连接的数目，当用户用完一个连接后，然后重新把这个连接放到空闲连接池中，如果此时的空闲连接数超过maxIdle，就会destroy部分
多余的空闲线程。

- maxWaitMillis
> 获取一个连接的最长超时时间，如果等于小于等于0表示无限等待。

- validationQuery
> 当获取一个连接后，用这个sql验证连接的有效性。

- testOnBorrow
> 当从池子中获取一个连接时，是否需要验证连接的有效性，如果需要验证，就使用validationQuery设置的语句验证连接的有效性。

- removeAbandonedTimeout
> 一个活动连接的超时时间（意思就是一个连接在removeAbandonedTimeout这个时间里一直处于使用状态），一个连接在过长的时间里处于活动状态，要么是连接设置状态出现问题，要么是执行一个很慢的sql语句，此时主动回收，可以中断慢sql的执行。这个参数只有removeAbandonedOnBorrow
和removeAbandonedOnMaintenance这个参数其中之一设置为true时才能起作用。

- removeAbandonedOnBorrow
> 表示当在pool中拿连接时，尝试将废弃的连接移除掉。

- minEvictableIdleTimeMillis
> 表示一个连接持续minEvictableIdleTimeMillis这么长的时间一直处于空闲时，空闲连接会尝试驱逐。注：主要可以防止一个连接空闲时间太久了，服务端主要将连接断开了，导致连接时效，从而查库失败。

- timeBetweenEvictionRunsMillis
> 表示驱逐线程每隔多久运行一次。

只有这个参数设置的值大于0，才会启动驱逐线程
```java
protected void startPoolMaintenance() {
  // 只有timeBetweenEvictionRunsMillis这个参数大于0，才会启动驱逐线程
    if (connectionPool != null && timeBetweenEvictionRunsMillis > 0) {
        connectionPool.setTimeBetweenEvictionRunsMillis(timeBetweenEvictionRunsMillis);
    }
}

public final void setTimeBetweenEvictionRunsMillis(
            final long timeBetweenEvictionRunsMillis) {
    this.timeBetweenEvictionRunsMillis = timeBetweenEvictionRunsMillis;
    startEvictor(timeBetweenEvictionRunsMillis);
}

//启动驱逐线程
final void startEvictor(final long delay) {
        synchronized (evictionLock) {
      EvictionTimer.cancel(evictor, evictorShutdownTimeoutMillis, TimeUnit.MILLISECONDS);
      evictor = null;
      evictionIterator = null;
      if (delay > 0) {
          evictor = new Evictor();
          EvictionTimer.schedule(evictor, delay, delay);
      }
  }
}
```

- testWhileIdle
> 表示驱逐线程是否要验证连接的有效性，就算一个空闲连接没有超时，但是如果有效性无法验证通过，也会进行驱逐。（验证有效性，主要是防止一个空闲连接服务端在很短的时间里就断开了。）

testWhileIdle参数也是针对于驱逐线程，当使用驱逐线程判断线程没有超时不需要驱逐时，会判断testWhileIdle是否为true，如果是，
对连接进行校验，校验失败也会从连接池中移除此线程。

核心代码如下：
```java
public void evict() throws Exception {
    assertOpen();
    // 有空闲连接就进行校验
    if (idleObjects.size() > 0) {

        PooledObject<T> underTest = null;
        final EvictionPolicy<T> evictionPolicy = getEvictionPolicy();

        synchronized (evictionLock) {
            final EvictionConfig evictionConfig = new EvictionConfig(
                    getMinEvictableIdleTimeMillis(),
                    getSoftMinEvictableIdleTimeMillis(),
                    getMinIdle());

            final boolean testWhileIdle = getTestWhileIdle();

            for (int i = 0, m = getNumTests(); i < m; i++) {
                if (evictionIterator == null || !evictionIterator.hasNext()) {
                    evictionIterator = new EvictionIterator(idleObjects);
                }
                if (!evictionIterator.hasNext()) {
                    // Pool exhausted, nothing to do here
                    return;
                }

                try {
                    underTest = evictionIterator.next();
                } catch (final NoSuchElementException nsee) {
                    // Object was borrowed in another thread
                    // Don't count this as an eviction test so reduce i;
                    i--;
                    evictionIterator = null;
                    continue;
                }

                if (!underTest.startEvictionTest()) {
                    // Object was borrowed in another thread
                    // Don't count this as an eviction test so reduce i;
                    i--;
                    continue;
                }

                // User provided eviction policy could throw all sorts of
                // crazy exceptions. Protect against such an exception
                // killing the eviction thread.
                boolean evict;
                try {
                    // 根据配置的驱逐策略进行驱逐校验
                    evict = evictionPolicy.evict(evictionConfig, underTest,
                            idleObjects.size());
                } catch (final Throwable t) {
                    // Slightly convoluted as SwallowedExceptionListener
                    // uses Exception rather than Throwable
                    PoolUtils.checkRethrow(t);
                    swallowException(new Exception(t));
                    // Don't evict on error conditions
                    evict = false;
                }
                // 如果应该驱逐，直接销毁连接
                if (evict) {
                    destroy(underTest);
                    destroyedByEvictorCount.incrementAndGet();
                } else {
                    // 判断testWhileIdle是否为true，进行校验。
                    if (testWhileIdle) {
                        boolean active = false;
                        try {
                            factory.activateObject(underTest);
                            active = true;
                        } catch (final Exception e) {
                            destroy(underTest);
                            destroyedByEvictorCount.incrementAndGet();
                        }
                        if (active) {
                            if (!factory.validateObject(underTest)) {
                                destroy(underTest);
                                destroyedByEvictorCount.incrementAndGet();
                            } else {
                                try {
                                    factory.passivateObject(underTest);
                                } catch (final Exception e) {
                                    destroy(underTest);
                                    destroyedByEvictorCount.incrementAndGet();
                                }
                            }
                        }
                    }
                    if (!underTest.endEvictionTest(idleObjects)) {
                        // TODO - May need to add code here once additional
                        // states are used
                    }
                }
            }
        }
    }
    final AbandonedConfig ac = this.abandonedConfig;
    // 如果removeAbandonedOnMaintenance设置为true时，在驱逐线程中还会移除废弃的连接。
    if (ac != null && ac.getRemoveAbandonedOnMaintenance()) {
        removeAbandoned(ac);
    }
}
```

- numTestsPerEvictionRun
> 表示驱逐线程每次校验的连接的数目

- maxTotal
> 表示连接的最大数目，包括空闲连接和活动的连接。

GenericObjectPool类中有两个对象allObjects和idleObjects，其中allObjects就是连接对象的总集合，
idleObjects就是空闲连接。

- accessToUnderlyingConnectionAllowed
> 主要是控制PoolGuard是否允许访问正在处理中的线程

- connectionProperties
> 设置连接的一些属性参数，主要是驱动器进行数据库连接时需要用到的一些参数。

- connectionInitSqls
> 当一个连接物理连接创建后，执行的一些sql语句的集合。

调用PoolableConnectionFactory的makObject方法构建连接时，会执行连接创建的初始化语句。
```java
protected void initializeConnection(final Connection conn) throws SQLException {
  final Collection<String> sqls = connectionInitSqls;
  if (conn.isClosed()) {
      throw new SQLException("initializeConnection: connection closed");
  }
  if (null != sqls) {
      try (Statement stmt = conn.createStatement()) {
          for (final String sql : sqls) {
              Objects.requireNonNull(sql, "null connectionInitSqls element");
              stmt.execute(sql);
          }
      }
  }
}
```

- testOnReturn
> 当一个连接重新归还到池子中时，校验连接的有效性。

当一个连接使用完后重新往连接池中放时，如果testOnReturn设置为true，则校验连接，如何正常，会重新放入连接池，否则
销毁连接。部分归还连接的代码如下：

```java
/**
 * Return me to my pool.
 */
@Override
public void close() throws SQLException {
    // calling close twice should have no effect
    if (!isClosed()) {
        try {
           // 整理就是归还连接池
            pool.returnObject(key, this);
        } catch (final SQLException e) {
            throw e;
        } catch (final RuntimeException e) {
            throw e;
        } catch (final Exception e) {
            throw new SQLException("Cannot close preparedstatement (return to pool failed)", e);
        }
    }
}
```

- validationQueryTimeoutSeconds
> 执行一个校验连接查询的超时时间，当小于等于0时，没有超时的限制。

```java
public void validateConnection(final PoolableConnection conn) throws SQLException {
    if (conn.isClosed()) {
        throw new SQLException("validateConnection: connection closed");
    }
    conn.validate(validationQuery, validationQueryTimeoutSeconds);
}
```

- removeAbandonedOnMaintenance
> 当对pool进行检查时，移除超时的废弃连接。也是在驱逐线程的evict()方法中用到这个参数

- evictionPolicyClassName
> 定义驱逐策略的类，也就是一个线程是否应该进行驱逐可以自己定义一个EvictionPolicy这个接口的实现类。

- fastFailValidation
> 使用工厂创建的连接能够进行快速失败验证, 验证时直接抛出异常

- testOnCreate
> 表示一个对象创建完成后，直接进行校验。

- softMinEvictableIdleTimeMillis
> 和minEvictableIdleTimeMillis类似，只是softMinEvictableIdleTimeMillis这个参数需要保证池中至少有minIdle个空闲连接存在才进行驱逐。

4、使用实例
```java
public static void main(String[] args) throws Exception {
    testGetConnection();
}

public static void testGetConnection() throws Exception {
    BasicDataSource dataSource = new BasicDataSource();
    dataSource.setDriverClassName("com.mysql.jdbc.Driver");
    dataSource.setInitialSize(2);
    dataSource.setMinIdle(3);
    dataSource.setMaxIdle(6);
//        dataSource.setMaxWaitMillis(500);
    dataSource.setMaxTotal(10);
    dataSource.setAccessToUnderlyingConnectionAllowed(true);
    dataSource.setConnectionProperties("m=1");
    List<String> sqls = new ArrayList<>();
    sqls.add("select 1");
    dataSource.setConnectionInitSqls(sqls);
    dataSource.setTestOnReturn(true);
//        dataSource.setValidationQueryTimeout(1);
    dataSource.setRemoveAbandonedOnMaintenance(true);
    // dataSource.setEvictionPolicyClassName();
    dataSource.setFastFailValidation(true);
    dataSource.setTestOnCreate(true);
//        dataSource.setSoftMinEvictableIdleTimeMillis(100);
    dataSource.setValidationQuery("select 1");
    dataSource.setTestOnBorrow(true);
    dataSource.setRemoveAbandonedTimeout(100);
    dataSource.setRemoveAbandonedOnBorrow(true);
    dataSource.setMinEvictableIdleTimeMillis(3000);
    dataSource.setTimeBetweenEvictionRunsMillis(3000);
    dataSource.setTestWhileIdle(true);
    dataSource.setNumTestsPerEvictionRun(10);
    dataSource.setUrl("jdbc:mysql://localhost:3306/testdb0");
    dataSource.setPassword("jcw123");
    dataSource.setUsername("root");
    for(int i = 0; i < 5; i++) {
        new Thread(()->{
            while(true) {
                try {
                Connection connection = dataSource.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement("select * from testtable0 limit 1");
                ResultSet resultSet = preparedStatement.executeQuery();
                resultSet.next();
                System.out.println(resultSet.getInt(2));

                    Thread.sleep(1000);
                }catch (Exception e) {}
            }
        }, "tread" + i).start();
    }
}
```
