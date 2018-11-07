#include "main.h"
#include "display/lvgl.h"

#include <string>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	flyWheel.set_reversed(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	competition_initialize();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

enum auton_choice_t {
SKILLSORMATCH,
REDORBLUE,
FLAGORCAP,
DONEMATCH,
DONESKILLS
};

lv_obj_t * container = lv_cont_create(lv_scr_act(), NULL);
lv_obj_t * autonLabel = lv_label_create(container, NULL);
lv_obj_t * backButton = lv_btn_create(container, NULL);
lv_obj_t * backButtonText = lv_label_create(backButton, NULL);

lv_obj_t * buttonContainer = lv_cont_create(container, NULL);
lv_obj_t * left_button = lv_btn_create(buttonContainer, NULL);
lv_obj_t * left_button_text = lv_label_create(left_button, NULL);
lv_obj_t * right_button = lv_btn_create(buttonContainer, NULL);
lv_obj_t * right_button_text = lv_label_create(right_button, NULL);

auton_choice_t choice;

std::string getAutonSideName(int as) {
	if (as == SIDE_CAP) {
		return "CAP";
	}
	if (as == SIDE_FLAG) {
		return "FLAG";
	}
	return "NONE";
}

std::string getAutonTeamName(int at) {
	if (at == TEAM_RED) {
		return "RED";
	}
	if (at == TEAM_BLUE) {
		return "BLUE";
	}
	return "NONE";
}

void updateState() {
	if (choice == SKILLSORMATCH) {
		lv_label_set_text(autonLabel, "Auton>");
		lv_label_set_text(left_button_text, "Skills");
		lv_label_set_text(right_button_text, "Match");
	} else if (choice == REDORBLUE) {
		lv_label_set_text(autonLabel, "Auton>Match>");
		lv_label_set_text(left_button_text, getAutonTeamName(TEAM_BLUE).c_str());
		lv_label_set_text(right_button_text, getAutonTeamName(TEAM_RED).c_str());
	} else if (choice == FLAGORCAP) {
		lv_label_set_text(autonLabel, ("Auton>Match>"+getAutonTeamName(autonTeam)+">").c_str());
		lv_label_set_text(left_button_text, getAutonSideName(SIDE_FLAG).c_str());
		lv_label_set_text(right_button_text, getAutonSideName(SIDE_CAP).c_str());
	} else if (choice == DONEMATCH) {
		lv_label_set_text(autonLabel, ("Auton>Match>"+getAutonTeamName(autonTeam)+">"+getAutonSideName(autonSide)+">").c_str());
		lv_label_set_text(left_button_text, "");
		lv_label_set_text(right_button_text, "");
	} else if (choice == DONESKILLS) {
		lv_label_set_text(autonLabel, "Auton>Skills");
		lv_label_set_text(left_button_text, "");
		lv_label_set_text(right_button_text, "");
	}
}

lv_res_t buttonPressed(lv_obj_t* obj) {
	if (obj == left_button) {
		if (choice == SKILLSORMATCH) {
			choice = DONESKILLS;
			autonType = AUTON_SKILLS;
		} else if (choice == REDORBLUE) {
			choice = FLAGORCAP;
			autonTeam = TEAM_BLUE;
		} else if (choice == FLAGORCAP) {
			choice = DONEMATCH;
			autonSide = SIDE_FLAG;
		}
	}
	if (obj == right_button) {
		if (choice == SKILLSORMATCH) {
			choice = REDORBLUE;
			autonType = AUTON_MATCH;
		} else if (choice == REDORBLUE) {
			choice = FLAGORCAP;
			autonTeam = TEAM_RED;
		} else if (choice == FLAGORCAP) {
			choice = DONEMATCH;
			autonSide = SIDE_CAP;
		}
	}
	if (obj == backButton) {
		choice = SKILLSORMATCH;
	}
	updateState();
}

void competition_initialize() {
	int screenWidth = lv_obj_get_width(lv_scr_act());
	int screenHeight = lv_obj_get_height(lv_scr_act());
	lv_obj_set_size(container, screenWidth, screenHeight);

	lv_cont_set_layout(buttonContainer, LV_LAYOUT_PRETTY);
	lv_obj_set_pos(buttonContainer, 100, 25);
	lv_obj_set_size(buttonContainer, screenWidth-100, screenHeight-25);

	lv_label_set_text(autonLabel, "Auton>");
	lv_obj_set_pos(autonLabel, 2, 3);

	lv_obj_set_pos(backButton, 2, 25);
	lv_obj_set_size(backButton, 80, 40);
	lv_btn_set_action(backButton, LV_BTN_ACTION_CLICK, buttonPressed);

	lv_btn_set_action(left_button, LV_BTN_ACTION_CLICK, buttonPressed);
	lv_btn_set_action(right_button, LV_BTN_ACTION_CLICK, buttonPressed);

	lv_label_set_text(backButtonText, "Back");

	updateState();
	while (true) {
		lv_task_handler();
		pros::delay(5);
	}
}
