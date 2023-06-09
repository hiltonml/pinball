/*
 * Define the switches and solenoids used by this pinball machine.
 *
 * Change the strings in the define statements to
 * something that describes the switch or mechanical device
 * connected to the solenoid, such as "SS_L" for
 * the left slingshot, or "PB_1" for pop bumper 1.
 *
 * By default, switches award 5 points each.  To change 
 * the points that should be awarded for a switch,
 * add a line with the statement
 * #define ScoreX points
 * where X is the number of the switch.  For example,
 * #define Score1 25
 * will award 25 points each time switch 1 is closed.
 *
 * By default, solenoids award 5 points each. To change
 * the points that should be awarded for a solenoid,
 * add a line with the statement
 * #define SolenoidScoreX points
 * where X is the number of the solenoid.  For example,
 * #define SolenoidScore1 10
 * will award 10 points each time solenoid 1 is activated.
 *
 * If a switch is not used on your machine,
 * change the statement to be 
 * #undef SwitchX
 * where X is the number of the switch.

 * If a solenoid is not used on your machine,
 * change the statement to be 
 * #undef SolenoidX
 * where X is the digit of the solenoid.
 */
  
#define Switch1 "R_1"
#define Switch2 "R_2"
#define Switch3 "R_3"
#define Switch4 "R_4"
#define Switch5 "R_8"
#define Switch6 "R_7"
#define Switch7 "R_6"
#define Switch8 "R_5"
#define Switch9 "T_2"
#define Switch10 "T_1"
#define Switch11 "Spinner"
#undef Switch12 //"R_8"


#define Solenoid1 "RT_S"
#define Solenoid2 "PB_3"
#define Solenoid3 "LF_S"
#define Solenoid4 "PB_1"
#define Solenoid5 "PB_2"
#define Solenoid6 "PB_6"
#define Solenoid7 "PB_7"
#undef Solenoid8 //"X8"


 
