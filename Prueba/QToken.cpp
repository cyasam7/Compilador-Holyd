#include "QToken.h"

QToken::QToken(QString contenido,int estado)
{
    this->contenido=contenido;
    this->estado=estado;
}
QToken::QToken(QString contenido){
    this->contenido=contenido;
}
QToken::QToken(int estado){
    this->estado=estado;
}
QString QToken::getContenido()
{
    return this->contenido;
}

int QToken::getEstado()
{
    return this->estado;
}

void QToken::setContenido(QString contenido)
{
    this->contenido=contenido;
}

void QToken::setEstado(int estado)
{
    this->estado=estado;
}
