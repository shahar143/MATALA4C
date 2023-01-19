//
// Created by shahar on 1/3/23.
//

#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MATALA4C_ALGO_H
#define MATALA4C_ALGO_H

#endif //MATALA4C_ALGO_H

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
    bool flag;
}vertex;

void append_new_vertex(int new_vertex_num, vertex** head); // append a new vertex to the list
void build_graph_cmd(vertex **main_head, int number_of_vertexes); // read the input and create the graph
void insert_node_cmd(vertex **main_head, int number_of_vertexes); // read the input and insert a new vertex to the graph
void delete_node_cmd(vertex **main_head, int number_of_vertexes); // read the input and delete a vertex from the graph
void printGraph_cmd(vertex **head); // print the graph
void append_new_edge(int vertex_num, int Pend_point, int weight, vertex** head); // append a new edge to a vertex in the graph
void set_the_graph_free(vertex **main_head); // free the graph
void set_edges_free(vertex **pVertex); // free the edges of a vertex
void free_all_edge_end_with(vertex** main_head, int end_point); // free all the edges that end with a specific vertex
void relax(vertex** chosen, edge** neighbor); // used in Dijsktra
void Dijsktra(vertex** main_head, int start, int number_of_vertexes);
// find the shortest path from a specific vertex to all the other vertexes in the graph and saves it in each destination vertex
void permute(int* a, int*** matrix, int start, int end, int cols, int rows); // a function that calculate all the permutations of a given array
void swap(int* x, int* y);
int factorial(int n);
int TSP(vertex** main_head);
// find the shortest path that goes through all given vertexes
