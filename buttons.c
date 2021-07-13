#include "Main.h"
#include "Port.h"
#include "buttons.h"

// void Button_Init(tBUTTON BUTTON)
// {
//     /* Add your code here! */
//     /* Configure led pins as output */
//     switch (BUTTON)
//     {
//         case BUTTON_4DOWN:
//             GPIO_InitPortPin(BUTTON_4DOWN_PORT_CR, BUTTON_4DOWN_PIN, GPIO_IN);
//             break;
//         case BUTTON_3UP:
//             GPIO_InitPortPin(BUTTON_3UP_PORT_CR, BUTTON_3UP_PIN, GPIO_IN);
//             break;
//         case BUTTON_3DOWN:
//             GPIO_InitPortPin(BUTTON_3DOWN_PORT_CR, BUTTON_3DOWN_PIN, GPIO_IN);
//             break;
//         case BUTTON_2UP:
//             GPIO_InitPortPin(BUTTON_2UP_PORT_CR, BUTTON_2UP_PIN, GPIO_IN);
//             break;
//         case BUTTON_2DOWN:
//             GPIO_InitPortPin(BUTTON_2DOWN_PORT_CR, BUTTON_2DOWN_PIN, GPIO_IN);
//             break;
//         case BUTTON_1UP:
//             GPIO_InitPortPin(BUTTON_1UP_PORT_CR, BUTTON_1UP_PIN, GPIO_IN);
//             break;
//         case BUTTON_1DOWN:
//             GPIO_InitPortPin(BUTTON_1DOWN_PORT_CR, BUTTON_1DOWN_PIN, GPIO_IN);
//             break;
//         case BUTTON_GUP:
//             GPIO_InitPortPin(BUTTON_GUP_PORT_CR, BUTTON_GUP_PIN, GPIO_IN);
// 			break;

//         case BUTTON_OPEN:
//             GPIO_InitPortPin(OPEN_PORT_CR, OPEN_PIN, GPIO_IN);
//             break;

//         case BUTTON_4:
//             GPIO_InitPortPin(BUTTON_4_PORT_CR, BUTTON_4_PIN, GPIO_IN);
//             break;
//         case BUTTON_3:
//             GPIO_InitPortPin(BUTTON_3_PORT_CR, BUTTON_3_PIN, GPIO_IN);
//             break;
//         case BUTTON_2:
//             GPIO_InitPortPin(BUTTON_2_PORT_CR, BUTTON_2_PIN, GPIO_IN);
//             break;
//         case BUTTON_1:
//             GPIO_InitPortPin(BUTTON_1_PORT_CR, BUTTON_1_PIN, GPIO_IN);
//             break;
//         case BUTTON_G:
//             GPIO_InitPortPin(BUTTON_G_PORT_CR, BUTTON_G_PIN, GPIO_IN);
//             break;
//         default:
//             /* Should not come here */
//             break;
//     }
// 	}

void button_init(unsigned char portNumber, unsigned char pinNumber)
{
    GPIO_InitPortPin(portNumber, pinNumber, 0);
}

unsigned char button_read(unsigned char portNumber, unsigned char pinNumber)
{
    unsigned char x;
    x = GPIO_ReadPortPin(portNumber, pinNumber);
    return x;
}
