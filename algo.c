//
// Created by shahar on 1/3/23.
//
#include "algo.h"

static int itr = 0; // a static variable used in the function permute

//2 loops in this function. first loop iterate over the vertexes, second loop iterates over the edges
void printGraph_cmd(vertex** head){
    vertex* runner = *head;
    while(runner != NULL){ // while there are still vertices
        printf("vertex num: %d\n", runner->vertex_num);
        edge* runner2 = runner->edge;
        //while there are still edges
        while(runner2 != NULL){
            printf("edge (%d,%d) with weight %d\n", runner->vertex_num, runner2->Pend_point->vertex_num,
                   runner2->weight);
            runner2 = runner2->next;
        }
        runner = runner->next;
    }
    printf("\n");
}

void append_new_vertex(int new_vertex_num, vertex** head){
    //create new vertex
    vertex* new_vertex = (vertex*)malloc(sizeof(vertex));
    if(new_vertex == NULL) exit(-1);
    new_vertex->vertex_num = new_vertex_num; // set the vertex number
    new_vertex->next = NULL; // set the next vertex to NULL
    new_vertex->edge = NULL; // set the edge LinkedList to NULL
    //if there is no vertex in the list
    if (*head == NULL){
        (*head) = new_vertex;
    }
    //if there are vertexes in the list
    else{
        vertex* runner = *head; // create a temp vertex to iterate over the list
        while(runner->next != NULL) runner = runner->next;
        runner->next = new_vertex; // set the next vertex to the new vertex
    }
}

void append_new_edge(int vertex_num, int Pend_point, int weight, vertex** head){
    //create new edge
    edge* new_edge = (edge*)malloc(sizeof(edge));
    if(new_edge == NULL) exit(-1);
    //set new_edge's weight and next
    new_edge->weight = weight;
    new_edge->next = NULL;
    //iterate over all vertexes until we find the Pend_point with runner2
    vertex* runner2 = *head;
    while(runner2->vertex_num != Pend_point) runner2 = runner2->next;
    new_edge->Pend_point = runner2; //make new_edge point on runner2
    //iterate over all vertexes until we find the vertex we want to attach new_edge to with runner
    vertex* runner = *head;
    while(runner->vertex_num != vertex_num) runner = runner->next;
    //if there are no edges in the vertex's edge LinkedList
    if(runner->edge == NULL){
        runner->edge = new_edge;
    }
    //if there are edges in the vertex's edges LinkedList
    else{
        edge* runner3 = runner->edge;
        while(runner3->next != NULL) runner3 = runner3->next;
        runner3->next = new_edge;
    }
}

void build_graph_cmd(vertex **main_head, int number_of_vertexes){
    if(number_of_vertexes == 0){
        return;
    }
    int vertex_current_num = 0;
    int edge_current_end_point = 0;
    int edge_current_weight = 0;
    //int control;
    int counter = 0;
    //int tmp;
    char useless;
    //head is the actual head of the graph
    vertex* head = NULL;
    //head_of_heads is a pointer to the head of the graph -> we use it inorder to not return anything from the functions
    vertex** head_of_heads = &head;
    //create the vertexes
    for(int i = 0; i < number_of_vertexes; i++){
        append_new_vertex(i, head_of_heads);
    }
    //scan the vertexes and their edges
    while(counter < number_of_vertexes){
        scanf("%c", &useless);//for the n char
        scanf("%d", &vertex_current_num);
        while(scanf("%d", &edge_current_end_point) != 0){  // while we dont try to scan chars like stupid people DAAAAA!!
            scanf("%d", &edge_current_weight); // read the weight
            //function that append a new edge to the vertex
            append_new_edge(vertex_current_num, edge_current_end_point,
                            edge_current_weight, head_of_heads);
        }
        //counter that mark that we have finished with the vertex number (counter)
        counter++;
    }
    *main_head = head;
}

void set_edges_free(vertex** pVertex){
    if((*pVertex)->edge == NULL) return; // if there are no edges return
    //set prev_runner and runner to the first edge
    edge* runner = (*pVertex)->edge;
    edge* prev_runner = (*pVertex)->edge;
    //while there are still edges
    while(runner != NULL){
        runner = runner->next; // set runner to the next edge
        free(prev_runner); // free the prev_runner
        prev_runner = runner; // set prev_runner to the runner
    }
    (*pVertex)->edge = NULL; //eventually set edge to NULL
}

