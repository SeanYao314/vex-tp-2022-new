#include "main.h"

namespace lima {
    void auton() {
        double initPos = imu_sensor.get_heading();
        arm_right.move_absolute(20,200);
        front_claw_drive(false);
        rear_piston_drive(false);

        chassis_drive_until_distance(147,200);
        mogo_cover_drive(false);

        front_claw_drive(true);
        chassis_drive_distance(2010,200);

    }
}