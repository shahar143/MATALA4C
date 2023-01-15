#include <stdio.h>
#include <string.h>
#include "algo.h"

int main() {
    vertex *head = NULL;
    vertex **head_of_heads = &head;
    char c = {0};
    while(scanf("%c", &c) != EOF){
        if(c == 'A'){
            A(head_of_heads);
            //printGraph_cmd(head_of_heads);
        }
        else if(c == 'B'){
            B(head_of_heads);
            //printGraph_cmd(head_of_heads);
        }
        else if(c == 'D'){
            D(head_of_heads);
            //printGraph_cmd(head_of_heads);
        }
        else if(c == 'S'){
            int start = 0, end = 0;
            scanf("%d", &start);
            scanf("%d", &end);
            Dijakstra(head_of_heads, start);
            vertex* runner = *head_of_heads;
            while(runner->vertex_num != end) runner = runner->next;
            int ans = runner->distance;
            if(ans >= MAX) ans = -1;
            printf("Dijsktra shortest path: %d \n", ans);
        }
        else if(c == 'T'){
            int ans = 0;
            ans = TSP(head_of_heads);
            printf("TSP shortest path: %d \n", ans);
        }
    }
    set_the_graph_free(head_of_heads);

    return 0;

}