void set_the_graph_free(vertex **main_head){
    if((*main_head) == NULL) return;
    vertex* prev_runner = *main_head;
    vertex* runner = *main_head;
    vertex** cab; //a double pointer to send to set_edges_free.
    // in this way, set_edges_free will get the address of edge and won't have to return anything
    while(runner != NULL){
        // same erasing technique as in set_edges_free
        runner = runner->next;
        cab = &prev_runner;
        set_edges_free(cab);
        free(prev_runner);
        prev_runner = runner;
    }
    *main_head = NULL;
    main_head = NULL;
}

void insert_node_cmd(vertex **main_head, int* pnumber_of_vertexes){
    int new_vertex_num;
    int edge_current_end_point;
    int edge_current_weight;
    scanf("%d", &new_vertex_num);
    //if the vertex is already in the graph
    if(new_vertex_num < (*pnumber_of_vertexes)){
        vertex *runner = *main_head;
        //iterate over the vertexes until we find the vertex we want to delete its edges
        while(runner->vertex_num != new_vertex_num) runner = runner->next;
        vertex** cab = &runner;
        set_edges_free(cab);
        //same code as in A function
        while(scanf("%d", &edge_current_end_point) != 0){  // while there is still input
            scanf("%d", &edge_current_weight); // read the weight
            append_new_edge(new_vertex_num, edge_current_end_point,
                            edge_current_weight, main_head);
        }
    }
    else{
        //continue else- if the vertex doesn't exist
        (*pnumber_of_vertexes)++;
        append_new_vertex(new_vertex_num, main_head);
        while(scanf("%d", &edge_current_end_point) != 0) {  // while there is still input
            scanf("%d", &edge_current_weight); // read the weight
            append_new_edge(new_vertex_num, edge_current_end_point,
                            edge_current_weight, main_head);
        }
    }
}

//a function that free all edges that end with the vertex we want to delete
void free_all_edge_end_with(vertex** main_head, int end_point){
    int counter;
    vertex* runner = *main_head;
    edge* runner2;
    edge* runner3;
    edge* victim;
    while(runner != NULL){ // iterate over all vertexes
        runner2 = runner->edge;
        counter = 0;
        runner3 = NULL;
        while(runner2 != NULL){ // iterate over all edges of a specific vertex
            if(runner2->Pend_point->vertex_num == end_point){ // if the edge ends with the vertex we want to delete
                if(counter == 0){ // if the edge is the first edge of the vertex
                    victim = runner2; // set victim to the edge we want to delete
                    runner2 = runner2->next; // set runner2 to the next edge
                    runner->edge = runner2; // set the vertex's edge to the next edge
                    free(victim);
                    continue;
                }
                else{ // if the edge is not the first edge of the vertex
                    victim = runner2; // set victim to the edge we want to delete
                    runner2 = runner2->next; // set runner2 to the next edge
                    runner3 = runner->edge;
                    while(runner3->next != victim)  runner3 = runner3->next; // iterate over the edges until we find the edge before the victim
                    runner3->next = runner2; // set the edge before the victim to the edge after the victim
                    free(victim);
                    continue;
                }
            }
            runner2 = runner2->next;
            counter++;
        }
        runner = runner->next;
    }
}


void delete_node_cmd(vertex** main_head, int* pnumber_of_vertexes){
    int vertex_num1 = -1;
    scanf("%d", &vertex_num1);
    if(vertex_num1 >= (*pnumber_of_vertexes) || (*main_head) == NULL || main_head == NULL){ // if the vertex doesn't exist
        printf("you can't delete something that doesn't exist buddy\n");
        return;
    }
    free_all_edge_end_with(main_head, vertex_num1); // free all edges that end with the vertex we want to delete
    int counter = 0;
    vertex* runner = *main_head;
    vertex* runner2 = *main_head;
    vertex* victim;
    vertex** cab;
    while(runner->vertex_num != vertex_num1){ // iterate over the vertexes until we find the vertex we want to delete
        runner = runner->next;
        counter++;
    }
    if(counter == 0){ // if the vertex is the first vertex
        cab = &runner;
        set_edges_free(cab);
        victim = runner;
        (*main_head) = runner->next;
        free(victim);
    }
    else{ // if the vertex is not the first vertex
        while(runner2->next != runner) runner2 = runner2->next;
        cab = &runner;
        set_edges_free(cab);
        victim = runner;
        runner = runner->next;
        runner2->next = runner;
        free(victim);
    }
    (*pnumber_of_vertexes)--;
}

