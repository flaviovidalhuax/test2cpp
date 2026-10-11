#pragma once
#include "sensor.h"
#include "../gateway/edo.h"
#include <cstdint>

std::string estatusSenalAtexto(Estatus est);

int validarRangos(Mensaje& msj, RangosParametros& rango);

EstadoECU calcularNuevoEstado(EstadoECU es, int siguienteEstado);