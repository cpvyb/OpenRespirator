#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#include "buzzer.h"
#include "alarm.h"

// This code generates alarm tones and alarm tones sequences



uint8_t alarmStep;
uint8_t alarmState;

//---------------------- BUZZER STATE
#define BUZZER_OFF 0
#define BUZZER_LOW 1
#define BUZZER_A   2
#define BUZZER_B   3
#define BUZZER_C   4
#define BUZZER_D   5
#define BUZZER_E   6
#define BUZZER_F   7

uint8_t buzzerState;

#define PERIOD_A  0x8D  // 440 Hz
#define PERIOD_B  0xFC  // 246.94 Hz
#define PERIOD_C  0xEE  // 261.63 Hz
#define PERIOD_D  0xD4  // 293.66 Hz
#define PERIOD_E  0xBD  // 329.63 Hz
#define PERIOD_F  0xB2  // 349.23 Hz

#define TIMER_400MS 102
#define TIMER_200MS 51
#define TIMER_100MS 26
#define TIMER_180MS 46
#define TIMER_1S    255

void BuzzerSet(uint8_t state) {
    alarmState = state;
    alarmStep = 0;
    BuzzerOff();
    BuzzerTask();
}

void BuzzerClear() {
    alarmState = ALARM_NONE;
    BuzzerOff();
    TMR4_Stop();
}

void BuzzerHandler( void) {
    printf("BH\r\n");
    BuzzerOff();
    BuzzerTask();
}
void BuzzerTestHandler( void) {
    
    printf("BTH\r\n");
    BuzzerOff();
}

void BuzzerTest(char note) {
    TMR4_SetInterruptHandler(BuzzerTestHandler);
    switch (note) {
        case 'A':
            BuzzerOn(PERIOD_A);
            break;
        case 'B':
            BuzzerOn(PERIOD_B);
            break;
        case 'C':
            BuzzerOn(PERIOD_C);
            break;
        case 'D':
            BuzzerOn(PERIOD_D);
            break;
        case 'E':
            BuzzerOn(PERIOD_E);
            break;
        case 'F':
            BuzzerOn(PERIOD_F);
            break;            
        default:
            BuzzerOff();
            return;         
    };
    TMR4_Period8BitSet(TIMER_200MS);
    TMR4_Start();
}

// ALARM_NONE 0
// ALARM_LOW  1 // E 200ms LOW 200ms C 200ms LOW 16s
// ALARM_MED  2 // C 200ms LOW 200ms A 200ms LOW 200ms F 200ms LOW 8s
// ALARM_HIGH 4 // C 180ms LOW 100ms A 180ms LOW 100ms F 180ms LOW 400ms A 180ms LOW 100ms F 180ms LOW 1s
                     // ... C 180ms LOW 100ms A 180ms LOW 100ms F 180ms LOW 400ms A 180ms LOW 100ms F 180ms LOW 4s

void BuzzerTask(void) {
    BuzzerOff();
    TMR4_Stop();
    TMR4_SetInterruptHandler(BuzzerHandler);
    switch(alarmState) {
        case ALARM_LOW:
            switch (alarmStep) {
                case 0:
                    BuzzerOn(PERIOD_E);
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;             
                case 1:
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 2:
                    BuzzerOn(PERIOD_C);
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 18:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep=0;
                    TMR4_Start();
                    break;
                default:
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep=0;
                    TMR4_Start();
                    break;                 
            };
            break;
        case ALARM_MED:
           switch (alarmStep) {
                case 0:
                    BuzzerOn(PERIOD_C);
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;             
                case 1:
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 2:
                    BuzzerOn(PERIOD_A);
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 3:
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 4:
                    BuzzerOn(PERIOD_F);
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 12:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep=0;
                    TMR4_Start();
                    break;
                default:
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep=0;
                    TMR4_Start();
                    break;                 
            };
            break;            
        case ALARM_HIGH:
            switch (alarmStep) {
                case 0:
                    BuzzerOn(PERIOD_C);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;             
                case 1:
                    TMR4_Period8BitSet(TIMER_100MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 2:
                    BuzzerOn(PERIOD_A);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 3:
                    TMR4_Period8BitSet(TIMER_100MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 4:
                    BuzzerOn(PERIOD_F);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 5:
                    TMR4_Period8BitSet(TIMER_400MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 6:
                    BuzzerOn(PERIOD_A);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 7:
                    TMR4_Period8BitSet(TIMER_100MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 8:
                    BuzzerOn(PERIOD_F);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 9:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep++;
                    TMR4_Start();
                    break;                     
                case 10:
                    BuzzerOn(PERIOD_C);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;             
                case 11:
                    TMR4_Period8BitSet(TIMER_100MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 12:
                    BuzzerOn(PERIOD_A);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 13:
                    TMR4_Period8BitSet(TIMER_100MS);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 14:
                    BuzzerOn(PERIOD_F);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 15:
                    TMR4_Period8BitSet(TIMER_400MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 16:
                    BuzzerOn(PERIOD_A);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 17:
                    TMR4_Period8BitSet(TIMER_100MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                    
                case 18:
                    BuzzerOn(PERIOD_F);
                    TMR4_Period8BitSet(TIMER_180MS);
                    alarmStep++;
                    TMR4_Start();
                    break;                       
                case 19:
                case 20:
                case 21:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep++;
                    TMR4_Start();
                    break;
                case 22:
                    TMR4_Period8BitSet(TIMER_1S);
                    alarmStep=0;
                    TMR4_Start();
                    break;
                default:
                    TMR4_Period8BitSet(TIMER_200MS);
                    alarmStep=0;
                    TMR4_Start();
                    break;                 
            };
            break;            
        case ALARM_NONE:
        default:
            BuzzerOff();
            break;
    };
    
}

void BuzzerInit (void) {
    // Initialize TIMER 4 handler
    TMR4_SetInterruptHandler(BuzzerHandler);
    BuzzerOff();
    
}


void BuzzerOn (uint8_t period) {
    T2PR = period;
    PWM6CON = 0x80;
}

void BuzzerOff (void) {
    PWM6CON = 0x00;
}