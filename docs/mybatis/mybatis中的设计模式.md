
## Builder模式
> 对象的构建过程过于复杂，可以使用建造者模式，将对象的创建过程和表示过程相分离。

- MapperAnnotationBuilder
  Mapper的注解构建者。当在配置文件中直接定义下面的语句时，就需要通过这个构建器进行注解解析，生成最终的结构化映射对象。
  ```xml
  <mapper class="com.im.sky.mybatis.GenericDao"/>
  ```
  关键方法如下：
  ```java
  public void parse() {
  String resource = type.toString();
  if (!configuration.isResourceLoaded(resource)) {
    loadXmlResource();
    configuration.addLoadedResource(resource);
    assistant.setCurrentNamespace(type.getName());
    parseCache();
    parseCacheRef();
    Method[] methods = type.getMethods();
    for (Method method : methods) {
      try {
        // issue #237
        if (!method.isBridge()) {
          parseStatement(method);
        }
      } catch (IncompleteElementException e) {
        configuration.addIncompleteMethod(new MethodResolver(this, method));
      }
    }
  }
  parsePendingMethods();
}
  ```

- XMLStatementBuilder
  用于解析mapper文件中单条配置信息
  ```java
  public void parseStatementNode() {
  String id = context.getStringAttribute("id");
  String databaseId = context.getStringAttribute("databaseId");

  if (!databaseIdMatchesCurrent(id, databaseId, this.requiredDatabaseId)) {
    return;
  }

  Integer fetchSize = context.getIntAttribute("fetchSize");
  Integer timeout = context.getIntAttribute("timeout");
  String parameterMap = context.getStringAttribute("parameterMap");
  String parameterType = context.getStringAttribute("parameterType");
  Class<?> parameterTypeClass = resolveClass(parameterType);
  String resultMap = context.getStringAttribute("resultMap");
  String resultType = context.getStringAttribute("resultType");
  String lang = context.getStringAttribute("lang");
  LanguageDriver langDriver = getLanguageDriver(lang);

  Class<?> resultTypeClass = resolveClass(resultType);
  String resultSetType = context.getStringAttribute("resultSetType");
  StatementType statementType = StatementType.valueOf(context.getStringAttribute("statementType", StatementType.PREPARED.toString()));
  ResultSetType resultSetTypeEnum = resolveResultSetType(resultSetType);

  String nodeName = context.getNode().getNodeName();
  SqlCommandType sqlCommandType = SqlCommandType.valueOf(nodeName.toUpperCase(Locale.ENGLISH));
  boolean isSelect = sqlCommandType == SqlCommandType.SELECT;
  boolean flushCache = context.getBooleanAttribute("flushCache", !isSelect);
  boolean useCache = context.getBooleanAttribute("useCache", isSelect);
  boolean resultOrdered = context.getBooleanAttribute("resultOrdered", false);

  // Include Fragments before parsing
  XMLIncludeTransformer includeParser = new XMLIncludeTransformer(configuration, builderAssistant);
  includeParser.applyIncludes(context.getNode());

  // Parse selectKey after includes and remove them.
  processSelectKeyNodes(id, parameterTypeClass, langDriver);

  // Parse the SQL (pre: <selectKey> and <include> were parsed and removed)
  SqlSource sqlSource = langDriver.createSqlSource(configuration, context, parameterTypeClass);
  String resultSets = context.getStringAttribute("resultSets");
  String keyProperty = context.getStringAttribute("keyProperty");
  String keyColumn = context.getStringAttribute("keyColumn");
  KeyGenerator keyGenerator;
  String keyStatementId = id + SelectKeyGenerator.SELECT_KEY_SUFFIX;
  keyStatementId = builderAssistant.applyCurrentNamespace(keyStatementId, true);
  if (configuration.hasKeyGenerator(keyStatementId)) {
    keyGenerator = configuration.getKeyGenerator(keyStatementId);
  } else {
    keyGenerator = context.getBooleanAttribute("useGeneratedKeys",
        configuration.isUseGeneratedKeys() && SqlCommandType.INSERT.equals(sqlCommandType))
        ? Jdbc3KeyGenerator.INSTANCE : NoKeyGenerator.INSTANCE;
  }

  builderAssistant.addMappedStatement(id, sqlSource, statementType, sqlCommandType,
      fetchSize, timeout, parameterMap, parameterTypeClass, resultMap, resultTypeClass,
      resultSetTypeEnum, flushCache, useCache, resultOrdered,
      keyGenerator, keyProperty, keyColumn, databaseId, langDriver, resultSets);
}
  ```

