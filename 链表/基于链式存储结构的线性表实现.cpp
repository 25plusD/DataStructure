#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
    
typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               LinkList L;    
     }elem[10];
     int length;
}LISTS;
LISTS Lists;

const int inf = 0x3f3f3f3f; //无穷大的定义
int whe=0;//作为是否进入多线性表模式的判断
int Listnum;
char Listname[30];
int a[100];


status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L) return INFEASIBLE;
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;

    /********** End **********/
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L){
        LinkList current=L;  
        while (current!=NULL) {  
            LinkList next=current->next;  
            free(current);  
            current=next;  
        } 
        L=NULL;
        return OK;
    }
    else return INFEASIBLE;


    /********** End **********/
}


status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L){
        LinkList current=L->next;  
        while (current!=NULL) {  
            LinkList next=current->next;  
            free(current);  
            current=next;  
        } 
        L->next=NULL;
        return OK;
    }
    else return INFEASIBLE;

    /********** End **********/
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(L->next==NULL) return TRUE;
    else return FALSE;
    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    int length=0;
    while(L->next!=NULL){
        L=L->next;
        length++;
    }
    return length;
    /********** End **********/
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    int length=0,j;
    LinkList p=L;
    while(p->next!=NULL){
        p=p->next;
        length++;
    }
    if(i<1||i>length) return ERROR;
    p=L;
    for(j=1;j<=i;j++){
        p=p->next;
    }
    e=p->data;
    return OK;
    /********** End **********/
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    int num=1;
    LinkList p=L->next;
    while(p!=NULL){
        if(p->data==e){
            return num;
        }
        p=p->next;
        num++;
    }
    return ERROR;
    /********** End **********/
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(L->next==NULL) return ERROR;
    LinkList p=L->next,q=L;
    if(p->data==e) return ERROR;
    while(p!=NULL){
        if(p->data==e){
            pre=q->data;
            return OK;
        }
        p=p->next;
        q=q->next;
    }
    return ERROR;
    /********** End **********/
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(L->next==NULL) return ERROR;//空表的特判
    LinkList p=L->next;
    while(p->next!=NULL){
        if(p->data==e){
            next=p->next->data;
            return OK;
        }
        p=p->next;
    }
    return ERROR;

    /********** End **********/
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    int length=0;
    LinkList p=L;
    while(p->next!=NULL){
        p=p->next;
        length++;
    }
    if(i<1||i>length+1) return ERROR;
    int j;
    p=L;
    for(j=2;j<=i;j++){
        p=p->next;
    }
    //插入新节点
    LinkList temp;
    temp=(LinkList)malloc(sizeof(LNode));
    temp->data=e;
    temp->next=p->next;
    p->next=temp;
    return OK;

    /********** End **********/
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    int length=0;
    LinkList p=L,q=L;
    while(p->next!=NULL){
        p=p->next;
        length++;
    }
    if(i<1||i>length) return ERROR;
    int j;
    p=L->next;
    for(j=2;j<=i;j++){
        p=p->next;
        q=q->next;
    }
    //删除节点
    q->next=p->next;
    e=p->data;
    free(p);
    return OK;

    /********** End **********/
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(L->next==NULL) return OK;
    while(L->next->next!=NULL){
        L=L->next;
        printf("%d ",L->data);
    }
    L=L->next;
    printf("%d",L->data);
    return OK;

    /********** End **********/
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(!L) return INFEASIBLE;
    FILE* fp;
    fp=fopen(FileName,"w+");
    LinkList p=L->next;
    while(p!=NULL){
        fprintf(fp,"%d ",p->data);
        p=p->next;
    }
    fclose(fp);
    return OK;

    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if(L) return INFEASIBLE;
    int data;
    L=(LinkList)malloc(sizeof(LNode));
    LinkList p=L;
    FILE* fp;
    fp=fopen(FileName,"r+");
    LinkList temp;
    while((fscanf(fp,"%d",&data))!=EOF){
        temp=(LinkList)malloc(sizeof(LNode));
        p->next=temp;
        temp->data=data;
        p=p->next;
    }
    p->next=NULL;
    fclose(fp);
    return OK;

    /********** End 2 **********/
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,j;
    for(i=0;i<Lists.length;i++){
        if(strcmp(ListName,Lists.elem[i].name)==0){
            return i+1;
        }
    }
    return 0;

    /********** End **********/
}

