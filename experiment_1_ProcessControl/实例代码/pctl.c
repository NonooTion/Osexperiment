#include "pctl.h"
int main(int argc,char *argv[])
{
    int i;
    int pid;//存放子进程号

    int status;//存放子进程返回状态

    char *args[]={"/bin/ls","-a",NULL};//子进程要缺省执行的命令
    signal(SIGINT,(sighandler_t)sigcat);//注册一个本进程处理键盘中断的函数
    pid=fork();//建立子进程
    if(pid<0)//建立子进程失败
    {
        printf("Create Process fail!\n");
        exit(EXIT_FAILURE);
    }
    if(pid==0)//子进程执行代码段
    {
        printf("I am Child process %d\nMy father is %d\n",getpid(),getppid());
        pause();
        printf("%d child will Running:",getpid());
        if(argv[1]!=NULL)
        {
            //如果命令行上输入了子进程要执行的命令，则执行该命令
            for(int i=1;argv[i]!=NULL;i++)
            {
                printf("%s",argv[i]);
            }
            printf("\n");
            status =execve(argv[1],&argv[1],NULL);
        }
        else
        {
            //如果命令行上没有输入子进程要执行的命令，则执行缺省的命令
            for(int i=0;args[i]!=NULL;i++)
            {
                printf("%s",args[i]);
            }
            printf("\n");
            status =execve(args[0],args,NULL);
        }
    }
    else//父进程执行代码段
    {
    	sleep(3);
    	printf("\nI am Parent process %d\n",getpid());
        if(argv[1]!=NULL){
        //如果命令行上输入了自进程需要执行的命令，则父进程等待子进程执行结束
        printf("%d Waiting for chld done.\n\n",getpid());
        waitpid(pid,&status,0);//等待子进程结束
        printf("\nMy child exit! status=%d\n\n",status);
        }
        else
        {
            //如果命令行上没输入子进程要执行的命令
            //唤醒子进程，与子进程并发执行
            if(kill(pid,SIGINT)>=0)
            printf("%d Wakeup %d child.\n",getpid(),pid);
            printf("%d don`t Wait for child done.\n\n",getpid());
        }
    }
    return EXIT_SUCCESS;
}
