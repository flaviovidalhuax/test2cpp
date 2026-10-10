#include <iostream>
#include <string>
#include "gateway/edo.h"
#include "simulador/simulador.h"


int main() {

     DatosVehiculo datos = generarDatosIniciales();

    EstadoECU estado = EstadoECU::INIT;

    EstadoECU estado_anterior = estado;


      
    return 0;
}