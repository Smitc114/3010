/**
 ******************************************************************************
 * @file    mylib/s4353096_pantilt.h
 * @author  Steffen Mitchell - 43530960
 * @date    16032016
 * @brief   Servo Pan and Tilt peripheral driver
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************
 * s4353096_pantilt_init() - Initialise servo (GPIO, PWM, Timer, etc)
 * s4353096_pantilt_angle(type, angle) - Write the pan or tilt servo to an angle
 * s4353096_terminal_angle_check () - Checks  angle setting values and adjusts
 * their values accordingly.
 ******************************************************************************
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

struct PanTilt {
	int write_angles;
	int read_angles;
  int set_angle_pan;
  int set_angle_tilt;
	int laser_state;
};
/* Task Priorities ------------------------------------------------------------*/
#define mainTASKPANTILT_PRIORITY					( tskIDLE_PRIORITY + 2 )
/* Task Stack Allocations -----------------------------------------------------*/
#define mainTASKPANTILT_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )

QueueHandle_t s4353096_QueuePan;
QueueHandle_t s4353096_QueueTilt;
SemaphoreHandle_t s4353096_SemaphoreLaser;		//Used to control laser
SemaphoreHandle_t s4353096_SemaphorePanLeft;	//Used to pan left 5degrees
SemaphoreHandle_t s4353096_SemaphorePanRight;	//Used to pan right 5degrees
SemaphoreHandle_t s4353096_SemaphoreTiltUp;		//Used to tilt up 5degrees
SemaphoreHandle_t s4353096_SemaphoreTiltDown;	//Used to tilt down 5degrees
 #define PWM_PAN_TIM TIM4
 #define PWM_PAN_PIN BRD_D6_PIN
 #define PWM_PAN_GPIO_PORT BRD_D6_GPIO_PORT
 #define __PWM_PAN_GPIO_CLK() __BRD_D6_GPIO_CLK()
 #define __PWM_PAN_TIMER_CLK() __TIM4_CLK_ENABLE()
 #define PWM_PAN_GPIO_AF_TIM GPIO_AF2_TIM4
 #define PWM_PAN_TIM_CHANNEL TIM_CHANNEL_4

 #define PWM_TILT_TIM TIM4
 #define PWM_TILT_PIN BRD_D5_PIN
 #define PWM_TILT_GPIO_PORT BRD_D5_GPIO_PORT
 #define __PWM_TILT_GPIO_CLK() __BRD_D5_GPIO_CLK()
 #define __PWM_TILT_TIMER_CLK() __TIM4_CLK_ENABLE()
 #define PWM_TILT_GPIO_AF_TIM GPIO_AF2_TIM4
 #define PWM_TILT_TIM_CHANNEL TIM_CHANNEL_3

 #define PANTILT_IR_TIM TIM2
 #define __PANTILT_IR_TIMER_CLK() __TIM2_CLK_ENABLE()
 #define PANTILT_TIM_IRQn TIM2_IRQn

 #define LASER_PIN BRD_D0_PIN
 #define LASER_GPIO_PORT BRD_D0_GPIO_PORT
 #define __LASER_GPIO_CLK() __BRD_D0_GPIO_CLK()
 
 extern void s4353096_pantilt_init(void);
 extern void s4353096_pantilt_angle_write(int type, int angle);
extern void s4353096_terminal_angle_check (void);
extern void s4353096_TaskPanTilt(void);
