/*  Nama program    :   Graph
    Nama            :   Muhammad Athar Alfarisi 140810250005, K.M.A.M.T. Mardova F. 140810250056, M. Faiz Nugoroho 140810250029
    NPM             :   140810250005
    Tanggal buat    :   14 Juni 2026
    Deskripsi       :   Operasi graph dengan DFS dan BFS
*/

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct AdjListNode 
{
    AdjListNode* next;
    char data;
};

struct AdjList 
{
    char label;
    AdjListNode* head;
};

struct Graph 
{
    AdjList* vertexList;
    int totalVertex;
};

Graph* createGraph(const char totalVertex);
AdjListNode* newAdjListNode(const char data);
void addEdge(Graph* &graph, const char srcLabel, const char destLabel);
void printGraph(Graph* &graph);
void printDFS(Graph* &graph, const char startLabel);
void printBFS(Graph* &graph, const char startLabel);
AdjList* getAdjList(Graph* &graph, const char targetLabel);

int main(){
//create new graph
    int totalVertices;
    cout << "Masukan total vertex: ";
    cin >> totalVertices;
    
    Graph *graph;
    graph = createGraph(totalVertices);
    //connect edges
    addEdge(graph,'A','B'); 
    addEdge(graph,'A','C');
    addEdge(graph,'B','A');
    addEdge(graph,'B','C');
    addEdge(graph,'B','D');
    addEdge(graph,'B','E');
    addEdge(graph,'C','F');
    addEdge(graph,'C','G');
    addEdge(graph,'D','H');
    addEdge(graph,'E','H');
    addEdge(graph,'F','H');
    addEdge(graph,'G','H');

    //print adjacency list
    printGraph(graph);
    printDFS(graph, 'H');
    printBFS(graph, 'H');
}


Graph* createGraph(const char totalVertex){
    Graph* graph = new Graph;
    graph->totalVertex = totalVertex;

    graph->vertexList = new AdjList[totalVertex];
    for (size_t i = 0; i < totalVertex; ++i)
    {
        cout << "Masukan label (char) untuk vertex ke-" << i+1 << ": ";
        cin >> graph->vertexList[i].label;
        graph->vertexList[i].head = nullptr;
    }
    return graph;
}

AdjListNode* newAdjListNode(const char data){
    AdjListNode* newPtr = new AdjListNode;
    newPtr->data = data;
    newPtr->next = nullptr;
    return newPtr;
}

//return a pointer to AdjList
AdjList* getAdjList(Graph* &graph, const char targetLabel) {
    for(size_t i = 0; i < graph->totalVertex; ++i){
        if(graph->vertexList[i].label == targetLabel) return &graph->vertexList[i];
    }
    cout << "getAdjList() error: vertex not found." << endl;
    return nullptr;
}

void addEdge(Graph* &graph, const char srcLabel, const char destLabel){
    AdjListNode* newPtr = newAdjListNode(getAdjList(graph, destLabel)->label);
    if (getAdjList(graph, srcLabel)->head == nullptr){
        getAdjList(graph, srcLabel)->head = newPtr;
    }
    else {
        AdjListNode* check = getAdjList(graph, srcLabel)->head;
        while (check != nullptr)
        {
            if(check->data == newPtr->data) {
                cout << "addEdge() error: edge already exists." << endl;
                return;
            }
            check = check->next;
        }
        
        newPtr->next = getAdjList(graph, srcLabel)->head;
        getAdjList(graph, srcLabel)->head = newPtr;
    }

    newPtr = newAdjListNode(getAdjList(graph, srcLabel)->label);
    if (getAdjList(graph, destLabel)->head == nullptr){
        getAdjList(graph, destLabel)->head = newPtr;
    } else {
        newPtr->next = getAdjList(graph, destLabel)->head;
        getAdjList(graph, destLabel)->head = newPtr;
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

void printBFS(Graph* &graph, const char startLabel){
    vector<char> visited;
    queue<char> queue;

    queue.push(startLabel);
    visited.push_back(startLabel);

    cout << "BFS(start:" << startLabel << "): ";
    while (!queue.empty())
    {
        char currentInt = queue.front();
        queue.pop();

        cout << currentInt << " ";

        AdjListNode* currentNode = getAdjList(graph, currentInt)->head;
        while(currentNode != nullptr){
            bool marked = false;
            for(const char& check: visited){
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

void printDFS(Graph* &graph, const char startLabel){
    vector<char> visited;
    stack<char> stack;
    
    stack.push(startLabel);
    visited.push_back(startLabel);

    cout << "DFS(start:" << startLabel << "): ";
    while (!stack.empty())
    {
        char currentInt = stack.top();
        stack.pop();
        
        cout << currentInt << " ";

        AdjListNode* currentNode = getAdjList(graph, currentInt)->head;
        while(currentNode != nullptr){
            bool marked = false; 
            for(const char& check : visited){
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