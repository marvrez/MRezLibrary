#include "humanize/time.h"

#include <iostream>
#include <chrono>
#include <assert.h>
using namespace std;

int main() {
    auto res = humanize::time::relativeTime(std::chrono::system_clock::now() + std::chrono::seconds(312312323), std::chrono::system_clock::now() + std::chrono::minutes(50),
                                            humanize::SuffixType::LONG, 3);
    std::cout << res.str << "\n";
    return 0;
}
