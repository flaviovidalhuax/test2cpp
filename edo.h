#pragma once

#include <string>

enum class EstadoECU{

    INIT,
    SELF_TEST,
    OPERATIONAL,
    DEGRADED,
    SAFE_STATE,
    SHUTDOWN

};
EstadoECU evaluarEstado();

std::string estadoAtexto(EstadoECU estado);