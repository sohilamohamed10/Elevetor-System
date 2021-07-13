#include "Main.h"
#include "Port.h"
#include "Led.h"
#include "buttons.h"
#include "seven_seg.h"
#include "Servo.h"
#include "ir.h"
#include <stdio.h>

#define PWM_Period 0xB7FE
sbit Servo_Motor_Pin = P3^4;
float cycle[5] ={2.7 , 6.4 , 7.5 , 8.6 , 9.7} ;
unsigned int ON_Period, OFF_Period, DutyCycle;
unsigned int counter=0;
unsigned char floors[5]={ 0,0,0,0,0};
unsigned char up[5]={ 0,0,0,0,0};
unsigned char down[5]={ 0,0,0,0,0};
unsigned char up_sum = 0;
unsigned char down_sum = 0;
unsigned char selectedFloor = 0;
unsigned char currentFloor = 0;
unsigned char elevatorDirection = 1; // 0= down , 1= up
unsigned char moving = 0 ;
unsigned char check_door = 0; // 0= door closed , 1= door opened
void bringElevator();
void elevatorUp();
void elevatorDown();
void getDirection();
void setDirection(unsigned char x);
void moveElevator();
void pullDown(unsigned char requestFloor);
void pullUp(unsigned char requestFloor);
void checkOuterButtons();
unsigned char final_floor_up();
unsigned char final_floor_down();
void open_door();
void Set_DutyCycle_To(float duty_cycle);

// void Delay_MS(unsigned int ms)
// {
//     unsigned int i;
//     unsigned int j;
//     for (i = 0; i < ms; i++)
//     {
//         for (j = 0; j < 120; j++)
//         {
//         }
//     }
// }
void Timer_init()
{
    TMOD = 0x11;
    TH0 = (PWM_Period >> 8);/* 20ms timer value */
	TL0 = PWM_Period;
    TR0 = 1;
    TL1 = 0x00;
    TH1 = 0x00;
    TR1 = 1;
}
// (void) interrupt 1
// void Check_buttons(void) interrupt 3

// {
//     // LED_Toggle(LED_1);
//     // LED_Toggle(LED_2);
//     // Delay_MS(400);
//     // LED_Toggle(LED_1);
//     // LED_Toggle(LED_2);
//     // TR0 = 0;

//         unsigned char i = 0; 

//         if (!button_read(BUTTON_G_PORT_DR, BUTTON_G_PIN))
//         {   
//             floors[0] = 1;
//             selectedFloor = 0;
//             getDirection();
//         }
//         if (!button_read(BUTTON_1_PORT_DR, BUTTON_1_PIN))
//         {
//             floors[1] = 1;
//             selectedFloor = 1;
//             getDirection();
//         }
//         if (!button_read(BUTTON_2_PORT_DR, BUTTON_2_PIN))
//         {
//             floors[2] = 1;
//             selectedFloor = 2;
//             getDirection();
//         }
//         if (!button_read(BUTTON_3_PORT_DR, BUTTON_3_PIN))
//         {   
//             floors[3] = 1;
//             selectedFloor = 3;
//             getDirection();
//         }
//         if (!button_read(BUTTON_4_PORT_DR, BUTTON_4_PIN))
//         {   
//             floors[4] = 1;
//             selectedFloor = 4;
//             getDirection();
//         }

//         if (!button_read(BUTTON_GUP_PORT_DR, BUTTON_GUP_PIN)) //G up
//         {
//             down[0] = 1;
//             selectedFloor = 0;
//             setDirection(0);
//         }

//         if (!button_read(BUTTON_1UP_PORT_DR, BUTTON_1UP_PIN)) // 1up
//         {

//             up[1] = 1;
//             selectedFloor = 1;
//             setDirection(1);
//         }
//         if (!button_read(BUTTON_2UP_PORT_DR, BUTTON_2UP_PIN)) // 2up
//         {

//             up[2] = 1;
//             selectedFloor = 2;
//             setDirection(1);
//         }
//         if (!button_read(BUTTON_3UP_PORT_DR, BUTTON_3UP_PIN)) // 3up
//         {

//             up[3] = 1;
//             selectedFloor = 3;
//             setDirection(1);
//         }

//         if (!button_read(BUTTON_1DOWN_PORT_DR, BUTTON_1DOWN_PIN)) // 1down
//         {

//             down[1] = 1;
//             selectedFloor = 1;
//             setDirection(0);
//         }

//         if (!button_read(BUTTON_2DOWN_PORT_DR, BUTTON_2DOWN_PIN)) // 2down
//         {
//             down[2] = 1;
//             selectedFloor = 2;
//             setDirection(0);
//         }

//         if (!button_read(BUTTON_3DOWN_PORT_DR, BUTTON_3DOWN_PIN)) // 3down
//         {
//             down[3] = 1;
//             selectedFloor = 3;
//             setDirection(0);
//         }

//         if (!button_read(BUTTON_4DOWN_PORT_DR, BUTTON_4DOWN_PIN)) // 4down
//         {
//             up[4] = 1;
//             selectedFloor = 4;
//             setDirection(1);
//         }
// up_sum = 0;
// down_sum =0;
// for (i ; i <= 4; i++)
//     {
//         up_sum = up_sum + up[i];
//         down_sum = down_sum + down[i];
//     }        
// }

void Timer0_ISR(void) interrupt 1	
{
	Servo_Motor_Pin = !Servo_Motor_Pin;
	if(Servo_Motor_Pin)
	{
		TH0 = (ON_Period >> 8);
		TL0 = ON_Period;
	}	
	else
	{
		TH0 = (OFF_Period >> 8);
		TL0 = OFF_Period;
	}	
			
}

