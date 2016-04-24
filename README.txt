Group 34
STEPHANIE HUANG <syh2115@columbia.edu>
SAMUEL NNODIM <son2105@columbia.edu>
RAJIV THAMBURAJ <rjt2132@columbia.edu>


COMMIT IDs

Commit IDs go here...


PART 1 WRITTEN ANSWERS

The test program for this part was written in C - it is located in the test
directory under the TOP, and is called myprogram.c (a Makefile is supplied as
well). This program is invoked as follows:

./myprogram <num_processes> <nice>

The above command will fork <num_processes> children and assign the given nice
value to these processes. The program uses a #define statement to run all
instances on CPU 2. Note that, in order to get the scheduler to recognize these
nice values, we had to disable autogrouping with the following command:

sudo sysctl kernel.sched_autogroup_enabled=0

In order to accomplish the first task, we started up two instances of myprogram
with nice values of 11 and 15 as follows:

./myprogram 5 11
./myprogram 5 15

Here is the top output for that session:

top - 02:45:44 up 57 min,  1 user,  load average: 10.01, 9.83, 9.35
Tasks: 151 total,  11 running, 140 sleeping,   0 stopped,   0 zombie
%Cpu0  :   4.7/0.0     5[|||||                                                                                               ]
%Cpu1  :   0.7/0.0     1[|                                                                                                   ]
%Cpu2  : 100.0/0.0   100[||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||]
%Cpu3  :   0.0/0.0     0[                                                                                                    ]
GiB Mem :  6.4/3.457    [                                                                                                    ]
GiB Swap:  0.0/0.000    [                                                                                                    ]

  PID USER      PR  NI    VIRT    RES  %CPU %MEM     TIME+ S COMMAND
  311 rajiv     20   0   44.6m  13.8m   0.0  0.4   0:00.30 S                  `- xfce4-session
  349 rajiv     20   0   58.3m  22.0m   1.3  0.6   0:10.59 S                      `- xfce4-terminal
  491 rajiv     20   0    5.6m   3.3m   0.0  0.1   0:00.05 S                          `- bash
 1028 rajiv     20   0    2.1m   0.6m   0.0  0.0   0:00.00 S                              `- myprogram
 1029 rajiv     31  11    2.0m   0.1m  14.7  0.0   1:59.84 R                                  `- myprogram
 1030 rajiv     31  11    2.1m   0.1m  14.0  0.0   1:59.84 R                                  `- myprogram
 1031 rajiv     31  11    2.1m   0.1m  14.0  0.0   1:59.84 R                                  `- myprogram
 1032 rajiv     31  11    2.1m   0.1m  14.0  0.0   1:59.84 R                                  `- myprogram
 1033 rajiv     31  11    2.1m   0.1m  14.7  0.0   1:59.84 R                                  `- myprogram
  640 rajiv     20   0    5.5m   3.4m   0.0  0.1   0:00.01 S                          `- bash
 1034 rajiv     20   0    2.1m   0.5m   0.0  0.0   0:00.00 S                              `- myprogram
 1035 rajiv     35  15    2.0m   0.0m   6.0  0.0   0:48.82 R                                  `- myprogram
 1036 rajiv     35  15    2.1m   0.0m   6.0  0.0   0:48.82 R                                  `- myprogram
 1037 rajiv     35  15    2.1m   0.0m   5.3  0.0   0:48.81 R                                  `- myprogram
 1038 rajiv     35  15    2.1m   0.0m   6.0  0.0   0:48.82 R                                  `- myprogram
 1039 rajiv     35  15    2.1m   0.0m   5.3  0.0   0:48.82 R                                  `- myprogram

In order to accomplish the second task, we retained the first two instances of
myprogram and added another instance with a nice value of 19 (this value is
arbitrary) as follows:

./myprogram 1 19

Then, we used the following command to make the new instance have
real-time priority:

sudo chrt -r -p 1 <pid>

Note that ROOT PERMISSION WAS REQUIRED to assign this priority. Here is the top
output for that session:

