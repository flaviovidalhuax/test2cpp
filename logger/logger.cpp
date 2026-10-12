#include <logger.h>

#include<iostream>
#include<iomanip>
#include<chrono>
#include<fstream>
#include<control.h>
#include<string>

namespace 
{
    std::ofstream logFile;

    void escribirCampoCsv(const std::string& campo) {
        logFile << '"';
        for (char caracter : campo) {
            if (caracter == '"') {
                logFile << '"';
            }
            logFile << caracter;
        }
        logFile << '"';
    }
}

std::string EstadoTextoLogger(EventoLogger evento) {
    switch (evento) {
        case EventoLogger::LOG: return "LOG";
        case EventoLogger::INFO: return "INFO";
        case EventoLogger::WARN: return "WARN";
        case EventoLogger::ERROR: return "ERROR";
    }
    return "INFO";
}

void inicializarLogger(const std::string& fileName){
    logFile.open(fileName);
    if(!logFile.is_open()){
        std::cerr << "No se pudo abrir el archivo de log.\n";
        return;
    }
    logFile << "timestamp_ms,Nivel,Modulo,Mensaje_log,Estado_ECU,PRESION_ACEITE,RPM,TEMPERATURA,VELOCIDAD,VOLTAJE\n";
    logFile.flush();
}
void cerrarLogger(){
    if(logFile.is_open()){
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
    logFile << obtenerTimestamp() << ',';
    escribirCampoCsv(EstadoTextoLogger(log));
    logFile << ',';
    escribirCampoCsv(modulo);
    logFile << ',';
    escribirCampoCsv(mensaje);
    logFile << ",,,,,,\n";
    logFile.flush();
}
void registrarDatosSensores(const DatosVehiculo& datos, EstadoECU estado){
    if(!logFile.is_open()){
        return;
    }
    logFile << obtenerTimestamp() << ",DEBUG,ECU_GATEWAY,,";
    escribirCampoCsv(estadoAtexto(estado));
    logFile << ',' << std::fixed << std::setprecision(2)
    << datos.presionAceite << ','
    << datos.rpm << ','
    << datos.temperatura << ','
    << datos.velocidad << ','
    << datos.voltajeBateria << '\n';
    logFile.flush();

}
