#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int status;
typedef int KeyType; 
typedef struct {
     KeyType  key;
     char others[20];
} TElemType; //二叉树结点类型定义

typedef struct BiTNode{  //二叉链表结点的定义
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct QueueNode//队列节点
{
    BiTree data;
    QueueNode* next;
}QueueNode, * pQueueNode;

typedef struct Queue//队列
{
    pQueueNode front,rear;
}Queue, * pQueue;

typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               BiTree T;    
     }elem[10];
     int length;
}LISTS;
LISTS Lists;//森林体系

int creatcnt=-1;//1 a 0 null 0 null -1 null
int judgecreat=0;
int judgedestroy=0;
int whe=0;
int Listnum;
char Listname[30];
TElemType definition[100];
int num=0;
int ndepth=0;

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //判断是否有重复的序号
    if(T!=NULL) return INFEASIBLE;
    int i,j,len;
    if(judgecreat==0){
        for(len=0;definition[len].key!=-1;len++);
        //printf("%d\n",len);
        for(i=0;i<len-1;i++){
            for(j=i+1;j<len;j++){
                if(definition[i].key!=0&&definition[i].key==definition[j].key){
                    return ERROR;
                }
            }
        }
        judgecreat=1;
    }
   
    creatcnt++;
    int data0;
    data0=definition[creatcnt].key;
	if(data0==0){
		T=NULL;
    }
    if(data0!=0&&data0!=-1){
        T=(BiTree)malloc(sizeof(BiTNode));
        T->lchild=NULL;
        T->rchild=NULL;
		T->data.key = data0;
        strcpy(T->data.others,definition[creatcnt].others);//strcpy
		CreateBiTree(T->lchild,definition);
		CreateBiTree(T->rchild,definition);
	}

    return OK;
    /********** End **********/
}

status DestroyBiTree(BiTree &T)
{
	if(T){
		judgedestroy=1;
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
		T=NULL;
	}
	if(judgedestroy==0) return INFEASIBLE;
    else return OK;
}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T){
		ClearBiTree(T->lchild);
		ClearBiTree(T->rchild);
		free(T);
		T=NULL;
	}
    return OK;
    /********** End **********/
}

status BiTreeEmpty(BiTree T)
{
	if (T == NULL) return TRUE;
	else return FALSE;
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int m, n;
    if (T == NULL)
        return 0; //如果是空树，深度为0，递归结束
    else
    {
        m = BiTreeDepth(T->lchild); //递归计算左子树的深度记为m
        n = BiTreeDepth(T->rchild); //递归计算右子树的深度记为n
        if (m > n)
            return (m + 1); //二叉树的深度为m 与n的较大者加1
        else
            return (n + 1);
    }

    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //优先考虑左边,然后再考虑右边
    if (T == NULL) {
		return NULL;
	}
	if (T->data.key == e) {
		return T;
	}
	BiTree node = LocateNode(T->lchild, e);
	if (node != NULL) {
		// 左子树中找到了
		return node;
	}
	node = LocateNode(T->rchild, e);
	if (node != NULL) {
		return node;
	}
	else {
		return NULL;
	}
    /********** End **********/
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode *p=LocateNode(T,e);
    if(p==NULL){
        return ERROR;
    }
    BiTNode *q=LocateNode(T,value.key);
    if(q!=NULL&&e!=value.key){//需要注意保持二叉树中关键字的唯一性
        return ERROR;
    }
    p->data.key=value.key;
    int i;
    for(i=0;i<20;i++){
        p->data.others[i]=value.others[i];
    }
    return OK;
    /********** End **********/
}

