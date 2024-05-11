#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

//信号处理函数，如果信号为SIGINT，进程优先级+1,否则进程优先级-1
void handle_signal(int signal)
{
    int priority=getpriority(PRIO_PROCESS,0);
    if(signal==SIGINT) setpriority(PRIO_PROCESS,0,priority+1);
    else if(signal==SIGTSTP) setpriority(PRIO_PROCESS,0,priority-1);
    return;
}

//父进程打印进程号和优先级
void print_info_father()
{
    while(1)
    {
        printf("PID = %d,Priority = %d\n",getpid(),getpriority(PRIO_PROCESS,0));
        kill(getpid(),SIGINT);
        sleep(3);
    }
}
//子进程打印进程号和优先级
void print_info_son()
{
    while(1)
    {
        printf("PID = %d,Priority = %d\n",getpid(),getpriority(PRIO_PROCESS,0));
        kill(getpid(),SIGTSTP);
        sleep(3);
    }
}
int main()
{
    signal(SIGINT,handle_signal);
    signal(SIGTSTP,handle_signal);
    int pid=fork();
    if(pid==0)
    {
        print_info_father();
    }
    else if(pid>0)
    {
        print_info_son();
    }
    else 
    {
        printf("create failure!");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
