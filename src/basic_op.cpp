#include "main.h"

using namespace std;

const int chass_power_threshold = 3;
const int arm_voltage = 127;

void set_cheassis_break_mode(const pros::motor_brake_mode_e_t mode) {
    chassis_left_front.set_brake_mode(mode);
    chassis_left_middle.set_brake_mode(mode);
    chassis_left_rear.set_brake_mode(mode);
    chassis_right_front.set_brake_mode(mode);
    chassis_right_middle.set_brake_mode(mode);
    chassis_right_rear.set_brake_mode(mode);
}

void chassis_drive(int left_power, int right_power) {

    // cout << "left: " << left_power << ", right: " << right_power << endl;

    if (abs(left_power) < chass_power_threshold) {
        left_power = 0;
    }
    if (abs(right_power) < chass_power_threshold) {
        right_power = 0;
    }
 	set_cheassis_break_mode(pros::E_MOTOR_BRAKE_COAST);
    chassis_left_front.move(-left_power);
    chassis_left_middle.move(-left_power);
    chassis_left_rear.move(-left_power);
    chassis_right_front.move(-right_power);
    chassis_right_middle.move(-right_power);
    chassis_right_rear.move(-right_power);
}



//--------------------------------------------------------------------------------------------------//
int testVar=0;
int targetMaxArmPos = -750;
void arm_drive(int direction) {
    // int leftArmTargetPos = (arm_left.get_position()+(600+arm_right.get_position()));
    int deltaRightArm = arm_right.get_position()-targetMaxArmPos;
    if(direction==1) {
        std::cout << "\nright arm Motor Position: " << arm_right.get_position();
        std::cout << "\nleft arm Motor Position: " << arm_left.get_position();
        std::cout << "\nleft arm target Position: " << "hi";

        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_right.move_absolute(targetMaxArmPos,200);
        if(deltaRightArm>20) {
            arm_left.move(200);
        } else if(deltaRightArm<-30) {
            arm_left.move(-30);
        } else {
            arm_left.move(0);
        }
        testVar=0;
    } else if (direction ==-1) {
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        testVar=1; 
    } else if (direction ==2) {
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_left.move(-20000);
    } else if (!(direction == 1) && testVar==0 && !(direction==2)) {
        arm_right.move(0);
        arm_left.move(0);
        testVar=0;
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    } else if(testVar=1) {
        arm_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_right.move_absolute(45,200);
        if(arm_right.get_position()<30) {
            arm_left.move(-200);
        } else {
            arm_left.move(0);
        }
    } 

    
}

void intake_drive(bool running) {
    
}
void rear_piston_drive(bool close) {
    if (close) {
        claw_back.set_value(1);
    } else {
        claw_back.set_value(0);
    }
}

void mogo_cover_drive(bool close) {
    if (close) {
        mogo_cover.set_value(1);
    } else {
        mogo_cover.set_value(0);
    }
}

void front_claw_drive(bool close) {
    if (close) {
        claw_front.set_value(1);
        claw_front_2.set_value(1);
    } else {
        claw_front.set_value(0);
        claw_front_2.set_value(0);
    }
}



//---------------------------------------------------------------------------------------------//



void chassis_rotate(int speed, bool clockwise) {
    int speed_modifier = clockwise ? 1 : -1;
    chassis_drive(speed_modifier * speed, -1 * speed_modifier * speed);
}

int calculate_rotate_speed(int delta) {
    if (std::abs(delta) < 30) {
        return 50;
    }
    return 60;
}

int calculate_rotation_threshold(int degree) {
    degree = abs(degree);
    if (degree >= 90) {
        return 7;
    } else if (degree >= 60) {
        return 6;
    } else if (degree >= 45) {
        return 5;
    } else if (degree >= 30) {
        return 3;
    } 

    return 2;
}

void chassis_turn(double degree) {

    std::cout << "chassis turn " << degree << std::endl;
    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    double chass_rotate_degree_threshold = calculate_rotation_threshold(degree);

    imu_sensor.tare_heading();
    double current_pos = imu_sensor.get_heading();
    double target_pos = (int)(current_pos + degree);
    double delta = degree;
    double last_delta = std::abs(delta);

    while (std::abs(delta) > chass_rotate_degree_threshold) {
        int speed = calculate_rotate_speed(delta);
        chassis_rotate(speed, delta > 0);
        pros::delay(20);
        
        current_pos = imu_sensor.get_heading();
        delta = (int)(target_pos - current_pos) % 360;
        cout << "target: " << target_pos 
            << ", current: " << current_pos
            << ", dalta: " << delta 
            << ", rotation: " << imu_sensor.get_rotation() 
            << ", last delta: " << last_delta << endl;
        // if (std::abs(delta) > (last_delta + chass_rotate_degree_threshold)) {
        //     break;
        // }
        last_delta = std::abs(delta);
    }
    cout << "break out from the loop" << endl;  
    chassis_drive(0, 0);

    // pros::delay(500);
    // cout << "final!! target: " << target_pos 
    //     << ", current: " << imu_sensor.get_heading() 
    //     << ", dalta: " << delta 
    //     << ", rotation: " << imu_sensor.get_rotation() 
    //     << ", last delta: " << last_delta << endl;

}