top - 16:42:39 up 11 min,  1 user,  load average: 10.85, 6.80, 2.97
Tasks: 150 total,  13 running, 137 sleeping,   0 stopped,   0 zombie
%Cpu0  :   0.7/0.0     1[|                                                                                                   ]
%Cpu1  :   0.0/0.0     0[                                                                                                    ]
%Cpu2  : 100.0/0.0   100[||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||]
%Cpu3  :   0.0/0.0     0[                                                                                                    ]
GiB Mem :  7.8/3.457    [                                                                                                    ]
GiB Swap:  0.0/0.000    [                                                                                                    ]

  PID USER      PR  NI    VIRT    RES  %CPU %MEM     TIME+ S COMMAND
  348 rajiv     20   0   44.6m  13.6m   0.0  0.4   0:00.13 S                  `- xfce4-session
  401 rajiv     20   0   57.5m  25.2m   0.0  0.7   0:02.83 S                      `- xfce4-terminal
  499 rajiv     20   0    5.5m   3.4m   0.0  0.1   0:00.01 S                          `- bash
  703 rajiv     20   0    2.1m   0.5m   0.0  0.0   0:00.00 S                              `- myprogram
  704 rajiv     31  11    2.0m   0.0m   0.0  0.0   0:24.39 R                                  `- myprogram
  705 rajiv     31  11    2.1m   0.1m   0.0  0.0   0:24.39 R                                  `- myprogram
  706 rajiv     31  11    2.1m   0.1m   0.0  0.0   0:24.40 R                                  `- myprogram
  707 rajiv     31  11    2.1m   0.1m   0.0  0.0   0:24.39 R                                  `- myprogram
  708 rajiv     31  11    2.1m   0.1m   0.0  0.0   0:24.40 R                                  `- myprogram
  642 rajiv     20   0    5.5m   3.4m   0.0  0.1   0:00.01 S                          `- bash
  709 rajiv     20   0    2.1m   0.5m   0.0  0.0   0:00.00 S                              `- myprogram
  710 rajiv     35  15    2.0m   0.0m   0.0  0.0   0:10.01 R                                  `- myprogram
  711 rajiv     35  15    2.1m   0.1m   0.0  0.0   0:10.02 R                                  `- myprogram
  712 rajiv     35  15    2.1m   0.1m   0.0  0.0   0:10.01 R                                  `- myprogram
  713 rajiv     35  15    2.1m   0.1m   0.0  0.0   0:10.01 R                                  `- myprogram
  714 rajiv     35  15    2.1m   0.1m   0.0  0.0   0:10.02 R                                  `- myprogram
  722 rajiv     20   0    5.6m   3.5m   0.0  0.1   0:00.01 S                          `- bash
  728 rajiv     20   0    2.1m   0.5m   0.0  0.0   0:00.00 S                              `- myprogram
  729 rajiv     -2  19    2.0m   0.0m 100.0  0.0   0:38.81 R                                  `- myprogram


PART 2 WRITTEN ANSWERS

Here is the diff of the two config files:

48a49
> CONFIG_SCHED_BFS=y
52c53
< CONFIG_LOCALVERSION="-rjt2132"
---
> CONFIG_LOCALVERSION="-rjt2132-bfs"
112,113c113
< CONFIG_TICK_CPU_ACCOUNTING=y
< # CONFIG_IRQ_TIME_ACCOUNTING is not set
---
> CONFIG_IRQ_TIME_ACCOUNTING=y
134d133
< # CONFIG_RCU_NOCB_CPU is not set
148d146
< CONFIG_CGROUP_CPUACCT=y
156,159d153
< CONFIG_CGROUP_SCHED=y
< CONFIG_FAIR_GROUP_SCHED=y
< CONFIG_CFS_BANDWIDTH=y
< # CONFIG_RT_GROUP_SCHED is not set
169d162
< CONFIG_SCHED_AUTOGROUP=y
221d213
< # CONFIG_SLAB is not set
423a416
> CONFIG_SMT_NICE=y
532,533d524
< # CONFIG_BOOTPARAM_HOTPLUG_CPU0 is not set
< # CONFIG_DEBUG_HOTPLUG_CPU0 is not set
3687d3677
< # CONFIG_RCU_TORTURE_TEST is not set

We were successfully able to patch and build a BFS-enabled kernel. Booting was
also successful.
