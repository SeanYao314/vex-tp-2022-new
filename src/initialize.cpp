#include "main.h"
#include "api.h"
#include "okapi/api.hpp"

#include <vector>

using namespace std;
using namespace pros;
using namespace okapi;

pros::Motor chassis_left_front(CHASSIS_LEFT_FRONT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_left_middle(CHASSIS_LEFT_MIDDLE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_left_rear(CHASSIS_LEFT_REAR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_front(CHASSIS_RIGHT_FRONT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_middle(CHASSIS_RIGHT_MIDDLE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_rear(CHASSIS_RIGHT_REAR, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor arm_right(RIGHT_ARM, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm_left(LEFT_ARM, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut claw_front(CLAW_FRONT, true);
pros::ADIDigitalOut claw_front_2(CLAW_FRONT_2, true);
pros::ADIDigitalOut claw_back(CLAW_BACK, true);
pros::ADIDigitalOut mogo_cover(MOGO_COVER, true);


pros::Imu imu_sensor(IMU_SENSOR_PORT);
pros::Distance distance_sensor (DISTANCE_SENSOR_PORT_FRONT);
pros::Distance distance_back_sensor(DISTANCE_SENSOR_PORT_BACK);
// auto lg = {chassis_left_front, chassis_left_middle, chassis_left_rear};

// okapi::MotorGroup chassis_mg_left(lg);
int auton_selector = 0;

vector<pros::Motor*>& get_motor_group() {
	static vector<pros::Motor*> motor_group;

	if (motor_group.size() == 0) {
        motor_group.push_back(&chassis_left_front);
        motor_group.push_back(&chassis_left_middle);
        motor_group.push_back(&chassis_left_rear);
        motor_group.push_back(&chassis_right_front);
        motor_group.push_back(&chassis_right_middle);
        motor_group.push_back(&chassis_right_rear);
        motor_group.push_back(&arm_left);
        motor_group.push_back(&arm_right);
	}

	return motor_group;
}

vector<pros::ADIDigitalOut*>& get_switch_group() {
    static vector<pros::ADIDigitalOut*> switch_group;
    if (switch_group.size() == 0) {
        switch_group.push_back(&claw_front);
        switch_group.push_back(&claw_front_2);
        switch_group.push_back(&claw_back);
        switch_group.push_back(&mogo_cover);
    }
    return switch_group;
}

void notify_controller(const char * rumble_msg, const char * msg) {
	master.rumble(rumble_msg);
	master.print(0, 0, "%s", msg);
}

vector<recording::RecordUnit>& load_replaying() {
	static vector<recording::RecordUnit> empty;
	if (storage::is_slot_taken(graviton_screen::get_selected_program())) {
		return storage::get_program(graviton_screen::get_selected_program());
	} else {
		return empty; 
	}
}

void graviton_initialize()
{
	graviton_screen::setup_screen();
	graviton_screen::set_notif_handler(notify_controller);
	storage::load_all_programs();
	recording::set_motor_group(get_motor_group(), get_switch_group());
	recording::set_replay_loader(load_replaying);
}