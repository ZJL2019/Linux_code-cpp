#include <stdio.h>
#include <sys/shm.h>

#define shm_key 0x12345678

int main()
{
    int shmid = shmget (shm_key,1024,IPC_CREAT | 0644);
    if (shmid < 0)
    {
        printf ("shmget");
    }
    printf ("shmid=%d\n",shmid);
    void *lp=shmat(shmid,NULL,0);
    return 0;
}
