#include<stdio.h>
#include <stdlib.h>
//陣列處理
int isen(char a)
{
	if((a>=65&&a<=90)||(a>=97&&a<=122)||(a>=49&&a<=57))return 1;
	else return 0; 
} 
int compare(char*a,char*b)
{
	int err=0; 
	while(*a!=0 && *b!=0)
	{
		if(*a==*b)
		{
			a++; b++; 
		} 
		else
		{
			err=1;
			break; 
		} 
			
	}
	if(*a!=0 || *b!=0)err=1; 
	if(!err)return 1;
	else return 0; 
}


struct node
{
	node()
	{
		l=0;	p=0;	v=0;	howlong=0; 
		for(int i=0;i<30;i++)
		{
			for(int j=0;j<20;j++)
			{
				key[i][j]=0;
			}
		}
	}
	void clean()
	{
		l=0;	p=0;	v=0;	howlong=0; 
		for(int i=0;i<30;i++)
		{
			for(int j=0;j<20;j++)
			{
				key[i][j]=0;
			}
		}
	} 
	void makeakey(char* s)
	{
		int i(0),j(0),k(0);
		while(*s!=0&&*s!=10)
		{
			//printf("%c",*s);
			if(isen(*s))
			{
			//	printf("~%c~\n",*s);
				 
				key[i][j]=*s; 
				j++; 
				
			}
			else if(*s==' ')
			{
				//printf("haha");
				if(key[i][0]!=0) 
				{
					i++;
					j=0;
				} 
				//printf("[%c %d]",*s,*s); 
			}
			else
			{
				if(key[i][0]!=0) 
				{
					i++;
				} 
				key[i][0]=*s;
				i++;
				j=0;
				 //printf("~%d~%c~\n",*s,*s);
			}
			s++; 
		}
			 
		while(key[k][0])
		{
			//printf("[%s]",key[k]);
			if(isen(key[k][0]))
			{
				v++; 
			}
			howlong++;
			k++; 
		}
		//printf("\n");
	}
	
	int p;//他老母 
	int l;//等級 
	int v;//絕對值
	int howlong;//字數 
	char key[30][20];
};
node* root;
node latree[50000];
int ncount=0;
int ans[100];

FILE *out,*input,*flist,*fuxk; 



void iDontLikeTree(FILE* in)
{
	int c=1;
	int parent=0;
	char tmp[600]; 
	for(int i=0;i<600;i++)
	{
		tmp[i]=0; 
	} 
	while (fgets(tmp,600,in))
	{
		//printf("%s\n",tmp);
		latree[ncount].l=c;
		if(latree[ncount].l==1)
		{
			
			parent=ncount;
		//	latree[ncount].p=0;
		}
		else 
		{	latree[ncount].p=parent;} 
		
		
		latree[ncount].makeakey(tmp);
		c=2;
		ncount++;
		
		for(int i=0;i<600;i++)
		{
			tmp[i]=0; 
		} 
		
	}
}
double calculator(int a,int b)
{
	double tmp=0.000000;
	for(int i=0;i<latree[a].howlong;i++)
	{
		for(int j=0;j<latree[b].howlong;j++)
		{
			if(isen(latree[a].key[i][0])&&isen(latree[b].key[j][0])&&compare(latree[a].key[i],latree[b].key[j]) )
			{
				int same=0;
				for(int k=0;k<i;k++)
				{
					if(compare(latree[a].key[i],latree[a].key[k]))same++; 
				} 
				for(int q=0;q<j;q++)
				{
					if(compare(latree[b].key[j],latree[b].key[q]))same++; 
				}
				if(same==0){tmp=tmp+1.000000;} 
			}
		} 
	} 
	return  tmp/(latree[a].v * latree[b].v) ; 
} 
int findmymom(int now)
{
	int tmp=0;
	double max=0;
	for(int i=0;i<now;i++)
	{
		if(max<calculator(now,i))
		{

		   
		      
			max=calculator(now,i);
		//	printf("%f",max) ;
			tmp=i; 
		}
		
		
		//printf(" %d %d",i,now) ; 
		//system("pause") ; 
	}
	return tmp; 
}

