1. uptime
查看系统负载
10:52:21 up  5:29,  2 users,  load average: 0.00, 0.00, 0.00

注：linux计算平均负载时，也会把IO等待的线程纳入计算；

2. PCB（process control block）
进程控制块，结构体task_struct是进程的物理表示，存储了大量的和进程有关的信息，一个进程映射为
这种结构的一个实例；

3. 平均负载的分析文章
https://zhuanlan.zhihu.com/p/80738361

4. top
  Z,B       Global: 'Z' change color mappings; 'B' disable/enable bold
  l,t,m     Toggle Summaries: 'l' load avg; 't' task/cpu stats; 'm' mem info
  1,I       Toggle SMP view: '1' single/separate states; 'I' Irix/Solaris mode
  f,o     . Fields/Columns: 'f' add or remove; 'o' change display order
  F or O  . Select sort field
  <,>     . Move sort field: '<' next col left; '>' next col right
  R,H     . Toggle: 'R' normal/reverse sort; 'H' show threads
  c,i,S   . Toggle: 'c' cmd name/line; 'i' idle tasks; 'S' cumulative time
  x,y     . Toggle highlights: 'x' sort field; 'y' running tasks
  z,b     . Toggle: 'z' color/mono; 'b' bold/reverse (only if 'x' or 'y')
  u       . Show specific user only
  n or #  . Set maximum tasks displayed
  k,r       Manipulate tasks: 'k' kill; 'r' renice
  d or s    Set update interval
  W         Write configuration file
  q         Quit

  5. ps
  ********* simple selection *********  ********* selection by list *********
-A all processes                      -C by command name
-N negate selection                   -G by real group ID (supports names)
-a all w/ tty except session leaders  -U by real user ID (supports names)
-d all except session leaders         -g by session OR by effective group name
-e all processes                      -p by process ID
T  all processes on this terminal     -s processes in the sessions given
a  all w/ tty, including other users  -t by tty
g  OBSOLETE -- DO NOT USE             -u by effective user ID (supports names)
r  only running processes             U  processes for specified users
x  processes w/o controlling ttys     t  by tty
*********** output format **********  *********** long options ***********
-o,o user-defined  -f full            --Group --User --pid --cols --ppid
-j,j job control   s  signal          --group --user --sid --rows --info
-O,O preloaded -o  v  virtual memory  --cumulative --format --deselect
-l,l long          u  user-oriented   --sort --tty --forest --version
-F   extra full    X  registers       --heading --no-heading --context
                    ********* misc options *********
-V,V  show version      L  list format codes  f  ASCII art forest
-m,m,-L,-T,H  threads   S  children in sum    -y change -l format
-M,Z  security data     c  true command name  -c scheduling class
-w,w  wide output       n  numeric WCHAN,UID  -H process hierarchy

6. netstat
usage: netstat [-veenNcCF] [<Af>] -r         netstat {-V|--version|-h|--help}
       netstat [-vnNcaeol] [<Socket> ...]
       netstat { [-veenNac] -I[<Iface>] | [-veenNac] -i | [-cnNe] -M | -s } [delay]

        -r, --route                display routing table
        -I, --interfaces=<Iface>   display interface table for <Iface>
        -i, --interfaces           display interface table
        -g, --groups               display multicast group memberships
        -s, --statistics           display networking statistics (like SNMP)
        -M, --masquerade           display masqueraded connections

        -v, --verbose              be verbose
        -n, --numeric              don't resolve names
        --numeric-hosts            don't resolve host names
        --numeric-ports            don't resolve port names
        --numeric-users            don't resolve user names
        -N, --symbolic             resolve hardware names
        -e, --extend               display other/more information
        -p, --programs             display PID/Program name for sockets
        -c, --continuous           continuous listing

        -l, --listening            display listening server sockets
        -a, --all, --listening     display all sockets (default: connected)
        -o, --timers               display timers
        -F, --fib                  display Forwarding Information Base (default)
        -C, --cache                display routing cache instead of FIB
        -T, --notrim               stop trimming long addresses
        -Z, --context              display SELinux security context for sockets
