// setSecondsPerTile(3.0);
// setrobotWheelDistance(15.0/24.0);
// intake = 127;
// go(1.0);
// intake = -127;
// go(-1.0);



// flyWheel = 127;		          //Start Shooter
// go(-2.1);					    //Toggle flag
// go(1.1);					    //Prepare to shoot
// turnDegrees(9);       //  --
// intake = -127;	           	//Shoot
// pros::delay(1000);			   	//  --
// intake = 0;			          	//  --
// flyWheel = 0;	            	//  --
// turnDegrees(-9);			//	--
// go(1.0);				    	//	--
// turnDegrees(90);			//Start towards first cap
// go(-1.0);					    //	--
// turnDegrees(-90);			//	--
// intake = 127;			          //Flip Cap
// go(-1.5);					    //	--
// intake = 0;				          //	--
// go(1.5);					    //	--
// turnDegrees(90);			//	--
// go(1.0);					    //	--
// goTime(0.5, 127);			//[Checkpoint] - Second Cap
// intake = -127;		          //Intake ball
// go(-2.2);				     	//	--
// flyWheel = 127;		          //	--
// turnDegrees(-90);			//Flip flag
// goTime(0.5, 127);			//[Checkpoint] - Middle flag
// go(2.2);					    //	--
// go(-1.0);				     	//Shoot
// turnDegrees(9);		 		//	--
// pros::delay(1000);		  	 	//	--
// intake = 0;			 	          //Turn off shooter
// flyWheel = 0;	            	//	--
// turnDegrees(81);			//Turn toward next cap



/*
motor[flyWheel] = 127;		//Start Shooter
go(-2.1);					//Toggle flag
go(1.1);					//Prepare to shoot
turnDegrees(9);
intakeSpeed(-127;			//Shoot
delay(1000);				//  --
intakeSpeed(0);				//  --
motor[flyWheel] = 0;		//  --
turnDegrees(-9);			//	--
go(1.0);					//	--
turnDegrees(90);			//Start towards first cap
go(-1.0);					//	--
turnDegrees(-90);			//	--
intakeSpeed(127;			//Flip Cap
go(-1.5);					//	--
intakeSpeed(0);				//	--
go(0.5);					//	--
turnDegrees(-90);			//Go to next cap
go(-1.0);					//	--
goTime(0.5, -1);			//[Checkpoint] - Second Cap I
go(0.2);					//	--
turnDegrees(90);			//	--
go(1.05);					//	--
turnDegrees(90);			//	--
goTime(0.5, 1);				//[Checkpoint] - Second Cap II
intakeSpeed(127;			//	--
go(-2.4);					//	--
intakeSpeed(0);				//	--
go(0.1);					//	--
turnDegrees(-90);			//Turn toward next flag and turn it
goTime(0.5, 1);				//[Checkpoint] - Middle Flag I
go(-2.3);					//Turn flag
goTime(0.5, -1);			//[Checkpoint] - Middle flag II
go(1.2);					//Align with next cap
turnDegrees(90);			//Head toward next cap
intakeSpeed(127;			//	--
go(-2.5);					//	--
intakeSpeed(0);				//	--
go(0.4);					//	--
turnDegrees(-90);			//Turn towards next flag
go(-1);						//Flip Flag
goTime(0.5, -1);			//[Checkpoint] - Far side flag
go(2.5);					//Head for next cap
turnDegrees(-90);			//	--
go(1);						//	--
goTime(0.5, 1);				//	--
go(-0.2);					//	--
turnDegrees(90);			//	--
go(1.9);					//	--
turnDegrees(-90);			//	--
goTime(0.7, 1);				//[Checkpoint] - Far side cap
intakeSpeed(127;			//Flip cap
go(-2.3);					//	--
intakeSpeed(0);				//	--
go(2.3);					//Begin Parking
goTime(0.5, 1);				//[Checkpoint] - Parking I
turnDegrees(-90);			//	--
go(0.85);					//	--
turnDegrees(-90);			//	--
goTime(0.5, -1);			//Park [Checkpoint] - Parking II
go(4.7);					//	--
*/
