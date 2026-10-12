# ECU

Es la segunda versión funcional de una plataforma vehicular simulada formada por una Gateway ECU  y una Control ECU.



Utiliza las siguientes señales:\
Velocidad\
Normales: 0 hasta 240\
Alerta: -0 o +270\
Críticos: -10 o +300

Revoluciones por minuto (RPM)\
Rangos físicos posibles en: revoluciones por minuto\
Normales: 0 hasta 5000\
Alerta: -0 o +6000\
Críticos: -100 o +7000

Temperatura\
Rangos físicos posibles en: temperatura\
Normales: -20 hasta 110\
Alerta: -30 o +125\
Críticos: -40 o +145

Voltaje de bateria\
Rangos físicos posibles en: batería baja potencia\
Normales: 11 hasta 15\
Alerta: -10.5 o +15.5\
Críticos: -10 o +16

Presion de aceite\
Rangos físicos posibles en: Bateria de alto voltaje\
Normales: 0.5 hasta 5\
Alerta: 0.2 o 0.3\
Críticos: 0.1 o +6


La maquina usa los siguientes estados:\
INIT Inicialización de variables y configuración.


SELF\_TEST Autoprueba antes de operar.

OPERATIONAL Todas las señales son válidas y normales.

DEGRADED Existe advertencia o falla menor.

SAFE\_STATE Existe una condición crítica.

SHUTDOWN Apagado controlado del sistema.

Arquitectura implementada:

- Capa de simulacion: En esta capa se generan los valores de cada una de las señales que seran clasificadas en la ECU Gateway.

- Capa Ecu Gateway: En esta capa se reciben las señales y se clasifican, asignando estatus a los valores mediante un ojeto struct.

- Capa ECU Control: En esta capa se toman las deciciones para detectar el estatus actual, interpretar los estatus de las señaes leidas y controlar el cabio de estado de la maquina.

- Capa panel: En esta capa se muestran en impresion los valores de las señales y sus estatus.


Para complilar el proyecto ejecutar el siguiente comando:\
g++ main.cpp gateway/edo.cpp control/sensor.cpp gateway/ECUGateway.cpp control/control.cpp simulador/simulador.cpp -o main.exe

Ejecutar el exe:\
./main.exe


El iniciar el sistema:\

- Se instancian las variables escenciales para el funcionamiento.
- Se actualizan los valores para cada una de las señales.
- Se envian a la ECUGateway para clasificar los valores y sus estatus por señal.
- Despues son enviadas a la ECUControl para determinar el cambio de estado.
- Con la variable struct se envian al panel para imprimir en pantalla el comportamiento de las señales.

