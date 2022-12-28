参考文档：
1、https://www.runoob.com/linux/linux-vim.html
2、键位参考文档：https://www.runoob.com/w3cnote/all-vim-cheatsheat.html
[配置参考文档](https://www.freecodecamp.org/news/vimrc-configuration-guide-customize-your-vim-editor/)


1. 批量进行注释：
使用名命令格式： :起始行号,结束行号s/^/注释符/g（注意冒号）。
取消注释：
使用名命令格式： :起始行号,结束行号s/^注释符//g（注意冒号）

2. 查看vim所有可配置的选项
:set all

3. 更改vim注释的颜色
hi comment ctermfg=6
后面数组的可选值为 0 ~ 7


