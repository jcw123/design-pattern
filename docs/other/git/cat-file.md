#### NAME
git-cat-file - Provide content or type and size information for repository objects

#### SYNOSIS
git cat-file (-t [--allow-unknown-type]| -s [--allow-unknown-type]| -e | -p | <type> | --textconv | --filters ) [--path=<path>] <object>
git cat-file (--batch | --batch-check) [ --textconv | --filters ] [--follow-symlinks]

> 可用来查看.git/objects中文件的类型，打印文件中的内容和查询文件的大小等等。

#### REMARK
可以用于查看一个commit具体的信息，比如类型、大小、内容等等，很实用的一个工具；
