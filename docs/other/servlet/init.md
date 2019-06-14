## Servlet

一、 主要方法
1. init
初始化时有servlet容器进行调用，表名此servlet放入到服务中。只会调用一次
2. getServletConfig
获取servlet初始化时的配置信息
3. service
当对客户端的请求进行相应时，调用此方法
4. getServletInfo
返回此servlet的基本信息
5. destroy
当servlet需要从服务中退出时，就调用此方法，只会调用一次

## GenericServlet

1、实现了Servlet、ServletConfig接口
2、除了service方法是抽象方法，其余方法都提供了默认实现