BiTNode* GetParent(BiTree T,KeyType e)
//获取父亲结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //优先考虑左边,然后再考虑右边
    if (T == NULL ) {
		return NULL;
	}
    if(T->lchild!=NULL){
        if (T->lchild->data.key == e){
            return T;
        }
    }
    if(T->rchild!=NULL){
        if (T->rchild->data.key == e){
            return T;
        }
    }
	BiTree node = GetParent(T->lchild, e);
	if (node != NULL) {
		// 左子树中找到了
		return node;
	}
	node = GetParent(T->rchild, e);
	if (node != NULL) {
		return node;
	}
	else {
		return NULL;
	}
    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* p=GetParent(T,e);
    if(p==NULL) return ERROR;
    if(p->lchild==NULL||p->rchild==NULL) return ERROR;
    if(p->lchild->data.key==e) return p->rchild;
    if(p->rchild->data.key==e) return p->lchild;
    else return ERROR;
    /********** End **********/
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //LR=-1时的特判
    if(LR==-1){
        BiTree q=(BiTree)malloc(sizeof(BiTNode));
        q->lchild=NULL;
        q->rchild=T;
        T=q;
        T->data.key=c.key;
        strcpy(T->data.others,c.others);//strcpy
        return OK;
    }
    //否则则开始查找结点
    BiTree p=LocateNode(T,e);
    if(p==NULL) return ERROR;//没有找到的情况
    BiTree q=LocateNode(T,c.key);
    if(q!=NULL) return ERROR;//关键字有重复的情况
    if(LR==0){
        BiTree m=(BiTree)malloc(sizeof(BiTNode));
        m->data.key=c.key;
        strcpy(m->data.others,c.others);//复制数据
        BiTree n=p->lchild;
        p->lchild=m;
        m->lchild=NULL;
        m->rchild=n;
        return OK;
    }
    if(LR==1){
        BiTree m=(BiTree)malloc(sizeof(BiTNode));
        m->data.key=c.key;
        strcpy(m->data.others,c.others);//复制数据
        BiTree n=p->rchild;
        p->rchild=m;
        m->rchild=n;
        m->lchild=NULL;
        return OK;
    }
    return ERROR;
    /********** End **********/
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree p=LocateNode(T,e);
    if(p==NULL) return ERROR;//没有找到的情况
    if(p->lchild==NULL&&p->rchild==NULL){
        //度为0的情况
        BiTree q=GetParent(T,e);
        if(q==NULL){
            free(T);
            T=NULL;
            return OK;
        }
        if(q!=NULL){
            if(q->lchild->data.key==p->data.key){
                free(p);
                q->lchild=NULL;
            }
            else if(q->rchild->data.key==p->data.key){
                free(p);
                q->rchild=NULL;//判断p是q的左右哪个节点
            }
            return OK;
        }
    }
    if(p->lchild!=NULL&&p->rchild==NULL){
        //p左节点不为空
        BiTree q=GetParent(T,e);
        if(q==NULL){//p为根节点
            T=p->lchild;
            free(p);
            return OK;
        }
        if(q!=NULL){
            if(q->lchild->data.key==p->data.key){
                q->lchild=p->lchild;
                free(p);//p是q的左节点
            }
            else if(q->rchild->data.key==p->data.key){
                q->rchild=p->lchild;
                free(p);//p是q的右节点
            }
            return OK;
        }
    }
    if(p->rchild!=NULL&&p->lchild==NULL){
        //p右节点不为空
        BiTree q=GetParent(T,e);
        if(q==NULL){//p为根节点
            T=p->rchild;
            free(p);
            return OK;
        }
        if(q!=NULL){
            if(q->lchild->data.key==p->data.key){
                q->lchild=p->rchild;
                free(p);//p是q的左节点
            }
            else if(q->rchild->data.key==p->data.key){
                q->rchild=p->rchild;
                free(p);//p是q的右节点
            }
            return OK;
        }
    }
    if(p->rchild!=NULL&&p->lchild!=NULL){
        //度为2的情况
        BiTree m=p->lchild;//用m去指向左子树的最右节点
        BiTree q=GetParent(T,e);
        if(q==NULL){//p为根节点
            while(m->rchild!=NULL){
                m=m->rchild;
            }
            T=p->lchild;
            m->rchild=p->rchild;
            free(p);
            return OK;
        }
    }
	return ERROR;
    /********** End **********/
}

void visit(BiTree T)
{//visit访问二叉树每个结点的数据
    printf(" %d,%s",T->data.key,T->data.others);
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL){//判出条件
        return OK;
    }
    visit(T);
    PreOrderTraverse(T->lchild,visit);
    PreOrderTraverse(T->rchild,visit);
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL){//判出条件
        return OK;
    }
    InOrderTraverse(T->lchild,visit);
    visit(T);
    InOrderTraverse(T->rchild,visit);
	return OK;
    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL){//判出条件
        return OK;
    }
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    visit(T);
	return OK;
    /********** End **********/
}

pQueue initQ(pQueue pq)//建立只有头结点的队列
{
	pq->front = (pQueueNode)malloc(sizeof(QueueNode));
    pq->front->next = NULL;//队列的front和rear的next初始化为空
    pq->rear = pq->front;
    return pq;
}

