#ifndef QCUADRUPLO_H
#define QCUADRUPLO_H

#include <QString>
class QCuadruplo
{
private:
    QString operando;
    QString operador1;
    QString operador2;
    QString resultado;
public:
    QCuadruplo();
    QCuadruplo(QString ope,QString op1,QString op2,QString res);

    QString getOperando();
    QString getOperador1();
    QString getOperador2();
    QString getResultado();
    void setOperando(QString ope);
    void setOperador1(QString op1);
    void setOperador2(QString op2);
    void setResultado(QString res);
};

#endif // QCUADRUPLO_H
