#include "main.h"

using namespace std;

// void claw_move(int position, int direction) {
//     auto arm_pos = arm_rear.get_position();
//     while (abs(arm_pos - position) > 5) {
//         arm_rear.move(90*direction);
//         pros::delay(20);

//         arm_pos = arm_rear.get_position();
//         cout << "position: " << arm_pos << endl;
//     }
// }

// void claw_move_time(int position, int time) {
//     arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//     arm_rear.move_absolute(position,200);
//     pros::delay(time);
//     arm_rear.move(0);
// }
// void claw_stop() {
//     arm_rear.move(0);
// }


void armMoveAbsolute(int armPosition) {
    int deltaRightArm = arm_right.get_position()-armPosition;
    if(deltaRightArm>0) {
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_right.move_absolute(armPosition,200);
        if(deltaRightArm>20) {
            arm_left.move(200);
        } else if(deltaRightArm<-30) {
            arm_left.move(-30);
        } else {
            arm_left.move(0);
        }
    } else if(deltaRightArm<0) {
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_right.move_absolute(armPosition,200);
        if(deltaRightArm>20) {
            arm_left.move(-200);
        } else {
            arm_left.move(0);
        }
    }
}
void auton_climb_bridge() {
    // arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    // auto arm_pos = arm_rear.get_position();
    // while (abs(arm_pos - 585) > 5) {
    //     arm_rear.move(90);
    //     pros::delay(20);

    //     arm_pos = arm_rear.get_position();
    //     cout << "position: " << arm_pos << endl;
    // }

    // arm_rear.move(0);

    chassis_drive_until_level();




}

void right_side_one_mogo_rings() {
    
//     front_claw_drive(true);
//     pros::delay(100);
//     front_claw_drive(false);

//     chassis_drive_until_distance(60, 90);
//     pros::delay(200);
//     front_claw_drive(true);

//     pros::delay(400);
//     arm_right.move_absolute(-140,200);


//     chassis_turn(20);
//     chassis_drive_distance(720, 70);

//     rear_arm_drive(1);
//     arm_right.move_absolute(-140,200);
//     chassis_turn(-105);
//     pros::delay(400);

//     chassis_drive_distance(540,70);
//     pros::delay(400);
//     rear_arm_drive(2);

//     chassis_drive_distance(790,-80);
//     rear_arm_drive(1);

//     arm_right.move_absolute(50,200);
//     front_claw_drive(false);

//     chassis_drive_distance(40,60);
//     chassis_turn(35);

//     chassis_drive_until_distance(60,90);

}

void right_side_two_mogos() {
    arm_right.move_absolute(24,200);
    front_claw_drive(false);
    rear_piston_drive(false);
    chassis_drive_until_distance(156,30);

    front_claw_drive(true);
    chassis_drive_distance(620,200);

    // front_claw_drive(false);
    // chassis_drive_distance(200,100);
    // pros::delay(100);
    // chassis_turn(-33.1);

    // arm_right.move_absolute(24,200);
    // chassis_drive_distance(1980,-180);
    // pros::delay(100);
    // front_claw_drive(true);
    // pros::delay(100);

    // chassis_drive_distance(1100, 200);
    // front_claw_drive(false);
    // pros::delay(200);
    // chassis_drive_distance(160,160);

    // pros::delay(100);
    // chassis_turn(-74);
    // chassis_drive_distance(320,110);
    // pros::delay(300);
    // rear_piston_drive(true);

    // chassis_drive_distance(50,-120);
    // arm_right.move_absolute(-200,200);
    // arm_drive(2);


    



//     chassis_drive_distance(734,60);

//     rear_arm_drive(1);
//     arm_right.move_absolute(-140,200);
//     chassis_turn(113.5);

//     chassis_drive_distance(1240,60);
//     pros::delay(600);
//     rear_arm_drive(2);

//     chassis_drive_distance(1140,-60);
//     arm_right.move_absolute(-140,200);
//     chassis_turn(-160);

//     chassis_drive_distance(290,60);
//     rear_arm_drive(1);
//     pros::delay(1000);
//     chassis_drive(130,130);
//     pros::delay(190);
//     chassis_drive(0,0);
//     rear_arm_drive(2);


    // pros::delay(300);
        
    // chassis_drive_distance(180, 60);
    // rear_arm_drive(2);

    // chassis_turn(-17);
    // rear_arm_drive(1);
    // chassis_drive_distance(-300,40);


    // chassis_drive(150,-150);
    // pros::delay(600);
    // chassis_drive(0,0);

    // // chassis_turn(50);
    // chassis_drive_distance(1600, -60);

    // rear_arm_drive(1);
    // chassis_drive_distance(500,-60);

    // front_arm_preset(0);



    // while (distance_not_met || arm_not_lower) {
    //     if (distance_not_met) {
    //         chassis_motor_run()
    //     }
    //     if (arm_not_lowered) {
    //         arm_motor_run()
    //     }
    //     delay(20);
    //     // check if condition met
    //     if (distance_met) {
    //         distance_not_met = false
    //         stop_chassi_motor();
    //     }
    //     if (arm_lowered) {
    //         arm_not_lowered = false;
    //         stop_arm_motor();
    //     }
    // }


    // pros::delay(2000);
}


void left_side() {
    // arm_right.move_absolute(50,200);
    // front_claw_drive(true);
    // pros::delay(100);
    // front_claw_drive(false);


    // chassis_drive_until_distance(100, 90);
    // pros::delay(450);
    // front_claw_drive(true);

    // pros::delay(400);
    // arm_right.move_absolute(-140,200);
    // pros::delay(200);

    // rear_arm_drive(1);
    // chassis_drive_distance(580,70);

    // chassis_turn(-124);
    // // chassis_turn(-30);
    // chassis_drive_distance(70,60);

    // chassis_turn(-40);
    // chassis_drive_distance(150,80);


    // pros::delay(700);
    // chassis_drive_distance(60,-60);
}