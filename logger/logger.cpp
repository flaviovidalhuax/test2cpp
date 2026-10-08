#include <logger.h>

#include<iostream>
#include<iomanip>
#include<chrono>
#include<fstream>
#include<control.h>

namespace 
{
    std::ofstream logFile;
}

void inicializarLogger(const std::string& fileName){
    logFile.open(fileName);
    logFile << "[\n";
    logFile.flush();

    if(!logFile.is_open()){
        std::cerr << "No se pudo abir el archivo de log.\n";
        return;
    }
}
void cerrarLogger(){
    if(!logFile.is_open()){
        logFile << "]";
        logFile.flush();
        logFile.close();
    }
}
long long obtenerTimestamp(){
    auto ahora = std::chrono::system_clock::now();
    auto tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(ahora.time_since_epoch());
    return tiempo.count();

}
void registrarEventos(EventoLogger log, const std::string& modulo, const std::string& mensaje){
    if(!logFile.is_open()){
        return;
    }
    logFile << ",{"
    <<"\"timestamp_ms\":" << obtenerTimestamp() << "," 
    <<"\"Nivel\":\"" <<EstadoTextoLogger(log) << "\","
    <<"\"Modulo\":\"" << modulo << "\","
    <<"\"Mensaje_log\":\"" <<mensaje <<"\""
    << "}\n";
    logFile.flush();
}
void registrarDatosSensores(const DatosVehiculo& datos, EstadoECU estado){
        if(!logFile.is_open()){
        return;
    }
    logFile << ",{"
    <<"\"timestamp_ms\":" << obtenerTimestamp() << "," 
    <<"\"Nivel\":\"DEBUG\","
    <<"\"Estado_ECU\":\"" <<estadoAtexto(estado) << "\","
    <<"\"PRESION_ACEITE\":" << std::fixed << std::setprecision(2)  << datos.presionAceite << ","
    <<"\"REVOLUCIONES POR MIN\":" << datos.presionAceite  << ","
    <<"\"TEMPERATURA\":" << std::fixed << std::setprecision(2)  << datos.presionAceite << ","
    <<"\"VELOCIDAD\":" << std::fixed << std::setprecision(2)  << datos.velocidad << ","
    <<"\"VOLTAJE\":" << std::fixed << std::setprecision(2)  << datos.voltajeBateria << ","    
    << "}\n";
    logFile.flush();

}