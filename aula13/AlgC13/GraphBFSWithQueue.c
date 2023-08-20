//
// Joaquim Madeira, AlgC, May 2020
// João Manuel Rodrigues, AlgC, May 2020
//
// GraphBFS - QUEUE-based Breadth-First Search
//

#include "GraphBFSWithQueue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "IntegersStack.h"

struct _GraphBFSWithQueue {
  unsigned int* marked;
  int* distance;
  int* predecessor;
  Graph* graph;
  unsigned int startVertex;
};

GraphBFSWithQueue* GraphBFSWithQueueExecute(Graph* g,
                                            unsigned int startVertex) {
  assert(g != NULL);
  assert(0 <= startVertex && startVertex < GraphGetNumVertices(g));

  GraphBFSWithQueue* traversal =
      (GraphBFSWithQueue*)malloc(sizeof(struct _GraphBFSWithQueue));
  assert(traversal != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // COMPLETAR !!
  //
  // CRIAR e INICIALIZAR os campos de traversal
  // traversal->marked
  // traversal->distance
  // traversal->predecessor
  //
  
  traversal->marked = (unsigned int*)calloc(numVertices, sizeof(unsigned int));
  
  traversal->distance = (int*)malloc(numVertices * sizeof(int));
  int i =0;
  while(i<numVertices){
    traversal->distance[i] = __INT_MAX__;
    i++;
  }
  
  traversal->predecessor = (int*)malloc(numVertices * sizeof(int));
  
  i =0;
  while(i<numVertices){
    traversal->predecessor[i] = -1;
  }
  traversal->predecessor[startVertex] = -1;

  traversal->graph = g;
  traversal->startVertex = startVertex;

  // EFETUAR A TRAVESSIA

  // COMPLETAR !!

  Queue* fila = QueueCreate(numVertices);
  QueueEnqueue(fila, traversal->startVertex);
  traversal->marked[startVertex] = 1;

  while(!QueueIsEmpty(fila))
  {
    int aux = QueueDequeue(fila);
    unsigned int* vizi = GraphGetAdjacentsTo(traversal->graph, aux);

    for (int i = 1; i <= vizi[0]; i++) {
      unsigned int aux1 = vizi[i];
      if (traversal->marked[aux1] == 0) {
        QueueEnqueue(fila, aux1);
        traversal->marked[aux1] = 1;
        traversal->predecessor[aux1] = aux;
      }
    }
    free(vizi);
  }
  QueueDestroy(&fila);
  return traversal;
}

void GraphBFSWithQueueDestroy(GraphBFSWithQueue** p) {
  assert(*p != NULL);

  GraphBFSWithQueue* aux = *p;

  free(aux->marked);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

unsigned int GraphBFSWithQueueHasPathTo(const GraphBFSWithQueue* p,
                                        unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

Stack* GraphBFSWithQueuePathTo(const GraphBFSWithQueue* p, unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBFSWithQueueShowPath(const GraphBFSWithQueue* p, unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBFSWithQueuePathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

void GraphBFSWithQueueDisplay(const GraphBFSWithQueue* p) {
  // COMPLETAR !!
  Graph* g = p->graph;

  printf("\n");
  printf("Vertices = %2d  Edges = %2d\n", GraphGetNumVertices(g), GraphGetNumEdges(g));

  printf("Initial Vertex: %d\n", p->startVertex);
  int i =0;
  while(i<GraphGetNumVertices(g)){
    printf("%d ->\tmarked: %d\tpredecessor: %d\tdistance: %d\n", i, p->marked[i], p->predecessor[i], p->distance[i]);
    i++;
  }
  
    

}
