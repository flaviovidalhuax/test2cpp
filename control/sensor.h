#pragma once 

struct DatosVehiculo{
    double velocidad;
    int rpm;
    double temperatura;
    double voltajeBateria;
    double presionAceite;
};

bool validarVelocidad(double velocidad);

bool validarRPM(int rpm);

bool validarTemperatura(double temperatura);

bool validarVoltaje(double voltaje);

bool validarPresion(double presion);




