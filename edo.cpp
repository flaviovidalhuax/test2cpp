#include"edo.h"

EstadoECU evaluarEstado(){
    return EstadoECU::INIT;
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