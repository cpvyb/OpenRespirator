/* 
 * File:   ORespGlobal.h
 * Author: David Ortiz
 *
 * Created on April 4, 2020, 12:56 PM
 */

#ifndef ORESPGLOBAL_H
#define	ORESPGLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
#include "aCapture.h"

// User parameter limits.
#define BPM_MIN 10
#define BPM_MAX 30
#define IP_MIN 4
#define IP_MAX 80
#define PEEP_MIN 4
#define PEEP_MAX 25
// Volume limit. With limitations of this equipment volume below 100ml can not be provided with accuracy. Probably lower limit should be higher.
#define VOL_MIN 100
#define VOL_MAX 900
#define VOL_AMIN 50
// At this moment this is only due to restriction on display.
#define VOL_AMAX 980

// Default value for volume alarms. +-25%
#define VOL_ALRM_DFL 25
    
// Max pressure overshoot. In milibars.
#define POVERSHOOT_LIMIT MPRESSURE_MBAR(3)
// Max Volume overshoot. In mililiters.
#define VOVERSHOOT_LIMIT 25
// Limit for pressure quanta estimation. Needed to saturate quanta measurement to avoid a deathlock.
#define PQUANTA_LIMIT    MPRESSURE_MBAR(7)
// Limit for pressure quanta estimation. Needed to saturate quanta measurement to avoid a deathlock.
#define VQUANTA_LIMIT    90
    //////////////////////////////////////
    // Actuation pins.
    //////////////////////////////////////
#if 0
#define SV2ISOPEN LATAbits.LATA2
#define OPEN_SV2 LATAbits.LATA2 = 1
#define CLOSE_SV2 LATAbits.LATA2 = 0
#else
#define SV2ISOPEN (sv2_pwmval!=0)
#define OPEN_SV2 sv2_pwmval=100;PWM5_LoadDutyValue(sv2_pwmval)
#define CLOSE_SV2 sv2_pwmval=0;PWM5_LoadDutyValue(sv2_pwmval)
#endif
    
#define SV3ISOPEN LATAbits.LATA3
#define OPEN_SV3 LATAbits.LATA3 = 1
#define CLOSE_SV3 LATAbits.LATA3 = 0

#define BLED_ON  LATDbits.LATD6 = 1
#define BLED_OFF LATDbits.LATD6 = 0

#define BUZZERISON  LATDbits.LATD0
#define BUZZER_ON  LATDbits.LATD0 = 1
#define BUZZER_OFF LATDbits.LATD0 = 0

#define DEBUG

#ifdef DEBUG
#define ERROR_CONDITION(k) CLOSE_SV2;CLOSE_SV3;printf("Fatal %d",k)
#else
#define ERROR_CONDITION(k) CLOSE_SV2;CLOSE_SV3;BUZZER_ON; while(1)
#endif


#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif

    typedef enum {
        VMODE_PRESSURE = 0,
        VMODE_VOLUME = 1
    } vmodeT;
    
    typedef enum {
    CTRL_UNCAL,
    CTRL_STOP,
    CTRL_RUN,
    CTRL_SLEEP
} ctrlStatusT;

    // Global variables.
    extern ctrlStatusT ctrlStatus;
    extern ctrlStatusT ctrlStatus;
    extern vmodeT VentMode; // 0 --> Pressure-control, 1 --> Volume-control.
    extern uint8_t BPM;
    extern uint16_t IDuration, EDuration;
    extern uint8_t IP;
    extern uint8_t MaxP;
    extern uint8_t MaxV;
    extern uint8_t LowVAlarm;
    extern uint8_t HighVAlarm;
    extern uint8_t PEEP;
    extern uint8_t eBRate;
    extern int16_t vddValMean;
    // Change detection for all user settings.
    extern bool chBPM, chIP, chMaxP, chPEEP, chLowVAlarm, chHighVAlarm, chMaxV, chPEEP, chVentMode;
    extern uint16_t lastCycleVol;
    extern uint16_t sv2_pwmval;

#ifdef	__cplusplus
}
#endif

#endif	/* ORESPGLOBAL_H */

