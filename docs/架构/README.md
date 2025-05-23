# 架构能力

## 架构图模型
1. C4模型
- System Context
- Container
- Components
- Code
2. 4 + 1视图
- 逻辑视图
描述了系统的功能需求，展示了系统中各个组件和它们之间的关系。这个视图通常使用类图或对象图来表示
- 物理视图
展示了系统的静态组织结构，包括源代码、编译单元、库和框架等。这个视图通常使用组件图或包图来表示
- 开发视图
描述了系统的部署和硬件环境，展示了系统的物理分布、服务器、网络设备等。这个视图通常使用部署图或拓扑图来表示
- 过程视图
展示了系统中各个进程和线程的交互和同步机制，描述了系统的动态行为。这个视图通常使用流程图或状态机图来表示
- 用例视图
描述了系统的功能性需求和用户交互，展示了系统的用例图和相关的活动图

## 业务视图、技术视图、数据视图
业务视图 (Business View): 这个视图关注的是系统的业务逻辑和功能需求。它描述了系统如何支持组织的业务流程和目标。业务视图通常包含业务流程图、用例图和活动图等。

技术视图 (Technical View): 这个视图关注的是系统的技术实现和架构。它描述了系统的组件、模块和技术栈等。技术视图通常包含组件图、部署图和技术架构图等。

数据视图 (Data View): 这个视图关注的是系统中的数据模型和数据流。它描述了数据如何被存储、处理和传输。数据视图通常包含实体关系图、数据流图和数据库设计图等。

这三个视图之间的关系可以总结如下：

业务视图驱动技术和数据视图：业务需求和流程是设计系统技术架构和数据模型的基础。
技术视图支持业务视图：选择合适的技术和架构可以更好地实现业务功能和流程。
数据视图是业务和技术视图的桥梁：数据模型和数据流反映了业务逻辑和技术实现之间的交互。

## 不同视角下的架构图
### 业务视图 (Business View):
描述系统的业务逻辑和功能需求，关注如何支持组织的业务流程和目标。
相关的架构图有：
业务流程图 (BPMN)
用例图
活动图
价值流图

### 技术视图 (Technical View):
描述系统的技术实现和架构，关注系统的组件、模块和技术栈等。
相关的架构图有：
组件图
模块图
系统架构图
技术栈图

### 数据视图 (Data View):
描述系统中的数据模型和数据流，关注数据如何被存储、处理和传输。
相关的架构图有：
实体关系图 (ERD)
数据流图
数据库设计图
数据模型图

### 部署视图 (Deployment View):
描述系统的部署和运行环境，关注系统的物理配置和分布情况。
相关的架构图有：
部署图
网络拓扑图
服务器配置图
环境配置图

### 运行时视图 (Runtime View):
描述系统在运行时的行为和交互，关注系统的动态特性。
相关的架构图有：
进程图
线程图
交互图
状态机图

### 开发视图 (Development View):
描述系统的开发和维护过程，关注源代码结构和依赖关系。
相关的架构图有：
包图
依赖关系图
源代码结构图
版本控制图

## 如何培养架构能力
培养架构思维需要时间和实践，以下是一些建议：

了解基础知识：首先，你需要掌握相关的技术和工具，比如数据库设计、网络协议、操作系统原理等。这些知识将为你提供一个良好的基础，让你能够理解系统的各个组成部分。

阅读经典书籍：阅读经典的架构设计书籍，如《设计模式》、《企业应用架构模式》等，可以帮助你建立正确的架构思维模式。

参与项目实践：参与实际项目的开发过程，尤其是大型复杂系统的构建，可以让你在实践中学习如何设计和优化架构。

思考抽象问题：尝试从更高的层次去思考问题，例如考虑如何设计一个可扩展的系统，或者如何保证系统的高可用性。

关注新技术：时刻关注新的技术和趋势，比如云计算、微服务、容器化等，这些都可能对你的架构设计产生影响。

与同行交流：参加架构师社区的活动，与其他架构师交流经验和观点，可以帮助你拓宽视野，学习到不同的设计思路。

持续学习：保持好奇心，不断学习新知识，更新自己的技能和知识储备。

记住，架构思维不是一蹴而就的，它需要长期的积累和实践。

## 参考文章
[架构师的基本品质](https://mp.weixin.qq.com/s?__biz=MzA5NTU2NTY5MA==&mid=2247483830&idx=1&sn=a1b7ece445e6e844855e72e39a0b9682&chksm=90bc23a3a7cbaab500d65cca5038d606754ab6ef81a962eb9d341c45002b84198995da04bba1&cur_album_id=2164029508759126020&scene=189#wechat_redirect)
[如何画好一张架构图](https://mp.weixin.qq.com/s/y5qjTHyvy8brwogAjhS4vg)
[如何画一个有效的架构图](https://www.alibabacloud.com/blog/how-to-create-an-effective-technical-architectural-diagram_596100)
[模版社区](https://www.processon.com/template)