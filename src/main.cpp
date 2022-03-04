#include "main.h"

using namespace std;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	// auton_selector = (auton_selector + 1) % 4;
	if (auton_selector == 0) {
		pros::lcd::set_text(1, "Auton Selection Cleared.");
	} else if (auton_selector == 1) {
		pros::lcd::set_text(1, "Straight and Get");
	} else if (auton_selector == 2) {
		pros::lcd::set_text(1, "Mobile goal right first!");
	} else if (auton_selector == 3) {
		pros::lcd::set_text(1, "Mobile goal center first!");
	}
}

void on_right_button() {
	auton_selector = 1;
	pros::lcd::set_text(1, "Auton Climbing the bridge");
}

void on_left_button() {
	auton_selector = 1;
	pros::lcd::set_text(1, "Auton get mobile goals!");
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	screen::setup_screen();
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "Hello PROS User!");

	// pros::lcd::register_btn1_cb(on_center_button);
	// pros::lcd::register_btn0_cb(on_left_button);
	// pros::lcd::register_btn2_cb(on_right_button);

	// cout << "resetting imu sensor ..." << endl;
	// imu_sensor.reset();
	// cout << "imu sensor finished calibrating..." << endl;
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// auton_selector = 2;

	// if (auton_selector == 1) {
	// 	right_side_one_mogo_rings();
	// } else if (auton_selector == 2) {
	// 	right_side_two_mogos();
	// } else if (auton_selector == 3) {
	// 	left_side();
	// }

	auto program = screen::get_selected_program();
	if (program == "Alpha") {
		alpha::auton();
	} else if (program == "Bravo") {
		bravo::auton();
	} else if (program == "Charlie") {
		charley::auton();
	} else if (program == "Delta") {
		delta::auton();
	} else if (program == "Echo") {
		echo::auton();
	} else if (program == "Kilo") {
		kilo::auton();
	} else if (program == "Lima") {
		lima::auton();
	} else if (program == "Mike") {
		mike::auton();
	} else if (program == "November") {
		november::auton();
	} else if (program == "Oscar") {
		oscar::auton();
	} else if (program == "Victor") {
		kilo::auton();
	} else if (program == "Uniform") {
		lima::auton();
	} else if (program == "Whiskey") {
		mike::auton();
	} else if (program == "Xray") {
		november::auton();
	} else if (program == "Yankee") {
		oscar::auton();
	} else {
		right_side_two_mogos();
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int posTwo = 1;
	int frontClawPos = 1;
	int intakeRun = 1;
	int backClawPos = 1;
	int mogoCoverPos = 1;
	while (true) {

		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		bool isRaisingFrontArm = master.get_digital(DIGITAL_R1) == 1;
		bool isDroppingFrontArm = master.get_digital(DIGITAL_R2) == 1;

		bool midArmPos = master.get_digital_new_press(DIGITAL_B) == 1;
		bool isDroppingRearArm = master.get_digital(DIGITAL_L2) == 1;

		bool frontClaw = master.get_digital_new_press(DIGITAL_L1) == 1;
		bool backClaw = master.get_digital_new_press(DIGITAL_L2) == 1;
		bool mogoCoverPressed = master.get_digital_new_press(DIGITAL_Y) == 1;

		bool testing_button_pressed = master.get_digital_new_press(DIGITAL_A) == 1;
		bool intake_pressed = master.get_digital_new_press(DIGITAL_RIGHT)==1;
		chassis_drive(left, right);

	
		if (isRaisingFrontArm) {
			arm_drive(1);
		} else if (isDroppingFrontArm) {
			arm_drive(-1);
		} else {
			arm_drive(0);
		}
		if(mogoCoverPressed) {
			mogoCoverPos*=-1;
		}
		if (mogoCoverPos==1) {
			mogo_cover_drive(true);
		} else if(mogoCoverPos==-1) {
			mogo_cover_drive(false);
		}

		if(intake_pressed) {
			intakeRun*=-1;
		}
		if(intakeRun==-1) {
			arm_drive(2);
		} else if(intakeRun==1) {
			
		}

		if(frontClaw) {
			frontClawPos*=-1;
		}
		if (frontClawPos==1) {
			front_claw_drive(true);
		} else if(frontClawPos==-1) {
			front_claw_drive(false);
		}

		if(backClaw) {
			backClawPos*=-1;
		}
		if (backClawPos==1) {
			rear_piston_drive(true);
		} else if(backClawPos==-1) {
			rear_piston_drive(false);
		}


		if (testing_button_pressed) {
			// chassis_drive_distance(1000, 50);
			// chassis_turn(-90);
			// chassis_drive_until_distance(50, 90);
			// auton_climb_bridge();
			
		}

		pros::delay(20);
	}
}
