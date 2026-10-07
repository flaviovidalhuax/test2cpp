#include <iostream>
#include <string>
#include "gateway/edo.h"
#include <dashboard.h>


int main() {

      EstadoECU estado = EstadoECU::INIT;
    
    std::cout << "hello" << "\n";
     std::cout << estadoAtexto(estado);
    return 0;
}