- XMLMapperBuilder

用于解析单个Mapper文件，关键方法如下：
  ```java
public void parse() {
    if (!configuration.isResourceLoaded(resource)) {
      configurationElement(parser.evalNode("/mapper"));
      configuration.addLoadedResource(resource);
      bindMapperForNamespace();
    }

    parsePendingResultMaps();
    parsePendingCacheRefs();
    parsePendingStatements();
  }

private void configurationElement(XNode context) {
    try {
      String namespace = context.getStringAttribute("namespace");
      if (namespace == null || namespace.equals("")) {
        throw new BuilderException("Mapper's namespace cannot be empty");
      }
      builderAssistant.setCurrentNamespace(namespace);
      cacheRefElement(context.evalNode("cache-ref"));
      cacheElement(context.evalNode("cache"));
      parameterMapElement(context.evalNodes("/mapper/parameterMap"));
      resultMapElements(context.evalNodes("/mapper/resultMap"));
      sqlElement(context.evalNodes("/mapper/sql"));
      buildStatementFromContext(context.evalNodes("select|insert|update|delete"));
    } catch (Exception e) {
      throw new BuilderException("Error parsing Mapper XML. The XML location is '" + resource + "'. Cause: " + e, e);
    }
  }
  ```


- XMLConfigBuilder
用于解析mybatis的配置文件，关键代码如下：

```java
public Configuration parse() {
    if (parsed) {
      throw new BuilderException("Each XMLConfigBuilder can only be used once.");
    }
    parsed = true;
    parseConfiguration(parser.evalNode("/configuration"));
    return configuration;
  }

private void parseConfiguration(XNode root) {
  try {
    //issue #117 read properties first
    propertiesElement(root.evalNode("properties"));
    Properties settings = settingsAsProperties(root.evalNode("settings"));
    loadCustomVfs(settings);
    typeAliasesElement(root.evalNode("typeAliases"));
    pluginElement(root.evalNode("plugins"));
    objectFactoryElement(root.evalNode("objectFactory"));
    objectWrapperFactoryElement(root.evalNode("objectWrapperFactory"));
    reflectorFactoryElement(root.evalNode("reflectorFactory"));
    settingsElement(settings);
    // read it after objectFactory and objectWrapperFactory issue #631
    environmentsElement(root.evalNode("environments"));
    databaseIdProviderElement(root.evalNode("databaseIdProvider"));
    typeHandlerElement(root.evalNode("typeHandlers"));
    mapperElement(root.evalNode("mappers"));
  } catch (Exception e) {
    throw new BuilderException("Error parsing SQL Mapper Configuration. Cause: " + e, e);
  }
}
```

上面几个构建者的调用顺序主要是，先通过XMLConfigBuilder构建器解析mybatis的配置文件，然后解析到mappers属性时，会调用XMLMapperBuilder或者MapperAnnotationBuilder进行基于xml文件的配置解析或者基于注解的配置解析。然后解析到单条配置信息时，会调用XMLStatementBuilder进行配置的解析。

## 工厂模式
三个主要的工厂类：MapperProxyFactory、ObjectFactory、SqlSessionFactory。

- MapperProxyFactory
```java
@SuppressWarnings("unchecked")
  protected T newInstance(MapperProxy<T> mapperProxy) {
    return (T) Proxy.newProxyInstance(mapperInterface.getClassLoader(), new Class[] { mapperInterface }, mapperProxy);
  }

  // 生成新的实例，通过代理方式构建
  public T newInstance(SqlSession sqlSession) {
    final MapperProxy<T> mapperProxy = new MapperProxy<>(sqlSession, mapperInterface, methodCache);
    return newInstance(mapperProxy);
  }
```

