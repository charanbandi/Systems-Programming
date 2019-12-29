#ifndef GRAPH_H
#define GRAPH_H

#define FILE_ENTRY_MAX_LEN  30
#define MAX_VERTICES        20

typedef struct graph_struct {
  int max_vertex;
  int adj_matrix[MAX_VERTICES][MAX_VERTICES];  
  int visited[MAX_VERTICES];
} Graph;

// Prototypes
// ---------------------------------------------------

// Initialization Functions
Graph *graph_initialize();

// Vertex Operations
int graph_add_vertex(Graph *graph, int v1);
int graph_contains_vertex(Graph *graph, int v1);
int graph_remove_vertex(Graph *graph, int v1);

// Edge Operations
int graph_add_edge(Graph *graph, int v1, int v2, int wt);
int graph_contains_edge(Graph *graph, int v1, int v2);
int graph_remove_edge(Graph *graph, int v1, int v2);

// Graph Metrics Operations
int graph_num_vertices(Graph *graph);
int graph_num_edges(Graph *graph);
int graph_total_weight(Graph *graph);

// Vertex Metrics Operations
int graph_get_degree(Graph *graph, int v1);
int graph_get_edge_weight(Graph *graph, int v1, int v2);
int graph_is_neighbor(Graph *graph, int v1, int v2);
int *graph_get_predecessors(Graph *graph, int v1);
int *graph_get_successors(Graph *graph, int v1);

// Graph Path Operations
int graph_has_path(Graph *graph, int v1, int v2);

// Input/Output Operations
void graph_print(Graph *graph);
void graph_output_dot(Graph *graph, char *filename);
int graph_load_file(Graph *graph, char *filename);
int graph_save_file(Graph *graph, char *filename);

#endif