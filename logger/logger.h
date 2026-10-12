#pragma once
#include "../control/control.h"
#include "../control/sensor.h"

enum class EventoLogger{
    LOG,
    INFO,
    WARN,
    ERROR
};
void inicializarLogger(const std::string& fileName);
void cerrarLogger();
long long obtenerTimestamp();
void registrarEventos(EventoLogger log, const std::string& modulo, const std::string& mensaje);
void registrarDatosSensores(const DatosVehiculo& datos, EstadoECU estado);
std::string EstadoTextoLogger(EventoLogger evento);