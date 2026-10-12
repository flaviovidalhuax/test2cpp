
#include "ECUGateway.h"
#include "../control/sensor.h"
#include <chrono>
#include <iostream>  // Se usa para impresión básica
#include <iomanip>  // Se usa para comandos de escape o fix para formato
#include <string>  // Se usa para manejar strings
#include <sstream>  // Nos permite hacer operaciones complejas con string
#include <cstdlib>  // Nos permite hacer operaciones referentes al sistema y su terminal
#include <cctype>

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
void TransferirDatos(const DatosVehiculo& datos, Mensaje& msj)
{
    msj.Velocidad.param = datos.velocidad;
    msj.RPM.param = static_cast<float>(datos.rpm);
    msj.Temperatura.param = datos.temperatura;
    msj.VoltajeBateria.param = datos.voltajeBateria;
    msj.PresionAceite.param = datos.presionAceite;
}
bool ValidarDatos(Mensaje& msj, RangosParametros& rango)
{
    std::array<parametro*, 5> senales = msj.signals(msj);
    std::array<Rangos*, 5> rangos = rango.limites(rango);

    for (size_t i = 0; i < senales.size(); i++)
    {
        parametro* s = senales[i];
        const Rangos* r = rangos[i];

        if (s->param < r->minCritical ||
            s->param > r->maxCritical)
        {
            s->valido = false;
        }
        else
        {
            s->valido = true;
        }
    }
    bool todosValidos = true;
        for (size_t t = 0; t < senales.size(); t++) {
        parametro* param = senales[t];
        if (!param->valido) {
            todosValidos = false;
            break;
        }
    }
    return todosValidos;
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
