#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct AdjListNode 
{
    AdjListNode* next;
    int data;
};

struct AdjList 
{
    int label;
    AdjListNode* head;
};

struct Graph 
{
    AdjList* vertexList;
    int totalVertex;
};

Graph* createGraph(const int totalVertex);
AdjListNode* newAdjListNode(const int data);
void addEdge(Graph* &graph, const int src, const int dest);
void printGraph(Graph* &graph);
void printDFS(Graph* &graph, const int start);
void printBFS(Graph* &graph, const int start);

int main(){
//create new graph
    int totalVertices;
    cout << "Masukan total vertex: ";
    cin >> totalVertices;
    
    Graph *graph;
    graph = createGraph(totalVertices);
    //connect edges
    addEdge(graph,0,1);
    addEdge(graph,0,2);
    addEdge(graph,1,0);
    addEdge(graph,1,2);
    addEdge(graph,1,3);
    addEdge(graph,1,4);
    addEdge(graph,2,5);
    addEdge(graph,2,6);
    addEdge(graph,3,7);
    addEdge(graph,4,7);
    addEdge(graph,5,7);
    addEdge(graph,6,7);

    //print adjacency list
    printGraph(graph);
    printDFS(graph, 3);
    printBFS(graph, 3);
}


Graph* createGraph(const int totalVertex){
    Graph* graph = new Graph;
    graph->totalVertex = totalVertex;

    graph->vertexList = new AdjList[totalVertex];
    for (size_t i = 0; i < totalVertex; i++)
    {
        cout << "Masukan label (int) untuk vertex ke-" << i+1 << ": ";
        cin >> graph->vertexList[i].label;
        graph->vertexList[i].head = nullptr;
    }
    return graph;
}

AdjListNode* newAdjListNode(const int data){
    AdjListNode* newPtr = new AdjListNode;
    newPtr->data = data;
    newPtr->next = nullptr;
    return newPtr;
}

void addEdge(Graph* &graph, const int src, const int dest){
    AdjListNode* newPtr = newAdjListNode(dest);
    if (graph->vertexList[src].head == nullptr){
        graph->vertexList[src].head = newPtr;
    }
    else {
        AdjListNode* check = graph->vertexList[src].head;
        while (check != nullptr)
        {
            if(check->data == newPtr->data) {
                cout << "addEdge() error: edge sudah ada" << endl;
                return;
            }
            check = check->next;
        }
        
        newPtr->next = graph->vertexList[src].head;
        graph->vertexList[src].head = newPtr;
    }

    newPtr = newAdjListNode(src);
    if (graph->vertexList[dest].head == nullptr){
        graph->vertexList[dest].head = newPtr;
    } else {
        newPtr->next = graph->vertexList[dest].head;
        graph->vertexList[dest].head = newPtr;
    }
}

void printGraph(Graph* &graph){
    cout << "Adjacency List Vertex\n---------------------\n";
    for (size_t i = 0; i < graph->totalVertex; i++)
    {
        AdjListNode *root = graph->vertexList[i].head;

        cout << "Vertex " << graph->vertexList[i].label << ": ";

        while (root != nullptr)
        {
            cout << root->data << "->";
            root = root->next;
        }
        cout << "nullptr\n";
    }
}

void printBFS(Graph* &graph, const int start){
    vector<int> visited;
    queue<int> queue;

    queue.push(start);
    visited.push_back(start);

    cout << "BFS: ";
    while (!queue.empty())
    {
        int currentInt = queue.front();
        queue.pop();

        cout << currentInt << " ";

        AdjListNode* currentNode = graph->vertexList[currentInt].head;
        while(currentNode != nullptr){
            bool marked = false;
            for(const int& check: visited){
                if (currentNode->data == check) marked = true;
            }
        
            if (marked){
                currentNode = currentNode->next;
                continue;
            }
            queue.push(currentNode->data);
            visited.push_back(currentNode->data);
            currentNode = currentNode->next;
        }
    }
    cout << endl;
}

void printDFS(Graph* &graph, const int start){
    vector<int> visited;
    stack<int> stack;
    
    stack.push(start);
    visited.push_back(start);

    cout << "DFS: ";
    while (!stack.empty())
    {
        int currentInt = stack.top();
        stack.pop();
        
        cout << currentInt << " ";

        AdjListNode* currentNode = graph->vertexList[currentInt].head;
        while(currentNode != nullptr){
            bool marked = false; 
            for(const int& check : visited){
                if (currentNode->data == check) marked = true;
            }
            if (marked){
                currentNode = currentNode->next;
                continue;
            } 
            stack.push(currentNode->data);
            visited.push_back(currentNode->data);
            currentNode = currentNode->next;
        }
    }
    cout << endl;
}