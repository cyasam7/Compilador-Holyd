#include "QTablaSemantica.h"
#include "mainwindow.h"
#include "QToken.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
QTablaSemantica::QTablaSemantica()
{

}
void QTablaSemantica::InsertarCuadruplo(QString operando, QString op1, QString op2, QString res){
    QCuadruplo cuadruplo;
    if(operando == "="){
        cuadruplo = QCuadruplo(operando,op1,"null",res);
    }else{
        cuadruplo = QCuadruplo(operando,op1,op2,res);
    }
    this->contador++;
    this->tabla.append(cuadruplo);
}
void QTablaSemantica::InsertarCuadruploSF(QString operando, QString op1){
    QCuadruplo cuadruplo = QCuadruplo(operando,op1,"null","?");
    this->contador++;
    this->tabla.append(cuadruplo);
}
void QTablaSemantica::InsertarCuadruploSI(QString operando,QString res){
    QCuadruplo cuadruplo = QCuadruplo(operando,"null","null",res);
    this->contador++;
    this->tabla.append(cuadruplo);
}
void QTablaSemantica::InsertarRead(QString operando,QString res){
    QCuadruplo cuadruplo = QCuadruplo(operando,"null","null",res);
    this->contador++;
    this->tabla.append(cuadruplo);
}
void QTablaSemantica::Rellenar(int direccion, QString valor){
    QCuadruplo sustitucion = QCuadruplo(this->tabla.value(direccion).getOperando(),
                                        this->tabla.value(direccion).getOperador1(),
                                        this->tabla.value(direccion).getOperador2(),
                                        valor);
    this->tabla.replace(direccion,sustitucion);
}
void QTablaSemantica::MostrarCuadruplos(){
    for (int var = 0; var < this->tabla.length(); ++var) {
     //   qDebug()<<var+1<<this->tabla.value(var).getOperando()<<" "<<this->tabla.value(var).getOperador1()<<" "<<this->tabla.value(var).getOperador2()<<" "<<this->tabla.value(var).getResultado();
    }
}
void QTablaSemantica::limpiarTabla(){
    this->tabla.clear();
}
QString QTablaSemantica::getSaltoIncondicionar(){
    return this->SALTOINCONDICIONAL;
}
QString QTablaSemantica::getSaltoFalso(){
    return  this->SALTOFALSO;
}
QString QTablaSemantica::getSaltoVerdadero(){
    return this->SALTOVERDADERO;
}
int QTablaSemantica::getContador(){
    return this->contador;
}
QQueue<QCuadruplo> QTablaSemantica::getTabla(){
    return this->tabla;
}
