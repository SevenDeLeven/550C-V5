#include "main.h"
#include "display/lvgl.h"
#include "sdlapi/timer.hpp"

#include <string>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	leftSide1.set_reversed(true);
	rightSide1.set_reversed(true);
	intake.set_reversed(true);
	rightLauncher.set_reversed(true);
	tilter.set_reversed(true);
	tilter.set_encoder_units(MOTOR_ENCODER_COUNTS);
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

 lv_res_t buttonPressed(lv_obj_t * obj);



enum auton_choice_t {
SKILLSORMATCH,
REDORBLUE,
FLAGORCAP,
DONE_MATCH,
DONE_SKILLS
} choice;
//
// lv_obj_t * container = lv_cont_create(lv_scr_act(), NULL);
// lv_obj_t * topScreenLabel = lv_label_create(container, NULL);
//
// lv_obj_t * backButton = lv_btn_create(container, NULL);
// lv_obj_t * backButtonText = lv_label_create(backButton, NULL);
//
// lv_obj_t * screenAutonomousButton = lv_btn_create(container, NULL);
// lv_obj_t * screenAutonomousButtonText = lv_label_create(screenAutonomousButton, NULL);
//
// lv_obj_t * screenSettingsButton = lv_btn_create(container, NULL);
// lv_obj_t * screenSettingsButtonText = lv_label_create(screenSettingsButton, NULL);
//
// lv_obj_t * screenObjectContainer;

//TABS
lv_obj_t * tabview = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * tabAuton = lv_tabview_add_tab(tabview, "Autonomous");
lv_obj_t * tabSettings = lv_tabview_add_tab(tabview, "Settings");

//AUTON SCREEN
lv_obj_t * autonLeftButton = lv_btn_create(tabAuton, NULL);
lv_obj_t * autonLeftButton_text = lv_label_create(autonLeftButton, NULL);
lv_obj_t * autonRightButton = lv_btn_create(tabAuton, NULL);
lv_obj_t * autonRightButton_text = lv_label_create(autonRightButton, NULL);
lv_obj_t * autonCenterButton = lv_btn_create(tabAuton, NULL);
lv_obj_t * autonCenterButton_text = lv_label_create(autonCenterButton, NULL);
lv_obj_t * autonBackButton = lv_btn_create(tabAuton, NULL);
lv_obj_t * autonBackButton_text = lv_label_create(autonBackButton, NULL);
lv_obj_t * autonLabel = lv_label_create(tabAuton, NULL);


//SETTINGS SCREEN
lv_obj_t * settingsParkSwitch = lv_sw_create(tabSettings, NULL);
lv_obj_t * settingsParkSwitchText = lv_label_create(tabSettings, NULL);
lv_obj_t * settingsTurnOffsetTitle = lv_label_create(tabSettings, NULL);
lv_obj_t * settingsTurnOffsetLeftButton = lv_btn_create(tabSettings, NULL);
lv_obj_t * settingsTurnOffsetLeftButton_text = lv_label_create(settingsTurnOffsetLeftButton, NULL);
lv_obj_t * settingsTurnOffsetRightButton = lv_btn_create(tabSettings, NULL);
lv_obj_t * settingsTurnOffsetRightButton_text = lv_label_create(settingsTurnOffsetRightButton, NULL);
lv_obj_t * settingsTurnOffsetLabel = lv_label_create(tabSettings, NULL);



std::string getAutonSideName(int as) {
	if (as == SIDE_CAP) {
		return "Cap";
	}
	if (as == SIDE_FLAG) {
		return "Flag";
	}
	return "None";
}

std::string getAutonTeamName(int at) {
	if (at == TEAM_RED) {
		return "Red";
	}
	if (at == TEAM_BLUE) {
		return "Blue";
	}
	return "None";
}


//Called whenever a button is pressed
void updateAutonomousState() {
	lv_label_set_text(autonBackButton_text, "Back");
	lv_obj_set_hidden(autonLeftButton, false);
	lv_obj_set_hidden(autonRightButton, false);
	lv_obj_set_hidden(autonCenterButton, true);
	if (choice == SKILLSORMATCH) {
		lv_obj_set_hidden(autonCenterButton, false);
		lv_label_set_text(autonCenterButton_text, "Test");
		lv_label_set_text(autonLeftButton_text, "Skills");
		lv_label_set_text(autonRightButton_text, "Match");
		lv_label_set_text(autonLabel, "Select");
	} else if (choice == REDORBLUE) {
		lv_label_set_text(autonLeftButton_text, getAutonTeamName(TEAM_BLUE).c_str());
		lv_label_set_text(autonRightButton_text, getAutonTeamName(TEAM_RED).c_str());
	} else if (choice == FLAGORCAP) {
		lv_label_set_text(autonLeftButton_text, getAutonSideName(SIDE_FLAG).c_str());
		lv_label_set_text(autonRightButton_text, getAutonSideName(SIDE_CAP).c_str());
	} else if (choice == DONE_MATCH) {
		lv_label_set_text(autonLeftButton_text, "");
		lv_label_set_text(autonRightButton_text, "");
		lv_label_set_text(autonLabel, std::string(getAutonTeamName(autonTeam) + " " + getAutonSideName(autonSide)).c_str());
		lv_obj_set_hidden(autonLeftButton, true);
		lv_obj_set_hidden(autonRightButton, true);
	} else if (choice == DONE_SKILLS) {
		lv_label_set_text(autonLeftButton_text, "");
		lv_label_set_text(autonRightButton_text, "");
		lv_label_set_text(autonLabel, "Skills");
		lv_obj_set_hidden(autonLeftButton, true);
		lv_obj_set_hidden(autonRightButton, true);
	}
}

