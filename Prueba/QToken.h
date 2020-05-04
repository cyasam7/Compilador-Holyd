#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
class QToken
{
private:
    QString contenido;
    int estado;
public:
    QToken(QString contenido,int estado);
    QToken(QString contenido);
    QToken(int estado);

    QString getContenido();
    int getEstado();
    void setContenido(QString lexema);
    void setEstado(int granema);
};

#endif // TOKEN_H
