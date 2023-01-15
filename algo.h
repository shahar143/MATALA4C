//
// Created by shahar on 1/3/23.
//

#include <stdbool.h>

#ifndef MATALA4C_ALGO_H
#define MATALA4C_ALGO_H

#endif //MATALA4C_ALGO_H

#define MAX 2000000

typedef struct edge{
    int weight;
    struct vertex* Pend_point;
    struct edge* next;
}edge;

typedef struct vertex{
    int vertex_num;
    struct vertex* next;
    edge* edge;
    int distance;
    int markos_mom;
    bool flag;
}vertex;

void append_new_vertex(int i, vertex** head); // append a new vertex to the list
void A(vertex **main_head); // read the input and create the graph
void B(vertex **main_head);
void D(vertex **main_head);
void printGraph_cmd(vertex **head);
void append_new_edge(int vertex_num, int Pend_point, int weight, vertex** head);
void set_the_graph_free(vertex **main_head);
void set_edges_free(vertex **pVertex);
void free_all_edge_end_with(vertex** main_head, int end_point);
void relax(vertex** chosen, edge** neighbor);
void Dijakstra(vertex** main_head, int start);
void permute(int* a, int*** matrix, int start, int end, int cols, int rows);
void swap(int* x, int* y);
int factorial(int n);
int TSP(vertex** main_head);
/*
void build_graph_cmd(vertex **head);
void insert_node_cmd(vertex **head);
void delete_node_cmd(vertex **head);
void printGraph_cmd(vertex **head); //for self debug
void deleteGraph_cmd(vertex **head);
void shortsPath_cmd(vertex **head);
void TSP_cmd(vertex **head);
*/
