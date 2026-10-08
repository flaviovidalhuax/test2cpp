
#include "ECUGateway.h"
#include "../control/sensor.h"
#include <chrono>
#include <iostream>  // Se usa para impresión básica
#include <iomanip>  // Se usa para comandos de escape o fix para formato
#include <string>  // Se usa para manejar strings
#include <sstream>  // Nos permite hacer operaciones complejas con string
#include <cstdlib>  // Nos permite hacer operaciones referentes al sistema y su terminal

std::string estatusSenalAtextoG(Estatus est){
    switch (est){
        case Estatus::OK:
            return "OK";
        case Estatus::WARNING:
            return "WARNING";
        case Estatus::ERROR:
            return "ERROR";
        case Estatus::MISSING:
            return "MISSING";    
    }
    return "MISSING";
}

bool esNumero(const std::string &str){
    if (str.empty()) return false;

    bool puntoDecimal = false;
    size_t inicio = 0;

    // Permitir signo al inicio
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) return false; // Solo signo no es válido
        inicio = 1;
    }

    for (size_t i = inicio; i < str.size(); ++i) {
        if (str[i] == '.') {
            if (puntoDecimal) return false; // Más de un punto decimal
            puntoDecimal = true;
        } else if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false; // Caracter no numérico
        }
    }
    return true;
}
std::string formatearDouble(double valor, int decimales)
{
    std::ostringstream salida;
    salida << std::fixed << std::setprecision(decimales) << valor;
    return salida.str();
}
/* Realiza la lectura de los datos y los almacena en un struct empleando los rangos definidos 
en los requerimientos, la funcion evalua al momento de la lectura el tiempo si dura más de 10 
segundos lo cuanta como MISSING y evalua si es numero y no pasa de los valores físicos posibles
*/
void LeerDatos(Mensaje& msj, RangosParametros& rango){
    std::array<parametro*, 6> senales = msj.signals(msj);
    std::array<Rangos*, 6> ran = rango.limites(rango);
    std::string entrada;
    for (size_t i=0; i < senales.size(); i++) {
        parametro* s = senales[i];
        const Rangos* r = ran[i];
        std::cout << "================   Rangos físicos posibles    ================" << std::endl;
        std::cout << "Normales:     " << formatearDouble(r->minOperative,2) << " " <<  s->unidades 
                    << " hasta " << formatearDouble(r->maxOperative,2) << " " << s->unidades << std::endl;
        std::cout << "Alerta:       menor a " << formatearDouble(r->minWarning,2) << " " << s->unidades 
                    << " y mayor a " << formatearDouble(r->maxWarning,2) << " " << s->unidades << std::endl;
        std::cout << "Críticos:     menor a " << formatearDouble(r->minCritical,2) << " " << s->unidades 
                  << " y mayor a " << formatearDouble(r->maxCritical,2) << " " << s->unidades << std::endl;
        std::cout << "Recibiendo señal de " << s->nombre << " desde " << s->ECUorigen << ": ";
        auto inicioMedicion = std::chrono::steady_clock::now();
        std::cin >> entrada;
        auto finMedicion=std::chrono::steady_clock::now();
        auto tiempoTranscurrido = std::chrono::duration_cast<std::chrono::seconds>(finMedicion-inicioMedicion);
        if(esNumero(entrada)){

            //Aqui se llama a la funcion que genera el valor simulado 
            s->param = std::stof(entrada); 


            if (s->param < r->minCritical || s->param > r->maxCritical){
                s->valido = false;
            }else{
                s->valido=true;
            }
        }else{
            s->valido = false;
        }
        if (tiempoTranscurrido.count()>10){//10 segundos para ingresar valor sino se considera señal perdida
            s->estatus=Estatus::MISSING;
            s->valido=false;
        }
    }
}


/*
void enviarPanel(Mensaje& msj){
    std::array<parametro*, 6> senales = msj.signals(msj);
    std::cout << "============== Panel Status==============="<<std::endl;
    int contadorOk=0, contadorWarning=0, contadorMissing=0, contadorError=0;
    for (size_t i=0; i < senales.size(); i++) {
        parametro* s = senales[i];
        std::cout 
            << "El estado de "  
            << s->nombre
            << ": "  << s->param << " " << s->unidades
            << " | Signal " 
            << estatusSenalAtexto(s->estatus)
            << "| Signal valida: " << s->valido
            << std::endl;
            if(s->estatus==Estatus::OK){
                contadorOk=contadorOk + 1;
            }
            if(s->estatus==Estatus::WARNING){
                contadorWarning=contadorWarning + 1;
            }
            if(s->estatus==Estatus::MISSING){
                contadorMissing=contadorMissing + 1;
            }
            if(s->estatus==Estatus::ERROR){
                contadorError=contadorError + 1;
            }
    }
    if(contadorOk>=6){
        std::cout << "Todas las señales son validas y normales. "<<std::endl;
    }
    if(contadorWarning>=3){
        std::cout << "Hay 3 o mas señales con advertencia. "<<std::endl;
    }
    if(contadorMissing>=3){
        std::cout << "Hay 3 o mas señales que no se peuden leer. "<<std::endl;
    }
    if(contadorError>=3){
        std::cout << "Hay 3 o mas señales con error critico. "<<std::endl;
    }
    std::cout << "==========================================="<<std::endl;
}
void enviarDiagnostico(Mensaje& msj){
    std::cout << "============== Inicia Diagnostico ==============="<<std::endl;
    std::array<parametro*, 6> senales = msj.signals(msj);
    int contadorOk=0, contadorWarning=0, contadorMissing=0, contadorError=0;
    for (size_t i=0; i < senales.size(); i++) {
        parametro* s = senales[i];
        std::cout 
            << s->codigo << ": " 
            << estatusSenalAtexto(s->estatus)
            << " | " << s->param << s->unidades
            << std::endl;
            if(s->estatus==Estatus::OK){
                contadorOk=contadorOk + 1;
            }
            if(s->estatus==Estatus::WARNING){
                contadorWarning=contadorWarning + 1;
            }
            if(s->estatus==Estatus::MISSING){
                contadorMissing=contadorMissing + 1;
            }
            if(s->estatus==Estatus::ERROR){
                contadorError=contadorError + 1;
            }
    }
    if(contadorOk>=6){
        std::cout << "Todas las señales son validas y normales. "<<std::endl;
    }
    if(contadorWarning>=3){
        std::cout << "Hay 3 o mas señales con advertencia. "<<std::endl;
    }
    if(contadorMissing>=3){
        std::cout << "Hay 3 o mas señales que no se pueden leer. "<<std::endl;
    }
    if(contadorError>=3){
        std::cout << "Hay 3 o mas señales con error critico. "<<std::endl;
    }
    std::cout << "=============== Fin Diagnostico ==============="<<std::endl;
}
*/