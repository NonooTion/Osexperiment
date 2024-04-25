#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    int pid; //进程号
    int pipe1[2]; //存放第一个无名管道标号
    int pipe2[2]; //存放第二个无名管道标号
    int x;//存放要传递的整数
    //使用pipe()系统调用建立两个无名管道。建立不成功程序退出，执行终止
    if(pipe(pipe1)<0)
    {
        perror("pipe not create");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipe2)<0)
    {
        perror("pipe not create");
        exit(EXIT_FAILURE);
    }
    //使用fork系统调用建立子进程，建立不成功程序退出
    if((pid=fork())<0)
    {
        perror("process not create");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {//自进程负责管道1的0端读，管道2的1端写
    //关闭管道1的1端和管道2的0端
    close(pipe1[1]);
    close(pipe2[0]);
    //每次循环从管道1的0端读一个整数放入变量X中，并加1放入管道二的1端，直到x大于10
    do{
        read(pipe1[0],&x,sizeof(int));
        printf("child %d read:%d\n",getpid(),x++);
        write(pipe2[1],&x,sizeof(int));
    }while(x<=9);
    //关闭管道
    close(pipe1[0]);
    close(pipe2[1]);
    exit(EXIT_SUCCESS);
    }
    //父进程执行
    else{
        close(pipe1[0]);
        close(pipe2[1]);
        x=1;
        do{
        write(pipe1[1],&x,sizeof(int));
        read(pipe2[0],&x,sizeof(int));
        printf("parent %d read:%d\n",getpid(),x++);
        }while(x<=9);
        close(pipe1[1]);
        close(pipe2[0]);
        return EXIT_SUCCESS;
    }
}
