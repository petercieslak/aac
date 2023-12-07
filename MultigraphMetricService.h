#ifndef AAC_MULTIGRAPHMETRIC_H
#define AAC_MULTIGRAPHMETRIC_H

#include <algorithm>
#include <climits>
#include <random>
#include <chrono>
#include "Multigraph.h"

class MultigraphMetricService {

    public:
        int calculateGraphEditDistance(Multigraph multigraph1, Multigraph multigraph2);

        int calculateGraphEditDistanceApproximation(Multigraph multigraph1, Multigraph multigraph2);

};

#endif //AAC_MULTIGRAPHMETRIC_H