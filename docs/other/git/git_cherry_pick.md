# git cherry-pick
> 选择几个commit到当前分支上。

基本语法：
git cherry-pick [--edit] [-n] [-m parent-number] [-s] [-x] [--ff]
		  [-S[<keyid>]] <commit>…​
git cherry-pick (--continue | --skip | --abort | --quit)

git checkout master
git cherry pick commitid

git cherry start-commitId  end-commitid  （左边是开区间）

git cherry start-commitId^ end-commitId   (左边是闭区间)
