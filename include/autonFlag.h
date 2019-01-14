// setSecondsPerTile(3.0);
//flyWheel.move(127);	                	//Start shooter
// go(-2.2);				           	//Toggle flag
// go(1.2);				           	//	--
// turnDegrees(-8*direction);	//	--
// intake.move(-127);		            //Shoot Ball
// pros::delay(1000);			         	//	--
// intake.move(0);			             	//	--
// //flyWheel.move(0);		              //	--
// turnDegrees(-82*direction);	//Turn toward cap
// intake.move(127);   		         	//Flip Cap
// go(-1.4);				           	//	--
// intake.move(0);				            //	--
// go(-0.20);					        //Push cap out of the way
// go(0.60);				           	//	--
// turnDegrees(-90*direction);	//	--
// go(-1.0);					          //	--
// turnDegrees(90*direction);	//	--
// intake.move(-127);			          //	--
// go(-0.9);					          //Score cap
// go(0.4);					          //	--
// turnDegrees(90*direction);	//	--
// go(-0.2);					          //Park
// go(1.5);					          //	--

tilter = -100;
turnDegrees(-15*direction);
pros::delay(500);
punch();
calibrateTilter();
tiltMid();
turnDegrees(15*direction);
go(-1.9);
go(1.0);
turnDegrees(-90*direction);
goTime(0.5,127);
intake = 127;
go(-1.1);
intake = 0;
go(-0.5);
go(0.25);
turnDegrees(90*direction);
go(1.0);
turnDegrees(-90*direction);
intake = -127;
go(-0.5);
go(0.5);
turnDegrees(90*direction);
go(1.2);
intake = 0;
