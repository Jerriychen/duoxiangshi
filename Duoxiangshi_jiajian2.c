#include<stdio.h>
#include<malloc.h>
#define NULL ((void *)0)
#define LEN sizeof(struct Duoxiangshi)

struct Duoxiangshi
{
	int a;									//系数
	int n;									//指数
	struct Duoxiangshi *next;
};

struct Duoxiangshi *create();
struct Duoxiangshi *paixu(struct Duoxiangshi *);
struct Duoxiangshi *addsubfunction(struct Duoxiangshi *,struct Duoxiangshi *,int);
void show(struct Duoxiangshi *);

int main(){
	struct Duoxiangshi *duoxiangshi1=paixu(create());
	struct Duoxiangshi *duoxiangshi2=paixu(create());
	printf("\nA(x)=");
	show(duoxiangshi1);
	printf("\nB(x)=");
	show(duoxiangshi2);
	struct Duoxiangshi *add=addsubfunction(duoxiangshi1,duoxiangshi2,0);
	printf("\nA(x)+B(x)=");
	show(add);
	struct Duoxiangshi *sub=addsubfunction(duoxiangshi1,duoxiangshi2,1);
	printf("\nA(x)-B(x)=");
	show(sub);
	return 0;
}

struct Duoxiangshi *create()																	//创建一个多项式链表 
{
    struct Duoxiangshi *head,*p1,*p2;
    int n=0;
    printf("请输入n对多项式的系数和指数，并以0和0作为结束:\n");
    p1=p2=(struct Duoxiangshi *)malloc(LEN);head=NULL;
    scanf("%d %d",&p1->a,&p1->n);
    while(p1->a!=0||p1->n!=0)
    {
        n++;
        if(n==1)
            head=p1;
        else
            p2->next=p1;
        p2=p1;
        p1=(struct Duoxiangshi *)malloc(LEN);
        scanf("%d %d",&p1->a,&p1->n);
    }
    p2->next=NULL;
    return head;
};

struct Duoxiangshi *paixu(struct Duoxiangshi *head)												//对链表进行排序，根据指数的降序进行排序 
{
	struct Duoxiangshi *p,*q;
    int temp1,temp2;
    for(p=head;p!=NULL;p=p->next)
        for(q=p->next;q!=NULL;q=q->next)
        {
            if(p->n<q->n)
            {
                temp1=p->n;temp2=p->a;
				p->n=q->n;p->a=q->a;
				q->n=temp1;q->a=temp2;
            }
        }
    for(p=head;p!=NULL;p=p->next)
        for(q=p->next;q!=NULL;q=q->next)
        {
            if(p->n==q->n)
            {p->a+=q->a;p->next=q->next;}
        }
    return head;
}

struct Duoxiangshi *addsubfunction(struct Duoxiangshi *q1,struct Duoxiangshi *q2,int p)				//多项式加减，当参数列表中的P为0时，进行加法运算，为1时进行减法运算 
{
	struct Duoxiangshi *head,*p1,*p2;
	p1=p2=(struct Duoxiangshi *)malloc(LEN);head=NULL;
	int n=1;
	while(q1!=NULL&&q2!=NULL)																		//当q1和q2都没有指向结尾时 ，进行加减运算 
	{
		if(q1->n>q2->n)
		   {p1->n=q1->n;
			p1->a=q1->a;
			q1=q1->next;
			goto s;}
		if(q1->n<q2->n)
		   {p1->n=q2->n;
			if(p==0) p1->a=q2->a;
			else p1->a=-q2->a;
		    q2=q2->next;
		    goto s;}
		if(q1->n==q2->n)
		{
			p1->n=q1->n;
			if(p==0) p1->a=q1->a+q2->a;
			else p1->a=q1->a-q2->a;
			q1=q1->next;
			q2=q2->next;
			goto s;
		}
		s:  if(n==1){head=p1;n++;}
            else	 p2->next=p1;
            p2=p1;
            p1=(struct Duoxiangshi *)malloc(LEN);
	}
	if(q1==NULL)													//当q1或q2结束时，将q1或q2赋给p2 
        {p2->next=q2;p2=p2->next;
        if(p==1)
         {while(p2!=NULL)
            {p2->a=-p2->a;p2=p2->next;}}
        }
    else
        p2->next=q1;
	return head;
}

void show(struct Duoxiangshi *p)									//输出多项式 
{
	while(p!=NULL)
	{
		if(p->n==0)													//当指数为0的情况 
		{
		if(p->a>0)
	            printf("+%d",p->a);
		else
	            printf("%d",p->a);
		}
		else if(p->n==1)											//档指数为1的情况 
		{
		if(p->a>0)
	        if(p->a==1)
	            printf("+X");
	        else
	            printf("+%dX",p->a);
		if(p->a<0)
	        if(p->a==-1)
	            printf("-X");
	        else
	            printf("%dX",p->a);
		}
		else														//当指数为其他数的情况 
		{
		if(p->a>0)
	        if(p->a==1)
	            printf("+X^%d",p->n);
	        else
	            printf("+%dX^%d",p->a,p->n);
		if(p->a<0)
	        if(p->a==-1)
	            printf("-X^%d",p->n);
	        else
	            printf("%dX^%d",p->a,p->n);
		}
	p=p->next;}
	printf("\n");
}