- ObjectFactory
> 普通对象的创建类，这是一个接口，看看其提供的默认实现DefaultObjectFactory
```java
// 内部就是通过发射实例化对象的
public <T> T create(Class<T> type, List<Class<?>> constructorArgTypes, List<Object> constructorArgs) {
    Class<?> classToCreate = resolveInterface(type);
    // we know types are assignable
    return (T) instantiateClass(classToCreate, constructorArgTypes, constructorArgs);
  }
```

- SqlSessionFactory
> 提供了openSession很多的重载方法，用于获取一个SqlSession对象，可以认为一个SqlSession关联一个数据库连接，进行数据库操作是通过Executor来进行的，内部关联一个Transaction，控制Connection的生命周期。
```java
@Override
  public SqlSession openSession() {
    return openSessionFromDataSource(configuration.getDefaultExecutorType(), null, false);
  }
```

## 单例模式
主要的类包括：ErrorContext（其实也不是单例，只是将实例化交于内部方法实现了）、LogFactory。

- ErrorContext
跟踪调用的上下文


```java
// 私有
private ErrorContext() {
}

//内部调用生成
public static ErrorContext instance() {
  ErrorContext context = LOCAL.get();
  if (context == null) {
    context = new ErrorContext();
    LOCAL.set(context);
  }
  return context;
}

public ErrorContext store() {
  ErrorContext newContext = new ErrorContext();
  newContext.stored = this;
  LOCAL.set(newContext);
  return LOCAL.get();
}
```

- LoggerFactory


```java
private LogFactory() {
  // disable construction
}

public static Log getLog(Class<?> aClass) {
  return getLog(aClass.getName());
}

public static Log getLog(String logger) {
  try {
    return logConstructor.newInstance(logger);
  } catch (Throwable t) {
    throw new LogException("Error creating logger for logger " + logger + ".  Cause: " + t, t);
  }
}
```

## 代理模式
主要的类包括：MapperProxy、ConnectionLogger、CglibProxyFactory、JavassistProxyFactory等。
> 上面几个类使用JDK、CGLIB、Javassist代理。具体代码可以自己研究。


```java
// MapperProxy的部分代码，实现了InvocationHandler接口。
@Override
  public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
    try {
      if (Object.class.equals(method.getDeclaringClass())) {
        return method.invoke(this, args);
      } else if (isDefaultMethod(method)) {
        return invokeDefaultMethod(proxy, method, args);
      }
    } catch (Throwable t) {
      throw ExceptionUtil.unwrapThrowable(t);
    }
    final MapperMethod mapperMethod = cachedMapperMethod(method);
    return mapperMethod.execute(sqlSession, args);
  }
```

## 组合模式
主要的类包括：SqlNode和其各个子类等。
```java
// 接口
public interface SqlNode {
  boolean apply(DynamicContext context);
}

// SqlNode的一个子类
public class MixedSqlNode implements SqlNode {
  private final List<SqlNode> contents;

  public MixedSqlNode(List<SqlNode> contents) {
    this.contents = contents;
  }

  @Override
  public boolean apply(DynamicContext context) {
    for (SqlNode sqlNode : contents) {
      sqlNode.apply(context);
    }
    return true;
  }
}
```

## 模板方法模式
> 例如BaseTypeHandler类，提供了一个基本的实现和模板，部分方法需要在子类中实现。

```java
@Override
  public T getResult(ResultSet rs, String columnName) throws SQLException {
    try {
      // getNullableResult方法需要在子类中实现。
      return getNullableResult(rs, columnName);
    } catch (Exception e) {
      throw new ResultMapException("Error attempting to get column '" + columnName + "' from result set.  Cause: " + e, e);
    }
  }
```

## 适配器模式
在mybatis中，对Log的实现是适配器模式的典型应用，将不同的日志实现基本通过适配器模式全部集成了过来。

