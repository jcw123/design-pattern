# ContextLoaderListener

## 主要功能
1. 初始化 Spring 应用上下文：ContextLoaderListener 在 Web 应用程序启动时被调用，它会创建并初始化 Spring 的根应用上下文。
2. 管理应用程序生命周期：它在应用程序关闭时会自动销毁 Spring 应用上下文，释放资源。
3. 与 Web 应用整合：通常与 DispatcherServlet 配合使用，DispatcherServlet 处理 Web 请求，而 ContextLoaderListener 管理应用程序范围的 Bean。