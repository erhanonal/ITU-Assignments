//Erhan Önal 15.03.2018

#include <stdio.h>

 int point_of_throw(int segment,char ring){
 	int points=0;
 	if(ring=='I'){
 		points=50;
 	}
 	else if(ring=='O'){
 		points=25;
 	}
 	else{
 		int multiplier;
 		if (ring=='D'){
 			multiplier=2;
 		}
 		else if(ring=='T'){
 			multiplier=3;
 		}
 		else {
 			multiplier=1;
 		}
 		points=segment*multiplier;
 	}
 	return points;
 }

int remaining_points(int points,int target, int segment, char ring){
	int deduction=0;
	if(points!=target || ring=='D'){
		deduction=point_of_throw(segment,ring);
		if((points-deduction<0 || points-deduction==1) || (points-deduction==0 && ring!='D')){
			deduction=0;
		}
	}
	return points-deduction;
}

int main(){
	int target=0;
	int segment=0;
	char ring;
	printf("Target: ");
	scanf("%d",&target);
	int points=target;
	while(points!=0){
		printf("Throw: ");
		scanf("%d %c",&segment,&ring);
		points=remaining_points(points,target,segment,ring);
		printf("Points: %d\n",points);
	}
	return 0;
}
