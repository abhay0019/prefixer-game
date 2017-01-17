
#include<stdio.h>
#include<stdlib.h>
struct winloss
{
	int win;
	int loss;
};
struct node
{
	int win;
	int isleaf;
	int isword;
	struct node *child[26];
};
int wins[2600000]={0},loses[2600000]={0};
struct node *newnode()
{
	int i=0;
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->isleaf=1;
	temp->isword=0;
	for(i=0;i<26;i++)
	temp->child[i]=NULL;
	return temp;
}
struct node * insert(struct node *root,char str[],int i,int win)
{
	if(str[i]=='\0')
	{
		root->isword=1;
	/*	if(root->win==1&&root->isleaf)
		winner=1;*/
		
		return root;
	}
	
	root->isleaf=0;
/*	if(root->isword)
	{
		if(winner==1)
		winner=2;
	}*/
	if(root->child[str[i]-'a']==NULL)
	{
	root->child[str[i]-'a']=newnode();
	root->child[str[i]-'a']->win=win;
	}
	root->child[str[i]-'a']=insert(root->child[str[i]-'a'],str,i+1,!win);
	
	return root;
}
struct winloss preorder(struct node *root)
{
	int i=0;
	int winstat=0,losstat=0;
	struct winloss child_stat;
	for(i=0;i<26;i++)
	{ 
	  if(root->isleaf==1)
	  {
	  //	printf("leaf return(0,1)\n");
	  	return (struct winloss){0,1};
	  }
	  
 	  if(root->child[i]!=NULL)
	  {
	  child_stat=preorder(root->child[i]);	
	  	
	  	winstat=(winstat | !(child_stat.win));
	  	losstat=(losstat | !(child_stat.loss));
	  	if(winstat==1 && losstat==1)
		  {
		  return (struct winloss){1,1};
          }
	  }	
	}
	//printf("zz return(%d,%d)\n",winstat,losstat);
	return (struct winloss){winstat,losstat};
//	printf("\n");
}
int main()
{
    printf("\t\tINPUT FORMAT \n\n\tNo._of_Strings No._of_Games\n\tList of strings ..\n\n\n");
    printf("\t\tOUTPUT FORMAT \n\n\tFirst : if First player wins \n\tSecond : if Second player wins\n");
	char str[100010];
	int win=1;
	int n,k;
	scanf("%d %d",&n,&k);
	int i=0;
	struct node *root=newnode();
	for(i=0;i<n;i++)
	{
		scanf("%s",&str);
		root=insert(root,str,0,win);
	}
	struct winloss st;
	st=preorder(root);
	//printf("wins %d loses %d\n",wins,loses);
	if(st.win>0)
	{
		if(st.loss>0)
		{
		printf("First\n");	
		}
		else
		{
		if(k%2==0)
		printf("Second\n");
		else
		printf("First\n");	
		}
	}
	else
	{
	    printf("Second\n");
	}
}

