#include <stdio.h>
#include "robotArm.h"
#include "robotLeg.h"

int
main( void )
{
    printf("|__Creating robot arm and leg controllers:\n");

    robotArm arm = robotArmCreate();
    robotArmInit( arm );

    robotLeg leg = robotLegCreate();
    robotLegInit( leg );

    printf("|__Moving robot arm:\n");
    
    robotArm_moveElbowTo(arm, 90);
    robotArm_moveWristTo(arm, 55);
    robotArm_moveShoulderTo(arm, 179);

    printf("|__Moving robot leg:\n");
    
    robotLeg_moveHipTo(leg, 10);
    robotLeg_moveAnkleTo(leg, 140);

    return 0;
}