#include <sys/time.h>
#include <stdio.h>

void main(void)
{
	struct timeval tm1; 

	while(1)
	{
	gettimeofday(&tm1,NULL);
	printf("%li.%li\n", tm1.tv_sec, tm1.tv_usec);
	}
	
	return;

}