void enqueue(pQueue pq, BiTree t)//把二叉树的数据取出放入队列
{
	pQueueNode pNew = new QueueNode;
	pNew->data = t;//二叉树的数据存入队列
	pNew->next = NULL;
	pq->rear->next = pNew;//尾插法建立连接
	pq->rear = pNew;//rear更新
}

BiTree dequeue(pQueue pq)//出队：删除队列第一个元素
{
	pQueueNode pTemp= (pQueueNode)malloc(sizeof(QueueNode));
	pTemp = pq->front->next;
	if (pTemp->next == NULL)//只剩下1个节点（不含队列空的头结点）
	{
		pq->rear = pq->front;
	}
	else{
		pq->front->next = pTemp->next;//front+1（从指向第1个非空节点改为指向第2个节点）
	}
	BiTree x;
	x= pTemp->data;//x为队列第一个元素的data
	free(pTemp);
	return x;
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //用队列实现非递归的层序遍历
    pQueue pq= (pQueue)malloc(sizeof(Queue));
	pq = initQ(pq);
	enqueue(pq,T);//取出二叉树的根节点，子节点存入队列
	while (pq->rear != pq->front)//当队列不为空
	{
		BiTree x = dequeue(pq);//x用于输出队列弹出元素的数据
		visit(x);
		if (x->lchild!=NULL)
		{
			enqueue(pq, x->lchild);//递归左节点
		}
		if (x->rchild!=NULL)
		{
			enqueue(pq, x->rchild);//递归右节点
		}
	}
    return OK;
    /********** End **********/
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的二叉树，成功返回逻辑序号，否则返回0
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

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    Lists.elem[Lists.length].T=NULL;
    int j,i=0;
	creatcnt=-1;
	judgecreat=0;//做必要的初始化
	printf("请输入数据(以-1 null结束):\n");
	do {
		scanf("%d%s",&definition[i].key,definition[i].others);
	} while (definition[i++].key!=-1);
    j=CreateBiTree(Lists.elem[Lists.length].T,definition);
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
                Lists.elem[j]=Lists.elem[j+1];//覆盖删除
            }
            Lists.length--;
            return OK;
        }
    }
    return INFEASIBLE;

    /********** End **********/
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    static FILE* fp=fopen(FileName,"w+");
    static int idx = 0;
    int i=idx++;
    if(T==NULL){//判出条件
        fprintf(fp,"0 ");//空节点用0代替
        //printf("0 ");
        return OK;
    }
    fprintf(fp,"%d ",T->data.key);
    //printf("%d ",T->data.key);
    fprintf(fp,"%s ",T->data.others);
    //printf("%s ",T->data.others);
    SaveBiTree(T->lchild,FileName);
    SaveBiTree(T->rchild,FileName);
    if(i==0) fclose(fp);
    return OK;//通过递归的方式输入先序
    /********** End 1 **********/
}

status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    static FILE* fp=fopen(FileName,"r+");
    static int idx = 0;
    int i=idx++;
    int num;
    fscanf(fp,"%d",&num);
    if(num==0){
        T=NULL;
    }else{
        T=(BiTree)malloc(sizeof(BiTNode));
        T->data.key=num;       //给新节点数据域赋值,生成根节点
        fscanf(fp,"%s",T->data.others);
        LoadBiTree(T->lchild,FileName);        //构造左子树过程
        LoadBiTree(T->rchild,FileName);        //构造右子树过程
    }
    if(i==0) fclose(fp);
    return OK;
    /********** End 2 **********/
}

int MaxPathSum(BiTree T)//测试数据1 a 0 null 3 c 6 f 0 null 4 d 0 null 0 null 11 x 0 null 0 null -1 null 输出15
{//采用递归的方式来计算二叉树根节点到叶子结点的最大路径
	int lenleft,lenright;
	if(T==NULL) return 0;//空节点为判出条件
	int num;
	num=T->data.key;
	lenleft=MaxPathSum(T->lchild);
	lenright=MaxPathSum(T->rchild);
	if(lenleft>=lenright) return (num+lenleft);//左大取左，右大取右
	else return (num+lenright);
}

BiTree InvertTree(BiTree &T)//测试数据同上,前序输出1 a 3 c 11 x 6 f 4 d
{//采用递归的方式来翻转二叉树
	if(T==NULL) return NULL;//判出条件
	BiTree tmp=T->lchild;
	T->lchild=InvertTree(T->rchild);
	T->rchild=InvertTree(tmp);
	return T;
}

