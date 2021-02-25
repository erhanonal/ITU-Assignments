/**************************
**Erhan Önal 150170713
*Development environment: ITU SSH servers
*To compile: gcc 150170713.c -o 150170713 -lpthread -lm -lrt  -g -Wall -Werror
*To run: ./150170713 interval_min interval_max np nt
*Example ./150170713 101 200 2 2
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  
#include <pthread.h> 
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h> 

#define MAX_ARRAY_SIZE 100000
int* sharedArray;
int* currentIndex; 
pthread_mutex_t lock;

struct args {
    int min;
    int max;
    int slaveNumber;
    int threadNumber;
};


bool isPrime(int num){
	if(num<2){
		return false;
	}
	if(num==2){
		return true;
	}
	int i=0;
	for(i=2;i<num;i++){
		if(num%i==0){
			return false;
		}
	}
	return true;
}

void *threadFindPrimeNumbers(void *arguments) 
{ 
	printf("Thread %d.%d: searching in %d-%d \n",((struct args*)arguments)->slaveNumber,((struct args*)arguments)->threadNumber,((struct args*)arguments)->min,((struct args*)arguments)->max);
	int begin = ((struct args*)arguments)->min;
	int end = ((struct args*)arguments)->max;
	int i;
	for(i = begin; i <= end; i++){
		if(isPrime(i)){
			int index = *((int*)currentIndex); 
      			memcpy(&sharedArray[index], &i, sizeof(int)); 
     	    		index++; // increment index
      			memcpy(currentIndex, &index, sizeof(int));
		}
	}
	return NULL; 
}

   
int main(int argc, char* argv[]) 
{ 	
	int index_id= shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

 	currentIndex = (int*) shmat(index_id, 0, 0);

	int i=0;
	
       	int segment_id = shmget(IPC_PRIVATE, sizeof(int)*MAX_ARRAY_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	sharedArray = (int*) shmat(segment_id, 0, 0);
	
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&(lock), &attr);

	pthread_mutexattr_destroy(&attr);
	
	
	printf("Master: Started\n");
	int intervalMin = atoi(argv[1]);
	int intervalMax = atoi(argv[2]);
	int processCount = atoi(argv[3]);
	int threadCount = atoi(argv[4]);
	//printf("erhan: %d %d %d %d",intervalMin,intervalMax, processCount,threadCount);
	int slaveNum=0;
	int procExtra =(intervalMax-intervalMin+1)%processCount;
	int procIncrease = (intervalMax-intervalMin+1)/(processCount);
	int pMin=intervalMin;
	int pMax=intervalMin+(procIncrease-1);
	int id=fork();
	if(id==0){
		slaveNum=1;
		
		//printf("Slave %d: pid: %d		  ppid: %d\n",slaveNum,getpid(),getppid());

		
	}
	int nonExtraProcCounter=1;
	for(i=0;i<processCount-1;i++) { 
		if(id!=0){
			id=fork();
			if(id==0){
				slaveNum=i+2;
				//printf("Slave %d: Started. Interval %d-%d\n",slaveNum,pMin,pMax);
				//printf("Slave %d: pid: %d		  ppid: %d\n",slaveNum,getpid(),getppid());
			}
			pMin=pMax+1;
			if(nonExtraProcCounter<processCount-procExtra){
				pMax+=procIncrease;
				nonExtraProcCounter++;
			}else{
				pMax+=(procIncrease+1);
			}
			
		}	
			
			
     } 
	int threadIncrease=(pMax-pMin+1)/threadCount;
	int threadExtra=(pMax-pMin+1)%threadCount;
	int nonExtraThreadCounter=0;
	
	if(id==0){
		
		printf("Slave %d: Started. Interval %d-%d\n",slaveNum,pMin,pMax);
		//printf("Slave %d pid: %d  parent: %d \n",slaveNum,getpid(),getppid());
		pthread_t threadID[threadCount];
		for(i=0;i<threadCount;i++){
			struct args *arguments = (struct args *)malloc(sizeof(struct args));
			int threadNum=i+1;
			arguments->min=pMin;
			if(nonExtraThreadCounter<threadCount-threadExtra){
				arguments->max=pMin+threadIncrease-1;
				pMin+=threadIncrease;
				nonExtraThreadCounter++;
			}else{
				arguments->max=pMin+threadIncrease;
				pMin+=threadIncrease+1;
			}

			arguments->slaveNumber=slaveNum;
			arguments->threadNumber=threadNum;

			int threadCreationResult=pthread_create(&threadID[i], NULL, threadFindPrimeNumbers, (void*)arguments);
			if(threadCreationResult!=0){
				printf("Error on Thread %d.%d  creation Error Code from pthread_create=%d\n",slaveNum, threadNum,threadCreationResult);
			}
				
			
			
			
		}
		
		for(i=0;i<threadCount;i++){
			pthread_join(threadID[i], NULL) ;
		}
		printf("Slave %d: Done.\n",slaveNum);

	}
	
	
	if(id!=0){
		for(i=0;i<processCount;i++){
			wait(NULL);
		}
		//printf("ID: %d 	pid: %d 		ppif: %d\n",id,getpid(),getppid());
		printf("Master: Done. Prime numbers are: "); 
		int index = *((int*)currentIndex);
		int result[index];
		for(i=0;i<index;i++){
			result[i]=(((int*)sharedArray)[i]);
		} 
		int j=0;
		int key=0;
		for(i=1;i<index;i++){
		//	printf("i: %d ",i);
			key=result[i];
			j=i-1;
			while(j>=0 && result[j] > key){
				result[j+1]= result[j];
				j = j-1;
			}
			result[j+1]=key;
		}
		
		for(i=0;i<index;i++){
			int prime= result[i];
			printf("%d, ",prime);
		}
		//printf("index: %d\n",*currentIndex);
		shmdt(currentIndex);
		shmdt(sharedArray);
		shmctl(index_id, IPC_RMID, NULL);
		shmctl(segment_id, IPC_RMID, NULL);	
	}
	return 0;
}