#include "humanize/numbers.h"

#include <iostream>
#include <assert.h>
using namespace std;

int main()
{
    std::cout << humanize::numbers::getCompactName(1000000) << "\n";
    return 0;
}
