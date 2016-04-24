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
myprogram and added another instance with a nice value of -20. Note that ROOT
PERMISSION WAS REQUIRED to assign this negative nice value.

top - 02:50:28 up  1:02,  1 user,  load average: 10.34, 10.02, 9.55
Tasks: 154 total,  12 running, 142 sleeping,   0 stopped,   0 zombie
%Cpu0  :   1.3/0.0     1[|                                                                                                   ]
%Cpu1  :   0.0/0.0     0[                                                                                                    ]
%Cpu2  : 100.0/0.0   100[||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||]
%Cpu3  :   0.0/0.0     0[                                                                                                    ]
GiB Mem :  6.7/3.457    [                                                                                                    ]
GiB Swap:  0.0/0.000    [                                                                                                    ]

  PID USER      PR  NI    VIRT    RES  %CPU %MEM     TIME+ S COMMAND
  311 rajiv     20   0   44.6m  13.8m   0.0  0.4   0:00.34 S                  `- xfce4-session
  349 rajiv     20   0   58.9m  22.3m   0.7  0.6   0:11.36 S                      `- xfce4-terminal
  491 rajiv     20   0    5.6m   3.3m   0.0  0.1   0:00.05 S                          `- bash
 1028 rajiv     20   0    2.1m   0.6m   0.0  0.0   0:00.00 S                              `- myprogram
 1029 rajiv     31  11    2.0m   0.1m   0.0  0.0   2:36.21 R                                  `- myprogram
 1030 rajiv     31  11    2.1m   0.1m   0.0  0.0   2:36.20 R                                  `- myprogram
 1031 rajiv     31  11    2.1m   0.1m   0.0  0.0   2:36.20 R                                  `- myprogram
 1032 rajiv     31  11    2.1m   0.1m   0.0  0.0   2:36.20 R                                  `- myprogram
 1033 rajiv     31  11    2.1m   0.1m   0.0  0.0   2:36.21 R                                  `- myprogram
  640 rajiv     20   0    5.5m   3.4m   0.0  0.1   0:00.01 S                          `- bash
 1034 rajiv     20   0    2.1m   0.5m   0.0  0.0   0:00.00 S                              `- myprogram
 1035 rajiv     35  15    2.0m   0.0m   0.0  0.0   1:03.86 R                                  `- myprogram
 1036 rajiv     35  15    2.1m   0.0m   0.0  0.0   1:03.87 R                                  `- myprogram
 1037 rajiv     35  15    2.1m   0.0m   0.0  0.0   1:03.86 R                                  `- myprogram
 1038 rajiv     35  15    2.1m   0.0m   0.0  0.0   1:03.86 R                                  `- myprogram
 1039 rajiv     35  15    2.1m   0.0m   0.0  0.0   1:03.86 R                                  `- myprogram
  828 rajiv     20   0    5.5m   3.4m   0.0  0.1   0:00.01 S                          `- bash
 1169 root      20   0   10.2m   4.5m   0.0  0.1   0:00.00 S                              `- sudo
 1170 root      20   0    2.1m   0.5m   0.0  0.0   0:00.00 S                                  `- myprogram
 1171 root       0 -20    2.0m   0.1m 100.0  0.0   0:26.93 R                                      `- myprogram
