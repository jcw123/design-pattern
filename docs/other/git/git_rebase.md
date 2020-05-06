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
(2)如果不传--onto，会议upstream为基底，如果upstream也不传，会以配置中的upstream为基底。
