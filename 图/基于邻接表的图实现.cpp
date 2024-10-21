#include "stdio.h"
#include "stdlib.h"
#include<string.h>
#include "ctype.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //顶点类型定义


typedef struct ArcNode {         //弧结点类型定义
	 int adjvex;              //顶点位置编号 
	 struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
	 VertexType data;       	//顶点信息
	 ArcNode *firstarc;      	 //指向第一条弧
	} VNode,AdjList[MAX_VERTEX_NUM];
	
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
   } ALGraph;

typedef struct QueueNode//队列节点
{
    VertexType data;
    QueueNode* next;
}QueueNode, * pQueueNode;

typedef struct Queue//队列
{
    pQueueNode front,rear;
}Queue, * pQueue;


typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               ALGraph G;    
     }elem[10];
     int length;
}LISTS;


LISTS Lists;//多图体系
int mark[MAX_VERTEX_NUM];
int arcmat[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
VertexType V[30];
KeyType VR[100][2];
const int inf = 0x3f3f3f3f; //无穷大的定义
int whe=0;
char Listname[30];
int Listnum;


int LocateVex(ALGraph G,KeyType u)
{//定位端点,成功则返回下标i,反之返回-1;
    int i;
    for(i=0;i<G.vexnum;i++){
        if(u==G.vertices[i].data.key) return i;
    }
    return INFEASIBLE;
}

pQueue InitQueue(pQueue pq)//建立只有头结点的队列
{
	pq->front = (pQueueNode)malloc(sizeof(QueueNode));
    pq->front->next = NULL;//队列的front和rear的next初始化为空
    pq->rear = pq->front;
    return pq;
}

void EnQueue(pQueue pq,VertexType t)//把图的数据取出放入队列
{
	pQueueNode pNew = new QueueNode;
	pNew->data = t;//图的数据存入队列
	pNew->next = NULL;
	pq->rear->next = pNew;//尾插法建立连接
	pq->rear = pNew;//rear更新
}

int DeQueue(pQueue pq,int &u,ALGraph G)//出队：删除队列第一个元素并存储在u中
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
	VertexType x;
	x= pTemp->data;//x为队列第一个元素的data
	free(pTemp);
    u=LocateVex(G,x.key);
	return OK;
}

