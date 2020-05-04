#ifndef TOKEN_H
#define TOKEN_H

class QToken
{
private:
    QString lexema;
    QString granema;
public:
    QToken(QString lexema,QString granema);
    QString getLexema();
    QString getGranema();
    void setLexema(QString lexema);
    void setGranema(QString granema);
};

#endif // TOKEN_H
