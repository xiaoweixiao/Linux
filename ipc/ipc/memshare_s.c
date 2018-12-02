/*  这是基于共享内存的一个进程间聊天程序
 *  共享内存是最快的ipc，因此相较于其他方式，少了两步内核态用户态
 *  数据拷贝的过程
 *  共享内存操作步骤：
 *      1. 创建共享内存
 *      2. 映射共享内存到虚拟地址空间
 *      3. 数据拷贝（通信）
 *      4. 不玩了
 *          1. 解除映射关系
 *          2. 删除共享内存
 *              如果有进程依然与共享内存保持映射连接关系，那么共享
 *              内存将不会被立即删除，而是等最后一个映射断开后删除
 *              ，在这期间，将拒绝其他进程映射。
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define IPC_KEY 0x12345678
int main()
{
    //1. 创建共享内存
    //int shmget(key_t key, size_t size, int shmflg);
    //  key：   操作系统上ipc标识
    //  size：  要创建的共享内存大小
    //  shmflg：
    //      IPC_CREAT|IPC_EXCL|0664
    //  返回值：操作句柄    失败：-1
    int shmid = -1;
    shmid = shmget(IPC_KEY, 32, IPC_CREAT|0664);
    if (shmid < 0) {
        perror("shmget error");
        return -1;
    }
    //2. 将共享内存映射到虚拟地址空间
    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    //  shmid:      操作句柄
    //  shmaddr：   映射起始地址，NULL(操作系统分配)
    //  shmflg:     SHM_RDONLY--只读    否则读写
    //  返回值：映射的虚拟地址空间首地址
    void *shm_start = shmat(shmid, NULL, 0);
    if (shm_start == (void*)-1) {
        perror("shmat errro");
        return -1;
    }
    while(1) {
        //直接通过这个首地址操作共享内存即可
        printf("please input:");
        fflush(stdout);
        //清空一下共享内存中的数据
        memset(shm_start, 0x00, 32);
        scanf("%s", (char*)shm_start);
        sleep(1);
    }
    //4. 不玩了 a. 解除映射     b. 删除
    //解除映射
    //int shmdt(const void *shmaddr);
    //  shmaddr 共享内存的映射首地址
    //  返回值：成功：0     失败：-1
    shmdt(shm_start);
    //删除共享内存
    //int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    //  shmid:  句柄
    //  cmd：   IPC_RMID    删除
    //  buf：   用于接收共享内存描述信息,不关心可以置空
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

