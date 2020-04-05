#include<stdio.h>
#include<stdlib.h>
typedef struct
{
	int hour;
	int min;
}time;
typedef struct 
{
	int id;
	time start;
	time end;
}slot;


int differ(time ,time ,time*);
int main()
{
	slot *task,*res,total,s;
	int n,i,j,res_size = 0,h,m;
	printf("Enter The number of task you have in hand:\n");
	scanf("%d",&n);
	task = (slot*)malloc(n*sizeof(slot));
	res = (slot*)malloc(n*sizeof(slot));
	
	printf("\n****Enter all the inputs in the format: hh:mm ****\n\n");
	for(i=0;i<n;i++)
	{
		task[i].id = i+1;
		printf("task[%d]\t\tstarting time\t:",i+1);
		scanf("%d%*c%d",&h,&m);
		task[i].start.hour = h%24;
		task[i].start.min = m%60;
		printf("\t\tEnding time\t:");
		scanf("%d%*c%d",&h,&m);
		task[i].end.hour = h%24;
		task[i].end.min = m%60;
		printf("\n");
		if(differ(task[i].start,task[i].end,NULL)==-1)
		{
			printf("\n*****ERROR: task ends before starting*****\n\nRenter\n\n");
			i--;
		}
	}
	printf("Enter the begining time of schedule:\n");
	scanf("%d%*c%d",&h,&m);
	total.start.hour = h%24;
	total.start.min = m%60;
	printf("Enter the ending time of schedule:\n");
	scanf("%d%*c%d",&h,&m);
	total.end.hour = h%24;
	total.end.min = m%60;
	
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
		{
			if(differ(task[i].end,task[j].end,NULL)==-1)
			{
				s = task[i];
				task[i] = task[j];
				task[j] = s;
			}		
		}
	
	i=0;
	do{
		if(differ(total.start,task[i].start,NULL)==-1)
		{
			i++;
			continue;
		}
		if(differ(task[i].end,total.end,NULL)==0)
			res[res_size++] = task[i];
		else
			break;
		total.start = task[i].end;
		i++;
	}while(i<n);
	printf("\n____________________________________");
	printf("\n|   The tasks are to be done are   |\n");
	printf("````````````````````````````````````\n");
	printf("\ntask id\t\tstart time\t\tend time\t\tduration\n\n");
	for(i=0;i<res_size;i++)
	{
		time diff;
		printf("%7d\t\t",res[i].id);
		printf("%2d:%2.2d\t\t\t",res[i].start.hour,res[i].start.min);
		printf("%2d:%2.2d\t\t\t",res[i].end.hour,res[i].end.min);
		differ(res[i].start,res[i].end,&diff);
		printf("%2d:%2.2d\n",diff.hour,diff.min);
	}
	printf("\n");
	free(task);
	free(res);
	
}

int differ(time start,time end,time *dif)
{
	int h,m,flag=0;
	m = end.min - start.min;
	if(m<0)
	{
		flag = 1;
		m+=60;
	}
	h = end.hour - start.hour;
	if(flag == 1)
		h--;
	if(dif!=NULL)
	{
		dif->hour = h;
		dif->min = m;
	}
	if(h<0)
		return -1;
	else return 0;
}

