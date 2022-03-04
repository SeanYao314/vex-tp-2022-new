#include "main.h"

namespace alpha {
    void auton() {
        double initPos = imu_sensor.get_heading();
        arm_right.move_absolute(20,200);
        front_claw_drive(false);
        rear_piston_drive(false);

        // chassis_drive_until_distance(150,200);
        mogo_cover_drive(false);
        chassis_drive_distance(2003,-200);

        front_claw_drive(true);
        chassis_drive_distance(655,200);

        pros::delay(700);
        double currentPos = imu_sensor.get_heading();
        chassis_turn((initPos-currentPos)-90);
        chassis_drive_distance(150,200);
        pros::delay(500);
        rear_piston_drive(true);
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_right.move_absolute(-700,200);
        arm_left.move_relative(760,200);

        pros::delay(400);
        arm_left.move(-150);

        chassis_drive_distance(320,-90);

        pros::delay(500);
        chassis_drive_distance(50,80);
        pros::delay(400);
        currentPos = imu_sensor.get_heading();
        chassis_turn((initPos-currentPos)-2);

        chassis_drive_distance(1350,-40);
        chassis_drive_distance(1350,70);
    }
}