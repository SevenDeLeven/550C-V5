setFlipTurning(true);

intake = -127;
tilter = -70;
go(1.9);
calibrateTilter();
tiltTop();
go(-1.9);
goTime(0.5, -127);
go(0.2);
turnDegrees(89);
go(0.25);
punchThen(TILTER_MID_CLOSE); //Position is actually next position after shooting
pros::delay(100);
punchThen(TILTER_TOP_CLOSE);
go(0.4);
turnDegrees(11);
go(1.3);
go(-1.55);
turnDegrees(-61);
intake = 127;
sdl::Event evt_arr[] = {sdl::Event(stopIntake, sdl::callback_point::DISTANCED, 1), sdl::Event(punchThenMid, sdl::callback_point::DISTANCED, 0.7)};
go(1.3,60,evt_arr,2);
go(-0.5);
punchThen(TILTER_TOP_CLOSE);
intake = 0;

// turnDegrees(-44);
// sdl::Event evt_arr[] = {sdl::Event(changeTargetDistance, sdl::callback_point::DISTANCED, 0.64)};
// go(0.7, 100, evt_arr, 2);
// pros::delay(1500);
// intake = 60;
// go(1.0);
// go(-0.4);
// intake = -127;
// turnDegrees(-3, 60);
// punchThen(TILTER_TOP_CLOSE); //Position is actually next position after shooting
// pros::delay(100);
// punchThen(TILTER_MID_CLOSE);
