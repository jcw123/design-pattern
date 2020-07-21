#### ulimit

Modify shell resource limits.
Provides control over the resources available to the shell and processes
it creates, on systems that allow such control.

Options:
  -S        use the `soft' resource limit
  -H        use the `hard' resource limit
  -a        all current limits are reported
  -b        the socket buffer size
  -c        the maximum size of core files created
  -d        the maximum size of a process's data segment
  -e        the maximum scheduling priority (`nice')
  -f        the maximum size of files written by the shell and its children
  -i        the maximum number of pending signals
  -k        the maximum number of kqueues allocated for this process
  -l        the maximum size a process may lock into memory
  -m        the maximum resident set size
  -n        the maximum number of open file descriptors
  -p        the pipe buffer size
  -q        the maximum number of bytes in POSIX message queues
  -r        the maximum real-time scheduling priority
  -s        the maximum stack size
  -t        the maximum amount of cpu time in seconds
  -u        the maximum number of user processes
  -v        the size of virtual memory
  -x        the maximum number of file locks
  -P        the maximum number of pseudoterminals
  -T        the maximum number of threads
