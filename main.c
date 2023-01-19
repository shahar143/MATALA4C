#include "algo.h"

int main() {
    vertex *head = NULL;
    vertex **head_of_heads = &head;
    int number_of_vertexes = 0;
    char c = {0};
    while(scanf("%c", &c) != EOF){
        if(c == 'A'){
            //scan the number of vertexes
            scanf("%d", &number_of_vertexes);
            build_graph_cmd(head_of_heads, number_of_vertexes);
            //printGraph_cmd(head_of_heads);
        }
        else if(c == 'B'){
            int* pnumber_of_vertexes = &number_of_vertexes;
            insert_node_cmd(head_of_heads, pnumber_of_vertexes);

            //printGraph_cmd(head_of_heads);
        }
        else if(c == 'D'){
            int* pnumber_of_vertexes = &number_of_vertexes;
            delete_node_cmd(head_of_heads, pnumber_of_vertexes);
            //printGraph_cmd(head_of_heads);
        }
        else if(c == 'S'){
            int start = 0, end = 0;
            scanf("%d", &start);
            scanf("%d", &end);
            Dijsktra(head_of_heads, start, number_of_vertexes);
            vertex* runner = *head_of_heads;
            while(runner->vertex_num != end) runner = runner->next;
            int ans = runner->distance;
            if(ans >= MAX_INT) ans = -1;
            printf("Dijsktra shortest path: %d \n", ans);
        }
        else if(c == 'T'){
            int ans = 0;
            ans = TSP(head_of_heads, number_of_vertexes);
            printf("TSP shortest path: %d \n", ans);
        }
    }
    set_the_graph_free(head_of_heads);

    return 0;

}
