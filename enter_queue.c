#include <stdio.h>
#include <stdlib.h> //rand
#include <unistd.h> //sleep
#include <sys/time.h> //gettimeofday
#include <sys/types.h> //gettid
#include <sys/syscall.h>
#include <syscall.h>
#include <string.h>
#include <linux/kernel.h>
#define gettid() syscall(SYS_gettid)

int enter_wait_queue(int x) {
    return syscall(351, x);
}

void itoa (int n,char s[])
{
	int i,j,num;
	char tmp[300];
	num = 0;
	i=0;
	do{
	      tmp[i++]=n%10+'0';
	}
	while ((n/=10)>0);
	while(num<i){
		s[num]=tmp[i-num-1];
		num++;		
	}
	s[num]='\0';
} 
void main(){
	int	random_num;
	int	ttid, count;
	char 	file[25]="file_";
	char 	id[20];
	char	str[300];
	struct timeval  t1, t2;
	
	gettimeofday(&t1, NULL);
	ttid=gettid();
	count=0;
	
	
	FILE *pFile;
	itoa(ttid,id);
	strcat(file, id);
	pFile = fopen( file,"w" );
	
	while(1){
		gettimeofday(&t2, NULL);
		if((t2.tv_sec-t1.tv_sec)>180){
			break;
		}
		//用不同的seed
		srand(gettid()+time(NULL));
		random_num= (rand()%3)+1;

		sprintf(str,"process %d is added into wait queue project2_queue_%d the %d th time\n", ttid, random_num, count);
		printf("process %d is added into project2_queue_%d the %d th time\n", ttid, random_num, count);
		count++;

		fwrite(str,1,strlen(str),pFile);
		enter_wait_queue(random_num); 
		sleep(random_num);

		printf("process %d wake up from wait queue project2_queue_%d\n", ttid, random_num); 
	}
	fclose(pFile);
	printf("process %d completes!\n", ttid);
}