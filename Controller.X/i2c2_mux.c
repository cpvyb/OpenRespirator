#include "i2c2_mux.h"
#include "mcc_generated_files/mcc.h"
#include "ORespGlobal.h"

uint8_t      currentTrfAddr;
i2c2_error_t lastI2C2MTrfResponse;
i2c2_error_t lastI2C2LTrfResponse;
i2c2_error_t lastI2C2MAckResponse;
i2c2_error_t lastI2C2LAckResponse;


void I2C2_NAckCallback(void){
    DEBUG_PRINT(("NACK %d\n", currentTrfAddr));    

    if (currentTrfAddr == MON_ADDR){
        lastI2C2MAckResponse = false;
    } else {
        lastI2C2LAckResponse = false;
    }
}

void I2C2_MuxInit(void){
    lastI2C2MAckResponse = true;
    lastI2C2LAckResponse = true;
    lastI2C2MTrfResponse = I2C2_NOERR;
    lastI2C2LTrfResponse = I2C2_NOERR;
    currentTrfAddr = 0x0;
    I2C2_SetDataNackCallback(I2C2_NAckCallback, NULL);   
    I2C2_SetAddressNackCallback(I2C2_NAckCallback, NULL);   
}

bool I2C2_MAck(void){
    return lastI2C2MAckResponse;
}
bool I2C2_LAck(void){
    return lastI2C2LAckResponse;
}


i2c2_error_t I2C2_MOpen(void){
    i2c2_error_t trfRsp;

    trfRsp = I2C2_Open(MON_ADDR);
    if (trfRsp != I2C2_BUSY) {
        lastI2C2MAckResponse = true;
        // Assign response to correct slave.
        if (currentTrfAddr == MON_ADDR){
            lastI2C2MTrfResponse = trfRsp;
        } else {
            lastI2C2LTrfResponse = trfRsp;
        }
        currentTrfAddr = MON_ADDR;
        // Return last response for Monitor.
        return lastI2C2MTrfResponse;
    } 
    return I2C2_BUSY;
}

i2c2_error_t I2C2_LOpen(void){
    i2c2_error_t trfRsp;

    trfRsp = I2C2_Open(LCD_ADDR);
    if (trfRsp != I2C2_BUSY) {
        lastI2C2LAckResponse = true;
        // Assign response to correct slave.
        if (currentTrfAddr == MON_ADDR){
            lastI2C2MTrfResponse = trfRsp;
        } else {
            lastI2C2LTrfResponse = trfRsp;
        }
        currentTrfAddr = LCD_ADDR;
        // Return last response for LCD.
        return lastI2C2LTrfResponse;
    }
    return I2C2_BUSY;
}

i2c2_error_t I2C2_MClose(void){
    i2c2_error_t trfRsp;

    trfRsp = I2C2_Close();
    if (trfRsp != I2C2_BUSY) {
        // Assign response to correct slave.
        if (currentTrfAddr == MON_ADDR){
            lastI2C2MTrfResponse = trfRsp;
        } else {
            lastI2C2LTrfResponse = trfRsp;
        }
        // Return last response for LCD.
        return lastI2C2MTrfResponse;    
    }
    return I2C2_BUSY;
}

i2c2_error_t I2C2_LClose(void){
    i2c2_error_t trfRsp;

    trfRsp = I2C2_Close();
    if (trfRsp != I2C2_BUSY) {
        // Assign response to correct slave.
        if (currentTrfAddr == MON_ADDR){
            lastI2C2MTrfResponse = trfRsp;
        } else {
            lastI2C2LTrfResponse = trfRsp;
        }
        // Return last response for LCD.
        return lastI2C2LTrfResponse;    
    }
    return I2C2_BUSY;
}
