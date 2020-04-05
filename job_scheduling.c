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
	float cost;
	time dur;
}JOB;

time differ(time,time);
float dur(time);

int main()
{
	time total;
	JOB *job,s;
	int n,i,j,h,m;
	float *r,*cost;

	printf("Enter The number of Jobs you have in hand:\n");
	scanf("%d",&n);
	job = (JOB*)malloc(n*sizeof(JOB));
	r = (float*)malloc(n*sizeof(float));	
	cost = (float*)malloc(n*sizeof(float));	

	printf("\n**** Enter all the inputs in the format: hh:mm ****\n\n");
	for(i=0;i<n;i++)
	{
		job[i].id = i+1;
		printf("Job[%d]\t\tduration\t:",i+1);
		scanf("%d%*c%d",&h,&m);
		job[i].dur.hour = h;
		job[i].dur.min = m%60;
		printf("\tEnter Cost per hour\t:");
		scanf("%f",&job[i].cost);
		printf("\n");
	}
	
	
	for(i=0;i<n;i++)
		r[i] = job[i].cost/dur(job[i].dur);
		
	printf("\n");

	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
		{
			if(r[i] < r[j])
			{
				s = job[i];
				job[i] = job[j];
				job[j] = s;
			}		
		}
	
	printf("\n___________________________________");
	printf("\n|   The Jobs are to be done are   |");
	printf("\n```````````````````````````````````\n");
	printf("\njob id\t\tduration\t\tcost/unit delay\t\tTotal cost\n\n");
	float duration = 0,tot_cost = 0;
	for(i=0;i<n;i++)
	{
		printf("%7d\t\t",job[i].id);
		printf("%2d:%2.2d\t\t\t",job[i].dur.hour,job[i].dur.min);
		printf("%5.2f\t\t\t",job[i].cost);
		duration +=dur(job[i].dur);
		cost[i] = duration*job[i].cost; 
		printf("%5.2f\n",cost[i]);
		tot_cost+=cost[i];
	}
	printf("\n\nTotal cost is : %4.2f\n\n",tot_cost);
	free(job);
	free(r);
	free(cost);
}

time differ(time start,time end)
{
	time t;
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
	t.hour = h;
	t.min = m;
	
	return t;
}
float dur(time t)
{
	float h;
	h = t.hour;
	h+=((float)t.min)/60;
	return h;
}
