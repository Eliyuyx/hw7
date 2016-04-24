#define _GNU_SOURCE

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

#define CPU_NUMBER 2

void create_new_process(int n, int num_processes, int nice)
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		// fork() error
		printf("fork() error");
		exit(1);
	} else if (pid == 0) {
		// Child
		cpu_set_t set;
		CPU_ZERO(&set);
		CPU_SET(CPU_NUMBER, &set);
		sched_setaffinity(0, sizeof(cpu_set_t), &set);

		if (setpriority(PRIO_PROCESS, getpid(), nice)) {
			printf("setpriority() error");
			exit(1);
		}

		for (;;) {
			int garbage = 999999 / 999;
		}
		exit(0);
	}

	// Parent
	printf("Child %d created.\n", n);
	if (n == num_processes) {
		wait(NULL);
	}
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Usage: ./myprogram <num_processes> <nice>\n");
		exit(1);
	}

	int num_processes = atoi(argv[1]);
	int nice = atoi(argv[2]);

	int i;
	for (i = 0; i < num_processes; i++) {
		create_new_process(i+1, num_processes, nice);
	}
}
