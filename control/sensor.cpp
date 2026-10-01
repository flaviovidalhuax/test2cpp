#include "sensor.h"


bool validarVelocidad(double velocidad){
    return velocidad >= 0.0 && velocidad <= 120.0;
}

bool validarRPM(int rpm){
    return rpm >= 0 && rpm <= 4000;
}

bool validarTemperatura(double temperatura){
    return temperatura >= -20.0 && temperatura <= 110.0;
}

bool validarVoltaje(double voltaje){
    return voltaje >= 10.0 && voltaje <= 15.5;
}


bool validarPresion(double presion){
    return presion >= 0.5 && presion <= 5.0;
}
