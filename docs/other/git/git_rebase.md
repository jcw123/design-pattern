# git rebase
> 重置分支的基底

使用说明：
git rebase [-i | --interactive] [<options>] [--exec <cmd>]
	[--onto <newbase> | --keep-base] [<upstream> [<branch>]]
git rebase [-i | --interactive] [<options>] [--exec <cmd>] [--onto <newbase>]
	--root [<branch>]
git rebase (--continue | --skip | --abort | --quit | --edit-todo | --show-current-patch)

git rebase -i HEAD~n : 交互式操作，用户选择如何操作。

git rebase upstream [branch]

git rebase --onto upstream Abranch Bbranch


参数说明：
（1）--onto branch
相当于将分支重置到这个branch上，相当于执行了git reset --hard branch
(2)如果不传--onto，会以upstream为基底，如果upstream也不传，会以配置中的upstream为基底。

### Examples

- git rebase --onto master test1 test2
> git rebase --onto newbase upstream branch

此条命令是最完整的写法，将test2相当于test1的改变存放到一个临时区域，然后再master分支重新应用这些改变；
--onto newbase不写的话，默认是upstream；upstream不写的话默认是当前分支，branch不写的话默认是当前分支；