// void wait_door(void) interrupt 0
// {

// if(check_door)
//     Delay_MS(2000);
// }

void main()
{

    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock
    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x14; // enable interrupt crossbar
    XBR2 = 0x40;  // Cross bar enabled , weak Pull-up enabled

    EA = 1;  //enable global interrupt
    EX0 = 1; // enable external interrupt 0
    EX1 = 1; //enable external interrupt 1
    IT0 = 1;
    IT1 = 1;

    ET0 = 1; //enable interrupt of timer0
    ET1 = 1; //enable interrupt of timer1
    Buzzer_init();
    IR_init();
    Timer_init();
    sevenSegment_write(0);
    //ET1 = 1; //enable interrupt of timer1

    // TL1 = 0xfb;
    // TH1 = 0xff;
    SERVO_Init();
    // LED_Init(LED_1, LED_OFF);
    // LED_Init(LED_2, LED_ON);
    // BUTTON_Init(BUTTON_OPEN);

    // Initialization of outside buttons
    button_init(BUTTON_4DOWN_PORT_CR, BUTTON_4DOWN_PIN);
    button_init(BUTTON_3DOWN_PORT_CR, BUTTON_3DOWN_PIN);
    button_init(BUTTON_3UP_PORT_CR, BUTTON_3UP_PIN);
    button_init(BUTTON_2DOWN_PORT_CR, BUTTON_2DOWN_PIN);
    button_init(BUTTON_2UP_PORT_CR, BUTTON_2UP_PIN);
    button_init(BUTTON_1DOWN_PORT_CR, BUTTON_1DOWN_PIN);
    button_init(BUTTON_1UP_PORT_CR, BUTTON_1UP_PIN);
    button_init(BUTTON_GUP_PORT_CR, BUTTON_GUP_PIN);

    // initialization of inside buttons
    button_init(BUTTON_4_PORT_CR, BUTTON_4_PIN);
    button_init(BUTTON_3_PORT_CR, BUTTON_3_PIN);
    button_init(BUTTON_2_PORT_CR, BUTTON_2_PIN);
    button_init(BUTTON_1_PORT_CR, BUTTON_1_PIN);
    button_init(BUTTON_G_PORT_CR, BUTTON_G_PIN);

    // initialization of seven segment
    sevenSegment_init(sevenSeg_PORT_CR);

    while (1)
    { // assume the door is open.
     if (GPIO_ReadPortPin(GPIO_PORT2_DATA,GPIO_PIN_6)==1)
     {
          counter=counter+1;
     }
     if (GPIO_ReadPortPin(GPIO_PORT2_DATA,GPIO_PIN_7)==1 && counter!=0)
     {
         counter=counter-1;
     }
     if(counter>4)
     {
          Buzzer_toggle();
     }
       // moveElevator();
        // bringElevator();
        // Check_buttons();
    }
}


// void moveElevator()
// {

//     // elevatorDirection = getDirection(); // return 1 OR 0
//     if(selectedFloor != currentFloor)
//     {

//     if (elevatorDirection == 1)
//         elevatorUp();

//     else
//         elevatorDown();
//     }
// }

// void getDirection()
// {
// if(selectedFloor != currentFloor)
//         {
//             if(selectedFloor > currentFloor)
//             {
//                 up[selectedFloor] = 1;
//                 elevatorDirection = 1;

//             }
//             else 
//             {
//                 down[selectedFloor] = 1;
//                 elevatorDirection = 0;
//             }
//         }

// }
// void setDirection(unsigned char x)
// {
//     if(moving == 0)
//         elevatorDirection = x;

// }

// void elevatorUp()
// {
//     int floor = final_floor_up();
//     int i = currentFloor;
//     for (i ; i <= floor && (i != 5); i++)
//     {
//         // cycle = cycle + 2;
//         // elevator up using dc motor
//         moving = 1;
//         sevenSegment_write(i); //print current floor on 7Seg
//         Set_DutyCycle_To(cycle[i]);
//         currentFloor = i;
//         Delay_MS(250);
//         // bringElevator();
//         if (up[i] == 1)
//         {   
//             up[i] = 0;
//             open_door();
//         }
            
//     }
//     moving = 0;
//     if(down_sum != 0)
//         elevatorDown();

//     //open door( check if current floor = selected floor );
// }

// void elevatorDown()
// {
    
//     int floor = final_floor_down();
//     int i = currentFloor;
//     for (i; i >= floor; i--)
//     {
//         moving = 1;
//         // cycle = cycle - 2;
//         // elevator down using dc motor
//         sevenSegment_write(i); //print current floor on 7Seg
//         Set_DutyCycle_To(cycle[i]);
//         currentFloor = i;
//         Delay_MS(250);
//         if (down[i] == 1)
//         {
//             down[i] = 0;
//             open_door();
//         }
//         // bringElevator();

//     }
//     moving = 0;
//     if(up_sum != 0)
//         elevatorUp();
//     //open door( check if movingFlag = 0 );
// }

// u

// void Set_DutyCycle_To(float duty_cycle)
// {
// 	float period = 65535 - PWM_Period;
// 	ON_Period = ((period/100.0) * duty_cycle);
// 	OFF_Period = (period - ON_Period);	
// 	ON_Period = 65535 - ON_Period;	
// 	OFF_Period = 65535 - OFF_Period;

// }