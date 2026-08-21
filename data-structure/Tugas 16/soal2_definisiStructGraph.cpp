/*  Nama program    :   Soal 2.C. Definisi struct graph
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   140810250005
    Tanggal buat    :   22 Juni 2026
    Deskripsi       :   Definisi struct untuk graph dengan adjacency list
*/

#include <iostream>
using namespace std;

struct AdjListNode{
    int data;
    AdjListNode *next;
};

struct AdjList{
    AdjListNode *head;
};

struct Graph{
    int totalVertices;
    AdjList *arr;
};