mybatis自己定义了一个Log接口
```java
public interface Log {

  boolean isDebugEnabled();

  boolean isTraceEnabled();

  void error(String s, Throwable e);

  void error(String s);

  void debug(String s);

  void trace(String s);

  void warn(String s);
}
```
其中一个对Slf4j2的适配实现如下：
```java
class Slf4jLoggerImpl implements Log {

  private final Logger log;

  public Slf4jLoggerImpl(Logger logger) {
    log = logger;
  }

  @Override
  public boolean isDebugEnabled() {
    return log.isDebugEnabled();
  }

  @Override
  public boolean isTraceEnabled() {
    return log.isTraceEnabled();
  }

  @Override
  public void error(String s, Throwable e) {
    log.error(s, e);
  }

  @Override
  public void error(String s) {
    log.error(s);
  }

  @Override
  public void debug(String s) {
    log.debug(s);
  }

  @Override
  public void trace(String s) {
    log.trace(s);
  }

  @Override
  public void warn(String s) {
    log.warn(s);
  }

}
```

## 装饰器模式
cache.decorators包下的Cache接口的实现类是典型的装饰器的实现方式，通过组合的方式，给Cache进行一定的细节处理，比如配置出入队策略、加锁、同步等小功能。

例如BlockingCache：
```java
// 部分代码如下，借助ReentrantLock实现加锁功能
public class BlockingCache implements Cache {

  private long timeout;
  private final Cache delegate;
  private final ConcurrentHashMap<Object, ReentrantLock> locks;

  public BlockingCache(Cache delegate) {
    this.delegate = delegate;
    this.locks = new ConcurrentHashMap<>();
  }
}
```

## 迭代器模式
PropertyTokenizer这个类是迭代器模式的一个实现。
```java
public class PropertyTokenizer implements Iterator<PropertyTokenizer> {
  private String name;
  private final String indexedName;
  private String index;
  private final String children;

  public PropertyTokenizer(String fullname) {
    int delim = fullname.indexOf('.');
    if (delim > -1) {
      name = fullname.substring(0, delim);
      children = fullname.substring(delim + 1);
    } else {
      name = fullname;
      children = null;
    }
    indexedName = name;
    delim = name.indexOf('[');
    if (delim > -1) {
      index = name.substring(delim + 1, name.length() - 1);
      name = name.substring(0, delim);
    }
  }

  public String getName() {
    return name;
  }

  public String getIndex() {
    return index;
  }

  public String getIndexedName() {
    return indexedName;
  }

  public String getChildren() {
    return children;
  }

  @Override
  public boolean hasNext() {
    return children != null;
  }

  @Override
  public PropertyTokenizer next() {
    return new PropertyTokenizer(children);
  }

  @Override
  public void remove() {
    throw new UnsupportedOperationException("Remove is not supported, as it has no meaning in the context of properties.");
  }
}
```

## 总结：

mybatis中使用的设计模式很多，不管是使用哪个设计模式，我们都需要思考使用这种设计模式有什么好处，如果不使用这种设计模式应该怎么写，会不会导致代码很臃肿。

1、上面设计的设计模式主要包括：建造者模式、工厂模式、单例模式、模板方法模式、组合模式、代理模式、适配器模式、装饰器模式、迭代器模式。

2、什么时候使用？
- 建造者模式
如果对象的构建过程很复杂，并且易变，不如采用建造者模式。lombok的jar包中就提供了一个自动生成建造者对象的注解。


- 工厂模式
工厂模式易于管理对象实例，甚至有时可以将工厂想象为一个容器。

- 单例模式
一个实例在多线程中不会遇到线程安全问题，可以考虑使用单例，像工具类等都是单例，spring的bean默认也是单例。

- 模板方法模式
如果一个行为可以分为多个步骤，这些步骤的顺序是固定的，只是有的步骤可以定制化，则可以采用模板方法模式。

- 组合模式
如果感觉有必要将一个对象和一个对象的组合看做是实现相同的接口，可以考虑采用这种模式，组合模式对象感觉有点像树结构，将叶子节点和非叶子节点同等看待。

- 代理模式
主要是对对象进行控制，代理层稍微做了比较多的东西，目前除了框架中看到外，平常业务中基本用不到代理模式。
- 适配器模式
这个模式使用的多，功能已经有了，但是向外暴露的接口和已实现功能的接口不一致，这时适配器就派上用场了。

- 装饰器模式
给对象添加些小功能，和代理模式结构很类似。

- 迭代器模式
有必要遍历对象时，可以考虑迭代器模式
