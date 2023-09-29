#include "main.h"
#include "initialize.h"

namespace Robot {
    extern int cata_intake_limit;
    extern int block_intake_limit;

    extern void launchCata             (int limit);
    extern void blockIntakeAndMatchLoad(int limit);
}