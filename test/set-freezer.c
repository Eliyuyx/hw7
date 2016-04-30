#include <sched.h>
#include <stdlib.h>
#include <stdio.h>

#define SCHED_FREEZER 7

int main(int argc, char **argv) {
    struct sched_param params;
    params.sched_priority = 0;
    pid_t pid = (pid_t) (atoi(argv[1]));
    if (sched_setscheduler(pid, SCHED_FREEZER, &params) == 0) {
        printf("[%d] sched policy changed\n", pid);
    }
    return 0;
}
