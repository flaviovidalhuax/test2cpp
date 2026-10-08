#include "sensor.h"
#include <cstdint>
#include "../gateway/edo.h"

std::string estatusSenalAtexto(Estatus est);

int validarRangos(Mensaje& msj, RangosParametros& rango);

EstadoECU calcularNuevoEstado(EstadoECU es, Mensaje msj, int siguienteEstado);

std::string estadoAtexto(EstadoECU estado);