#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0X100		//The length of file, it can be modified.

int main (int argc, char* const argv[])
{
  int fd;
  void* file_memory;
  char *data;		//a string array to store the entered message.
  printf("Please enter the message.\n");
  scanf("%s",data);
  fd = open (argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);		//creat a file at appointed address.
  lseek (fd, FILE_LENGTH + 1, SEEK_SET);	//move the file pointer to the end.
  write (fd, "" , 1 );		//write an ending signal.
  lseek (fd, 0 ,SEEK_SET);	//move the file pointer to the beginning.
  file_memory = mmap (0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);	//Mapping the fd to the memory,every procsee which is mapped to this address can shared this area.
  close (fd);		//close this file.
  sprintf((char*) file_memory, "%s\n", data);	//write data into the memory.
  munmap (file_memory, FILE_LENGTH);		//release the memory.But it's not necessary.
  return 0;
}
  
