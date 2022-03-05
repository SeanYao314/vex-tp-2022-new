/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2021, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

const int ITERATION_INTERVAL = 20;

const int CHASSIS_LEFT_FRONT    = 14;
const int CHASSIS_LEFT_MIDDLE   = 13;
const int CHASSIS_LEFT_REAR     = 11;
const int CHASSIS_RIGHT_FRONT   = 17;
const int CHASSIS_RIGHT_MIDDLE  = 18;
const int CHASSIS_RIGHT_REAR    = 19;

const int RIGHT_ARM = 20;
const int LEFT_ARM  = 12;

const int DISTANCE_SENSOR_PORT_FRONT = 1;
const int DISTANCE_SENSOR_PORT_BACK = 9;
const int IMU_SENSOR_PORT = 16;

const std::uint8_t CLAW_FRONT = 'A';
const std::uint8_t CLAW_FRONT_2 = 'B';
const std::uint8_t CLAW_BACK = 'C';
const std::uint8_t MOGO_COVER = 'G';

extern pros::Motor chassis_left_front;
extern pros::Motor chassis_left_middle;
extern pros::Motor chassis_left_rear;
extern pros::Motor chassis_right_front;
extern pros::Motor chassis_right_middle;
extern pros::Motor chassis_right_rear;

extern pros::Motor arm_right;
extern pros::Motor arm_left;

extern pros::ADIDigitalOut claw_front;
extern pros::ADIDigitalOut claw_front_2;
extern pros::ADIDigitalOut claw_back;
extern pros::ADIDigitalOut mogo_cover;

extern pros::Imu imu_sensor;
extern pros::Distance distance_sensor;
extern pros::Distance distance_back_sensor;

extern pros::Controller master;

extern int auton_selector;

#ifdef __cplusplus
extern "C" {
#endif
void chassis_drive(int x, int y);
void arm_drive(int d);
void rear_piston_drive(bool d);
void front_claw_drive(bool c);
void mogo_cover_drive(bool c);
void intake_drive(bool c);


void chassis_turn(double degree);
void chassis_drive_distance(int unit, int speed);
void chassis_drive_until_distance(int stop_distance, int speed);
void chassis_drive_until_distance_back(int stop_distance, int speed);
void chassis_drive_until_level();

void auton_climb_bridge();
void right_side_two_mogos();
void left_side();
void right_side_one_mogo_rings();

void graviton_initialize();

#ifdef __cplusplus
}
#endif

namespace alpha {
    void auton();
}
namespace bravo {
    void auton();
}
namespace charley {
    void auton();
}
namespace delta {
    void auton();
}
namespace echo {
    void auton();
}
namespace kilo {
    void auton();
}
namespace lima {
    void auton();
}
namespace mike {
    void auton();
}
namespace november {
    void auton();
}
namespace oscar {
    void auton();
}
namespace uniform {
    void auton();
}
namespace victor {
    void auton();
}
namespace whiskey {
    void auton();
}
namespace xray {
    void auton();
}
namespace yankee {
    void auton();
}

namespace graviton_screen {
    void setup_screen();
    const char * get_selected_program();
    void set_notif_handler(void (*handler)(const char *, const char *));
}

namespace recording {
    struct RecordUnit {
        short tick;
        std::vector<int> units;
        std::vector<std::int32_t> switches;
    } ;

    void reset(int duration, int interval, void (*post_record_action)(void));
    void record();
    void printout();
    void replay();
    void set_replay_loader(std::vector<RecordUnit>& (*)(void));
    void set_motor_group(std::vector<pros::Motor*>&, std::vector<pros::ADIDigitalOut*>&);
    // void init(std::vector<int>& (*input_device)(void), void (*output_device)(std::vector<int>&), std::vector<RecordUnit>& (*replay_loader)(void));
    std::vector<RecordUnit>& dump();
}

namespace storage {
    bool is_slot_taken(const char * slot_name);
    bool save_to_slot(std::vector<recording::RecordUnit>& recording, const char * slot_name);
    void clear_slot(const char * slot_name);
    void load_all_programs();
    std::vector<recording::RecordUnit>& get_program(const char *);
}

#endif  // _PROS_MAIN_H_
