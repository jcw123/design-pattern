#### IndexRequest核心参数

##### OpType

-  OpType.INDEX
索引，如果文档已存在，覆盖，内部版本号+1。

-  OpType.CREATE
创建，如果文档已存在，返回错误。

-  OpType.UPDATE
更新操作。

-  OpType.DELETE
删除操作。