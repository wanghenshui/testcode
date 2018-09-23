#define _GNU_SOURCE 
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int child(void *args)
{
    printf("pid as seen in the child: %d\n", getpid());
    system("bash");

}

int main()
{
    int namespaces = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    pid_t p = clone(child, malloc(4096) + 4096, SIGCHLD|namespaces, NULL);
    if (p == -1) {
        perror("clone");
        exit(1);
    }
    printf("child pid: %d./na   \n", p);
    waitpid(p, NULL, 0);
    return 0;
}