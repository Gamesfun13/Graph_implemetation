# Graph Pathfinding using DFS (Adjacency Matrix)

A C implementation of a graph data structure using an adjacency matrix, with Depth-First Search (DFS) pathfinding via a stack-based approach.

## Project Structure

| File | Purpose |
|------|---------|
| `main.c` | Entry point: graph construction, edge setup, DFS pathfinding logic |
| `node.h` | Defines `struct element` (vertex + cost) and `struct node` (linked list node for stack) |
| `stack_functions.h` | Declares stack operations: `push`, `pop`, `isStackEmpty` |
| `stack_functions.c` | Implements stack operations using a singly linked list |
| `graph.png`  | Graph Image |

## Data Structures

### Graph Representation

The graph is stored as a **square adjacency matrix** of size `NUM_VERTICES × NUM_VERTICES` (10×10, defined in `main.c`). Each cell `matrix[src][dst]` contains:

| Value | Meaning |
|-------|---------|
| `-1`  | No edge (infinite cost) |
| `0`   | Self-loop (cost to visit the same vertex) |
| `>0`  | Edge weight/cost from `src` to `dst` |

The matrix is accessed through a flat `int*` pointer using the formula:

```
*(graph + (src * size + dst))
```

### Stack (Linked List)

Used to track the DFS traversal path:

```c
struct element {
    int vertex_num;    // Vertex identifier
    int cost_to_visit; // Accumulated cost from source to this vertex
};

struct node {
    struct element data;
    struct node *next;
};
```

Stack operations (`push` to top, `pop` from top) are implemented in `stack_functions.c` with dynamic memory allocation.

## Graph Layout

The code constructs a directed weighted graph with 10 vertices (0–9). Based on the `add_edge` calls, the graph is:

```
    0 → 3 (13)
    1 → 4 (14), 1 → 5 (6)
    2 → 3 (9),  2 → 9 (10)
    3 → 0 (13), 3 → 8 (9)
    4 → 1 (14), 4 → 6 (8)
    5 → 1 (6),  5 → 2 (7),  5 → 6 (12)
    6 → 7 (15), 6 → 4 (8)
    7 → 6 (15)
    8 → 5 (11)
    9 → 8 (23)
```

## Functions

### `add_edge(int *graph, int size, int src, int dst, int cost)`

Inserts a directed edge with the given cost into the adjacency matrix.

### `print_graph(int *graph, int size)`

Prints a formatted adjacency matrix with row/column labels.

### `find_path_dfs(int *graph, int size, int src, int dst)`

Searches for a path from `src` to `dst` using DFS:

1. Mark `crnt_visiting` as visited (stored in `visited[]` array).
2. If `crnt_visiting == dst`, print the cost and exit.
3. Otherwise, iterate through all neighbours of `crnt_visiting`:
   - Skip if no edge exists (`-1`), it's a self-loop (`0`), or already visited.
   - Push each **unvisited neighbour** onto the stack along with its **accumulated cost** from the source.
4. Pop the next vertex from the stack to continue exploring (backtracking behaviour).

**Note:** The DFS explores neighbours and pushes **all** unvisited neighbours onto the stack at once. The stack's LIFO order means the last neighbour pushed is explored first, which is consistent with DFS behaviour.

## Compilation & Execution

```bash
# Compile
gcc -o graph_dfs main.c stack_functions.c

# Run with source and destination vertices as command-line arguments
./graph_dfs 4 8
./graph_dfs 9 2
./graph_dfs 0 8
```

The program takes the source and destination vertex numbers directly from the **command line**. If the wrong number of arguments is supplied, it shows usage information.

### Example Output

```
$ ./graph_dfs 4 8
        0       1       2       3       4       5       6       7       8       9

0       0       -1      -1      13      -1      -1      -1      -1      -1      -1
1       -1      0       -1      -1      14      6       -1      -1      -1      -1
2       -1      -1      0       9       -1      -1      -1      -1      -1      10
3       13      -1      -1      0       -1      -1      -1      -1      9       -1
4       -1      14      -1      -1      0       -1      8       -1      -1      -1
5       -1      6       7       -1      -1      0       12      -1      -1      -1
6       -1      -1      -1      -1      8       -1      0       15      -1      -1
7       -1      -1      -1      -1      -1      -1      15      0       -1      -1
8       -1      -1      -1      -1      -1      11      -1      -1      0       -1
9       -1      -1      -1      -1      -1      -1      -1      -1      23      0

Path found:
Cost: 60
Pop
```

Other examples:

```
$ ./graph_dfs 9 2
Path found:
Cost: 66
Pop
```

(cost depends on the path discovered; the DFS will find the **first** path encountered, not necessarily the shortest).

## Key Concepts

- **Adjacency Matrix**: Simple O(1) edge lookup but O(V²) memory.
- **Depth-First Search**: Explores as far as possible along each branch before backtracking, using a stack.
- **Dynamic Stack**: Linked-list-based stack grows and shrinks at runtime, no fixed capacity limit.
- **Accumulated Path Cost**: Each stack entry carries the cumulative cost from the source vertex.