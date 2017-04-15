#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main()
{
  int segment_id;
  char* shared_memory;
  char  data[500];		//a character array to store transmitted data.
  struct shmid_ds shmbuffer;		//a special data struct which kernel holds for shared memory.
  printf("Type the message you want to deliver.\n");
  scanf("%s",data);		//store the message into the array.
  int segment_size;
  const int shared_segment_size = 0x6400;	//A given size of shared memory,which can be modified.
  segment_id = shmget (IPC_PRIVATE,shared_segment_size,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);	//a function which can get an id of shared memory or creat a new shared memory and return its id.
  shared_memory = (char *)shmat (segment_id,0,0);	//get the address of the shared memory.
  printf ("shared memory attached at address %p\n",shared_memory);	//output necessay messages.
  shmctl (segment_id,IPC_STAT,&shmbuffer);		//get necessary informations.
  segment_size = shmbuffer.shm_segsz;
  printf ("segment size: %d\n",segment_size);
  sprintf (shared_memory,"%s",data);	//write the data into shared memory.
  shmdt (shared_memory);		//cut off connection with shared memory.
  shared_memory = (char *) shmat (segment_id,(void *) 0x5000000,0);	//given the shared memory a new address.
  printf ("shared memory reattached at address %p\n",shared_memory);
  printf ("%s\n",shared_memory);
  shmdt (shared_memory);		//cut off connection with shared memory.
  shmctl (segment_id, IPC_RMID, 0);		////get necessary informations.
  return 0;
}
  
  

