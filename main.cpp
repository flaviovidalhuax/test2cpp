#include <iostream>
#include <string>
#include <dashboard.h>
#include <logger.h>
#include <thread>
#include "gateway/edo.h"
#include "simulador/simulador.h"
#include "gateway/ECUGateway.h"
#include "control/control.h"


int main() {

    DatosVehiculo datos = generarDatosIniciales();
    EstadoECU estado = EstadoECU::INIT;

    EstadoECU estado_anterior = estado;
    bool estadoActivo = true;
    long long ciclosMaximos =  300;
    long cicloActual = 0;
    Mensaje msj;
    RangosParametros rango;
    //Inicalizamos los limites
    rango=inicializarParametros(msj);
    int siguienteEstado=0;
    while (ciclosMaximos < cicloActual)
    {
       estadoActivo = false;
        datos = actualizarSimulacion(datos);
        TransferirDatos(datos, msj);
        //ecugateway
        ValidarDatos(msj,rango);
        siguienteEstado = validarRangos(msj, rango);

        calcularNuevoEstado(estado, siguienteEstado);


        LeerDatos(msj, rango);


        cicloActual++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    std::cout << "Se ha terminado la ejecucion" << std::endl;
    cerrarLogger();
    return 0;
}