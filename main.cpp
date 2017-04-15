#include "numbers.h"

#include <iostream>
#include <assert.h>
using namespace std;

int main()
{
    std::cout << humanize::numbers::getCompactName(-1000,310) << "\n";
    return 0;
}
