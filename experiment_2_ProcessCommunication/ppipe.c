#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int px1[2];
int px2[2];
int py1[2];
int py2[2]; 

//f(x)
int f_x(int x)
{
if(x==1) return 1;
else return f_x(x-1)*x;
}

//f(y)
int f_y(int y)
{
if(y==1||y==2) return 1;
else return f_y(y-1)+f_y(y-2);
}

//f(x,y)
void f_xy(int x,int y)
{
write(px1[1],&x,sizeof(int));
write(py1[1],&y,sizeof(int));
int fx,fy;
read(px2[0],&fx,sizeof(int));
read(py2[0],&fy,sizeof(int));
printf("f(%d,%d) = %d\n",x,y,fx+fy);
}

//进程fx
void f_x_process()
{
close(px1[1]);
close(px2[0]);
while(1){
int x;
read(px1[0],&x,sizeof(x));
int fx=f_x(x);
write(px2[1],&fx,sizeof(fx));
}
}

//进程fy
void f_y_process()
{
close(py1[1]);
close(py2[0]);
int y;
while(1){
read(py1[0],&y,sizeof(y));
int fy=f_y(y);
write(py2[1],&fy,sizeof(fy));
}
}

void parent_process()
{
//向px1,py1 1端写，从px2,py20端读
close(px1[0]);
close(py1[0]);
close(px2[1]);
close(py2[1]);
int x,y;
printf("请输入x和y的值，用空格分割\n");
scanf("%d %d",&x,&y);
f_xy(x,y);
}
int main()
{
if ((pipe(px1))==-1||(pipe(px2))==-1||(pipe(py1))==-1||(pipe(py2))==-1)
{
perror("can`t create pipe");
exit(EXIT_FAILURE);
}

pid_t pid_x=fork();
if(pid_x<0)
{
perror("can`t create process x");
exit(EXIT_FAILURE);
}
else if(pid_x==0)
{
    f_x_process();
    exit(EXIT_SUCCESS);
}

pid_t pid_y=fork();
if(pid_y<0)
{
perror("can`t create process y");
exit(EXIT_FAILURE);
}
else if(pid_y==0)
{
    f_y_process();
    exit(EXIT_SUCCESS);
}
if(pid_x>0&&pid_y>0){
parent_process();
return 0;
}
}

