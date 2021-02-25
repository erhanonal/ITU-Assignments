#include <stdio.h>
#include <semaphore.h> 
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char** argv){
	int N = atoi(argv[1]);
	int incCount = atoi(argv[2]);
	int decCount = atoi(argv[3]);
	int incTurn = atoi(argv[4]);
	int decTurn = atoi(argv[5]);
	printf("%d %d %d %d %d\n", N, incCount, decCount, incTurn, decTurn);

	int index_id= shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

 	int *M = (int*) shmat(index_id, 0, 0);
	*M = 0;
	int id = 1;
	int i;
	for(i=0; i < incCount/2; i++){
		if(id != 0){
			id = fork();
		}
	}
	int incAmount = -1;
	if(id == 0){
		incAmount = 10;
	}
	for(i=0; i < incCount/2; i++){
		if(id != 0){
			id = fork();
		}
	}
	if(incAmount == -1 && id == 0){
		incAmount = 15;
	}
	//printf("First: %d \n", incAmount);

	int decType = -1;// 0 even, 1 odd, -1 not decreaser
	for(i=0; i < decCount/2; i++){
		if(id != 0){
			id = fork();
		}
	}
	if(incAmount == -1 && id == 0){
		decType = 0;
	} 
	for(i=0; i < decCount/2; i++){
		if(id != 0){
			id = fork();
		}
	}
	if(incAmount == -1 && id == 0 && decType == -1){
		decType = 1;
	} 
	printf("%d %d\n", incAmount, decType);
	sem_t mutex;

	int index_id1= shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	sem_init(&mutex, 1, 1);
	 
	while(*M<N){
		if(incAmount != -1){
			sem_wait(&mutex); 
			*M += incAmount;
			printf("id: %d, inc: %d\n", id, incAmount);
			sem_post(&mutex); 
			
		}
	}
        printf("%d %d \n", getpid(), *M);
	if(id != 0){
		for(i = 0; i< incCount + decCount; i++){
			wait(NULL);
		} 
	}
	printf("id: %d\n", id);
	sem_destroy(&mutex);
	shmdt(M);
	shmctl(index_id, IPC_RMID, NULL);


}
