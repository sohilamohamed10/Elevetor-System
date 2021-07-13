#ifndef __BUTTON_H__
#define __BUTTON_H__



// typedef enum
// {
//     BUTTON_4DOWN,
//     BUTTON_3UP,
//     BUTTON_3DOWN,
//     BUTTON_2UP,
//     BUTTON_2DOWN,
//     BUTTON_1UP,
//     BUTTON_1DOWN,
//     BUTTON_GUP,
//     BUTTON_OPEN,
//     BUTTON_1,
//     BUTTON_2,
//     BUTTON_3,
//     BUTTON_4,
//     BUTTON_G,
    
    
// }tBUTTON;


// void BUTTON_Init(tBUTTON BUTTON);



void button_init(unsigned char portNumber, unsigned char pinNumber);

unsigned char button_read(unsigned char portNumber, unsigned char pinNumber);



#endif // __BUTTON_H__