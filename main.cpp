#include <iostream>
#include <string>
#include <dashboard.h>
#include "gateway/edo.h"
#include "simulador/simulador.h"
#include "gateway/ECUGateway.h"
#include "control/control.h"


int main(){

  EstadoECU estado = EstadoECU::INIT;

  std::cout << "hello" << "\n";
  std::cout << estadoAtexto(estado);

  Mensaje msj;
  RangosParametros rango;

  rango=inicializarParametros(msj);
  LeerDatos(msj, rango);

  int siguienteEstado = validarRangos(msj, rango);
  std::cout << "Arranque: " 
            << 
              estadoAtexto(calcularNuevoEstado(estado, msj, siguienteEstado)) 
            << std::endl;
  std::cout << "Estado actual: " <<  estadoAtexto(calcularNuevoEstado(estado, msj, siguienteEstado)) << std::endl;
  return 0;
}