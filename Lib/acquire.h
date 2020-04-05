///////////////////////////////////////////////////////////////////////////////
//     Primitive Test Ventilator
///////////////////////////////////////////////////////////////////////////////
// FileName:        acquire.h
// Dependencies:    See INCLUDES section below
// Processor:       PIC18
// Compiler:        C18 3.00
///////////////////////////////////////////////////////////////////////////////

#ifndef ACQUIRE_H
#define ACQUIRE_H

/// I N C L U D E S ///////////////////////////////////////////////////////////
#include "calibrate.h"

/// D E F I N I T I O N S /////////////////////////////////////////////////////
#define ADC_SETTLING_CYCLES			15		// 15 x 10 clock cycles = 12uS

/// E X T E R N S /////////////////////////////////////////////////////////////
extern int pressure;
extern int pot_bpm;
extern int pot_ti;
extern int pot_peep;
extern int pot_pip;

/// P U B L I C  P R O T O T Y P E S //////////////////////////////////////////
void ADCTasks(void);
void InitADC(void);

#endif //ACQUIRE_H