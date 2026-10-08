#include <dashboard.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sensor.h>


void LimpiarPantalla(){
    system("cls");
}
std::string FormatearDouble(double valor, int decimales){
    std::ostringstream output;
    output << std::fixed << std::setprecision(decimales) << valor;
    return output.str();
}
std::string AgregarDecorador(TipoDecorador_Dashboard tipoImpresion, std::string textoImpresion = ""){
    std::string tipoDecorador;
    switch(tipoImpresion){
        case TipoDecorador_Dashboard::ASTERISCOS:
            tipoDecorador = "********************************************************" + std::string("\n");
        break;
        case TipoDecorador_Dashboard::LINEA_PUNTEADA:
            tipoDecorador = "--------------------------------------------------------" + std::string("\n");
        break;
        case TipoDecorador_Dashboard::TEXTO_EN_MEDIO:
            tipoDecorador = "*********           " + textoImpresion +  "           *********";
            if(tipoDecorador.length() > 56){
                int maxLenght = 56;
                int counterLen =tipoDecorador.length();
                int excesoRecortar =  ((maxLenght - counterLen) % 2 == 0.5) ?  ((maxLenght - counterLen) + 1)/2 : (maxLenght - counterLen)/2;
                tipoDecorador = tipoDecorador.substr(maxLenght, excesoRecortar).substr(0,excesoRecortar);
            }
        break;
        case TipoDecorador_Dashboard::SALTO_LINEA:
            tipoDecorador = std::string("\n");
        break;                
    }
    return tipoDecorador;
}
std::string CrearBarrar(double& valorSensor, double limiteInferior, double limiteSuperior, int anchoBarra = 20){
    valorSensor = valorSensor < limiteInferior ? limiteInferior : valorSensor;
    valorSensor = valorSensor > limiteSuperior ? limiteSuperior : valorSensor;

    double proporcion = (valorSensor - limiteInferior)/(limiteSuperior - limiteInferior);
    int redondearUpside = static_cast<int>(proporcion*anchoBarra + 0.3);
    redondearUpside = redondearUpside < 0 ? 0: redondearUpside; 
    redondearUpside = redondearUpside > anchoBarra ? anchoBarra: redondearUpside; 
    
    std::string barraImprimir;
    for(int i = 0; i < redondearUpside; i++){
        barraImprimir += "█";
    }
    for(int i = redondearUpside; i < anchoBarra; i++){
        barraImprimir += "░";
    }
    return barraImprimir;
}
void ImprimirBarraConFormato(const std::string& contenidoGrafica ){
    const int Ancho_interno = 60;
    std::string texto = contenidoGrafica;
    if(static_cast<int>(texto.length()) > Ancho_interno){
        texto = texto.substr(0,Ancho_interno);
    }
    std::cout << "||" << std::left << std::setw(Ancho_interno) << texto << "\n";
}
RangosPermitidos RetornarLimitesSensores(std::string nombreSensor){
   RangosPermitidos rangos;
   if (nombreSensor == "presionAceite") {
        rangos.RangoInferior = static_cast<double>(SignalMin::Psi);
        rangos.RangoSuperior = static_cast<double>(SignalMax::Psi);
    } else if (nombreSensor == "velocidad") {
        rangos.RangoInferior = static_cast<double>(SignalMin::Vel);
        rangos.RangoSuperior = static_cast<double>(SignalMax::Vel);
    } else if (nombreSensor == "rpm") {
        rangos.RangoInferior = static_cast<double>(SignalMin::RPM);
        rangos.RangoSuperior = static_cast<double>(SignalMax::RPM);
    } else if (nombreSensor == "temperatura") {
        rangos.RangoInferior = static_cast<double>(SignalMin::Temp);
        rangos.RangoSuperior = static_cast<double>(SignalMax::Temp);
    } else if (nombreSensor == "voltajeBateria") {
        rangos.RangoInferior = static_cast<double>(SignalMin::Volt);
        rangos.RangoSuperior = static_cast<double>(SignalMax::Volt);
    } 
    return rangos;
}
GraficaValores_Sensores GenerarGraficas(DatosVehiculo datosSensores){
    GraficaValores_Sensores representacionGraficaSensores;
    RangosPermitidos rangosSensores;
    
    rangosSensores = RetornarLimitesSensores("presionAceite");
    representacionGraficaSensores.lineaSensorPresionAceite = 
    "PRESION ACEITE:         "  +CrearBarrar(datosSensores.presionAceite, rangosSensores.RangoInferior, rangosSensores.RangoSuperior);
    
    rangosSensores = RetornarLimitesSensores("rpm");
    representacionGraficaSensores.lineaSensorRpm = 
    "REVOLUCIONES POR MIN:   "  +CrearBarrar(datosSensores.presionAceite, rangosSensores.RangoInferior, rangosSensores.RangoSuperior);
    
    rangosSensores = RetornarLimitesSensores("temperatura");
    representacionGraficaSensores.lineaSensorTemperatura = 
    "TEMPERATURA:            "  +CrearBarrar(datosSensores.presionAceite, rangosSensores.RangoInferior, rangosSensores.RangoSuperior);
    
    rangosSensores = RetornarLimitesSensores("voltajeBateria");
    representacionGraficaSensores.lineaSensorVoltajeBateria =
    "VOLTAJE:                "  + CrearBarrar(datosSensores.presionAceite, rangosSensores.RangoInferior, rangosSensores.RangoSuperior);
    
    rangosSensores = RetornarLimitesSensores("velocidad");
    representacionGraficaSensores.lineaSensorVelocidad = 
    "VELOCIDAD:              "  + CrearBarrar(datosSensores.presionAceite, rangosSensores.RangoInferior, rangosSensores.RangoSuperior);

    return representacionGraficaSensores;
}
void MostrarGraficas_Dashboard(GraficaValores_Sensores valoresGrafica){
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::TEXTO_EN_MEDIO, "GRAFICAS") << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);

    ImprimirBarraConFormato(valoresGrafica.lineaSensorPresionAceite);
    ImprimirBarraConFormato(valoresGrafica.lineaSensorRpm);
    ImprimirBarraConFormato(valoresGrafica.lineaSensorTemperatura);
    ImprimirBarraConFormato(valoresGrafica.lineaSensorVelocidad);
    ImprimirBarraConFormato(valoresGrafica.lineaSensorVoltajeBateria);

    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::TEXTO_EN_MEDIO, "GRAFICAS") << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
}
void mostrarValores_Dashboard(DatosVehiculo datosSensores){
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::TEXTO_EN_MEDIO, "VALOR SENSORES") << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);


        std::cout << "\n=== ESTADO ACTUAL DE SENALES ===" << std::endl;
        std::cout << "Presion aceite: " << datosSensores.presionAceite << "PSI" << std::endl;
        std::cout << "RPM: " << datosSensores.rpm << " rpm" << std::endl;
        std::cout << "Temperatura: " << datosSensores.temperatura << " C" << std::endl;
        std::cout << "Velocidad: " << datosSensores.velocidad << " km/h" << std::endl;      
        std::cout << "Voltaje: " << datosSensores.voltajeBateria << " V" << std::endl;

    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::TEXTO_EN_MEDIO, "VALOR SENSORES") << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
    std::cout << AgregarDecorador(TipoDecorador_Dashboard::ASTERISCOS) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA) << AgregarDecorador(TipoDecorador_Dashboard::SALTO_LINEA);
}