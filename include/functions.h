#include "main.h"
#include "initialize.h"

namespace Robot {
    extern int cata_intake_limit;
    extern int block_intake_limit;

    extern void moveCataTo             (int limit);
    extern void blockIntakeAndMatchLoad(int limit);
    extern void launchCataOnce         (void);
    extern void blockIntake            (void);
    extern void relaxCata              (void);
    extern void driveForwardCounts     (int counts,   double target_heading);
    extern void driveForwardInches     (double inches, double target_heading);
    extern void driveBackwardCounts    (int counts,   double target_heading);
    extern void driveBackwardInches    (double inches, double target_heading);
    extern void driveForwardTime       (int ms);
    extern void driveBackwardTime      (int ms);
    extern void rotateToHeading        (double target_heading, bool reversed=false);
    extern void intakeOnce             (void);
    extern void reverseIntakeOnce      (void);
    extern void enableIntake           (void);
    extern void disableIntake          (void);
}