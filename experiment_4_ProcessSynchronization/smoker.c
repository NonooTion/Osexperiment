#include "ipc.h"

// 三个抽烟者的信号量
extern int smoker_sem[3];
extern key_t smoker_key;

// 供应者的信号量
extern int supplier_sem;
extern key_t supplier_key;

extern int sem_val;
extern int sem_flg;
extern int shm_flg;
void smoker(int id) {
    while(1)
    {
        down(smoker_sem[id]);
        printf("somker %d is smoking\n",id+1);
        sleep(0);
        up(supplier_sem); 
    }
}

int main(int argc, char *argv[]) {
for(int i = 0; i < 3; i++) {
    semctl(smoker_sem[i], 0, IPC_RMID);
}
    semctl(supplier_sem, 0, IPC_RMID);
    int id=0;
    if(argc !=2)
    {
    	printf("which smoker want to smoker? 1~3\n");
    }
    id=atoi(argv[1])-1;
    smoker_key=401;
    supplier_key=501;
    sem_flg=IPC_CREAT | 0644;

    //吸烟者信号量初始值设为0
    sem_val = 0;
    for(int i=0;i<3;i++)
    smoker_sem[i]=set_sem(smoker_key+i,sem_val,sem_flg);

    //供应者同步信号灯设为1
    sem_val=1;
    supplier_sem=set_sem(supplier_key,sem_val,sem_flg);
    smoker(id);
    return 0;
}
