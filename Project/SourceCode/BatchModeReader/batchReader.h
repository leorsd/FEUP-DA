#ifndef BATCHREADER_H
#define BATCHREADER_H

#include "graph.h"

void normalBatchReader(Graph* graph);

void restrictedBatchReader(Graph* graph);

void drivingAndWalkingBatchReader(Graph* graph);

void approximateSolutionBatchReader(Graph* graph);

#endif //BATCHREADER_H
