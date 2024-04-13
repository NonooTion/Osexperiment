#include "pctl.h"
int main(int argc,char *argv[])
{
    int i;
    int pid;//存放子进程号

    int status;//存放子进程返回状态
    int times=0;//存放子进程运行次数
    bool done=false;//是否继续执行子程序
    signal(SIGINT,(sighandler_t)sigcat);//注册一个本进程处理键盘中断的函数
    pid=fork();//建立子进程
    if(pid<0)//建立子进程失败
    {
        printf("Create Process fail!\n");
        exit(EXIT_FAILURE);
    }
    if(pid==0)//子进程执行代码段
    {
	  while(1){
	  times++;
    	  printf("\nThis is child process %d times execute.",times);
          system("/bin/ls -a");
          sleep(3);
    	}
    }
    else//父进程执行代码段
    {
    	printf("\nI am Parent process %d\n",getpid());
        //父进程等待子进程执行结束
        printf("%d Waiting for chld done.\n\n",getpid());
        waitpid(pid,&status,0);//等待子进程结束
        printf("\nMy child exit! status=%d\n\n",status);
    }
    return EXIT_SUCCESS;
}
