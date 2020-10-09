##### SPI
Service Provider Interface (SPI) is an API intended to be implemented or extended by a third party. It can be used to enable framework extension and replaceable components
> 定义一个接口，具体实现由第三方类库来做。会存在一个服务发现加载类，在特定的目录下查找接口的具体实现；

SPI思想挺好，关键点就是服务发现，定义解析规则获取具体的实现类；
