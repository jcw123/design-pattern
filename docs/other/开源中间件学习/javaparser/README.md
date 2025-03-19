# javaparser

JavaParser是一个开源的Java库，用于解析和操作Java源代码。它提供了一个抽象语法树（AST）表示形式，可以让开发者在不直接处理字符串或字节码的情况下，分析、修改和生成Java代码。以下是JavaParser的主要架构组件：

Parser: 负责将Java源代码转换成抽象语法树（AST）。JavaParser支持Java 1到Java 19的语法。

AST (Abstract Syntax Tree): 是Java源代码的树形表示形式。每个节点代表源代码中的一个构造，如类、方法、变量等。AST是JavaParser的核心数据结构。

Node: AST中的每个节点都继承自Node类。节点可以是叶子节点（如标识符、文字等）或非叶子节点（如类声明、方法调用等）。每个节点都有自己的属性和方法。

Visitor Pattern: JavaParser使用访问者模式来遍历AST。这意味着开发者可以编写自己的访问者来处理特定的节点类型，从而实现自定义的代码分析或修改逻辑。

Code Generation: JavaParser可以将AST转换回Java源代码。这使得开发者可以在AST上进行修改，然后生成新的Java源代码。

Symbol Resolution: JavaParser提供了符号解析功能，可以将AST中的符号（如类名、方法名）解析到实际的Java元素上。

Utilities: JavaParser提供了一些实用工具，例如Utils类，帮助开发者执行常见的任务，如查找特定类型的节点或获取节点的父节点。

Parser Configuration: JavaParser允许配置解析器的行为，例如是否解析注释或是否支持Java 9+的模块系统。

Error Handling: JavaParser提供了错误处理机制，包括语法错误和解析错误。如果解析过程中出现错误，JavaParser会抛出相应的异常。

Integration: JavaParser可以与其他工具和框架集成，例如Maven、Gradle、Eclipse、IntelliJ IDEA等。

总的来说，JavaParser的架构设计旨在提供一个灵活、可扩展的平台，方便开发者在Java源代码上进行各种操作。

## 可以实现的功能
1. 动态分析源文件
2. 动态修改源文件
进行动态插装

## 参考文档
[使用方式](https://blog.csdn.net/weixin_42577140/article/details/139522634)
[官方文档](https://leanpub.com/javaparservisited/read_full)