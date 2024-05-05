
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void bubbleSort(int arr[], int n)
{
	int temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j = 0; j<n-i; j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp = arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

int main()
{
int n;

printf("Enter the no. of integers to sort: \n");
scanf("%d",&n);

int arr[n];

printf("Enter the integers to be sorted: \n");
for(int i = 0;i<n;i++)
{
	scanf("%d",&arr[i]);
}

pid_t pid = fork();

if(pid < 0)
{
	perror("Fork Failed");
}
else if(pid == 0)
{
	sleep(2);
	printf("Child Process Completed.\n");
}
else
{
printf("Parent Process (PID:%d) sorting the integers...\n",getpid());
bubbleSort(arr,n);
printf("Integers Sorted by the parent process:\n");
for(int i=0;i<n;i++)
{
	printf("%d ",arr[i]);
}

printf("\n");

int status;
wait(&status);

printf("Parent Process (PID:%d) completed. Child Process has Terminated.\n",getpid());
}
return 0;
}