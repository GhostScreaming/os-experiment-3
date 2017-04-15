#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *_buf;
};

//define necessary function to be used.

int binary_semaphore_allocation (key_t key, int sem_flags)
{
  return semget (key, 1 ,sem_flags);
}	//creat a new semaphore.

int binary_semaphore_deallocate (int semid)
{
  union semun ignored_argument;
  return semctl (semid, 1, IPC_RMID, ignored_argument);
}	//destroy an existed semaphore.

int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}	//initialize an empty semaphore.

int binary_semaphore_wait (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = -1;
  operations[0].sem_flg = SEM_UNDO;
  return semop (semid, operations, 1);
}	//wait operation to operate the semaphore.

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = 1;
  operations[0].sem_flg = SEM_UNDO;
  return semop (semid, operations, 1);
}	//deliver a signal to release the semaphore.

int main()	//only one semaphore exists.
{
  int semid;
  semid = binary_semaphore_allocation (IPC_PRIVATE,IPC_CREAT);
  printf("%d",semid);
  binary_semaphore_initialize (semid);
  while(1)
  {
     if(!binary_semaphore_wait(semid))	//if semaphore is unlocked,it outputs 1.
       {
          printf("1");
          binary_semaphore_post (semid);
       }
  }
  return 0;
}


