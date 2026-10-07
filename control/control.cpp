#include "control.h"


    
std::string estatusSenalAtexto(Estatus est){
    switch (est){
        case Estatus::OK:
            return "Signal OK";
        case Estatus::WARNING:
            return "Signal WARNING";
        case Estatus::ERROR:
            return "Signal ERROR";
        case Estatus::MISSING:
            return "Signal MISSING";    
    }
    return "Signal MISSING";
}

bool evaluarCondicionDeArvertencia(double temperatura, double rpm, double voltage){
    return  temperatura >= 100.0 ||
            rpm > 6000 ||
            voltage < 12.0;


}
bool evaluarCondicionCritica(double temperatura, double rpm, double voltage){
    return  temperatura >= 110.0 ||
            rpm > 7000 ||
            voltage < 11.0;
}
/*
Evalua los rangos de las variables fisicas solo si el ECUgateway valido la señal o llego en el plazo establecido.
La funcion, además, retorna una de las condiciones para el cambio de estado
*/
int validarRangos(Mensaje& msj, RangosParametros& rango){
    std::array<parametro*, 6> senales = msj.signals(msj);
    std::array<Rangos*, 6> ran = rango.limites(rango);
    uint8_t contador=0, contError=0;
    for (size_t i = 0; i < senales.size(); i++){
        parametro* p = senales[i];
        const Rangos* r = ran[i];
        if (p->valido){
            if (p->param >= r->minOperative && p->param <= r->maxOperative) {
                p->estatus = Estatus::OK;
            } 
            else if (p->param < r->minWarning && p->param > r->minCritical || p->param > r->maxWarning && p->param < r->maxCritical) {
                p->estatus = Estatus::ERROR; 
            } 
            else if (p->param < r->minOperative && p->param > r->minWarning 
                    || p->param > r->maxOperative && p->param < r->maxWarning){
                p->estatus = Estatus::WARNING; 
            }else{
                p->estatus = Estatus::MISSING;
            }
        }else{
            p->estatus = Estatus::MISSING;
        }
        if (p->estatus==Estatus::WARNING||p->estatus==Estatus::MISSING){
                contador++;
        }else if(p->estatus==Estatus::ERROR){
            contError++;
        }
    }
    if(contError>0 || contador>3){
            return 2;
    }else if (contador>0 && contador<4){
        return 1;
    }else{
        return 0;
    }
}
EstadoECU seleccion(int s){
switch (s){
    case 0:
        return EstadoECU::OPERATIONAL;
    case 1:
        return EstadoECU::DEGRADED;
    case 2:
        return EstadoECU::SAFE_STATE;
    }
    return EstadoECU::SAFE_STATE;
}
EstadoECU calcularNuevoEstado(EstadoECU es, Mensaje msj, int siguienteEstado=2){
    if (es==EstadoECU::INIT){
        return EstadoECU::SELF_TEST;
    }
    if(es==EstadoECU::SELF_TEST){
        return seleccion(siguienteEstado);
    }
    if(es==EstadoECU::OPERATIONAL){
        return seleccion(siguienteEstado);
    }
    if(es==EstadoECU::DEGRADED){
        return seleccion(siguienteEstado);
    }
    if(es==EstadoECU::SAFE_STATE){
        return EstadoECU::SAFE_STATE;
    }
    return es;
}