int DepthAssitant(BiTree T,int currentdepth,KeyType e)
{//求指定结点深度的辅助函数
	if(T==NULL) return 0;//判出条件
	currentdepth++;
	if(T->data.key==e){
		ndepth=currentdepth;
		return currentdepth;
	}
	if(T->lchild!=NULL) currentdepth=DepthAssitant(T->lchild,currentdepth,e);
	if(T->rchild!=NULL) currentdepth=DepthAssitant(T->rchild,currentdepth,e);
	return (currentdepth-1);
}

int NodeDepth(BiTree T,KeyType e)
{//求指定结点的深度
	int depth=0;
	ndepth=0;
	depth=DepthAssitant(T,depth,e);
	depth=ndepth;
	return depth;
}

int LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)//测试数据同上,输入11 4，输出3
{//寻找某两个节点的最近公共祖先
	BiTree tmp;
	if(NodeDepth(T,e1)==0||NodeDepth(T,e2)==0) return ERROR;//没有找到e1 e2的情况
	if(NodeDepth(T,e1)==1) return e1;
	if(NodeDepth(T,e2)==1) return e2;//其中某个结点为根节点的情况
	while(NodeDepth(T,e1)!=NodeDepth(T,e2)){
		if(NodeDepth(T,e1)>NodeDepth(T,e2)){
			tmp=GetParent(T,e1);
			e1=tmp->data.key;
		}
		if(NodeDepth(T,e1)<NodeDepth(T,e2)){
			tmp=GetParent(T,e2);
			e2=tmp->data.key;
		}
	}
	if(e1==e2) return e1;//找到的情况
	//同层时还没找到,则同时向上找
	while(NodeDepth(T,e1)!=1){
		if(e1==e2) return e1;
		tmp=GetParent(T,e1);
		e1=tmp->data.key;
		tmp=GetParent(T,e2);
		e2=tmp->data.key;
	}
	return e1;
}


