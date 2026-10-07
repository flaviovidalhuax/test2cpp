
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
//Inicializa las señales y configura los rangos
const RangosParametros inicializarParametros(Mensaje& msj){
    msj.Velocidad.set("velocidad", "km/h", "SPEED", 0);
    msj.Aceleracion.set("aceleracion", "%", "ACCEL", 0);
    msj.RPM.set("revoluciones por minuto", "rpm", "RPM", 0);
    msj.Temperatura.set("temperatura", "°C", "ENG_TEMP", 25);
    msj.VoltajeBateria.set("batería baja potencia", "V", "VOL_BATT", 12, "ECU_BJB");
    msj.PresionAceite.set("presión de aceite", "PSI", "PRESS", 48, "ECU_PS");
    RangosParametros ran;
    ran.Velocidad.set(240, 270, 300,-10);
    ran.Aceleracion.set(60, 70, 100, -10);
    ran.RPM.set(5000, 6000, 7000, 0, 500);
    ran.Temperatura.set(110, 125, 145, -40, -30,-20);
    ran.VoltajeBateria.set(15, 15.5, 16, 10, 10.5, 11);
    ran.PresionAceite.set(54, 56, 58, 39, 40, 44);
    return ran;
}