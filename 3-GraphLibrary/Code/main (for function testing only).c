#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
void main(){
    printf("Main\n");
    Graph *tab = malloc(sizeof(Graph));
    tab = graph_initialize();
    graph_add_vertex(tab, 2);
    graph_add_vertex(tab, 4);
    graph_add_vertex(tab, 3);
    graph_add_vertex(tab, 1);
    graph_contains_vertex(tab, 2);
    graph_remove_vertex(tab,2);
    //graph_contains_edge(tab,2,4);
    graph_add_edge(tab, 2,4,5);
    //graph_add_edge(tab, 2,2,-3);
    graph_add_edge(tab, 4,2,10);
    //graph_add_edge(tab, 2,2,5);
    //graph_remove_edge(tab,2,4);
    graph_num_vertices(tab);
    graph_num_edges(tab);
    graph_total_weight(tab);
    graph_get_degree(tab,2);
    graph_get_edge_weight(tab,2,2);
    graph_is_neighbor(tab,2,2);
    /*if((int *ptr = graph_get_predecessors(tab,2)) == NULL){
        print("SKRR");
    }*/
    //int x = ptr[2];
    //printf("\t%d",(ptr[1]));//works perfectly
    graph_add_vertex(tab, 4);
    graph_add_vertex(tab, 3);
    graph_add_vertex(tab, 1);
    graph_add_vertex(tab, 2);
    graph_add_vertex(tab, 5);
    graph_add_vertex(tab, 0);

    graph_add_edge(tab, 0,1,1);
    graph_add_edge(tab, 0,2,2);
    graph_add_edge(tab, 0,4,3);
    graph_add_edge(tab, 4,0,4);
    graph_add_edge(tab, 1,3,5);
    graph_add_edge(tab, 2,5,2);
    int x = graph_has_path(tab,0,4);
    //printf("HELOOOOO\t");
    printf(" has path is: %d",x);/*
    //printf("\t%d",x);
    //int *ptr = graph_get_successors(tab,2);
    //printf("!!%d!!",ptr[4]);
    //int *ptr = graph_get_predecessors(tab,2);
        //printf("!!%d!!",ptr[0]);
    //printf("%d",ptr[5]);
    //printf("\tvalue: %d",tab->adj_matrix[1][4]);
    //graph_print(tab);
    //char *a ="test.txt";
    //graph_output_dot(tab,a);
    //char *a ="test.txt";
    //graph_load_file(tab,a);*/
    //graph_print(tab);
    char *b = "test2.txt";
    graph_save_file(tab,b);
    char *c ="test3.txt";
    graph_output_dot(tab,c);
    graph_remove_edge(tab,0,4);
    //int x;
    graph_output_dot(tab,c);
    graph_print(tab);
}