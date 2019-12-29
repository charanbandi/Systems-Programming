 /*
 * Name: Venkat Sai Charan Bandi
 * No known Problems, i tried my best to test everything, seems to run fine.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"graph.h"

void bfs (Graph *graph, int);//Function declaration to Breadth First Search in graph_has_path() function

// Initialization Functions

Graph *graph_initialize(){
    Graph *graph = malloc(sizeof(Graph));//size of graph_struct
    if(graph == NULL){
        return NULL;
    }
    else{
        int i=0,j=0;
    for(i = 0;i<MAX_VERTICES;i++){
        for (j = 0; j<MAX_VERTICES; j++){
            graph->adj_matrix[i][j] = -1;//initializing all elements to -1 so represents no vertices and no edges
        }    
    }
    return graph;// pass graph
    }

}

// Vertex Operations

int graph_add_vertex(Graph *graph, int v1){
    if(graph->adj_matrix[v1][0] != -1){
        return 0;//vertex already exists
    }
    else if (v1<0 || v1>= MAX_VERTICES){
        return -1;//error condition
    }
    else{
        int i=0;
        for(i = 0;i<MAX_VERTICES;i++){
                graph->adj_matrix[v1][i] = 0;//initialize vertex values to zero, turning the vertex into exists state
            }
            return 0;
    }
} 
    
int graph_contains_vertex(Graph *graph, int v1){
    if (graph != NULL){
        if (graph->adj_matrix[v1][0] != (-1)){//check if vertex exists
        return 1;
        }
    }
    return 0;
}

int graph_remove_vertex(Graph *graph, int v1){
    if (graph->adj_matrix[v1][0] == -1){//if the vertex doesnt exist
        return 0;
    }
    else if (graph->adj_matrix[v1][0] != -1){//contains vertex
        int x=0;
        for(x = 0;x<MAX_VERTICES;x++){
            graph->adj_matrix[v1][x] = -1;//remove vertex
            if (graph->adj_matrix[x][v1] > 0)
            {
                graph->adj_matrix[x][v1] = 0;//remove all edges belonging to that vertex in other vertices related
            }
        } 
        return 0;//success return
    }
    return -1;
}

// Edge Operations

int graph_add_edge(Graph *graph, int v1, int v2, int wt){
    if(graph->adj_matrix[v1][0] != -1 && graph->adj_matrix[v2][0] != -1){//if both vertces exists only
        if(wt > 0){
            graph->adj_matrix[v1][v2] = wt;//add weight to the correct vertices
            return 0;//success return
        }  
    }
    return -1;//error return
}

int graph_contains_edge(Graph *graph, int v1, int v2){
    if(graph->adj_matrix[v1][v2] > 0){//if weight is greater than zero the edge exists
        return 1;//success return
    }
    return 0;//doesn't exist return
}

int graph_remove_edge(Graph *graph, int v1, int v2){
    if(graph->adj_matrix[v1][0] != -1 && graph->adj_matrix[v2][0] != -1){//vertex check condition
        graph->adj_matrix[v1][v2] = 0;//set edge weight to zero turning it in inexistent state
        return 0;//success return
    }
    return -1;//error return
} 

// Graph Metrics Operations

int graph_num_vertices(Graph *graph){
    if (graph != NULL){
    int count = 0,i=0;
        for (i = 0; i < MAX_VERTICES; i++){
            if (graph->adj_matrix[i][0] != -1){//count all vertices that exists
                count++;//increment count var
            } 
        }
        return count;
    }
    return -1;
}

int graph_num_edges(Graph *graph){
    int count = 0,i=0,j=0;
    for(i = 0;i<MAX_VERTICES;i++){
        for (j = 0; j<MAX_VERTICES; j++){
            if(graph->adj_matrix[i][j] > 0){//count all edges that exists
                count++;//increment count var
            }
        }    
    }
    return count;
}

int graph_total_weight(Graph *graph){
    if (graph != NULL || graph->adj_matrix != NULL){
        int count=0,i=0,j=0;
        for(i = 0;i<MAX_VERTICES;i++){
            for (j = 0; j<MAX_VERTICES; j++){
                if(graph->adj_matrix[i][j] > 0){//if edge exists
                    count = count + (graph->adj_matrix[i][j]);//get its weight
                }
            }    
        } 
        return count;
    }
    return -1;
}

// Vertex Metrics Operations

int graph_get_degree(Graph *graph, int v1){
    int count = 0,i=0;
    if(graph->adj_matrix[v1][0] != -1){
        count = 0;
        for(i = 0;i<MAX_VERTICES;i++){
            if(graph->adj_matrix[v1][i] > 0){
                count++;//increment counter if vertex has outgoing edge
            }
            if(graph->adj_matrix[i][v1] > 0){
                count++;//increment counter if vertex has incoming edge from other nodes
            }
        }
        return count;
    }
    return -1;
}

int graph_get_edge_weight(Graph *graph, int v1, int v2){
    if(graph->adj_matrix[v1][0] != -1 || graph->adj_matrix[v2][0] != -1){//both vertices exist
        if(graph->adj_matrix[v1][v2] > 0){
            return (graph->adj_matrix[v1][v2]);//returning edge weight at the element
        }
    }
    return -1;
}

int graph_is_neighbor(Graph *graph, int v1, int v2){
    if(graph->adj_matrix[v1][0] != -1 && graph->adj_matrix[v2][0] != -1){//both vertices exist
        if(graph->adj_matrix[v1][v2] > 0 || graph->adj_matrix[v2][v1] > 0){//if either of the vertices have an edge associated with them
            return 1;
        }
        return 0;
    }
    return 0;
}

int *graph_get_predecessors(Graph *graph, int v1){
    if(graph->adj_matrix[v1][0] != -1){//considered self loops as predeccesors also
        int count = 0,i=0;
        for(i=0;i<MAX_VERTICES;i++){
            if(graph->adj_matrix[i][v1] > 0){
                count ++;//counting and incrementing each edge incoming
            }
        }

        count++;
        int *temp = malloc(count * sizeof(int));//creating a pointer with enough size to hold all predecessors and +1
        int j=-1,x=0;
        for(x=0;x<count;x++){
            temp[x]=0;//initilaize all elements of the array
        }
        temp[count-1] = -1;
        
        for(i=0;i<MAX_VERTICES;i++){
            if(graph->adj_matrix[i][v1] > 0){
                j++;
                temp[j] = i;//add to the array at index
            }
        }
        return temp;//return pointer 
    }
    return NULL;
}

int *graph_get_successors(Graph *graph, int v1){
    if(graph->adj_matrix[v1][0] != -1){//considered self loops as predeccesors also
        int count = 0,i=0;
        for(i=0;i<MAX_VERTICES;i++){
            if(graph->adj_matrix[v1][i] > 0){
                count ++;//counting and incrementing each edge outgoing
            }
        }

        count++;
        int *temp = malloc(count * sizeof(int));
        int x=0;
        for(x=0;x<count;x++){
            temp[x]=0;//initialize all elements of the array
        }
        temp[count-1] = -1;
        int j=-1;

        for(i=0;i<MAX_VERTICES;i++){
            if(graph->adj_matrix[v1][i] > 0){
                j++;
                temp[j] = i;//add to the array at index
            }
        }
        return temp;//return pointer
    }
    return NULL;
}

// Graph Path Operations

int graph_has_path(Graph *graph, int v1, int v2){    
    if(graph->adj_matrix[v1][0]==-1 || graph->adj_matrix[v2][0]==-1){
        return 0;//return 0 if any of the two vertices dont exist
    }
    int i;
    for(i=0;i<MAX_VERTICES;i++){
        graph->visited[i] = -1;//intialize to -1 values
    }
    graph->visited[0]=v1;
    graph->max_vertex=1;//set index for the visited counter as 1 so the while loop doesnt terminate at first
    int top = 0;
    while(graph->visited[top] != -1){
        bfs(graph,graph->visited[top]);//call BFS alg and get array of successors
        top ++;
    }
    i=0;
    while(graph->visited[i]!= -1){
        if(graph->visited[i]==v2){
            //found at visted so hence has path
            return 1;
        }
        i++;
    } 
    return 0;
}

void bfs(Graph *graph,int index){//performs BFS on a called vertex ad returns the visited nodes if they aren't already in the list
    int i=0,j=0,check=0;
    int *ptr = graph_get_successors(graph,index);//calling all child nodes of the index so searching breadth wise
    while(ptr[i]!=-1){
        for(j=0;j<graph->max_vertex;j++){
            if(ptr[i]==graph->visited[j]){
                check = 1;//check it off list as it exists
            }
        }
        if(check == 0){
            graph->visited[graph->max_vertex]=ptr[i];//add vertex to visited
            graph->max_vertex += 1;//increment the top of visited pointer
        }
            i++;//incerment children pointer of the succesor pointer array
    }
}

// Input/Output Operations

void graph_print(Graph *graph){//standard adjacency matric print
    int i=0,j=0;
    printf("\n\n Printing Adj Graph\n '-' represents no edge and 'x' represents non-existent vertex\n");
    printf("\n*********************************************************************************************************************************************************************\n");
    printf("\t");
    for(i=0;i<MAX_VERTICES;i++){
        printf("V(%d)\t",i);
    }
    printf("\n");
    for(i=0;i<MAX_VERTICES;i++){
        printf("\nV(%d)\t",i);
        for(j=0;j<MAX_VERTICES;j++){
            if(graph->adj_matrix[i][j] == -1){
                printf("x\t");
            }
            else if(graph->adj_matrix[i][j] == 0){
                printf("-\t");
            }
            else{
                printf("%d\t",graph->adj_matrix[i][j]);
            }
        }
    }
    printf("\n*********************************************************************************************************************************************************************\n\n");
}

void graph_output_dot(Graph *graph, char *filename){
    FILE *fp = fopen(filename, "w+");//open file with pointer name in write+ mode
    if(fp == NULL){
        return;//return on error
    }

    int i=0,j=0;
    fprintf(fp,"digraph {\n");
    for(i=0;i<MAX_VERTICES;i++){
        if(graph->adj_matrix[i][0] != -1){
            fprintf(fp,"%d;\n",i);//print all existing vertices first
        }
    }
    for(i=0;i<MAX_VERTICES;i++){
        for(j=0;j<MAX_VERTICES;j++){
            if(graph->adj_matrix[i][j]>0){
                fprintf(fp,"%d -> %d [label = %d];\n",i,j,graph->adj_matrix[i][j]);//print all the edges
            }
        }
    }
    fprintf(fp,"}");
    fclose(fp);//close file pointer
}

int graph_load_file(Graph *graph, char *filename){
    FILE *fp = fopen(filename, "r");//open file with pointer name in read mode
    if(fp == NULL){
        return -1;//error
    }

    char line[FILE_ENTRY_MAX_LEN];//using like a buffer for each line
    while (fgets(line, sizeof(line), fp)) {
        //declaring variables for logic of identifying and switching cases
        int tok_num = 0; 
        int vertex1 = -1;
        int vertex2 = -1;

        char* token = strtok(line,","); //seperator is a comma according to format

        while (token != NULL) {
            int num = atoi(token);//atoi is a stdlib function that converts string to integer
            tok_num++;
            token = strtok(NULL, ",");//next token with seperator
            int x=-1;
            switch(tok_num){//switching according to vertices or edge
                case 1:
                    x = graph_add_vertex(graph,num);//add vertex 1
                    vertex1 = num;
                    if(x == -1){
                        return -1;
                    }
                    break;
                case 2:
                    x = graph_add_vertex(graph,num);//add vertex 2
                    vertex2 = num;
                    if(x == -1){
                        return -1;
                    }
                    break;
                case 3:
                    x = graph_add_edge(graph,vertex1,vertex2,num);//add edge
                    if(x == -1){
                        return -1;
                    }
                    break;                    
            }
    }
    }
    fclose(fp);//close file pointer
    return 0;//success
}

int graph_save_file(Graph *graph, char *filename){
    FILE *fp = fopen(filename, "w+");//open file with pointer name in write+ mode
    if(fp == NULL){
        return -1;//return -1 on error
    }
    int i=0,j=0;
    for(i=0;i<MAX_VERTICES;i++){
        if(graph->adj_matrix[i][0] != -1){
            fprintf(fp,"%d\n",i);//print all vertices
        }
    }
    for(i=0;i<MAX_VERTICES;i++){
        for(j=0;j<MAX_VERTICES;j++){
            if(graph->adj_matrix[i][j]>0){
                fprintf(fp,"%d,%d,%d\n",i,j,graph->adj_matrix[i][j]);//print all edges
            }
        }
    }

    fclose(fp);//close file pointer
    return 0;//success
}