double average_chassis_motor_position() {
    auto l_pos = chassis_left_front.get_position();
    auto r_pos = chassis_right_front.get_position(); 

    cout << "left position: " << l_pos
        << ", right position: " << r_pos
        << endl;

    return (l_pos + r_pos) / 2;
}

void chassis_drive_distance(int unit, int speed) {

    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    int direction = speed > 0 ? -1 : 1;
    if(speed > 0) {
        int direction = 1;
    } else {
        direction = -1;
    }
    chassis_left_front.tare_position();
    chassis_right_front.tare_position();
    chassis_drive(30 * direction, 30 * direction);
    pros::delay(200);
    while (true) {
        chassis_drive((speed) * direction, speed * direction);
        pros::delay(20);
        auto pos = average_chassis_motor_position();
        if ((abs(pos) - unit) >= 400) {
            break;
        }
    }
    while (true) {
        chassis_drive(30 * direction, 30 * direction);
        pros::delay(20);
        auto pos = average_chassis_motor_position();
        if (abs(pos) >= unit) {
            break;
        }
    }
    chassis_drive(0, 0);
}

void chassis_drive_until_distance(int stop_distance, int speed) {
    cout << "start chassis_drive_until_distance" << endl;
    auto distance = distance_sensor.get();
    chassis_drive(200, 200);
    pros::delay(500);
    while (distance > (stop_distance + 700)) {
        chassis_drive(speed, speed);
        pros::delay(20);

        distance = distance_sensor.get();
        auto confidence = distance_sensor.get_confidence();
        auto size = distance_sensor.get_object_size();

        cout << "distance: " << distance
            << ", confidence: " << confidence
            << ", size: " << size << endl;
    }
    while (distance > stop_distance) {
        chassis_drive(200, 200);
        pros::delay(20);
        distance = distance_sensor.get();
    }
    chassis_drive(-200, -200);
    pros::delay(30);
    chassis_drive(0,0);

    // pros::delay(500);
    cout << "finish drive_until_distance, final distance: " << distance_sensor.get() << endl;
}
void chassis_drive_until_distance_back(int stop_distance, int speed) {
    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    auto distance = distance_back_sensor.get();
    chassis_drive(-30, -30);
    pros::delay(200);
    while (distance > (stop_distance + 500)) {
        chassis_drive(-speed, -speed);
        pros::delay(20);

        distance = distance_back_sensor.get();
        auto confidence = distance_back_sensor.get_confidence();
        auto size = distance_back_sensor.get_object_size();

        cout << "distance: " << distance
            << ", confidence: " << confidence
            << ", size: " << size << endl;
    }
    while (distance > stop_distance) {
        chassis_drive(30, 30);
        pros::delay(20);
        distance = distance_back_sensor.get();
    }
    chassis_drive(0, 0);

    // pros::delay(500);
    // cout << "final distance: " << distance_sensor.get() << endl;
}

void chassis_drive_until_level() {

    const int pitch_threshold = 10;
    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    bool is_chassis_on_bridge = false;
    bool is_chassis_leveled = false;
    double max_pitch = 0;
    while (!is_chassis_on_bridge) {
        chassis_drive(-80, -80);
        pros::delay(20);

        auto pitch = imu_sensor.get_pitch();
        max_pitch = max(max_pitch, abs(pitch));
        cout << "pitch: " << pitch << endl;
        if (abs(pitch) > pitch_threshold) {
            is_chassis_on_bridge = true;
            cout << "on the bridge now" << endl;
        }
    }
    pros::delay(700);
    while (!is_chassis_leveled) {
        // chassis_drive(-50, -50);
        pros::delay(20);
        auto pitch = imu_sensor.get_pitch();
        max_pitch = max(max_pitch, abs(pitch));
        cout << "pitch: " << pitch << ", max pitch: " << max_pitch << endl;
        if (abs(pitch) < max_pitch - 1) {
            is_chassis_leveled = true;
            cout << "on the bridge and leveled now." << endl;
        }
    }
    //chassis_drive(50, 50);
    //pros::delay(100);
    chassis_drive(0, 0);
    pros::delay(100);

    chassis_drive(50, 50);
    // pros::delay(200);

    chassis_drive(0, 0);
    
    pros::delay(1000);
    cout << "final pitch: " << imu_sensor.get_pitch() << endl;
    
    // auto pitch = imu_sensor.get_pitch();
    // while (abs(pitch) > pitch_threshold) {
    //     int direction = pitch > 0 ? 1 : -1;
    //     chassis_drive(direction * 40, direction * 40);
    //     pros::delay(100);
    //     chassis_drive(0, 0);
    //     pros::delay(100);
    //     cout << "pitch: " << pitch << endl;
    // }

    // chassis_drive(0, 0);
    
    // pros::delay(1000);
    // cout << "final pitch: " << imu_sensor.get_pitch() << endl;
    
}