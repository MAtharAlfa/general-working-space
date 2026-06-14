#include<iostream>
using namespace std;
//struct untuk adjacency list node
struct AdjListNode{
 int data;
 AdjListNode *next;
};
//struct untuk adjacency list
struct AdjList{
 AdjListNode *head; //pointer ke head node of list
};
//struct untuk graph. graph adalah array dari
// adjacency lists
//Size array adalah V (total vertex)
struct Graph{
 int V;
 AdjList *arr;
};
AdjListNode *newAdjListNode(int);
Graph *createGraph(int);
void addEdge(Graph*,int,int);
void printGraph(Graph*);
int main(){
//create sebuah graph baru
 int totalVertices=4;
 Graph *graph;
 graph=createGraph(totalVertices);
//connect edges
 addEdge(graph,0,1);
 addEdge(graph,0,2);
 addEdge(graph,0,3);
 addEdge(graph,1,3);
 addEdge(graph,2,3);
 addEdge(graph,0,1);
 addEdge(graph,0,4);
 addEdge(graph,1,2);
 addEdge(graph,1,3);
 addEdge(graph,1,4);
 addEdge(graph,2,3);
 addEdge(graph,3,4);

 //print adjacency list
 printGraph(graph);
}
//create node baru
AdjListNode* newAdjListNode(int data){
 AdjListNode *nptr=new AdjListNode;
 nptr->data=data;
 nptr->next=NULL;
 return nptr;
}
//function untuk create sebuah graph -> V -
// vertices
Graph* createGraph(int V){
 Graph *graph=new Graph;
 graph->V=V;
 //create sebuah array of adjacency list. size
// array - V
 graph->arr=new AdjList[V];
 //initialisasi dengan NULL (contoh root=NULL)
 for(int i=0;i<V;i++){
 graph->arr[i].head=NULL;
 }
 return graph;
}
//add edge ke sebuah undirected Graph
void addEdge(Graph *graph,int src,int dest){
 //Add edge dari src ke dest. Sebuah new node
// ditambahkan ke adjacency list src
 //node ditambahkan di awal
 AdjListNode *nptr=newAdjListNode(dest);
 nptr->next=graph->arr[src].head;
 graph->arr[src].head=nptr;
 //connect dari dest ke src (karena tidak berarah
// / undirected)
 nptr=newAdjListNode(src);
 nptr->next=graph->arr[dest].head;
 graph->arr[dest].head=nptr;
}
//function print graph
void printGraph(Graph* graph){
//loop pada setiap adjacent list
 for(int i=0;i<graph->V;i++){
 AdjListNode *root=graph->arr[i].head;
 cout<<"Adjacency list vertex "<<i<<endl;
 //loop pada setiap node dalam list
 while(root!=NULL){
 cout<<root->data<<" -> ";
 root=root->next;
 }
 cout<<endl;
 }
}