int main()
{
	BiTree T=NULL,TC;
	Lists.length=0;
	TElemType e;
	int choice;
    while(1){
    	printf(
	    "                基于二叉链表的二叉树实现\n"
	    "__________________________________________________________________\n"
	    "             1.CreateBiTree      10.DeleteNode\n"
	    "             2.DestroyBiTree     11.PreOrderTraverse\n"
	    "             3.ClearBiTree       12.InOrderTraverse\n"
	    "             4.BiTreeEmpty       13.PostOrderTraverse\n"
	    "             5.BiTreeDepth       14.LevelOrderTraverse\n"
	    "             6.LocateNode        15.SaveBiTree & LoadBiTree\n"
	    "             7.Assign            16.MaxPathSum\n"
	    "             8.GetSibling        17.LowestCommonAncestor\n"
	    "             9.InsertNode        18.InvertTree          \n"
	    "             20.exit             19.TreeLists\n"
	    "                                						   \n"
	    "__________________________________________________________________\n"
	    "请输入你所选择的操作[1-20]：\n");
	    if(whe==0){
			printf("当前模式为单二叉树模式\n");
		}else{
			printf("当前模式为多二叉树模式\n");
		}
		scanf("%d",&choice);
    	switch(choice)//选择菜单
    	{
    		case 0:	{
				printf("无效的操作！输入的数字应在1~20之间，请重新输入!\n");
				break;
			}
    		case 1:	{
				int j,i=0;
				creatcnt=-1;
				judgecreat=0;//做必要的初始化
				printf("请输入数据(以-1 null结束):\n");
				do {
					scanf("%d %s",&definition[i].key,definition[i].others);
				} while (definition[i++].key!=-1);
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=CreateBiTree(Lists.elem[Listnum-1].T,definition);
					}else{
						printf("输入的名称有误或不存在!\n");break;
					}
				}
				if(whe==0){
					j=CreateBiTree(T,definition);
				}
				if(j==INFEASIBLE) printf("不能对已经存在的二叉树初始化!\n");
				if(j==ERROR) printf("关键字不唯一!\n");
				if(j==OK) printf("成功初始化二叉树!\n");
				break;
	    	}
    		case 2:{
    			int j;
    			judgedestroy=0;
    			if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DestroyBiTree(Lists.elem[Listnum-1].T);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DestroyBiTree(T);
				}
    			if(j==INFEASIBLE) printf("二叉树不存在,销毁失败!\n");
    			if(j==OK) printf("已成功删除二叉树!\n");
				break;
			}
			case 3:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ClearBiTree(Lists.elem[Listnum-1].T);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ClearBiTree(T);
				}
    			if(j==INFEASIBLE) printf("二叉树不存在,清空失败!\n");
    			if(j==OK) printf("已成功清空二叉树!\n");
				break;
			}
			case 4:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=BiTreeEmpty(Lists.elem[Listnum-1].T);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=BiTreeEmpty(T);
				}
    			if(j==INFEASIBLE) printf("二叉树不存在,判空失败!\n");
    			if(j==TRUE) printf("二叉树为空!\n");
    			if(j==FALSE) printf("二叉树不为空!\n");
				break;
			}
			case 5:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=BiTreeDepth(Lists.elem[Listnum-1].T);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=BiTreeDepth(T);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,获取深度失败!\n");
    			else printf("二叉树的深度为%d\n",j);
				break;
			}
			case 6:{
				int i;
				printf("请输入想要获取元素的内容:\n");
				scanf("%d",&i);
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						TC=LocateNode(Lists.elem[Listnum-1].T,i);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					TC=LocateNode(T,i);
				}
				//if(j==INFEASIBLE) printf("二叉树不存在,获取失败!\n");
    			if(TC) printf("成功获取元素结点%s并存储在TC中!\n",TC->data.others);
    			if(TC==NULL) printf("未查找到该元素!\n");
				break;
			}
			case 7:{
				int e1;
				printf("请输入想要被替换的结点关键字:\n");
				scanf("%d",&e1);
				TElemType value;
				printf("请输入想要将结点关键字替换为什么:\n");
				scanf("%d %s",&value.key,value.others);
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=Assign(Lists.elem[Listnum-1].T,e1,value);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=Assign(T,e1,value);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,赋值失败!\n");
    			if(j==OK) printf("结点赋值成功!\n");
    			if(j==ERROR) printf("所要查找的元素不存在或关键字不唯一!\n");
				break;
			}
			case 8:{
				int e1;
				printf("请输入想要获取何关键字的兄弟结点:\n");
				scanf("%d",&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						TC=GetSibling(Lists.elem[Listnum-1].T,e1);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					TC=GetSibling(T,e1);
				}
				//if(j==INFEASIBLE) printf("二叉树不存在,获取失败!\n");
    			if(TC) printf("成功获取元素兄弟结点%d %s!\n",TC->data.key,TC->data.others);
    			if(TC==NULL) printf("该元素没有兄弟结点或该元素不存在!\n");
				break;
			}
			case 9:{
				int e1,LR;
				TElemType c;
				printf("请输入想要在何关键字处插入 插入的操作为-1或者0或者1时为根节点或左孩子或右孩子 插入何值:\n");
				scanf("%d %d %d %s",&e1,&LR,&c.key,c.others);
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=InsertNode(Lists.elem[Listnum-1].T,e1,LR,c);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=InsertNode(T,e1,LR,c);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,获取失败!\n");
    			if(j==OK) printf("成功插入元素!\n");
    			if(j==ERROR) printf("插入失败!\n");
				break;
			}
			case 10:{
				int e1;
				printf("请输入想要删除的关键字:\n");
				scanf("%d",&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DeleteNode(Lists.elem[Listnum-1].T,e1);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DeleteNode(T,e1);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,插入失败!\n");
    			if(j==OK) printf("成功删除!\n");
    			if(j==ERROR) printf("删除失败!\n");
				break;
			}
			case 11:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=PreOrderTraverse(Lists.elem[Listnum-1].T,visit);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=PreOrderTraverse(T,visit);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,遍历失败!\n");
    			if(j==OK) printf("\n已成功先序遍历二叉树!\n");
    			//if(j==ERROR) printf("删除位置不正确!\n");
				break;
			}
			case 12:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=InOrderTraverse(Lists.elem[Listnum-1].T,visit);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=InOrderTraverse(T,visit);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,遍历失败!\n");
    			if(j==OK) printf("\n已成功中序遍历二叉树!\n");
				break;
			}
			case 13:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=PostOrderTraverse(Lists.elem[Listnum-1].T,visit);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=PostOrderTraverse(T,visit);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,遍历失败!\n");
    			if(j==OK) printf("\n已成功后序遍历二叉树!\n");
				break;
			}
			case 14:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=LevelOrderTraverse(Lists.elem[Listnum-1].T,visit);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=LevelOrderTraverse(T,visit);
				}
				if(j==INFEASIBLE) printf("二叉树不存在,遍历失败!\n");
    			if(j==OK) printf("\n已成功层序遍历二叉树!\n");
				break;
			}
			case 15:{
				char ListName[100];
				int key;
				file:
				printf("请选择你的操作:1.将二叉树写入文件 2.将文件中的数据读入二叉树 3.退出该功能\n");
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
						int j=SaveBiTree(T,ListName);
						if(whe==1){
							printf("请输入想要操作的二叉树的名称:\n");
							scanf("%s",Listname);
							Listnum=LocateList(Lists,Listname);
							if(Listnum!=0){
								j=SaveBiTree(Lists.elem[Listnum-1].T,ListName);
							}else{
								printf("输入的名称有误或不存在!\n");
							}
						}	
    					if(j==INFEASIBLE) printf("二叉树不存在,写入失败!\n");
    					if(j==OK) printf("写入成功!\n");
						break;
					}
					case 2:{
						int j=LoadBiTree(T,ListName);
						if(whe==1){
							printf("请输入想要操作的二叉树的名称:\n");
							scanf("%s",Listname);
							Listnum=LocateList(Lists,Listname);
							if(Listnum!=0){
								j=LoadBiTree(Lists.elem[Listnum-1].T,ListName);
							}else{
								printf("输入的名称有误或不存在!\n");
							}
						}
    					if(j==INFEASIBLE) printf("二叉树已经存在,读取失败!\n");
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
			case 16:{
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=MaxPathSum(Lists.elem[Listnum-1].T);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=MaxPathSum(T);
				}
				if (j) printf("最长路径为%d!\n",j);
				else printf("求最长路径失败!\n");
				break;
			}
			case 17:{
				int e1,e2;
				printf("请输入想要查找哪两个顶点的最近公共祖先:\n");
				scanf("%d %d",&e1,&e2);
				int j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=LowestCommonAncestor(Lists.elem[Listnum-1].T,e1,e2);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=LowestCommonAncestor(T,e1,e2);
				}
				//if(j==INFEASIBLE) printf("线性表不存在或为空表,删除失败!\n");
				if(j==ERROR) printf("至少有一个顶点不在二叉树中!\n");
    			if(j) printf("最近公共祖先的关键字为%d!\n",j);
				break;
			}
			case 18:{
				BiTree j;
				if(whe==1){
					printf("请输入想要操作的二叉树的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=InvertTree(Lists.elem[Listnum].T);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=InvertTree(T);
				}
				if(j==NULL) printf("二叉树翻转失败!\n");
				if(j) printf("已成功翻转二叉树!\n");
				break;
			}
			case 19:{
				printf("进入多二叉树操作模式!\n");
				whe=1;
				printf("请选择你的操作:1.多二叉树添加 2.多二叉树删除 3.多二叉树查找 4.退出多二叉树模式\n");
				int key;
				scanf("%d",&key);
				switch(key)
				{
					case 1:{
						printf("请输入想要创建的二叉树的名称:\n");
						scanf("%s",Listname);
						int j=AddList(Lists,Listname);
						if(j==INFEASIBLE) printf("二叉树不为空,创建失败!\n");
						if(j==OK) printf("创建成功!\n");
						break;
					}
					case 2:{
						printf("请输入想要删除的二叉树的名称:\n");
						scanf("%s",Listname);
						int j=RemoveList(Lists,Listname);
						if(j==INFEASIBLE) printf("二叉树不存在,删除失败!\n");
						if(j==OK) printf("删除成功!\n");
						break;
					}
					case 3:{
						printf("请输入想要查找的二叉树的名称:\n");
						scanf("%s",Listname);
						int j=LocateList(Lists,Listname);
						if(j==0) printf("不存在该名称的二叉树!\n");
						else printf("该二叉树的序号为%d!\n",j);
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
			case 20:{
				printf("已成功退出程序,欢迎下次再使用本系统!\n");
				return 0;
			}
    		default:{
				printf("无效的操作！输入的数字应在1~20之间，请重新输入!\n");
				break;
			}
		}
		fflush(stdin);
		system("pause");
		system("cls");
	}
	return 0;
}



