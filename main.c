#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node.h"
#include "stack_functions.h"

#define NUM_VERTICES 10
/** This function takes a pointer to the
    adjacency matrix of a Graph and the
    size of this matrix as arguments and
    prints the matrix
*/
void print_graph(int *graph, int size);

/** This function takes a pointer to the
    adjacency matrix of a Graph, the size
    of this matrix, the source and dest
    node numbers along with the weight or
    cost of the edge and fills the adjacency
    matrix accordingly.
*/
void add_edge(int *graph, int size, int src, int dst, int cost);

/** This function takes a pointer to the adjacency matrix of
    a graph, the size of this matrix, source and destination
    vertex numbers as inputs and prints out the path from the
    source vertex to the destination vertex. It also prints
    the total cost of this path.
*/
void find_path_dfs(int *graph, int size, int src, int dst);

int main(int argc, char *argv[])
{
    int my_graph[NUM_VERTICES][NUM_VERTICES]; /// An adjacency matrix representation of graph

    memset(my_graph, -1, NUM_VERTICES * NUM_VERTICES * sizeof(int)); /// Initiallize with -1 representing infinte cost.

    for (int i = 0; i < NUM_VERTICES; i++)
        add_edge(&my_graph[0][0], NUM_VERTICES, i, i, 0); /// All the vertices have a cost of 0 for visiting themselves

    add_edge(&my_graph[0][0], NUM_VERTICES, 0, 3, 13);
    add_edge(&my_graph[0][0], NUM_VERTICES, 1, 4, 14);

    add_edge(&my_graph[0][0], NUM_VERTICES, 9, 8, 23);
    add_edge(&my_graph[0][0], NUM_VERTICES, 2, 3, 9);
    add_edge(&my_graph[0][0], NUM_VERTICES, 2, 9, 10);
    add_edge(&my_graph[0][0], NUM_VERTICES, 3, 0, 13);
    add_edge(&my_graph[0][0], NUM_VERTICES, 1, 5, 6);
    add_edge(&my_graph[0][0], NUM_VERTICES, 8, 5, 11);
    add_edge(&my_graph[0][0], NUM_VERTICES, 5, 1, 6);
    add_edge(&my_graph[0][0], NUM_VERTICES, 5, 2, 7);
    add_edge(&my_graph[0][0], NUM_VERTICES, 5, 6, 12);
    add_edge(&my_graph[0][0], NUM_VERTICES, 4, 1, 14);
    add_edge(&my_graph[0][0], NUM_VERTICES, 4, 6, 8);
    add_edge(&my_graph[0][0], NUM_VERTICES, 6, 7, 15);
    add_edge(&my_graph[0][0], NUM_VERTICES, 6, 4, 8);
    add_edge(&my_graph[0][0], NUM_VERTICES, 7, 6, 15);
    add_edge(&my_graph[0][0], NUM_VERTICES, 3, 8, 9);

    if (argc != 3)
    {
        printf("Usage: %s <source_vertex> <destination_vertex>\n", argv[0]);
        printf("Vertices must be between 0 and %d.\n", NUM_VERTICES - 1);
        return 1;
    }

    int src_vert = atoi(argv[1]);
    int dst_vert = atoi(argv[2]);

    if (src_vert < 0 || src_vert >= NUM_VERTICES || dst_vert < 0 || dst_vert >= NUM_VERTICES)
    {
        printf("Invalid vertex number(s). Please enter values between 0 and %d.\n", NUM_VERTICES - 1);
        return 1;
    }

    print_graph(&my_graph[0][0], NUM_VERTICES);

    find_path_dfs(&my_graph[0][0], NUM_VERTICES, src_vert, dst_vert);
    return 0;
}

void add_edge(int *graph, int size, int src, int dst, int cost)
{
    *(graph + (src * size + dst)) = cost; 
}

void print_graph(int *graph, int size)
{
    // char vertices[size];
    for (int i = 0; i < size; i++)
    {
        printf("\t%d", i);
    }
    printf("\n\n");
    for (int x = 0; x < size; x++)
    {
        printf("%d\t", x);
        for (int y = 0; y < size; y++)
            printf("%d\t", *(graph + (x * size + y)));
        printf("\n");
    }
}

void find_path_dfs(int *graph, int size, int src, int dst)
{
    int visited[size]; /// To keep track of all the visited nodes
    memset(visited, 0, size * sizeof(int));
    /********** We make a stack for holding the visited vertices *****************/

    struct node *top = NULL; /// This is the top of the stack

    /** The DFS will work as follows:
        1. Visit src vertex. Set 'current_visiting' to src.
        2. Explore this vertex.
            If it is the destination vertex, stop.
            Otherwise visit its first unvisited neighbour (add to stack the current vertex)
            If no unvisited neighbour vertex remains, go back (pop from stack)
        3. Repeat 2*/

    int crnt_visiting = src;
    int crnt_exploring = src;
    int path_cost = 0;
    bool PATH_FOUND = false;
    while (!PATH_FOUND)
    {
        visited[crnt_visiting] = 1; /// Now we have visited this node
        struct element temp;
        if (top != NULL)
        {
            temp = pop(&top);
            crnt_visiting = temp.vertex_num;
        }
        else
        {

            temp.cost_to_visit = -1;
            temp.vertex_num = -1;
        }

        if (crnt_visiting == dst) /// If the vertex is found
        {
            // path_cost+=temp.cost_to_visit+(*(graph+8));
            path_cost = temp.cost_to_visit;
            printf("\nPath found: ");
            printf("\nCost: %d\n", path_cost);
            while (!isStackEmpty(&top)) /// Empty the stack so all the allocated memory is freed.
            {
                printf("Pop\n");
                pop(&top);
            }
            PATH_FOUND = true;
            continue;
        }
        else /// Explore this vertex
        {

            int x = 0;
            for (int i = crnt_visiting * NUM_VERTICES; i < ((crnt_visiting * NUM_VERTICES) + size); i++)
            {
                if (*(graph + i) != -1 && *(graph + i) != 0 && visited[x] != 1)
                {
                    int h = temp.cost_to_visit;                            /// saved for later
                    visited[x] = 1;                                        /// Node visited
                    if (temp.cost_to_visit == -1 && temp.vertex_num == -1) /// if the stack is empty then temp is -1
                    {
                        /// only cost to the visited node
                        temp.cost_to_visit = *(graph + i);
                    }
                    else
                    {
                        /// cost to visited node plus the current visiting
                        ///  to constitute the cost till the source
                        temp.cost_to_visit += *(graph + i);
                    }
                    temp.vertex_num = x;    /// vertex number stored in temp
                    push(&top, temp);       /// temp psuhed into stack
                    temp.cost_to_visit = h; /// cost of current node reset
                    temp.vertex_num = -1;   /// vertex number also reset
                }
                x++; /// increments to the column, or connected node to current node
            }
        }
    }
}