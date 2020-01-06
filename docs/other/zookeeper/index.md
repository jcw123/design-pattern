1、zookeeper是什么？
是一个开源的分布式协调服务，提供了一个基本的原语集合，分布式服务可以在此基础上构建高层次
的服务，用于实现同步、配置管理、组管理和命名空间。通过使用一个类似于文件系统的目录树结构使
编程非常方便。

2、zookeeper的底层数据模型
zookeeper有一个类似于分布式文件系统的垂直命名空间，但有点不同，是在命名空间的每一个节点都有与之关联的数据。

3、znode是是什么？
znode是zookeeper的核心，znode不是表示一个服务节点，而是在存储数据的一个节点。

4、会话
如果一个连接建立之后，将会创建一个会话，此时的状态是CONNECTED，但是如果在连接过程出现权限验证失败，或者会话过期，
状态会转为CLOSED。

5、Watcher
watcher涉及三个主要的关键点：
- One-time trigger:只触发一次
- Sent to the client:如果wach事件没有到达客户端，数据的变化客户端是看不到的。
-The data for which the watch was set：可以表明是哪个操作触发的watcher
> 事件的分发是有顺序的；在看到一份新数据到达节点之前，会先收到一个watch事件；wacher事件
的顺序是和服务看到的数据更新的数据一致的。

6、ACL
> 权限控制

- CREATE
- READ
- WRITE
- DELETE
- ADMIN

7、zookeeper的分布式锁、配置服务、命名空间等如何实现的？
（1）分布式协调
当A系统想观察B系统某一个事件是否执行完成，A系统可以观察一个znode节点的变化，当B系统执行完成
后修改znode节点的值，A系统自然就能收到（有点类似于事件驱动，注册，通知）
（2）分布式锁
（3）元数据/配置信息管理

8、paxos算法是什么？
少数服从多数，最终达成一致性意见。算法本身还是很难理解。
系统中的角色可以分为提议者（Proposer）、决策者（Accepter）、最终学习者（Learner）。
在多副本中，一个副本可能会同时承担三个角色。

- Propose: Proposer 收到多数Acceptors的Promise应答后，从应答中选择Proposal ID最大的提案的Value，作为本次要发起的提案。如果所有应答的提案Value均为空值，则可以自己随意决定提案Value。然后携带当前Proposal ID，向所有Acceptors发送Propose请求。
- Accept: Acceptor收到Propose请求后，在不违背自己之前作出的承诺下，接受并持久化当前Proposal ID和提案Value。
- Learn: Proposer收到多数Acceptors的Accept后，决议形成，将形成的决议发送给所有Learners。

9、ZAB协议？
