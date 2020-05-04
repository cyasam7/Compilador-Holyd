#include "QVariable.h"

QVariable::QVariable(QString contenido,QString valor,QString tipo)
{
    this->contenido=contenido;
    this->valor=valor;
    this->tipo=tipo;
}
QVariable::QVariable()
{
}
QString QVariable::getContenido()
{
    return this->contenido;
}

QString QVariable::getValor()
{
    return this->valor;
}

void QVariable::setContenido(QString contenido)
{
    this->contenido=contenido;
}

void QVariable::setValor(QString valor)
{
    this->valor=valor;
}
QString QVariable::getTipo(){
    return this->tipo;
}
void QVariable::setTipo(QString t){
    this->tipo=t;
}