void Dijsktra(vertex** main_head, int start, int number_of_vertexes){
    vertex* runner = *main_head;
    //filling all vertex's info
    while(runner != NULL){
        runner->distance = INT_MAX;
        runner->flag = false;
        runner = runner->next;
    }
    runner = *main_head;
    //initializing the start vertex's distance to zero
    while(runner->vertex_num != start) runner = runner->next;
    runner->distance = 0;
    int counter = 0;
    while(counter != number_of_vertexes){
        runner = *main_head;
        vertex* chosen = *main_head;
        //a loop that iterates over all vertexes
        while(runner != NULL){
            //choosing the chosen without choosing any true vertexes.
            //we will iterate on the node list as long as we do find an unused vertex with false flag
            //if chosen is true move it until you find a false vertex
            while((chosen != NULL) && (chosen->flag != false)) chosen = chosen->next;
            if(chosen == NULL) return; //all vertex has been examined
            if((chosen->distance > runner->distance) && (runner->flag == false)) chosen = runner;
            runner = runner->next;
        }
        //assign the chosen flag to true
        chosen->flag = true;
        edge* neighbor = chosen->edge;
        //if vertex has no egdes, continue to next iteration
        if(neighbor == NULL) continue;
        //a while loop that sends every edge to relax function
        while(neighbor != NULL){
            vertex** chosen_cab = &chosen;
            edge** neighbor_cab = &neighbor;
            relax(chosen_cab, neighbor_cab);
            neighbor = neighbor->next;
        }
        counter++;
    }

}

void relax(vertex** chosen, edge** neighbor){
    if((*neighbor)->Pend_point->distance > ((*chosen)->distance + (*neighbor)->weight)){
        (*neighbor)->Pend_point->distance = ((*chosen)->distance + (*neighbor)->weight);
    }
}


int TSP(vertex** main_head, int number_of_vertexes){
    int col = 0;
    scanf("%d", &col);
    int* arr = (int *)malloc(col* sizeof(int));
    if(arr == NULL) exit(-1);
    for(int i = 0; i < col; i++) scanf("%d", &arr[i]);
    int row = factorial(col);
    int** matrix = (int **) malloc(row*sizeof(int*));
    for(int i = 0; i < row; i++) matrix[i] = (int *)malloc(col* sizeof(int));
    int*** matrix_cab = &matrix;
    // create all permutations of the arr and insert them to a matrix in size of row*col or actually col*(col!)
    permute(arr, matrix_cab, 0, col -1, col, row);
    itr = 0;
    int* result_arr = (int *)calloc(row, sizeof(int));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col-1; j++){
            Dijsktra(main_head, matrix[i][j], number_of_vertexes); // run dijakstra on every permutation and calculate the distance between every 2 vertexes in the permutation
            vertex* runner = *main_head;
            while(runner->vertex_num != matrix[i][j+1]) runner = runner->next;
            //we are looking for the destination vertex that we run dijakstra on because it will contain in its distance field the shortest distance between the 2 vertexes
            result_arr[i] += runner->distance;
            //sum all distances and store it in the result_arr
        }
    }
    int min_path = INT_MAX;
    // find the minimum path in the result_arr
    for(int i = 0; i < row; i++){
        if(result_arr[i] < min_path) min_path = result_arr[i];
    }

    free(result_arr);
    for(int i = 0; i < row; i++) free(matrix[i]);
    free(matrix);
    free(arr);
    //if min_path is still MAX, it means that there is no path between the vertexes, so return -1
    if(min_path >= INT_MAX) return -1;
    else return min_path;
}

void swap(int* x, int* y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int factorial(int n){
    if(n == 0) return 1;
    else return n* factorial(n-1);
}

//this function is a recursive function that creates all permutations of the arr and stores them to the matrix
void permute(int* a, int*** matrix, int start, int end, int cols, int rows){
    if (start == end){
        for(int j = 0; j < cols; j++) {
            (*matrix)[itr][j] = a[j];
        }
        itr++;
    }
    else {
        for (int i = start; i <= end; i++) {
            swap((a+ start) , (a + i));
            permute(a, matrix, start + 1, end, cols, rows);
            swap((a + start), (a + i));
            }
        }
}