void mix()
{
	int c=1;
	while(latree[c].l!=0)
	{ 
		//printf("[%d](%d)",c,latree[c].howlong); 
	 	while(latree[c].l>1)
		 {
			
			latree[c].l=latree[latree[c].p].l+1; 
			c++; 
		//	printf("[%d]",c);
		
		  }
		   latree[c].p=findmymom(c);
		   	
		   latree[c].l=latree[latree[c].p].l+1;
		   c++;
		while(latree[c].l>1)
		{
			
			latree[c].l=latree[latree[c].p].l+1; 
			c++; 
		//	printf("[%d]",c);
		
		 }
		 
	}
}
void anssheet(double a=-1,int c=-1)
{
	static double v=-1; 
	static int now=0; 
	if(a>v||a<0)
	{ 
		for(int i=0;i<now;i++)
		{
			ans[i]=-1 ; 
		}
		now=0; 
		ans[0]=c;
		if(c)now++;
		v=a;
	}
	else
	{
		 ans[now]=c;
		 now++; 
	}
	
}
void sort()
{
	
	int min=10000,mans=0; 
	for(int i=0;i<100;i++)
	{
		for(int j=i;j<100;j++)
		{
			if(latree[ans[j]].l<min)
			{
				min=latree[ans[j]].l; 
				mans=j;
			} 
		}
		int tmp=i;i=mans;mans=tmp;
		min=10000,mans=i+1; 
	} 
} 
void pkey(int c)
{
	int i=0;
	fprintf(out," [");
	while(latree[c].key[i][0]) 
	{
		if(isen(latree[c].key[i][0]))
		{
			fprintf(out," %s",latree[c].key[i]) ; 
		} 
		else
		{
			fprintf(out,"%c",latree[c].key[i][0]); 
		} 
		i++; 
	}
	fprintf(out,"]",latree[c].key[i]);
}
void printans(int c) 
{
	fprintf(out,"[%d]",latree[c].l);
	pkey(c); 
	pkey(latree[c].p);
	fprintf(out,"\n"); 
} 

void output(char *tmp)
{ 

		fprintf(out,"===The response of query %s ===\n",tmp);

		if(ans[0]>=0)
		{ 
			if(ans[1]>=0)sort();
	 		for(int i=0;ans[i]!=-1;i++)
			{
				printans(ans[i]);
			}
		}
		else
		{
			fprintf(out,"[0] [No message is related to iPhone]\n",tmp);
		} 
		fprintf(out,"\n");
}

void search()
{
	
	char tmp[610];

	int p=ncount+1; 
	while(fgets(tmp,610,input))
	{
		latree[p].clean (); 
		int c=0;
		while(tmp[c])c++;
		if(!isen(tmp[c-1])) tmp[c-1]=0;
		c=0; 
		double ansmax=0.00000;
		latree[p].l=tmp[1]-48;                      //LEVEL<10
		latree[p].makeakey(tmp+4);
		//	printf("%d\n",latree[21].v); 
		while(latree[c].howlong)
		{
			//printf("   [%d %d]\n",c,latree[c].l);
			if(latree[c].l<=latree[p].l)
			{
			
				if(calculator(c,p)>=ansmax&&calculator(c,p)!=0)
				{

					ansmax= calculator(c,p); 
					anssheet(calculator(c,p),c);
				}	
			}
			c++; 
		}
		output(tmp);
		anssheet(); 
		for(int a=0;a<610;a++)
		{
			tmp[a]=0; 
		} 
	} 
	
} 

int main()
{
	for(int i=0;i<100;i++)ans[i]=-1;
	char filename[10];
	input=fopen("input.txt","r");
	out=fopen("output(1).txt","w");
	flist=fopen("filelist.txt","r");
	while(fscanf(flist,"%s",filename),filename[0])
	{
		
		if(fopen(filename,"r"))
		{ 
			fuxk=fopen(filename,"r");
			iDontLikeTree(fuxk);
			
		} 
	
		for(int i=0;i<10;i++)
		{
			filename[i]=0; 
		} 
		
	}	
									//etelpmoc si eert al 
	mix();
	
	search(); 
	
	
}
