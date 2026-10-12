
#include "../control/sensor.h"

std::string estatusSenalAtexto(Estatus est);

std::string formatearDouble(double valor, int decimales);

bool esNumero(const std::string &str);

void TransferirDatos(const DatosVehiculo& datos, Mensaje& msj);
bool ValidarDatos(Mensaje& msj, RangosParametros& rango);
