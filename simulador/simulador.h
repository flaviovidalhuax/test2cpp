#pragma once
#include "../control/sensor.h"
#include <string>

DatosVehiculo generarDatosIniciales();

DatosVehiculo actualizarSimulacion(const DatosVehiculo& datosActuales);