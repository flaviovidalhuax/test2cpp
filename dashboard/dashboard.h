#pragma once
#include <string>
#include <sensor.h>
#include <edo.h>
#include <control.h>

struct GraficaValores_Sensores{
    std::string lineaSensorVelocidad;
    std::string lineaSensorRpm;
    std::string lineaSensorTemperatura;
    std::string lineaSensorVoltajeBateria;
    std::string lineaSensorPresionAceite;    
};
enum class TipoDecorador_Dashboard{
    LINEA_PUNTEADA,
    ASTERISCOS,
    TEXTO_EN_MEDIO,
    SALTO_LINEA
};
struct RangosPermitidos{
    double RangoSuperior;
    double RangoInferior;
};


void LimpiarPantalla();
std::string AgregarDecorador(TipoDecorador_Dashboard tipoImpresion, std::string textoImpresion);
std::string FormatearDouble(double valor, int decimales);
std::string CrearBarrar(double& valorSensor, double limiteInferior, double limiteSuperior, int anchoBarra);
void ImprimirBarraConFormato(const std::string& contenidoGrafica );
void mostrarValores_Dashboard(DatosVehiculo datosSensores);
void MostrarGraficas_Dashboard(GraficaValores_Sensores valoresGrafica);
GraficaValores_Sensores GenerarGraficas(DatosVehiculo datosSensores);
RangosPermitidos RetornarLimitesSensores(std::string nombreSensor);
void MostrarLimitesRangos(Mensaje& msj, RangosParametros& rango);