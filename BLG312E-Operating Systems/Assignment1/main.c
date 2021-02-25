#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{	
	int level=1;
	int a = fork();
	int b=0;
	int c=0;
	int d=0;
	int e=0;
	if(a){
		b = fork();
		if(b){
			c = fork();
			if(!c){
				level++;
			}
		}else{
			level++;
		}
	}else{
		level++;
	}
	if(c == 0){
		a = b = 0;
		d = fork();
		if(!d){
			level++;
		}
		e = fork();
		if(!e){
			level++;
			d=0;
		}
	}
    printf("<PID: %d, Children_PID(s):  ",getpid());
	
    if(a){
		printf("%d ",a); 
	}
	if(b){
		printf("%d ",b); 
	}
	if(c){
		printf("%d ",c); 
	}
	if(d){
		printf("%d ",d); 
	}
	if(e){
		printf("%d ",e); 
	}
	
	printf(", Level: %d> \n",level);
    return 0;
}
