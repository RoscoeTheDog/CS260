#include <stdio.h>
#include <math.h>

#define STEP_PULSE(steps, microsteps, rpm) (60.0*1000000L/steps/microsteps/rpm)
#define HIGH 1
#define LOW 0
#define DEFAULT_ACCELERATION 1000
#define DEFAULT_DECELERATION 1000
#define MIN_YIELD_MICROS 50


typedef enum StepperDriverMode_t{
	CONSTANT_SPEED,
	LINEAR_SPEED,
} StepperDriverMode_t;


typedef enum StepperMotorState_t{
	STOPPED,
	ACCELERATING,
	CRUISING,
	DECELERATING,
} StepperMotorState_t;

typedef enum {
    GPIO_NUM_NC = -1,    /*!< Use to signal not connected to S/W */
    GPIO_NUM_0 = 0,     /*!< GPIO0, input and output */
    GPIO_NUM_1 = 1,     /*!< GPIO1, input and output */
    GPIO_NUM_2 = 2,     /*!< GPIO2, input and output */
    GPIO_NUM_3 = 3,     /*!< GPIO3, input and output */
    GPIO_NUM_4 = 4,     /*!< GPIO4, input and output */
    GPIO_NUM_5 = 5,     /*!< GPIO5, input and output */
    GPIO_NUM_6 = 6,     /*!< GPIO6, input and output */
    GPIO_NUM_7 = 7,     /*!< GPIO7, input and output */
    GPIO_NUM_8 = 8,     /*!< GPIO8, input and output */
    GPIO_NUM_9 = 9,     /*!< GPIO9, input and output */
    GPIO_NUM_10 = 10,   /*!< GPIO10, input and output */
    GPIO_NUM_11 = 11,   /*!< GPIO11, input and output */
    GPIO_NUM_12 = 12,   /*!< GPIO12, input and output */
    GPIO_NUM_13 = 13,   /*!< GPIO13, input and output */
    GPIO_NUM_14 = 14,   /*!< GPIO14, input and output */
    GPIO_NUM_15 = 15,   /*!< GPIO15, input and output */
    GPIO_NUM_16 = 16,   /*!< GPIO16, input and output */
    GPIO_NUM_17 = 17,   /*!< GPIO17, input and output */
    GPIO_NUM_18 = 18,   /*!< GPIO18, input and output */
    GPIO_NUM_19 = 19,   /*!< GPIO19, input and output */
    GPIO_NUM_20 = 20,   /*!< GPIO20, input and output */
    GPIO_NUM_21 = 21,   /*!< GPIO21, input and output */

    GPIO_NUM_22 = 22,   /*!< GPIO22, input and output */
    GPIO_NUM_23 = 23,   /*!< GPIO23, input and output */

    GPIO_NUM_25 = 25,   /*!< GPIO25, input and output */

    /* Note: The missing IO is because it is used inside the chip. */
    GPIO_NUM_26 = 26,   /*!< GPIO26, input and output */
    GPIO_NUM_27 = 27,   /*!< GPIO27, input and output */
    GPIO_NUM_28 = 28,   /*!< GPIO28, input and output */
    GPIO_NUM_29 = 29,   /*!< GPIO29, input and output */
    GPIO_NUM_30 = 30,   /*!< GPIO30, input and output */
    GPIO_NUM_31 = 31,   /*!< GPIO31, input and output */
    GPIO_NUM_32 = 32,   /*!< GPIO32, input and output */
    GPIO_NUM_33 = 33,   /*!< GPIO33, input and output */
    GPIO_NUM_34 = 34,   /*!< GPIO34, input mode only(ESP32) / input and output(ESP32-S2) */
    GPIO_NUM_35 = 35,   /*!< GPIO35, input mode only(ESP32) / input and output(ESP32-S2) */
    GPIO_NUM_36 = 36,   /*!< GPIO36, input mode only(ESP32) / input and output(ESP32-S2) */
    GPIO_NUM_37 = 37,   /*!< GPIO37, input mode only(ESP32) / input and output(ESP32-S2) */
    GPIO_NUM_38 = 38,   /*!< GPIO38, input mode only(ESP32) / input and output(ESP32-S2) */
    GPIO_NUM_39 = 39,   /*!< GPIO39, input mode only(ESP32) / input and output(ESP32-S2) */

    GPIO_NUM_40 = 40,   /*!< GPIO40, input and output */
    GPIO_NUM_41 = 41,   /*!< GPIO41, input and output */
    GPIO_NUM_42 = 42,   /*!< GPIO42, input and output */
    GPIO_NUM_43 = 43,   /*!< GPIO43, input and output */
    GPIO_NUM_44 = 44,   /*!< GPIO44, input and output */
    GPIO_NUM_45 = 45,   /*!< GPIO45, input and output */
    GPIO_NUM_46 = 46,   /*!< GPIO46, input mode only */

    GPIO_NUM_MAX,
/** @endcond */
} gpio_num_t;

