#include "simulador.h"
#include <random>

static std::mt19937 generador(42);
    const int Num = 10;

double generarNumerosAletorio(double min, double max){
    std::uniform_real_distribution<double> distribucion(min, max);
    return distribucion(generador);
}

DatosVehiculo generarDatosIniciales(){
    DatosVehiculo datos;

    datos.velocidad = 0.0;
    datos.rpm = 800;
    datos.temperatura = 25.0;
    datos.voltajeBateria = 12.5;
    datos.presionAceite = 2.5;

    return datos;
}

DatosVehiculo acelerar(const DatosVehiculo& datosActuales){
    DatosVehiculo datos=datosActuales;


    for(int i=0; i<=Num; i++ ){
    datos.velocidad = i*10;
    datos.rpm = (i*10)/800;
    if(datos.velocidad>=80){
        datos.temperatura--;
        datos.voltajeBateria =- 0.1;
        datos.presionAceite =- 0.1;
    }
        if(datos.velocidad>=90){
        datos.temperatura--;
        datos.voltajeBateria =- 0.2;
        datos.presionAceite =- 0.2;
    }
    
    }
return datos;
}

DatosVehiculo frenos(const DatosVehiculo& datosActuales){
    DatosVehiculo datos=datosActuales;


    for(int i=0; i<=Num; i++ ){
    datos.velocidad = i*10;
    datos.rpm = (i*10)/800;
    if(datos.velocidad>=80){
        datos.temperatura++;
        datos.voltajeBateria =+ 0.1;
        datos.presionAceite =+ 0.1;
    }
        if(datos.velocidad>=90){
        datos.temperatura++;
        datos.voltajeBateria =+ 0.2;
        datos.presionAceite =+ 0.2;
    }
    
    }
return datos;
}

DatosVehiculo actualizarSimulacion(const DatosVehiculo& datosActuales){
    DatosVehiculo datosNuevos = datosActuales;

    datosNuevos.velocidad += generarNumerosAletorio(-2.0, 4.0);

    if (datosNuevos.velocidad < 0){
        datosNuevos.velocidad = 0;
    }

    if (datosNuevos.velocidad > 180.0){
        datosNuevos.velocidad = 180.0;
    }

    datosNuevos.rpm = 800 + static_cast<int>(datosNuevos.velocidad * 30.0) + static_cast<int>(generarNumerosAletorio(-150, 150));

    if (datosNuevos.rpm < 750){
        datosNuevos.rpm = 750;
        
    }

    if (datosNuevos.rpm > 6500){
        datosNuevos.rpm = 6500;
    }

    if(datosNuevos.temperatura < 90.0){
        datosNuevos.temperatura += generarNumerosAletorio(0.1, 0.6);
    }

    else
    {
        datosNuevos.temperatura += generarNumerosAletorio(-0.2, 0.2);
    }

    datosNuevos.voltajeBateria = 13.8 + generarNumerosAletorio(-0.15, 0.15);

    datosNuevos.presionAceite = 1.5 + datosNuevos.rpm/2000.0 + generarNumerosAletorio(-0.15, 0.15);

    return datosNuevos;
}

