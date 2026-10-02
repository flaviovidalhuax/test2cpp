#include"edo.h"
#include "sensor.h"
//add chages
EstadoECU evaluarEstado(const DatosVehiculo& datos){
 bool velocidadValida = validarVelocidad(datos.velocidad);
    bool rpmValida = validarRPM(datos.rpm);
    bool temperaturaValida = validarTemperatura(datos.temperatura);
    bool voltajeValido = validarVoltaje(datos.voltajeBateria);
    bool presionValida = validarPresion(datos.presionAceite);

    if (!temperaturaValida || !rpmValida || !presionValida || !velocidadValida || !voltajeValido){
        return EstadoECU::SAFE_STATE;
    }

    if (datos.temperatura > 100.0 || datos.voltajeBateria < 11.5 || datos.presionAceite < 1.0){
        return EstadoECU::DEGRADED;
    }

    return EstadoECU::OPERATIONAL;
 }

std::string estadoAtexto(EstadoECU estado){
    switch(estado){

        case EstadoECU::INIT:
            return "INIT";

        case EstadoECU::SELF_TEST:
            return "SELF_TEST";

        case EstadoECU::OPERATIONAL:
            return "OPERATIONAL";

        case EstadoECU::DEGRADED:
            return "DEGRADED";

        case EstadoECU::SAFE_STATE:
            return "SAFE_STATE";

        case EstadoECU::SHUTDOWN:
            return "SHUTDOWN";
    }

    return "DESCONOCIDO";
}