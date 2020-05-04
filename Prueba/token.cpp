#include "QToken.h"

QToken::QToken(QString lexema,QString granema)
{
    this->lexema=lexema;
    this->granema=granema;
}

QString QToken::getLexema()
{
    return this->lexema;
}

QString QToken::getGranema()
{
    return this->granema;
}

void QToken::setLexema(QString lexema)
{
    this->lexema=lexema;
}

void QToken::setGranema(QString granema)
{
    this->granema=granema;
}

