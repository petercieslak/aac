#include "MultigraphMetricService.h"

int MultigraphMetricService::calculateGraphEditDistance(Multigraph multigraph1, Multigraph multigraph2) {
    
    Multigraph smallerMultigraph(0);
    Multigraph biggerMultigraph(0);

    int sizeDifference = abs(multigraph1.getVerticesNo() - multigraph2.getVerticesNo());

    if(multigraph1.getVerticesNo() <= multigraph2.getVerticesNo()) {
        smallerMultigraph = multigraph1;
        biggerMultigraph = multigraph2;
    }

    else if(multigraph1.getVerticesNo() > multigraph2.getVerticesNo()) {
        smallerMultigraph = multigraph2;
        biggerMultigraph = multigraph1;
    }

    if(sizeDifference > 0)
        smallerMultigraph.addEmptyVertices(biggerMultigraph.getVerticesNo() - smallerMultigraph.getVerticesNo());

    int graphEditDistance = INT_MAX;
    int graphEditDistanceLocal = 0;

    int *vertexIndex = new int[smallerMultigraph.getVerticesNo()];
    for (int i = 0; i < smallerMultigraph.getVerticesNo(); i++) {
        vertexIndex[i] = i;
    }

    do {
        for(int i = 0; i < smallerMultigraph.getVerticesNo(); i++) {
            for(int j = 0; j < smallerMultigraph.getVerticesNo(); j++) {
                graphEditDistanceLocal += abs(smallerMultigraph.getVertex(vertexIndex[i],vertexIndex[j]) - biggerMultigraph.getVertex(i,j));
            }
        }

        graphEditDistanceLocal += sizeDifference;
        if(graphEditDistanceLocal < graphEditDistance)
            graphEditDistance = graphEditDistanceLocal;

        graphEditDistanceLocal = 0;
    } while (std::next_permutation(vertexIndex, vertexIndex + smallerMultigraph.getVerticesNo()));

    std::cout << "Graph edit distance: " << graphEditDistance << std::endl;
    std::cout << std::endl;

    return graphEditDistance;
}

int MultigraphMetricService::calculateGraphEditDistanceApproximation(Multigraph multigraph1, Multigraph multigraph2) {
    Multigraph smallerMultigraph(0);
    Multigraph biggerMultigraph(0);

    int sizeDifference = abs(multigraph1.getVerticesNo() - multigraph2.getVerticesNo());

    if(multigraph1.getVerticesNo() <= multigraph2.getVerticesNo()) {
        smallerMultigraph = multigraph1;
        biggerMultigraph = multigraph2;
    }

    else if(multigraph1.getVerticesNo() > multigraph2.getVerticesNo()) {
        smallerMultigraph = multigraph2;
        biggerMultigraph = multigraph1;
    }

    if(sizeDifference > 0)
        smallerMultigraph.addEmptyVertices(biggerMultigraph.getVerticesNo() - smallerMultigraph.getVerticesNo());

    int graphEditDistance = INT_MAX;
    int graphEditDistanceLocal = 0;

    int *vertexIndex = new int[smallerMultigraph.getVerticesNo()];
    for (int i = 0; i < smallerMultigraph.getVerticesNo(); i++) {
        vertexIndex[i] = i;
    }

    //guess

    for(int i = 0; i < smallerMultigraph.getVerticesNo(); i++) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(vertexIndex, vertexIndex + smallerMultigraph.getVerticesNo(), std::default_random_engine());

        for(int i = 0; i < smallerMultigraph.getVerticesNo(); i++) {
            for(int j = 0; j < smallerMultigraph.getVerticesNo(); j++) {
                graphEditDistanceLocal += abs(smallerMultigraph.getVertex(vertexIndex[i],vertexIndex[j]) - biggerMultigraph.getVertex(i,j));
            }
        }

        graphEditDistanceLocal += sizeDifference;
        if(graphEditDistanceLocal < graphEditDistance)
            graphEditDistance = graphEditDistanceLocal;

        graphEditDistanceLocal = 0;
    }

    std::cout << "Graph edit distance: " << graphEditDistance << std::endl;
    std::cout << std::endl;

    return graphEditDistance;
}