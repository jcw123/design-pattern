1. 核心的抽象类

- Writer
用于写字符流

- Reader
用于读字符流

- InputStream
用于读字节流

- OutputStream
用于写字节流

2. 具体实现方式

- Writer实现方式

- Reader实现方式
  - BufferedReader
  内部提供一个数组，支持临时缓存数据，然后从这个缓存数组取取数据；
  - LineNumberReader
  在BufferedReader的基础上，提供了新的可以获取行数和设置行数的方法；
  - CharArrayReader
  - InputStreamReader
  - FileReader
  - FilterReader
  - PushbackReader
  -

- InputStream实现方式

- OutputStream实现方式

注：
1. 常见的就是字节流和字符流，而流的输入和输出可以来源于各种地方，比如来源于网络、文件、标准输入输出、一个java对象等等。
这些东西都是可以自定义的。
2. java中实现字节流转换为字符流的一个类是InputStreamReader。
