/*这是一个基于共享内存的聊天程序
 * 共享内存使用步骤：
 *  1. 创建共享内存
 *  2. 将共享内存映射到虚拟地址空间
 *  3. 内存的数据操作
 *  4.  不玩了
 *       1.  解除映射
 *       2. 删除共享内存
 *             如果有进程与共享内存有保持映射连接关系，那么共享内存将不会被立即删除
 *             ，而是等最后一个映射断开后删除，在这期间，将拒绝其它进程的映射
 */
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#define IPC_KEY 0x12345678
int main()
{
    //创建创建共享内存int shmget(key_t key, size_t size, int shmflg);
    //key 操作系统上的ipc标识
    //size 创建的共享内存大小
    //shmflg:
    //      IPC_CREAT|IPCEXCL|0664
    //      返回值：操作句柄     失败：-1
    int shmid=-1;
    shmid=shmget(IPC_KEY,32,IPC_CREAT|0664);
    if(shmid<0){
        perror("shmget error");
        return -1;
    }
    //共享内存映射到虚拟地址空间
    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    //shmid:操作句柄
    //shmaddr:映射起始位置，NULL(操作系统分配）
    //shmflg:SHM_RDONLY---只读    否则读写
    //返回值 ：映射的虚拟地址空间首地址
    void *shm_start=shmat(shmid,NULL,0);
    if(shm_start==(void*)-1){
        perror("shmat error");
        return -1;
    }
    while(1){
        printf("%s\n",(char*)shm_start);
        sleep(1);
    }
    //不玩了
    //          解除映射
    //          int shmdt(const void *shmaddr);
    //          shmaddr:共享内存的映射首地址
    //          成功：0  失败：-1
    shmdt(shm_start);
    //删除共享内存
    //int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    //cmd:IPC_RMID删除
    //buf：用于接受共享内存的描述信息，不关心可以置空
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
