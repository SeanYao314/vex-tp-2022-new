#include "main.h"
#include "okapi/api.hpp"

#include <exception>
#include <vector>

namespace okapi {
    class AbstractMotor;
}

namespace recording {

    void reset_chassis_encoders();
    bool is_moving_straight(RecordUnit&);

    using namespace std;
    bool is_power_changed();
    void do_record();

    // private variables
    vector<RecordUnit> recording;
    vector<RecordUnit>& (*replay_loader)(void);
    const int threshold = 15;
    int recording_interval = ITERATION_INTERVAL;
    int recording_time = 15000;
    int tick = 0;
    void (*post_record_action)(void) = NULL;

    vector<pros::Motor*> empty_motor_group;
    vector<pros::Motor*> * motor_group = &empty_motor_group;
    vector<pros::ADIDigitalOut*> empty_switch_group;
    vector<pros::ADIDigitalOut*> * switch_group = &empty_switch_group;

    void set_motor_group(vector<pros::Motor*>& motors, vector<pros::ADIDigitalOut*>& switches) {
        motor_group = &motors;
        switch_group = &switches;
    }

    void reset(int duration, int interval, void (*action)(void)) {
        recording_interval = interval;
        recording_time = duration;
        tick = 0;
        post_record_action = action;
        
        recording.clear();
        int capacity = duration / interval;
    }

    void set_replay_loader(std::vector<RecordUnit>& (* loader)(void)) {
        replay_loader = loader;
    }

    void record() {
        int capacity = recording_time/ recording_interval;

        if (tick == capacity - 1) {
            if (post_record_action != NULL) {
                post_record_action();
            }
            ++tick; 
            return;
        } else if (tick == capacity) {
            return;
        }

        ++ tick;

        if (is_power_changed()) {
            do_record();
        }
    }

    bool is_power_changed() {
        if (recording.size() == 0) {
            for (int i=0; i<(*motor_group).size(); ++i) {
                if (abs((*motor_group)[i]->get_voltage()) > threshold) {
                    cout << "initial position changed, "; 
                    return true;
                }
            }
        } else { 
            RecordUnit& last_unit = recording.back();
            for (int i=0; i<last_unit.units.size(); ++i) {
                if (abs(last_unit.units[i] - (*motor_group)[i]->get_voltage()) > threshold) {
                    cout << "new change detected, ";
                    return true;
                }
            }
            for (int i=0; i<last_unit.switches.size(); ++i) {
                auto switcher = (pros::ADIPort *)(*switch_group)[i];
                if (last_unit.switches[i] != switcher->get_value()) {
                    cout << "adi value change detected";
                    return true;
                }
            }
        }
        return false;
    }

    void do_record() {
        if (recording.size() == 0) {
            tick = 0; // reset tick position
        }
        RecordUnit new_unit; 
        cout << "saving a new record " << endl; 
        new_unit.tick = tick;
        for (int i=0; i<(*motor_group).size(); ++i) {
            new_unit.units.push_back((*motor_group)[i]->get_voltage());
        }
        for (int i=0; i<(*switch_group).size(); ++i) {
            auto switcher = (pros::ADIPort *)(*switch_group)[i];
            new_unit.switches.push_back(switcher->get_value());
        }
        recording.push_back(new_unit);
    }

    void printout() {
        for (int i=0; i<=recording.size(); ++i) {
            cout << "{";
            std::cout << recording[i].tick;
            for (int j=0; j<recording[i].units.size(); ++j) {
                cout << ", " << recording[i].units[j];
            }
            cout << "}," << endl;
        }
    }

    void replay() {
        if (replay_loader == NULL) {
            cout << "no replay loader found" << endl;
            return;
        }
        vector<RecordUnit> replay_recording = replay_loader();
        if (replay_recording.empty()) {
            cout << "load empty records, nothing to replay" << endl;
            return;
        }
        cout << "about to replay " << replay_recording.size() << " steps" << endl;
        int starting_tick = replay_recording.front().tick;
        int ending_tick = replay_recording.back().tick;
        cout << "starting at " << starting_tick << " and end at " << ending_tick << " for total " 
                << (ending_tick - starting_tick) * 50 / 1000 << " senconds" << endl;

        // reset_chassis_encoders();

        int r_index = 0;
        for (int t = starting_tick; t < ending_tick; ++t) {
            RecordUnit& unit = replay_recording[r_index];
            int tick = unit.tick;
            if (tick == t) {
                for (int j=0; j<(*motor_group).size(); ++j) {
                    (*motor_group)[j]->move_voltage(unit.units[j]);
                }
                for (int j=0; j<(*switch_group).size(); ++j) {
                    (*switch_group)[j]->set_value(unit.switches[j]);
                }
                r_index ++;
            }

            // if (is_moving_straight(unit)) {
            //     // compensate_chassis_motors();
            // }
            pros::delay(recording_interval);
        }
        cout << "replaying done !!" << endl;
    }

    // void compensate_chassis_motors() {
    //     double encoder_num_sum = 0;
    //     for (int i=0; i<chassis_motor_numbers; ++i) {
    //         encoder_num_sum += (*motor_group)[i]->getPosition();
    //     }
    //     double average_encode_value = encoder_num_sum / chassis_motor_numbers;
    //     double encoder_delta_threshold = 10;
    //     int motor_voltage_increment = 5;
    //     for (int i=0; i<chassis_motor_numbers; ++i) {
    //         if (abs(average_encode_value - (*motor_group)[i]->getPosition()) > encoder_delta_threshold) {

    //         }
    //     }
    // }

    // void reset_chassis_encoders() {
    //     for (int i=0; i<chassis_motor_numbers; ++i) {
    //         (*motor_group)[i]->tarePosition();
    //     }
    // }

    // bool is_moving_straight(RecordUnit & ru) {
    //     for (int i=1; i<chassis_motor_numbers; ++i) {
    //         if (ru.units[i] != ru.units[0]) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }

    vector<RecordUnit>& dump() {
        return recording;
    }
}