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

void supplier() {
    while (1) {
    	down(supplier_sem);  // 等待抽烟者抽完烟
        sleep(1);
        // 提供两种材料
        int i=rand()%3;
        printf("%d Supplier is supplying for smoker %d.\n",getpid(),i+1);
        up(smoker_sem[i]);  // 唤醒对应的抽烟者
    }
}

int main() {
for(int i = 0; i < 3; i++) {
    semctl(smoker_sem[i], 0, IPC_RMID);
}
    semctl(supplier_sem, 0, IPC_RMID);
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
    supplier();
    return 0;
}
