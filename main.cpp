#include <iostream>
#include <string>
#include <dashboard.h>
#include <logger.h>
#include <thread>
#include <chrono>
#include "gateway/edo.h"
#include "simulador/simulador.h"
#include "gateway/ECUGateway.h"
#include "control/control.h"

namespace {
DatosVehiculo datosDesdeGateway(const Mensaje& msj) {
    return {
        msj.Velocidad.param,
        static_cast<int>(msj.RPM.param),
        msj.Temperatura.param,
        msj.VoltajeBateria.param,
        msj.PresionAceite.param
    };
}
}

int main() {
    DatosVehiculo datos = generarDatosIniciales();
    EstadoECU estado = EstadoECU::INIT;
    const long long ciclosMaximos = 300;
    long long cicloActual = 0;
    Mensaje msj;
    RangosParametros rango;
    rango = inicializarParametros(msj);

    inicializarLogger("gateway_log.csv");
    registrarEventos(EventoLogger::INFO, "MAIN", "Inicia la simulacion");

    while (cicloActual < ciclosMaximos) {
        datos = actualizarSimulacion(datos);
        TransferirDatos(datos, msj);
        const bool datosValidos = ValidarDatos(msj, rango);
        const int siguienteEstado = validarRangos(msj, rango);
        const EstadoECU estadoAnterior = estado;
        estado = calcularNuevoEstado(estado, msj, siguienteEstado);

        const DatosVehiculo datosGateway = datosDesdeGateway(msj);
        registrarDatosSensores(datosGateway, estado);
        if (estado != estadoAnterior) {
            registrarEventos(EventoLogger::INFO, "ECU_CONTROL",
                "Estado cambiado de " + estadoAtexto(estadoAnterior) + " a " + estadoAtexto(estado));
        }
        if (!datosValidos) {
            registrarEventos(EventoLogger::WARN, "ECU_GATEWAY", "Una o mas senales recibidas estan fuera de rango");
        }

        LimpiarPantalla();
        std::cout << "Datos recibidos desde ECU Gateway" << std::endl;
        std::cout << "Estado ECU: " << estadoAtexto(estado) << std::endl;
        mostrarValores_Dashboard(datosGateway);
        MostrarGraficas_Dashboard(GenerarGraficas(datosGateway));

        cicloActual++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Se ha terminado la ejecucion" << std::endl;
    registrarEventos(EventoLogger::INFO, "MAIN", "Termina la simulacion");
    cerrarLogger();
    return 0;
}