typedef struct StepperConfig_t {
    gpio_num_t direction_pin;
    gpio_num_t step_pin;
    gpio_num_t enable_pin;
	int motor_steps;
    int enable_active_state;
    int microstepping;
    float rpm;
    StepperDriverMode_t mode;
} StepperConfig_t;


typedef struct StepperHandler_t {
    StepperConfig_t *configuration;
	StepperMotorState_t motor_state;
    short direction_state; // dir pin state.
    long rest;
    long last_action_end;
    long next_action_interval;
    long step_count;
    long steps_remaining;
    long steps_to_cruise;
    long steps_to_brake;
    long step_pulse;
    long cruise_step_pulse;
	int step_high_min;
	int step_low_min;
	int wakeup_time;
} StepperHandler_t;


/*
 * Set up a new move (calculate and save the parameters)
 */
inline void startMove(StepperHandler_t *stepper_handler, long steps, long time){
	// float speed;
    // set up new move
    // stepper_handler->direction_state = (steps >= 0) ? HIGH : LOW;
    // stepper_handler->last_action_end = 0;
    // stepper_handler->steps_remaining = labs(steps);
    // stepper_handler->step_count = 0;
    // stepper_handler->rest = 0;
	int i = stepper_handler->configuration->step_pin;
	printf("%i\n", stepper_handler->configuration->step_pin);
	printf("%i\n", stepper_handler->configuration->step_pin);
    // switch ((int)stepper_handler->configuration->mode){

		// case LINEAR_SPEED:
		// 	// speed is in [steps/s]
		// 	speed = stepper_handler->configuration->rpm * stepper_handler->configuration->motor_steps / 60;
		// 	if (time > 0){
		// 		// Calculate a new speed to finish in the time requested
		// 		float t = time / (1e+6);                  // convert to seconds
		// 		float d = stepper_handler->steps_remaining / stepper_handler->configuration->microstepping;   // convert to full steps
		// 		float a2 = 1.0 / DEFAULT_ACCELERATION + 1.0 / DEFAULT_DECELERATION;
		// 		float sqrt_candidate = t*t - 2 * a2 * d;  // in √b^2-4ac
		// 		if (sqrt_candidate >= 0){
		// 			speed = fmin(speed, (t - (float)sqrt(sqrt_candidate)) / a2);
		// 		};
		// 	}
		// 	// how many microsteps from 0 to target speed
		// 	stepper_handler->steps_to_cruise = stepper_handler->configuration->microstepping * (speed * speed / (2 * DEFAULT_ACCELERATION));
		// 	// how many microsteps are needed from cruise speed to a full stop
		// 	stepper_handler->steps_to_brake = stepper_handler->steps_to_cruise * DEFAULT_ACCELERATION / DEFAULT_DECELERATION;
		// 	if (stepper_handler->steps_remaining < stepper_handler->steps_to_cruise + stepper_handler->steps_to_brake){
		// 		// cannot reach max speed, will need to brake early
		// 		stepper_handler->steps_to_cruise = stepper_handler->steps_remaining * DEFAULT_DECELERATION / (DEFAULT_ACCELERATION + DEFAULT_DECELERATION);
		// 		stepper_handler->steps_to_brake = stepper_handler->steps_remaining - stepper_handler->steps_to_cruise;
		// 	}
		// 	// Initial pulse (c0) including error correction factor 0.676 [us]
		// 	stepper_handler->step_pulse = (1e+6)*0.676*sqrt(2.0f/DEFAULT_ACCELERATION/stepper_handler->configuration->microstepping);
		// 	// Save cruise timing since we will no longer have the calculated target speed later
		// 	stepper_handler->cruise_step_pulse = 1e+6 / speed / stepper_handler->configuration->microstepping;
		// 	break;

		// case CONSTANT_SPEED:
		// default:
		// 	stepper_handler->steps_to_cruise = 0;
		// 	stepper_handler->steps_to_brake = 0;
		// 	stepper_handler->step_pulse = stepper_handler->cruise_step_pulse = getStepPulse(stepper_handler->configuration->motor_steps, stepper_handler->configuration->microstepping, stepper_handler->configuration->rpm);

		// 	if (time > stepper_handler->steps_remaining * stepper_handler->step_pulse){
		// 		stepper_handler->step_pulse = (float)time / stepper_handler->steps_remaining;
		// 	}

		// }
		// printf("%p\n", &stepper_handler->configuration->step_pin);
}

/*
 * Move the motor a given number of steps.
 * positive to move forward, negative to reverse
 */
inline void move(StepperHandler_t *stepper_handler, long steps){
    startMove(stepper_handler, steps, 0);
    while (nextAction(stepper_handler));
}


inline long calcStepsForRotation(StepperHandler_t *stepper_handler, double deg){
	return deg * stepper_handler->configuration->motor_steps * stepper_handler->configuration->microstepping / 360;
}

/*
 * Move the motor with sub-degree precision.
 * Note that using this function even once will add 1K to your program size
 * due to inclusion of float support.
 */
inline void rotate(StepperHandler_t *stepper_handler, double deg){
    move(stepper_handler, calcStepsForRotation(stepper_handler, deg));
}


int main() {

	printf("Hello, World!\n");
	return 0;
}
