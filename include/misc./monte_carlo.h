#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

template<typename D>
using reduction_func_t = std::function<D(const D&, const D&)>;

template<typename D, typename R>
using sample_func_t = std::function<D(const std::function<R()>&)>;

template<typename DataType, typename RNGType = DataType>
class MonteCarlo {
public:
    explicit MonteCarlo(
    const sample_func_t<DataType, RNGType>& samplingFunc,
    const reduction_func_t<DataType>& reductionFunc = std::plus<DataType>())
    : rng(this->rd()), samplingFunc(samplingFunc) , reductionFunc(reductionFunc)
    {
    }

    DataType simulate(const std::size_t& sample_count) {
        auto rngFunc = [this] () { return dist(rng); };

        std::vector<DataType> samples(sample_count);
        std::generate_n(
          samples.begin(),
          samples.size(),
          [&] { return samplingFunc(rngFunc); });

        return std::accumulate(
          samples.begin(),
          samples.end(),
          static_cast<DataType>(0),
          reductionFunc)
          / sample_count;
    }

protected:
    std::random_device                       rd;
    std::mt19937                             rng;
    std::uniform_real_distribution<RNGType>  dist;

    sample_func_t<DataType, RNGType> 	samplingFunc;
    reduction_func_t<DataType> 			reductionFunc;
};

#endif // MONTE_CARLO_H