int QueueEmpty(pQueue pq)
{
    if(pq->rear == pq->front) return 0;
    return 1;
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //judge error
    //空图返回ERROR(什么破玩意)
    int size=MAX_VERTEX_NUM;
    if(V[0].key==-1) return ERROR;
    int vexnum=0;
    for(vexnum=0;V[vexnum].key!=-1;vexnum++);
    int i,j,k;
    for(i=0;i<vexnum-1;i++){
        for(j=i+1;j<vexnum;j++){
            if(V[i].key==V[j].key) return ERROR;//判重
        }
    }
    int arcnum=0;
    for(arcnum=0;VR[arcnum][0]!=-1;arcnum++);
    G.vexnum=vexnum;
    G.arcnum=arcnum;
    while(vexnum>size){
        //G.vertices=(VNode*)realloc(G.vertices,size+MAX_VERTEX_NUM);
        //size=size+MAX_VERTEX_NUM;
        return ERROR;
    }
    //copy头结点数据
    for(i=0;i<vexnum;i++){
        G.vertices[i].data.key=V[i].key;
        G.vertices[i].firstarc=NULL;
        strcpy(G.vertices[i].data.others,V[i].others);
    }
    for(i=0;i<arcnum;i++){
        if(LocateVex(G,VR[i][0])==-1||LocateVex(G,VR[i][1])==-1) return ERROR;//判存在
    }
    //建立指针的连接
    ArcNode* p,*q;
    for(i=0;i<arcnum;i++){
        j=LocateVex(G,VR[i][0]);
        p=new ArcNode;
        p->adjvex=LocateVex(G,VR[i][1]);
        p->nextarc=G.vertices[j].firstarc;
        G.vertices[j].firstarc=p;
        k=LocateVex(G,VR[i][1]);
        q=new ArcNode;
        q->adjvex=LocateVex(G,VR[i][0]);
        q->nextarc=G.vertices[k].firstarc;
        G.vertices[k].firstarc=q;
    }
    return OK;

    /********** End **********/
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    if(G.vexnum==0) return INFEASIBLE;
    ArcNode* p;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].firstarc!=NULL){
            p=G.vertices[i].firstarc;
            while(p->nextarc!=NULL){
                ArcNode* q=p->nextarc;
                free(p);
                p=q;
            }
            free(p);
            G.vertices[i].firstarc=NULL;
        }
        //G.vertices[i].data.key=0;
    }
    G.vexnum=0;
    G.arcnum=0;
    return OK;
    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    for(i=0;i<G.vexnum;i++){
        if(value.key==G.vertices[i].data.key) return ERROR;
    }
    for(i=0;i<G.vexnum;i++){
        if(u==G.vertices[i].data.key){
            G.vertices[i].data.key=value.key;
            strcpy(G.vertices[i].data.others,value.others);
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}


int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,j,num;
    i=LocateVex(G,u);
    if(i==-1) return -1;
    if(G.vertices[i].firstarc==NULL) return -1;
    num=G.vertices[i].firstarc->adjvex;
    return num;

    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,j,num;
    i=LocateVex(G,v);
    if(i==-1) return -1;
    if(G.vertices[i].firstarc==NULL) return -1;
    ArcNode* p=G.vertices[i].firstarc;
    while(p->nextarc!=NULL){
        if(p->adjvex==LocateVex(G,w)){
            return p->nextarc->adjvex;
        }
        p=p->nextarc;
    }
    return -1;
    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum>=MAX_VERTEX_NUM) return ERROR;
    if(LocateVex(G,v.key)!=-1) return ERROR;
    G.vertices[G.vexnum].data.key=v.key;
    G.vertices[G.vexnum].firstarc=NULL;
    strcpy(G.vertices[G.vexnum].data.others,v.others);
    G.vexnum++;
    return OK;
    /********** End **********/
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=0,j,num;
    i=LocateVex(G,v);
    if(i==-1) return -1;
    if(G.vexnum==1) return -1;//删除后为空表报错
    ArcNode* p=G.vertices[i].firstarc;
    while(p!=NULL){
        ArcNode* q=p->nextarc;
        num=p->adjvex;
        ArcNode* m=G.vertices[num].firstarc;
        ArcNode* n=G.vertices[num].firstarc->nextarc;
        if(m->adjvex==LocateVex(G,v)){
        	G.vertices[num].firstarc=m->nextarc;
        	free(m);
		}
	    else{
			while(m->nextarc!=NULL){
	            if(n->adjvex==LocateVex(G,v)){
	                m->nextarc=n->nextarc;
	                free(n);
	                break;
	            }
	            n=n->nextarc;
	            m=m->nextarc;
	        }
	    }
        G.arcnum=G.arcnum-1;
        free(p);
        p=q;
    }
    G.vertices[i].firstarc=NULL;
    for(j=i;j<G.vexnum;j++){
        G.vertices[j].firstarc= G.vertices[j+1].firstarc;
        G.vertices[j].data.key=G.vertices[j+1].data.key;
        strcpy(G.vertices[j].data.others,G.vertices[j+1].data.others);
    }
    G.vexnum--;
    for(j=0;j<G.vexnum;j++){
    	p=G.vertices[j].firstarc;
    	while(p!=NULL){
    		if(p->adjvex>i) p->adjvex--;
    		p=p->nextarc;
		}
	}
    return OK;
    /********** End **********/
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int vex1,vex2;
    vex1=LocateVex(G,v);
    vex2=LocateVex(G,w);
    if(vex1==-1||vex2==-1) return ERROR;
    ArcNode* test=G.vertices[vex1].firstarc;
    while(test!=NULL){
        if(test->adjvex==vex2) return ERROR;
        test=test->nextarc;
    }
    ArcNode* p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=vex2;
    p->nextarc=G.vertices[vex1].firstarc;
    G.vertices[vex1].firstarc=p;
    ArcNode* q=(ArcNode*)malloc(sizeof(ArcNode));
    q->adjvex=vex1;
    q->nextarc=G.vertices[vex2].firstarc;
    G.vertices[vex2].firstarc=q;
    G.arcnum++;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int vex1,vex2;
    vex1=LocateVex(G,v);
    vex2=LocateVex(G,w);
    if(vex1==-1||vex2==-1) return ERROR;
    ArcNode* p,*q;
    p=G.vertices[vex1].firstarc;
    if(p==NULL) return ERROR;
    if(p->adjvex==vex2){
        free(p);
        G.vertices[vex1].firstarc=NULL;
        goto next;
    }
    q=p->nextarc;
    while(q!=NULL){
        if(q->adjvex==vex2){
            p->nextarc=q->nextarc;
            free(q);
            goto next;
        }
        p=p->nextarc;
        q=q->nextarc;
    }
    return ERROR;
    next:
    p=G.vertices[vex2].firstarc;
    if(p==NULL) return ERROR;
    if(p->adjvex==vex1){
        free(p);
        G.vertices[vex2].firstarc=NULL;
        G.arcnum--;
        return OK;
    }
    q=p->nextarc;
    while(q!=NULL){
        if(q->adjvex==vex1){
            p->nextarc=q->nextarc;
            free(q);
            G.arcnum--;
            return OK;
        }
        p=p->nextarc;
        q=q->nextarc;
    }
    return ERROR;
    /********** End **********/
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

