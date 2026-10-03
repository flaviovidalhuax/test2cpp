
#pragma once
#include "sensor.h"
#include <string>

DatosVehiculo generarDatosIniciales();

DatosVehiculo acelerar(const DatosVehiculo& datosActuales);

DatosVehiculo frenos(const DatosVehiculo& datosActuales);

DatosVehiculo sistemError(const DatosVehiculo& datosActuales);
