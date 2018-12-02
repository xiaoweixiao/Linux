/*这是共享内存的客户端，目的：隔一秒，去共享内存取一次数据*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
//定义一个ipc标识符
#define KEY 0x520

int main()
{
    umask(0);
    //创建共享内存
    //int shmget(key_t key, size_t size, int shmflg);
    int shmid=shmget(KEY,520,IPC_CREAT|0664);
    if(shmid<0){
        perror("shmget error");
        return -1;
    }else
    {
        //映射到虚拟地址空间
        //void *shmat(int shmid, const void *shmaddr, int shmflg);
        void*shmhead=shmat(shmid,NULL,SHM_RDONLY);//shmaddr是要映射的起始地址，NULL表示由系统分配，
        //shmflg如果是SHM_RDONLY则只读权限，否则读写
        if(shmhead==(void*)-1)
        {
            perror("shmat error");
            return -1;
        }
        while(1)
        {
            //映射成功,读取数据
            printf("memshare:%s\n",(char*)shmhead);
            sleep(1);
        }
        //解除映射int shmdt(const void *shmaddr);
        shmdt(shmhead);
        //删除共享内存int shmctl(int shmid, int cmd, struct shmid_ds *buf);
        shmctl(shmid,IPC_RMID,NULL);
    }
    return 0;
}