void DFS(ALGraph G,int v,void (*visit)(VertexType))
{
    mark[v]=1;
    visit(G.vertices[v].data);
    int w;
    for(w=FirstAdjVex(G,G.vertices[v].data.key);w>=0;w=NextAdjVex(G,G.vertices[v].data.key,G.vertices[w].data.key)){
        if(mark[w]==0) DFS(G,w,visit);
    }
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int v;
    for(v=0;v<G.vexnum;v++) mark[v]=0;//初始化
    for(v=0;v<G.vexnum;v++){
        if(mark[v]==0) DFS(G,v,visit);
    }
    return OK;
    /********** End **********/
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int v,u,w;
    for(v=0;v<G.vexnum;++v) mark[v]=0;
    pQueue Q=(pQueue)malloc(sizeof(Queue));
    Q=InitQueue(Q);
    for(v=0;v<G.vexnum;++v){
        if(mark[v]==0){
            mark[v]=1;
            visit(G.vertices[v].data);
            EnQueue(Q,G.vertices[v].data);
            while(QueueEmpty(Q)!=0){
                DeQueue(Q,u,G);
                for(w=FirstAdjVex(G,G.vertices[u].data.key);w>=0;w=NextAdjVex(G,G.vertices[u].data.key,G.vertices[w].data.key)){
                    if(mark[w]==0){
                        visit(G.vertices[w].data);
                        mark[w]=1;
                        EnQueue(Q,G.vertices[w].data);
                    }
                }
            }
        }
    }
    return OK;
    /********** End **********/
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE* fp=fopen(FileName,"w+");
    int i;
    ArcNode* p;
    for(i=0;i<G.vexnum;i++){
        fprintf(fp,"%d ",G.vertices[i].data.key);
        fprintf(fp,"%s ",G.vertices[i].data.others);
        if(G.vertices[i].firstarc!=NULL){
            p=G.vertices[i].firstarc;
            while(p!=NULL){
                fprintf(fp,"%d ",p->adjvex);
                p=p->nextarc;
            }
        }
        fprintf(fp,"-1 ");//末尾用-1代替
        //G.vertices[i].data.key=0;
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE* fp=fopen(FileName,"r+");
    int headnum=0,i=0,arcnum=0;
    ArcNode* p,*q;
    while((fscanf(fp,"%d",&headnum))!=EOF){//头结点创建完毕
        G.vertices[i].data.key=headnum;
        fscanf(fp,"%s",G.vertices[i].data.others);
        G.vexnum++;//读取头结点
        //接下来读取弧结点
        fscanf(fp,"%d",&arcnum);
        q=G.vertices[i].firstarc;
        if(arcnum==-1){
        	G.vertices[i].firstarc=NULL;
        	i++;
        	continue;
		}
        if(arcnum!=-1){
        	p=new ArcNode;
        	p->adjvex=arcnum;
        	G.vertices[i].firstarc=p;
        	q=p;
		}
		fscanf(fp,"%d",&arcnum);
        while(arcnum!=-1){
            p=new ArcNode;
            p->adjvex=arcnum;
            q->nextarc=p;
            q=p;
            G.arcnum++;
            fscanf(fp,"%d",&arcnum);//直到读到-1
        }
        p->nextarc=NULL;
        i++;
    }
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

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=0,j;
	printf("请输入顶点数据(以-1 nil结束):\n");
	do {
	    scanf("%d%s",&V[i].key,V[i].others);
	} while(V[i++].key!=-1);
	i=0;
	printf("请输入边数据(以-1 -1结束):\n");
	do {
	    scanf("%d%d",&VR[i][0],&VR[i][1]);
	} while(VR[i++][0]!=-1);
    j=CreateGraph(Lists.elem[Lists.length].G,V,VR);
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

void table_convert_matrix(ALGraph G) { // 邻接表转化为邻接矩阵
	int i,j;
    for(i = 1; i <= G.vexnum; i++) {
        for(j = 1; j <= G.vexnum; j++) {
            arcmat[i][j] = inf; // 初始化邻接矩阵
        }
    }
    ArcNode *p;
    for(i = 1; i <= G.vexnum; i++) { //依次遍历各顶点表结点为头的边链表
        p = G.vertices[i-1].firstarc; // 取出顶点 i 的第一条出边
        while(p) { //遍历边链表
            arcmat[i][p->adjvex+1] = 1; 
            p = p -> nextarc; // 取出下一条出边
        }
    }
    for(i=1;i<=G.vexnum; i++){
    	arcmat[i][i] = 0;//自身到自身的距离为0;
	}
}

int min(int a,int b)
{//求两数的最小值
	if(a<=b) return a;
	else return b;
}

void Floyd(ALGraph G)
{   //表示从j点到k点的最短路径，其中的i为中间的中转点
    for (int i = 1; i <= G.vexnum; ++i) //i为中转在最外层
        for (int j = 1; j <= G.vexnum; ++j)
            for (int k = 1; k <= G.vexnum; ++k)
                arcmat[j][k] = min(arcmat[j][k], arcmat[j][i] + arcmat[i][k]);
}

int VerticesSetLessThanK(ALGraph G,int v,int k)
{//求距离小于k的顶点集合
	int i;
	table_convert_matrix(G);
	Floyd(G);//Floyd算法
	int v0=LocateVex(G,v)+1;//下标不统一,故+1
	printf("与顶点v距离小于k的顶点集合为:");
	for(i=1;i<=G.vexnum;i++){
		if(arcmat[v0][i]<k){
			printf(" %d %s",G.vertices[i-1].data.key,G.vertices[i-1].data.others);
		}
	}
	return OK;
}

int ShortestPathLength(ALGraph G,int v,int w)
{//求两顶点间的最短路径函数
	table_convert_matrix(G);
	Floyd(G);//Floyd算法
	int v0=LocateVex(G,v)+1;//下标不统一,故+1
	int w0=LocateVex(G,w)+1;//下标不统一,故+1
	return arcmat[v0][w0];
}

void DFS0(ALGraph G,int v)
{//深度优先搜索辅助求图的连通分量个数函数
    mark[v]=1;
    //visit(G.vertices[v].data);
    int w;
    for(w=FirstAdjVex(G,G.vertices[v].data.key);w>=0;w=NextAdjVex(G,G.vertices[v].data.key,G.vertices[w].data.key)){
        if(mark[w]==0) DFS0(G,w);
    }
}

int ConnectedComponentsNums(ALGraph G)
{//求图的连通分量个数函数
	int v,cnt=0;
    for(v=0;v<G.vexnum;v++) mark[v]=0;//初始化
    for(v=0;v<G.vexnum;v++){
        if(mark[v]==0){
        	DFS0(G,v);
        	cnt++;
		}
    }
    return cnt;
}


int main()//头歌中测试集 5 线性表 8 集合 7 二叉树 6 无向图 -1 nil    5 6 5 7 6 7 7 8 -1 -1
{
	ALGraph G;
	G.vexnum=0;
	G.arcnum=0;
	Lists.length=0;
	int choice;
    while(1){
    	printf(
	    "                  基于邻接表的图实现\n"
	    "__________________________________________________________________\n"
	    "             1.CreateGraph      10.DeleteArc\n"
	    "             2.DestroyGraph     11.DFSTraverse\n"
	    "             3.LocateVex        12.BFSTraverse\n"
	    "             4.PutVex           13.VerticesSetLessThanK\n"
	    "             5.FirstAdjVex      14.ShortestPathLength\n"
	    "             6.NextAdjVex       15.SaveGraph & LoadGraph\n"
	    "             7.InsertVex        16.ConnectedComponentsNums\n"
	    "             8.DeleteVex        17.GraphLists\n"
	    "             9.InsertArc        18.exit          \n"
	    "                                						   \n"
	    "__________________________________________________________________\n"
	    "请输入你所选择的操作[1-18]：\n");
	    if(whe==0){
			printf("当前模式为单图模式\n");
		}else{
			printf("当前模式为多图模式\n");
		}
		scanf("%d",&choice);
    	switch(choice)//选择菜单
    	{
    		case 0:	{
				printf("无效的操作！输入的数字应在1~18之间，请重新输入!\n");
				break;
			}
    		case 1:	{
				int i=0,j;
				if(G.vexnum!=0){
					printf("不能对已经存在的图初始化!\n");
					break;
				}
				printf("请输入顶点数据(以-1 nil结束):\n");
				do {
				    scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i=0;
				printf("请输入边数据(以-1 -1结束):\n");
				do {
				    scanf("%d%d",&VR[i][0],&VR[i][1]);
				} while(VR[i++][0]!=-1);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=CreateGraph(Lists.elem[Listnum-1].G,V,VR);
					}else{
						printf("输入的名称有误或不存在!\n");break;
					}
				}
				if(whe==0){
					j=CreateGraph(G,V,VR);
				}
				if(j==ERROR) printf("输入的顶点或弧不正确!\n");
				if(j==OK) printf("成功创建无向图!\n");
				break;
	    	}
    		case 2:{
    			int j;
    			if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DestroyGraph(Lists.elem[Listnum-1].G);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DestroyGraph(G);
				}
    			if(j==INFEASIBLE) printf("图不存在,销毁失败!\n");
    			if(j==OK) printf("已成功销毁图!\n");
				break;
			}
			case 3:{
				int j;
				int u;
				printf("请输入顶点关键字:\n");
				scanf("%d",&u);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=LocateVex(Lists.elem[Listnum-1].G,u);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=LocateVex(G,u);
				}
    			if(j==INFEASIBLE) printf("该顶点不存在!\n");
    			if(j>=0) printf("该顶点在G中的位序为%d!\n",j);
				break;
			}
			case 4:{
				int j,u;
				VertexType value;
				printf("请输入想要赋值的顶点关键字:\n");
				scanf("%d",&u);
				printf("请输入想要赋的值:\n");
				scanf("%d %s",&value.key,value.others);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=PutVex(Lists.elem[Listnum-1].G,u,value);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=PutVex(G,u,value);
				}
    			if(j==ERROR) printf("查找失败或关键字不唯一!\n");
    			if(j==OK) printf("赋值成功!\n");
				break;
			}
			case 5:{
				int j;
				int u;
				printf("请输入获取何顶点的第一邻接顶点:\n");
				scanf("%d",&u);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=FirstAdjVex(Lists.elem[Listnum-1].G,u);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=FirstAdjVex(G,u);
				}
				if (j!=-1) printf("第一临接点为:%d %s\n",G.vertices[j].data.key,G.vertices[j].data.others);
				else printf("查找失败");
				break;
			}
			case 6:{
				int j;
				int v,w;
				printf("请输入查找v顶点的邻接点中w的下一个(中间以空格分隔):\n");
				scanf("%d %d",&v,&w);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=NextAdjVex(Lists.elem[Listnum-1].G,v,w);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=NextAdjVex(G,v,w);
				}
				if (j!=-1) printf("下一临接点为:%d %s\n",G.vertices[j].data.key,G.vertices[j].data.others);
				else printf("无下一邻接顶点或未查找到临接点\n");
				break;
			}
			case 7:{
				VertexType v;
				printf("请输入想要添加的新顶点v:\n");
				scanf("%d %s",&v.key,v.others);
				int j;
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=InsertVex(Lists.elem[Listnum-1].G,v);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=InsertVex(G,v);
				}
    			if(j==OK) printf("顶点插入成功!\n");
    			if(j==ERROR) printf("所要插入的顶点关键字不唯一或顶点个数已满!\n");
				break;
			}
			case 8:{
				int e1;
				printf("请输入想要删除何关键字的顶点:\n");
				scanf("%d",&e1);
				int j;
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DeleteVex(Lists.elem[Listnum-1].G,e1);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DeleteVex(G,e1);
				}
				//if(j==INFEASIBLE) printf("二叉树不存在,获取失败!\n");
    			if(j==OK) printf("已成功删除顶点!\n");
    			if(j==-1) printf("删除失败!\n");
				break;
			}
			case 9:{
				int v,w;
				printf("请输入插入边<v,w>(以空格分隔):\n");
				scanf("%d %d",&v,&w);
				int j;
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=InsertArc(Lists.elem[Listnum-1].G,v,w);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=InsertArc(G,v,w);
				}
				//if(j==INFEASIBLE) printf("二叉树不存在,获取失败!\n");
    			if(j==OK) printf("成功插入弧!\n");
    			if(j==ERROR) printf("插入失败!\n");
				break;
			}
			case 10:{
				int v,w;
				printf("请输入想要删除的弧<v,w>:\n");
				scanf("%d %d",&v,&w);
				int j;
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DeleteArc(Lists.elem[Listnum-1].G,v,w);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DeleteArc(G,v,w);
				}
				//if(j==INFEASIBLE) printf("二叉树不存在,插入失败!\n");
    			if(j==OK) printf("成功删除!\n");
    			if(j==ERROR) printf("删除失败!\n");
				break;
			}
			case 11:{
				int j;
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=DFSTraverse(Lists.elem[Listnum-1].G,visit);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=DFSTraverse(G,visit);
				}
    			if(j==OK) printf("\n已成功深度优先搜索图!\n");
    			else printf("深度优先搜索失败!\n");
    			//if(j==ERROR) printf("删除位置不正确!\n");
				break;
			}
			case 12:{
				int j;
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=BFSTraverse(Lists.elem[Listnum-1].G,visit);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=BFSTraverse(G,visit);
				}
				if(j==OK) printf("\n已成功广度优先搜索图!\n");
    			else printf("广度优先搜索失败!\n");
				break;
			}
			case 13:{
				int j;
				int v,k;
				printf("请输入获取与顶点v路径小于k的顶点中的v,k(以空格分隔):\n");
				scanf("%d %d",&v,&k);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=VerticesSetLessThanK(Lists.elem[Listnum-1].G,v,k);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=VerticesSetLessThanK(G,v,k);
				}
    			if(j==OK) printf("\n已成功获取与顶点v路径小于k的顶点集合!\n");
    			else printf("获取集合失败!\n");
				break;
			}
			case 14:{
				int j;
				int v,w;
				printf("请输入顶点v和顶点w(以空格分隔):\n");
				scanf("%d %d",&v,&w);
				if(whe==1){
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ShortestPathLength(Lists.elem[Listnum-1].G,v,w);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ShortestPathLength(G,v,w);
				}
				if(j>0&&j<inf) printf("\n顶点v到w的最短路径为%d!\n",j);
    			if(j==inf) printf("两顶点间不连通!\n");
    			if(j==0) printf("两顶点为同一点!\n");
				break;
			}
			case 15:{
				char ListName[100];
				int key;
				file:
				printf("请选择你的操作:1.将图写入文件 2.将文件中的数据读入图 3.退出该功能\n");
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
						int j=SaveGraph(G,ListName);
						if(whe==1){
							printf("请输入想要操作的图的名称:\n");
							scanf("%s",Listname);
							Listnum=LocateList(Lists,Listname);
							if(Listnum!=0){
								j=SaveGraph(Lists.elem[Listnum-1].G,ListName);
							}else{
								printf("输入的名称有误或不存在!\n");
							}
						}	
    					if(j==INFEASIBLE) printf("图不存在,写入失败!\n");
    					if(j==OK) printf("写入成功!\n");
						break;
					}
					case 2:{
						int j=LoadGraph(G,ListName);
						if(whe==1){
							printf("请输入想要操作的图的名称:\n");
							scanf("%s",Listname);
							Listnum=LocateList(Lists,Listname);
							if(Listnum!=0){
								j=LoadGraph(Lists.elem[Listnum-1].G,ListName);
							}else{
								printf("输入的名称有误或不存在!\n");
							}
						}
    					if(j==INFEASIBLE) printf("图已经存在,读取失败!\n");
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
					printf("请输入想要操作的图的名称:\n");
					scanf("%s",Listname);
					Listnum=LocateList(Lists,Listname);
					if(Listnum!=0){
						j=ConnectedComponentsNums(Lists.elem[Listnum-1].G);
					}else{
						printf("输入的名称有误或不存在!\n");
					}
				}
				if(whe==0){
					j=ConnectedComponentsNums(G);
				}
				if (j) printf("图的连通分量有%d个!\n",j);
				else printf("求图连通分量失败!\n");
				break;
			}
			case 17:{
				printf("进入多图操作模式!\n");
				whe=1;
				printf("请选择你的操作:1.多图添加 2.多图删除 3.多图查找 4.退出多图模式\n");
				int key;
				scanf("%d",&key);
				switch(key)
				{
					case 1:{
						printf("请输入想要创建的图的名称:\n");
						scanf("%s",Listname);
						int j=AddList(Lists,Listname);
						if(j==INFEASIBLE) printf("创建失败!\n");
						if(j==OK) printf("创建成功!\n");
						break;
					}
					case 2:{
						printf("请输入想要删除的图的名称:\n");
						scanf("%s",Listname);
						int j=RemoveList(Lists,Listname);
						if(j==INFEASIBLE) printf("图不存在,删除失败!\n");
						if(j==OK) printf("删除成功!\n");
						break;
					}
					case 3:{
						printf("请输入想要查找的图的名称:\n");
						scanf("%s",Listname);
						int j=LocateList(Lists,Listname);
						if(j==0) printf("不存在该名称的图!\n");
						else printf("该图的序号为%d!\n",j);
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
				printf("无效的操作！输入的数字应在1~20之间，请重新输入!\n");
				break;
			}
		}
		system("pause");
		system("cls");
	}
	return 0;
}
