#include<QCuadruplo.h>

QCuadruplo::QCuadruplo()
{

}
QCuadruplo::QCuadruplo(QString ope,QString op1,QString op2,QString res){
    this->operando = ope;
    this->operador1= op1;
    this->operador2 = op2;
    this->resultado = res;
}

QString QCuadruplo::getOperando(){
    return this->operando;
}
void QCuadruplo::setOperando(QString ope){
    this->operando=ope;
}
QString QCuadruplo::getOperador1(){
    return this->operador1;
}
void QCuadruplo::setOperador1(QString op1){
    this->operador1= op1;
}
QString QCuadruplo::getOperador2(){
    return this->operador2;
}
void QCuadruplo::setOperador2(QString op2){
    this->operador2= op2;
}
QString QCuadruplo::getResultado(){
    return this->resultado;
}
void QCuadruplo::setResultado(QString res){
    this->resultado= res;
}
