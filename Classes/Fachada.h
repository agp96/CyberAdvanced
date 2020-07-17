//
// Created by agpal on 13/07/2020.
//

#ifndef PROJ_ANDROID_FACHADA_H
#define PROJ_ANDROID_FACHADA_H

class Fachada {
public:
    static Fachada* getInstance();

    void cambiarEstado(int cambiaEstado);
    int getEstado();

private:
    static Fachada *instance;
    Fachada();

    int estado;
};


#endif //PROJ_ANDROID_FACHADA_H
