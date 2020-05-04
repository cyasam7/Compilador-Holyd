#ifndef QTABLASEMANTICA_H
#define QTABLASEMANTICA_H
#include "QCuadruplo.h"
#include "QString"
#include <QQueue>
class QTablaSemantica
{

public:
    int contador=1;
    QTablaSemantica();
    void InsertarCuadruplo(QString operando, QString op1, QString op2, QString res);
    void InsertarCuadruploSF(QString operando, QString op1);
    void InsertarCuadruploSI(QString operando, QString res);
    void InsertarRead(QString operando, QString res);
    void Rellenar(int direccion, QString valor);
    void MostrarCuadruplos();
    QString getSaltoIncondicionar();
    QString getSaltoVerdadero();
    QString getSaltoFalso();
    QQueue<QCuadruplo> getTabla();
    void limpiarTabla();
    int getContador();

private:
    QQueue<QCuadruplo> tabla;
    QString SALTOINCONDICIONAL="SI";
    QString SALTOVERDADERO="SV";
    QString SALTOFALSO="SF";
};

#endif // QTABLASEMANTICA_H
