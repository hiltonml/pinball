/*
 * Pinball Solenoid-Side Declaration Macros
 *
 * Change the strings in the define statements to
 * something that describes the mechanical device
 * connected to the solenoid, such as "SS_L" for
 * the left slingshot, or "PB_1" for pop bumper 1.
 *
 * If a solenoid is not used on your machine,
 * change the statement to be 
 * #undef SolenoidX
 * where X is the digit of the solenoid.
 */

#define Solenoid1 "RT_S"
#define Solenoid2 "PB_3" 
#define Solenoid3 "LF_S"
#define Solenoid4 "PB_2"
#define Solenoid5 "P_2"
#define Solenoid6 "P_6"  // drop target
#define Solenoid7 "P_7"  // drop target
#undef Solenoid8 //"S8"
