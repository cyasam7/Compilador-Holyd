#ifndef QVARIABLE_H
#define QVARIABLE_H
#include <QString>

class QVariable
{

public:
    QString contenido;
    QString valor;
    QString tipo;
    QVariable(QString contenido,QString valor,QString tipo);
    QVariable();

    QString getContenido();
    QString getValor();
    QString getTipo();
    void setContenido(QString contenido);
    void setValor(QString valor);
    void setTipo(QString tipo);
};

#endif // QVARIABLE_H
