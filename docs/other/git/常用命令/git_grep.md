#### Name
git-grep - Print lines matching a pattern\

#### SYNOSIS
git grep [-a | --text] [-I] [--textconv] [-i | --ignore-case] [-w | --word-regexp]
	   [-v | --invert-match] [-h|-H] [--full-name]
	   [-E | --extended-regexp] [-G | --basic-regexp]
	   [-P | --perl-regexp]
	   [-F | --fixed-strings] [-n | --line-number]
	   [-l | --files-with-matches] [-L | --files-without-match]
	   [(-O | --open-files-in-pager) [<pager>]]
	   [-z | --null]
	   [-c | --count] [--all-match] [-q | --quiet]
	   [--max-depth <depth>]
	   [--color[=<when>] | --no-color]
	   [--break] [--heading] [-p | --show-function]
	   [-A <post-context>] [-B <pre-context>] [-C <context>]
	   [-W | --function-context]
	   [--threads <num>]
	   [-f <file>] [-e] <pattern>
	   [--and|--or|--not|(|)|-e <pattern>…​]
	   [--recurse-submodules] [--parent-basename <basename>]
	   [ [--[no-]exclude-standard] [--cached | --no-index | --untracked] | <tree>…​]
	   [--] [<pathspec>…​]

#### DESCRIPTION
Look for specified patterns in the tracked files in the work tree, blobs registered in the index file, or blobs in given tree objects. Patterns are lists of one or more search expressions separated by newline characters. An empty string as search expression matches all lines.

#### CONFIGURATION
balabala...

#### OPTIONS
balabala...

#### Examples
- git grep 'time_t' -- '*.[ch]'
Looks for time_t in all tracked .c and .h files in the working directory and its subdirectories.

- git grep -e '#define' --and \( -e MAX_PATH -e PATH_MAX \)
Looks for a line that has #define and either MAX_PATH or PATH_MAX.

- git grep --all-match -e NODE -e Unexpected
Looks for a line that has NODE or Unexpected in files that have lines that match both.

- git grep solution -- :^Documentation
Looks for solution, excluding files in Documentation.

#### REMARK
- 通用正则表达式匹配行
