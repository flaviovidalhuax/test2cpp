#include <iostream>
#include <string>
#include "control/sensor.h"
#include "gateway/edo.h"
#include "gateway/ECUGateway.h"
#include "control/control.h"
#include "simulador/simulador.h"

#include <chrono>
#include <thread>


int main(){

  EstadoECU estado = EstadoECU::INIT;

  std::cout << estadoAtexto(estado);

  Mensaje msj;
  RangosParametros rango;

  
  rango=inicializarParametros(msj);
  DatosVehiculo datosVeiculo = generarDatosIniciales();

  long long ciclo = 0;
  const long long MAX_CICLOS = 200;
  int siguienteEstado=0;

  while(ciclo < MAX_CICLOS)
  {
    datosVeiculo = actualizarSimulacion(datosVeiculo);
    LeerDatos(msj, rango, datosVeiculo);

    siguienteEstado = validarRangos(msj, rango);
    std::cout << "Ciclo: " 
              << ciclo  << " " <<
                estadoAtexto(calcularNuevoEstado(estado, siguienteEstado)) 
              << std::endl;
    std::cout << "Estado actual: " <<  estadoAtexto(calcularNuevoEstado(estado, siguienteEstado)) 
              << " Sig Estado: " << siguienteEstado << " "  << std::endl;
    
    ciclo++;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    estado = calcularNuevoEstado(estado, siguienteEstado);
  }

  if(ciclo >= MAX_CICLOS)
  {
    std::cout << "Estado actual: " << estadoAtexto(calcularNuevoEstado(estado, siguienteEstado + 1)) << std::endl;
  }

  return 0;
}