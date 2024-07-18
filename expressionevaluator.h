#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include <QString>
#include <QStringList>

class ExpressionEvaluator
{
public:
    static QStringList splitExpression(const QString& expression);
    static bool validateExpression(QString& expression);
};

#endif // EXPRESSIONEVALUATOR_H
