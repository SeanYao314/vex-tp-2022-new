#include "main.h"

namespace kilo {
    void auton() {
        double initPos = imu_sensor.get_heading();
        arm_right.move_absolute(20,200);
        front_claw_drive(false);
        rear_piston_drive(false);

        mogo_cover_drive(false);
        chassis_drive_distance(2093,-200);

        front_claw_drive(true);
        chassis_drive_distance(1960,200);

        pros::delay(700);
        double currentPos = imu_sensor.get_heading();
        chassis_turn((initPos-currentPos)-100);
        chassis_drive_distance(150,200);
        pros::delay(500);
        rear_piston_drive(true);
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_right.move_absolute(-700,200);
        arm_left.move_relative(760,200);

        pros::delay(1200);
        arm_left.move(-150);

        chassis_drive_distance(220,-90);
    }
}