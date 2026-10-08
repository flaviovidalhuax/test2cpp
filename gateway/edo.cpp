#include"edo.h"
#include "../control/sensor.h"
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