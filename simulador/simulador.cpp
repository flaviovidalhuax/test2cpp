#include "simulador.h"
#include <random>

static std::mt19937 generador(42);

double generarNumeroAleatorio(double minimo, double maximo)
{
    std::uniform_real_distribution<double> distribucion(minimo, maximo);

    return distribucion(generador);
}

DatosVehiculo generarDatosIniciales()
{
    DatosVehiculo datos;

    datos.velocidad = 0.0;
    datos.rpm = 800;
    datos.temperatura = 25.0;
    datos.voltajeBateria = 12.5;
    datos.presionAceite = 2.5;

    return datos;
}

DatosVehiculo actualizarSimulacion(const DatosVehiculo& datosActuales){
    DatosVehiculo datosNuevos = datosActuales;

    datosNuevos.velocidad += generarNumeroAleatorio(-2.0, 4.0);

    if (datosNuevos.velocidad < 0){
        datosNuevos.velocidad = 0;
    }

    if (datosNuevos.velocidad > 180.0){
        datosNuevos.velocidad = 180.0;
    }

    datosNuevos.rpm = 800 + static_cast<int>(datosNuevos.velocidad * 30.0) + static_cast<int>(generarNumeroAleatorio(-150, 150));

    if (datosNuevos.rpm < 750)
    {
        datosNuevos.rpm = 750;
    }

    if (datosNuevos.rpm > 6500)
    {
        datosNuevos.rpm = 6500;
    }

    if(datosNuevos.temperatura < 90.0)
    {
        datosNuevos.temperatura += generarNumeroAleatorio(0.1, 0.6);
    }
    else
    {
        datosNuevos.temperatura += generarNumeroAleatorio(-0.2, 0.2);
    }

    datosNuevos.voltajeBateria = 13.8 + generarNumeroAleatorio(-0.15, 0.15);

    datosNuevos.presionAceite = 1.5 + datosNuevos.rpm/2000.0 + generarNumeroAleatorio(-0.15, 0.15);

    return datosNuevos;
}