//Called whenever a button is pressed
void updateSettingsState() {
	lv_label_set_text(settingsParkSwitchText, "Park");
	lv_label_set_text(settingsTurnOffsetLeftButton_text, "<");
	lv_label_set_text(settingsTurnOffsetRightButton_text, ">");
	lv_label_set_text(settingsTurnOffsetTitle, "Shooting Turn Offset");

	std::stringstream formatter;
	std::string turnOffsetStr;
	formatter.precision(10);
	formatter << autonConfig.turnOffset;
	formatter >> turnOffsetStr;
	lv_label_set_text(settingsTurnOffsetLabel, turnOffsetStr.c_str());
	if (autonConfig.park) {
		lv_sw_on(settingsParkSwitch);
	} else {
		lv_sw_off(settingsParkSwitch);
	}
}


//Called whenever a button is pressed
lv_res_t buttonPressed(lv_obj_t* obj) {
	if (obj == autonLeftButton) {
		if (choice == SKILLSORMATCH) {
			choice = DONE_SKILLS;
			autonType = AUTON_SKILLS;
		} else if (choice == REDORBLUE) {
			choice = FLAGORCAP;
			autonTeam = TEAM_BLUE;
		} else if (choice == FLAGORCAP) {
			choice = DONE_MATCH;
			autonSide = SIDE_FLAG;
		}
	}
	if (obj == autonRightButton) {
		if (choice == SKILLSORMATCH) {
			choice = REDORBLUE;
			autonType = AUTON_MATCH;
		} else if (choice == REDORBLUE) {
			choice = FLAGORCAP;
			autonTeam = TEAM_RED;
		} else if (choice == FLAGORCAP) {
			choice = DONE_MATCH;
			autonSide = SIDE_CAP;
		}
	}
	if (obj == autonCenterButton) {
		if (choice == SKILLSORMATCH) {
			choice = DONE_SKILLS;
			autonType = AUTON_TEST;
		}
	}
	if (obj == autonBackButton) {
		if (choice == REDORBLUE) {
			choice = SKILLSORMATCH;
		} else if (choice == FLAGORCAP) {
			choice = REDORBLUE;
		} else if (choice == DONE_MATCH) {
			choice = FLAGORCAP;
		} else if (choice == DONE_SKILLS) {
			choice = SKILLSORMATCH;
		}
	}
	if (obj == settingsParkSwitch) {
		autonConfig.park = lv_sw_get_state(settingsParkSwitch);
	}
	if (obj == settingsTurnOffsetLeftButton) {
		autonConfig.turnOffset-=0.5;
	}
	if (obj == settingsTurnOffsetRightButton) {
		autonConfig.turnOffset+=0.5;
	}
	updateAutonomousState();
	updateSettingsState();
}

void competition_initialize() {
	int screenWidth = lv_obj_get_width(lv_scr_act());
	int screenHeight = lv_obj_get_height(lv_scr_act());
	lv_obj_set_size(tabview, screenWidth, screenHeight);

	lv_obj_set_size(autonLeftButton, 80, 40);
	lv_obj_set_size(autonRightButton, 80, 40);
	lv_obj_set_size(autonCenterButton, 80, 40);
	lv_obj_set_size(autonBackButton, 80, 40);
	lv_obj_set_size(settingsParkSwitch, 50, 25);
	//settingsParSwitch_text
	//settingsTurnOffsetTitle
	lv_obj_set_size(settingsTurnOffsetLeftButton, 40, 40);
	lv_obj_set_size(settingsTurnOffsetRightButton, 40, 40);
	//settingsTurnnOffsetLabel

	lv_obj_set_pos(autonLeftButton, (screenWidth/4) - (80/2), (screenHeight/2) - (20/2));
	lv_obj_set_pos(autonRightButton, ((screenWidth*3)/4) - (80/2), (screenHeight/2) - (20/2));
	lv_obj_set_pos(autonCenterButton, (screenWidth/2) - (80/2), (screenHeight/2) - (20/2));
	lv_obj_set_pos(autonBackButton, (screenWidth/2)-(80/2), (screenHeight/2)+30);
	lv_obj_set_pos(autonLabel, 0, screenHeight-20);
	lv_obj_set_pos(settingsParkSwitch, (screenWidth/2)-(50/2), 30);
	lv_obj_set_pos(settingsParkSwitchText, screenWidth/2-15, 4);
	lv_obj_set_pos(settingsTurnOffsetTitle, screenWidth/2-60, 70);
	lv_obj_set_pos(settingsTurnOffsetLeftButton, 4, 90);
	lv_obj_set_pos(settingsTurnOffsetRightButton, screenWidth-4-60, 90);
	lv_obj_set_pos(settingsTurnOffsetLabel, screenWidth/2, 90);

	lv_btn_set_action(autonLeftButton, LV_BTN_ACTION_CLICK, buttonPressed);
	lv_btn_set_action(autonRightButton, LV_BTN_ACTION_CLICK, buttonPressed);
	lv_btn_set_action(autonCenterButton, LV_BTN_ACTION_CLICK, buttonPressed);
	lv_btn_set_action(autonBackButton, LV_BTN_ACTION_CLICK, buttonPressed);
	lv_sw_set_action(settingsParkSwitch, buttonPressed);
	lv_btn_set_action(settingsTurnOffsetLeftButton, LV_BTN_ACTION_CLICK, buttonPressed);
	lv_btn_set_action(settingsTurnOffsetRightButton, LV_BTN_ACTION_CLICK, buttonPressed);

	updateAutonomousState();
	updateSettingsState();

	while (true) {
		lv_task_handler();
		pros::delay(10);
	}
}
