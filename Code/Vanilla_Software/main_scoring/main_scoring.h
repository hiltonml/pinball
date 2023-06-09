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

#define Switch1 "S1"
#define Switch2 "S2"
#define Switch3 "S3"
#define Switch4 "S4"
#define Switch5 "S5"
#define Switch6 "S6"
#define Switch7 "S7"
#define Switch8 "S8"
#define Switch9 "S9"
#define Switch10 "S10"
#define Switch11 "S11"
#define Switch12 "S12"


#define Solenoid1 "X1"
#define Solenoid2 "X2"
#define Solenoid3 "X3"
#define Solenoid4 "X4"
#define Solenoid5 "X5"
#define Solenoid6 "X6"
#define Solenoid7 "X7"
#define Solenoid8 "X8"


 
