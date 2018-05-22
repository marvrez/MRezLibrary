#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <math/matrix.h>
#include <math/math.h>
#include "humanize/time.h"
#include "misc./log.h"
#include "misc./color.h"
#include "misc./string_utils.h"
#include "misc./rng.h"
#include "misc./array_util.h"
#include "misc./monte_carlo.h"
#include "network/net.h"

#ifdef THREADS
#include <thread>
#include <mutex>
#include <atomic>
#endif


int main() {
    // Sampling function. Provides a callable random number generator
    // and expects a data type (double for this case) return value.
    auto sampling_func = [] (const std::function<double()>& rng) -> double {
        // Sample a point within the unit square i.e. x and y in [0,1].
        auto x = rng(), y = rng();

        // Calculate distance from the origin.
        auto distance = sqrtf(x * x + y * y);

        // If the point is within the quarter circle, append 1.0.
        return distance <= 1.0 ? 1.0 : 0.0;
    };

    MonteCarlo<double> pi_estimator(sampling_func);

    // Apply 5 *10 ^ times.
    MEASURE_TIME(printf("%.6f\n", 4*pi_estimator.simulate(5e8)));
  return 0;
}
