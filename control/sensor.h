#pragma once
#include <iostream>
#include <array>

struct DatosVehiculo{
    double velocidad;
    int rpm;
    double temperatura;
    double voltajeBateria;
    double presionAceite;
};

bool validarVelocidad(double velocidad);

bool validarRPM(int rpm);

bool validarTemperatura(double temperatura);

bool validarVoltaje(double voltaje);

bool validarPresion(double presion);

enum class Estatus{
    OK,
    WARNING,
    ERROR,
    MISSING
};

struct parametro{

    std::string nombre;
    std::string unidades;
    std::string codigo;
    float param;
    std::string ECUorigen;
    std::string ECUdestino;
    bool valido;
    Estatus estatus;
    void set(std::string nom, std::string un, std::string cod, float p=0, std::string orig="ECUEngine", std::string dest="ECUControl", bool v = true, Estatus es = Estatus::OK) {
        nombre = nom;
        unidades = un;
        codigo = cod;
        param = p;
        ECUorigen = orig;
        ECUdestino = dest;
        valido = v;
        estatus = es;
    }
};

struct Mensaje{

    parametro Velocidad;
    parametro RPM;
    parametro Temperatura;
    parametro VoltajeBateria;
    parametro PresionAceite;
    std::array<parametro*, 5> signals(Mensaje& msj){
        return {
            &msj.Velocidad,
            &msj.RPM,
            &msj.Temperatura,
            &msj.VoltajeBateria,
            &msj.PresionAceite
        };
    }
};

struct Rangos{

    float maxOperative;
    float minOperative;
    float maxWarning;
    float minWarning;
    float maxCritical;
    float minCritical;

    void set(float MaxO, float MaxW, float MaxC, float MinC=0, float MinW=0, float MinO=0){
        maxOperative=MaxO;
        minOperative=MinO;
        maxWarning=MaxW;
        minWarning=MinW;
        maxCritical=MaxC;
        minCritical=MinC;
    }
 };

 struct RangosParametros{

    Rangos Velocidad;
    Rangos RPM;
    Rangos Temperatura;
    Rangos VoltajeBateria;
    Rangos PresionAceite;

    std::array<Rangos*, 5> limites(RangosParametros& ran){
        return {
            &ran.Velocidad,
            &ran.RPM,
            &ran.Temperatura,
            &ran.VoltajeBateria,
            &ran.PresionAceite
        };
    }
 };
 
 struct acciones{

        std::string velocidad;
        std::string aceleracion;
        std::string rpm;
        std::string temperatura;
        std::string voltajeBateria;
        std::string presionAceite;
        void set(std::string v, std::string a, std::string r, std::string t, std::string bl, std::string bh){
            velocidad = v;
            aceleracion = a;
            rpm = r;
            temperatura = t;
            voltajeBateria = bl;
            presionAceite = bh;
        }
};

struct accionesControl{
        acciones limitacion;
        acciones critico;
        acciones causa;
        std::array<acciones*, 6> deciciones(accionesControl& a){
        return {
            &a.limitacion,
            &a.critico,
            &a.causa
        };
    }
};

const RangosParametros inicializarParametros(Mensaje& msj);

enum class SignalMinO         { Vel = 0,   RPM = 0,    Temp = -20, Psi = 44, Volt = 11 };
enum class SignalMaxO        { Vel = 240, RPM = 5000, Temp = 110, Psi = 54, Volt = 15 };
enum class SignalMinWarning  { Vel = 0,   RPM = 500,  Temp = -30, Psi = 40, Volt = 11 };
enum class SignalMaxWarning  { Vel = 255, RPM = 6000, Temp = 125, Psi = 56, Volt = 16 };
enum class SignalMinCritical { Vel = -10, RPM = 0,    Temp = -40, Psi = 39, Volt = 10 };
enum class SignalMaxCritical { Vel = 300, RPM = 7000, Temp = 145, Psi = 58, Volt = 17 };