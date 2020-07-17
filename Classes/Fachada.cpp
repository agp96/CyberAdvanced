//
// Created by agpal on 13/07/2020.
//

#include <cocos/platform/CCStdC.h>
#include "Fachada.h"

Fachada* Fachada::instance = NULL;

Fachada::Fachada() {
}

Fachada* Fachada::getInstance() {
    if(instance==NULL) {
        instance = new Fachada();
    }
    return instance;
}


void Fachada::cambiarEstado(int cambiaEstado){
    estado = cambiaEstado;
}

int Fachada::getEstado(){
    return estado;
}
