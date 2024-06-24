#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "IRremote.h"

#define IR_SENSOR PB0
#define W_1 PD3
#define W_2 PD5
#define W_3 PD6
#define W_4 PB3
#define R   PD2
#define G   PD4
#define B   PD7

#define V_U 6
#define V_D 5
#define C_D 4
#define NUM_WHITE 4
#define NUM_RGB 3

uint8_t current_bulb_index = 0;
uint8_t W_Brightness[4] = {255, 255, 255, 255};
int To_Be_reduced[4] = {0, 0, 0, 0};
bool RGB_Toggling = false;
int RGB_Toggle_Counter = 1;
int decrement = 30;
uint8_t RGB_Cycles = 0;
uint8_t RGB_remainder = 0;
uint8_t RGB_count = 0;

void init_bulbs() {
    DDRD |= _BV(W_1) | _BV(W_2) | _BV(W_3) | _BV(R) | _BV(G) | _BV(B);
    DDRB |= _BV(W_4);
    PORTD &= ~(_BV(W_1) | _BV(W_2) | _BV(W_3));
    PORTD |= _BV(R) | _BV(G) | _BV(B);
    PORTB &= ~_BV(W_4);
}

void Turn_On_LEDS() {
    printf("in turn on led\n");
    current_bulb_index++;
    if (current_bulb_index > 7) {
        current_bulb_index = 7;
        RGB_Toggling = true;
        RGB_Toggle_Counter = 1;
        RGB_count++;
    }
}

void Turn_OFF_LEDS() {
    current_bulb_index--;
    if (current_bulb_index <= 0) {
        current_bulb_index = 0;
    }
}

void RGB_LED_ON() {
    RGB_Toggle_Counter++;
    if (RGB_Toggle_Counter > 3) {
        RGB_Toggle_Counter = 1;
    }
}

void RGB_LED_OFF() {
    RGB_Cycles = RGB_count / NUM_RGB;
    RGB_remainder = RGB_count % NUM_RGB;
    if (RGB_Cycles >= 0) {
        switch (RGB_remainder) {
            case 0:
                RGB_Toggle_Counter = 2;
                break;
            case 1:
                RGB_Toggle_Counter = 3;
                break;
            case 2:
                RGB_Toggle_Counter = 1;
                break;
        }
        RGB_count--;
    }
    if (RGB_Cycles == 0 && RGB_count == 0) {
        RGB_Toggling = false;
    }
}

void White_LED_Off() {
    current_bulb_index--;
    if (current_bulb_index <= 0) {
        current_bulb_index = 0;
    }
}

void set_All_LED_OFF() {
    OCR2B = OCR0B = OCR0A = OCR2A = 0;
    PORTD &= ~((1 << W_1) | (1 << W_2) | (1 << W_3));
    PORTB &= ~(1 << W_4);
    PORTD |= (1 << R) | (1 << G) | (1 << B);
}

void set_White_LED_ON(uint8_t index) {
    if (index >= 1) {
        DDRD |= _BV(DDD3);
        TCCR2A |= (_BV(COM2B1) | _BV(WGM21) | _BV(WGM20));
        TCCR2B |= (_BV(CS20));
        OCR2B = 255;
        if (To_Be_reduced[0] == 1) {
            OCR2B = W_Brightness[0];
        }
    } else {
        OCR2B = 0;
        PORTD &= ~(1 << W_1);
    }

    if (index >= 2) {
        DDRD |= _BV(DDD5);
        TCCR0A |= (_BV(COM0B1) | _BV(WGM01) | _BV(WGM00));
        TCCR0B |= (_BV(CS00));
        OCR0B = 255;

        if (To_Be_reduced[1] == 1) {
            OCR0B = W_Brightness[1];
        }
    } else {
        OCR0B = 0;
        PORTD &= ~(1 << W_2);
    }

    if (index >= 3) {
        DDRD |= _BV(DDD6);
        TCCR0A |= (_BV(COM0A1) | _BV(WGM01) | _BV(WGM00));
        TCCR0B |= (_BV(CS00));
        OCR0A = 255;

        if (To_Be_reduced[2] == 1) {
            OCR0A = W_Brightness[2];
        }
    } else {
        OCR0A = 0;
        PORTD &= ~(1 << W_3);
    }

    if (index >= 4) {
        DDRB |= _BV(DDB3);
        TCCR2A |= (_BV(COM2A1) | _BV(WGM21) | _BV(WGM20));
        TCCR2B |= (_BV(CS20));
        OCR2A = 255;

        if (To_Be_reduced[3] == 1) {
            OCR2A = W_Brightness[3];
        }
    } else {
        OCR2A = 0;
        PORTB &= ~(1 << W_4);
    }
    PORTD |= (1 << R) | (1 << G) | (1 << B);
}

void set_RGB_LED_ON(int ledPin) {
    PORTD |= (1 << R) | (1 << G) | (1 << B);
    PORTD &= ~(1 << ledPin);
}

void updateLEDs() {
    if (!RGB_Toggling) {
        switch (current_bulb_index) {
            case 0:
                set_All_LED_OFF();
                break;
            case 1:
                set_White_LED_ON(1);
                break;
            case 2:
                set_White_LED_ON(2);
                break;
            case 3:
                set_White_LED_ON(3);
                break;
            case 4:
                set_White_LED_ON(4);
                break;
            case 5:
                set_RGB_LED_ON(R);
                break;
            case 6:
                set_RGB_LED_ON(G);
                break;
            case 7:
                set_RGB_LED_ON(B);
                break;
        }
    } else {
        switch (RGB_Toggle_Counter) {
            case 0:
                set_White_LED_ON(4);
                break;
            case 1:
                set_White_LED_ON(R);
                break;
            case 2:
                set_White_LED_ON(G);
                break;
            case 3:
                set_White_LED_ON(B);
                break;
        }
    }
}

void Vol_Up() {
    if (RGB_Toggling) {
        RGB_LED_ON();
        RGB_count++;
    } else {
        Turn_On_LEDS();
    }
    updateLEDs();
}

void Vol_Down() {
    if (current_bulb_index <= 4 && !RGB_Toggling) {
        White_LED_Off();
    } else if (RGB_Toggling) {
        RGB_LED_OFF();
    } else {
        Turn_OFF_LEDS();
    }
    updateLEDs();
    if (current_bulb_index == 0) {
        return;
    }
}

void Channel_Down() {
    if (current_bulb_index == 0) {
        return;
    }
    W_Brightness[current_bulb_index - 1] = 30;
    To_Be_reduced[current_bulb_index - 1] = 1;
    updateLEDs();
}

int main(void) {
    init_serial();
    IR_init();
    init_bulbs();

    printf("Ready to receive IR codes...\n");

    // Main loop
    while (1) {
        if (IR_codeAvailable()) {
            uint16_t address, command;
            IR_getCode(&address, &command);
            if (!IR_isRepeatCode()) {
                printf("IR_code not repeated\n");
                if (command == V_U) {
                    Vol_Up();
                } else if (command == V_D) {
                    Vol_Down();
                } else if (command == C_D) {
                    Channel_Down();
                }
            } else {
                printf("IR_code repeated\n");
            }
        }
    }
}
