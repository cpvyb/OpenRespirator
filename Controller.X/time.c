#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/tmr1.h"
#include "time.h"

void timeInit(void){
    TMR0_StartTimer();
    TMR1_StartTimer();
}

// TIME function. Maintains global time. Resolution 0.1ms. Span about 6s. 
time_t timeGet(void){
    return TMR1_ReadTimer();
}

// Checks if time has finish and refresh tstamp.
bool timeElapsedR(time_t *prevTime, time_t duration){
    time_t intTime, intDur;
    intTime = TMR1_ReadTimer();
    intDur = intTime - *prevTime;
    if (intDur < duration) {
        return false;
    } else {
        *prevTime = intTime;
        return true;
    }
}

// Only checks if time hasfinished.
bool timeElapsed(time_t prevTime, time_t duration){
    time_t intTime, intDur;
    intTime = TMR1_ReadTimer();
    intDur = intTime - prevTime;
    if (intDur < duration) {
        return false;
    } else {
        return true;
    }
}