int reverseList(LinkList &L)
{//使用类似于头插法的方法来翻转链表
	if(!L) return INFEASIBLE;//线性表不存在则返回INFEASIBLE
	LinkList p=L->next;
	L->next=NULL;
	LinkList q;
	while(p!=NULL){
		q=p;//用q记录p的位置
		p=p->next;//p寻找下一个元素
		q->next=L->next;
		L->next=q;
	}
	return OK;
}

int RemoveNthFromEnd(LinkList &L,int n)
{//删除倒数第n个节点
	if(!L) return INFEASIBLE;//线性表不存在则返回INFEASIBLE
	int count=0,i;//用count来获取链表的长度
	LinkList p=L->next;
	LinkList q=L->next;//采用双指针
	while(p!=NULL){
		count++;
		p=p->next;
	}
	p=L;
	if(n>count||n<1) return ERROR;
	for(i=1;i<=count-n;i++){
		p=p->next;
		q=q->next;//p指到待删除节点的前一位置,q指到待删除节点
	}
	p->next=q->next;
	q->next=NULL;
	free(q);
	return OK;
}

int sortList(LinkList &L)
{//将线性表由小到大排序
	if(!L) return INFEASIBLE;//线性表不存在则返回INFEASIBLE
	int i=0,lena=0;
	LinkList p=L->next;
	while(p!=NULL){
		a[i]=p->data;
		p=p->next;
		lena++;
		i++;
	}
	//采用冒泡排序法 O(n^2)
	int j;
	ElemType temp;
	for(i=0;i<lena;i++){
		for(j=i;j<lena;j++){
			if(a[j]<a[i]){
				temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
		}
	}
	p=L->next;
	i=0;
	while(p!=NULL){
		p->data=a[i];
		p=p->next;
		i++;
	}
	return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int j;
    Lists.elem[Lists.length].L=NULL;
    j=InitList(Lists.elem[Lists.length].L);
    if(j==OK){
        //导入表名
        strcpy(Lists.elem[Lists.length].name,ListName);
        Lists.length++;
        return OK;
    }
    return INFEASIBLE;
    /********** End **********/
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,j;
    for(i=0;i<Lists.length;i++){
        if(strcmp(ListName,Lists.elem[i].name)==0){
            for(j=i;j<Lists.length-1;j++){
                Lists.elem[j]=Lists.elem[j+1];
            }
            Lists.length--;
            return OK;
        }
    }
    return INFEASIBLE;

    /********** End **********/
}


int main()
{
    int choice;
    ElemType e,pre,next;
    LinkList L;
    L=NULL;
    while(1){
    	printf(
	    "                基于链式存储结构的线性表实现\n"
	    "__________________________________________________________________\n"
	    "             1.InitList        10.ListInsert\n"
	    "             2.DestroyList     11.ListDelete\n"
	    "             3.ClearList       12.ListTraverse\n"
	    "             4.ListEmpty       13.SaveList & LoadList\n"
	    "             5.ListLength      14.reverseList\n"
	    "             6.GetElem         15.RemoveNthFromEnd\n"
	    "             7.LocateElem      16.sortList\n"
	    "             8.PriorElem       17.Lists\n"
	    "             9.NextElem        18.exit\n"
	    "                               \n"
	    "            													 \n"
	    "__________________________________________________________________\n"
	    "请输入你所选择的操作[1-18]：\n");
	    if(whe==0){
			printf("当前模式为单线性表模式\n");
		}else{
			printf("当前模式为多线性表模式\n");
		}
		scanf("%d",&choice);
    	switch(choice)//选择菜单
    	{
    		case 0:	{
				printf("无效的操作！输入的数字应在1~18之间，请重新输入!\n");
				break;
			}
    		case 1:	{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=InitList(Lists.elem[Listnum-1].L);
						//if(j==OK) printf("成功初始化线性表!\n");
						//else printf("不能对已经存在的线性表初始化!\n");
					}else{
						printf("输入的名称有误或不存在!\n");break;
					}
				}
				if(whe==0){
					j=InitList(L);
				}
				if(j==INFEASIBLE) printf("不能对已经存在的线性表初始化!\n");
				if(j==OK) printf("成功初始化线性表!\n");
				break;
	    	}
    		case 2:{
    			int j;
    			if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DestroyList(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DestroyList(L);
				}
    			if(j==INFEASIBLE) printf("线性表不存在,销毁失败!\n");
    			if(j==OK) printf("已成功删除线性表!\n");
				break;
			}
			case 3:{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ClearList(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ClearList(L);
				}
    			if(j==INFEASIBLE) printf("线性表不存在,清空失败!\n");
    			if(j==OK) printf("已成功清空线性表!\n");
				break;
			}
			case 4:{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ListEmpty(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ListEmpty(L);
				}
    			if(j==INFEASIBLE) printf("线性表不存在,判空失败!\n");
    			if(j==TRUE) printf("线性表为空!\n");
    			if(j==FALSE) printf("线性表不为空!\n");
				break;
			}
			case 5:{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ListLength(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ListLength(L);
				}
				if(j==INFEASIBLE) printf("线性表不存在,获取长度失败!\n");
    			else printf("线性表的长度为%d\n",j);
				break;
			}
			case 6:{
				int i;
				printf("请输入想要获取第几个元素:\n");
				scanf("%d",&i);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=GetElem(Lists.elem[Listnum-1].L,i,e);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=GetElem(L,i,e);
				}
				if(j==INFEASIBLE) printf("线性表不存在,获取失败!\n");
    			if(j==OK) printf("成功获取元素%d并存储在e中!\n",e);
    			if(j==ERROR) printf("输入的位置值不合法!\n");
				break;
			}
			case 7:{
				int e1;
				printf("请输入想要查找的元素的数值:\n");
				scanf("%d",&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=LocateElem(Lists.elem[Listnum-1].L,e1);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=LocateElem(L,e1);
				}
				if(j==INFEASIBLE) printf("线性表不存在,查找失败!\n");
    			if(j>0) printf("所要查找的元素位置序号为%d!\n",j);
    			if(j==0) printf("所要查找的元素不存在!\n");
				break;
			}
			case 8:{
				int e1;
				printf("请输入想要获取何数值元素的前驱:\n");
				scanf("%d",&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=PriorElem(Lists.elem[Listnum-1].L,e1,pre);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=PriorElem(L,e1,pre);
				}
				if(j==INFEASIBLE) printf("线性表不存在,获取失败!\n");
    			if(j==OK) printf("成功获取元素前驱%d并存储在pre中!\n",pre);
    			if(j==ERROR) printf("该元素没有前驱或该元素不存在!\n");
				break;
			}
			case 9:{
				int e1;
				printf("请输入想要获取何数值元素的后继:\n");
				scanf("%d",&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=NextElem(Lists.elem[Listnum-1].L,e1,next);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=NextElem(L,e1,next);
				}
				if(j==INFEASIBLE) printf("线性表不存在,获取失败!\n");
    			if(j==OK) printf("成功获取元素后继%d并存储在next中!\n",next);
    			if(j==ERROR) printf("该元素没有后继或该元素不存在!\n");
				break;
			}
			case 10:{
				int i,e1;
				printf("请输入 在第几个元素之前插入 和 想要插入的元素的数值 (中间以空格分隔):\n");
				scanf("%d %d",&i,&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ListInsert(Lists.elem[Listnum-1].L,i,e1);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ListInsert(L,i,e1);
				}
				if(j==INFEASIBLE) printf("线性表不存在,插入失败!\n");
    			if(j==OK) printf("成功插入!\n");
    			if(j==ERROR) printf("插入位置不正确!\n");
				break;
			}
			case 11:{
				int i;
				printf("请输入删除第几个元素:\n");
				scanf("%d",&i);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ListDelete(Lists.elem[Listnum-1].L,i,e);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ListDelete(L,i,e);
				}
				if(j==INFEASIBLE) printf("线性表不存在,删除失败!\n");
    			if(j==OK) printf("成功删除并将元素值%d保存在e中!\n",e);
    			if(j==ERROR) printf("删除位置不正确!\n");
				break;
			}
			case 12:{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ListTraverse(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ListTraverse(L);
				}
    			if(j==INFEASIBLE) printf("线性表不存在,遍历失败!\n");
    			if(j==OK) printf("\n已成功遍历线性表!\n");
				break;
			}
			case 13:{
				char ListName[100];
				int key;
				file:
				printf("请选择你的操作:1.将线性表写入文件 2.将文件中的数据读入线性表 3.退出该功能\n");
				scanf("%d",&key);
				printf("请输入文件名\n");
				fflush(stdin);				
				scanf("%[^\n]",ListName);
				switch(key)
				{
					case 0:{
						printf("无效的操作！输入的数字应在1~3之间，请重新输入!\n");
						goto file;
						break;
					}
					case 1:{
						int j=SaveList(L,ListName);
						if(whe==1){
							printf("请输入想要操作的线性表的名称:\n");
							scanf("%s",Listname);
							Listnum=LocateList(Lists,Listname);
							if(Listnum!=0){
								j=SaveList(Lists.elem[Listnum-1].L,ListName);
							}else{
								printf("输入的名称有误或不存在!\n");
							}
						}	
    					if(j==INFEASIBLE) printf("线性表不存在,写入失败!\n");
    					if(j==OK) printf("写入成功!\n");
						break;
					}
					case 2:{
						int j=LoadList(L,ListName);
						if(whe==1){
							printf("请输入想要操作的线性表的名称:\n");
							scanf("%s",Listname);
							Listnum=LocateList(Lists,Listname);
							if(Listnum!=0){
								j=LoadList(Lists.elem[Listnum-1].L,ListName);
							}else{
								printf("输入的名称有误或不存在!\n");
							}
						}
    					if(j==INFEASIBLE) printf("线性表已经存在,读取失败!\n");
    					if(j==OK) printf("读取成功!\n");
						break;
					}
					case 3:break;
					default:{
						printf("无效的操作！输入的数字应在1~3之间，请重新输入!\n");
						goto file;
						break;
					}
				}
				break;
			}
			case 14:{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=reverseList(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=reverseList(L);
				}
				if (j==INFEASIBLE) printf("线性表不存在或为空表,无法翻转!\n");
				else printf("链表已成功翻转!\n",j);
				break;
			}
			case 15:{
				int k;
				printf("请输入想要删除倒数第几个节点:\n");
				scanf("%d",&k);
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=RemoveNthFromEnd(Lists.elem[Listnum-1].L,k);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=RemoveNthFromEnd(L,k);
				}
				if(j==INFEASIBLE) printf("线性表不存在或为空表,删除失败!\n");
				if(j==ERROR) printf("n的值非法!\n");
    			if(j==OK) printf("已成功删除!\n",k,j);
				break;
			}
			case 16:{
				int j;
				if(whe==1){
					printf("请输入想要操作的线性表的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=sortList(Lists.elem[Listnum-1].L);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=sortList(L);
				}
				if (j==INFEASIBLE) printf("线性表不存在，排序失败!\n");
				if(j==OK) printf("已成功从小到大排序线性表中元素!\n");
				break;
			}
			case 17:{
				printf("进入多线性表操作模式!\n");
				whe=1;
				printf("请选择你的操作:1.多线性表添加 2.多线性表删除 3.多线性表查找 4.退出多线性表模式\n");
				int key;
				scanf("%d",&key);
				switch(key)
				{
					case 1:{
						printf("请输入想要创建的线性表的名称:\n");
						scanf("%s",Listname);
						int j=AddList(Lists,Listname);
						if(j==INFEASIBLE) printf("线性表不为空,创建失败!\n");
						if(j==OK) printf("创建成功!\n");
						break;
					}
					case 2:{
						printf("请输入想要删除的线性表的名称:\n");
						scanf("%s",Listname);
						int j=RemoveList(Lists,Listname);
						if(j==INFEASIBLE) printf("线性表不存在,删除失败!\n");
						if(j==OK) printf("删除成功!\n");
						break;
					}
					case 3:{
						printf("请输入想要查找的线性表的名称:\n");
						scanf("%s",Listname);
						int j=LocateList(Lists,Listname);
						if(j==0) printf("不存在该名称的线性表!\n");
						else printf("该线性表的序号为%d!\n",j);
						break;
					}
					case 4:{
						whe=0;
						break;
					}
					default:{
						printf("无效的操作！输入的数字应在1~4之间，请重新输入!\n");
						break;
					}
				}
				break;
			}
			case 18:{
				printf("已成功退出程序,欢迎下次再使用本系统!\n");
				return 0;
			}
    		default:{
				printf("无效的操作！输入的数字应在1~18之间，请重新输入!\n");
				break;
			}
		}
		fflush(stdin);
		system("pause");
		system("cls");
	}
}