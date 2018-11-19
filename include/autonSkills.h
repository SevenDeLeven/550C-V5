go(-2.0);           //Flip flag
go(1.0);            //  --
turnDegrees(16);    //Shoot mid flag close
launcher = 127;     //  --
pros::delay(1000);  //  --
launcher = 0;       //  --
turnDegrees(-16);   //  --
go(1.0);            //Flip close flagside cap
turnDegrees(90);    //  --
goTime(0.5, 127);   //[Checkpoint] - Close flagside cap
go(-1.0);           //  --
turnDegrees(-90);   //  --
intake = -127;      //  --
go(-1.5);           //  --
intake = 0;         //  --
go(1.5);            //  --
turnDegrees(90);    //Get Close flagside parking cap ball
intake = 127;       //  --
go(-1.2);           //  --
go(0.2);            //  --
turnDegrees(-90);   //Middle flag
goTime(0.5, 40);    //[Checkpoint] - Middle bottom flag
