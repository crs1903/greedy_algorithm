#include<stdio.h>
#include<stdlib.h>

struct mynode
{
	int freq;
	char c,*code;
	struct mynode *L,*R;
};
typedef struct mynode node;

node **arr,**saved;
int n,arr_size;


node* get_code(node*,int,char*);
node* encode(void);
int main()
{
	int i,j;
	printf("Enter the number of alphabets:\n");
	scanf("%d",&n);
	node *head;
	
	arr = (node**)malloc(n*sizeof(node*));
	saved = (node**)malloc(n*sizeof(node*));

	for(i=0;i<n;i++)
		arr[i] = (node*)malloc(sizeof(node));
	
	
	for(i=0;i<n;i++)
	{
		getchar();
		printf("[%d] Symbol\t: ",i+1);
		scanf("%c",&(arr[i]->c));
		arr[i]->L = arr[i]->R = NULL;
		printf("\tfreq\t: ");
		scanf("%d",&(arr[i]->freq));
		printf("\n");
		saved[i] = arr[i];
	}
	head = encode();
	head = get_code(head,1,NULL);
	for(i=0;i<n;i++)
		printf("Symbol %c\tcode : %s\n",saved[i]->c,saved[i]->code);
	
}
node* encode()
{
	int i,j;
	arr_size = n;
	node *p,*new; 
	while(arr_size != 1)
	{
		new = (node*)malloc(sizeof(node));
		for(i=0;i<arr_size-1;i++)
			for(j=i+1;j<arr_size;j++)
			{
				if(arr[i]->freq < arr[j]->freq)
				{
					p=arr[i];
					arr[i]=arr[j];
					arr[j]=p;
				}
			}
		new->L = arr[arr_size-2];
		new->R = arr[arr_size-1];
		new->c = '\0';
		new->freq = arr[arr_size-1]->freq + arr[arr_size-2]->freq;
		arr[arr_size-2] = new;
		arr_size--; 
	}
	return *arr;
}


node* get_code(node *head,int level,char *st)
{
	char *s;
	if(head->L==NULL && head->R==NULL)
	{	
		head->code = (char*)malloc(level*sizeof(char));
		sprintf(head->code,"%s",st);
		return head;
	}
	s=(char*)malloc((level)*sizeof(char));
	if(st==NULL)
		sprintf(s,"%d",0);
	else
		sprintf(s,"%s%d",st,0);
	head->L = get_code(head->L,level+1,s);

	if(st==NULL)
		sprintf(s,"%d",1);
	else
		sprintf(s,"%s%d",st,1);
	head->R = get_code(head->R,level+1,s);	
	
	return head;
}
