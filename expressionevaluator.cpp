#include "expressionevaluator.h"

#include <QRegularExpression>

//! Fix to allow it to work with negative integers w/out using '+/-' operator
QStringList ExpressionEvaluator::splitExpression(const QString& expression)
{
    // Regular expression to match numbers, operators, and spaces, including negative numbers and brackets
    static const QRegularExpression re("(–?[0-9]*\\.?[0-9]+)|([+\\-×÷()]|\\s+)");
    QRegularExpressionMatchIterator i = re.globalMatch(expression);
    QStringList result;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString captured = match.captured(0).trimmed(); // Trim to remove surrounding spaces

        // Replace × with *
        if (captured == "×") {
            captured = "*";
        }
        // Replace ÷ with /
        else if (captured == "÷") {
            captured = "/";
        }
        // Ignore whitespace tokens
        else if (captured.isEmpty()) {
            continue;
        }
        // Remove brackets
        else if (captured.startsWith("(") || captured.endsWith(")")) {
            captured = captured.mid(1, captured.length() - 2); // Remove the brackets
        }
        else if (captured.startsWith("-") || captured.startsWith("–")) {
            captured = captured.replace(0, 1, "-");
        }

        result << captured;
    }

    return result;
}

bool ExpressionEvaluator::validateExpression(QString& expression)
{
    // Regular expression to detect multiple operators in a row
    static const QRegularExpression multipleOperatorsRe("[+\\-×÷]{2,}");

    // Simplifying expression
    expression = expression.simplified();
    expression.replace(" ", "");

    // Check for multiple operators in a row
    if (expression.contains(multipleOperatorsRe)) { return false; }

    // Checks if expression ends in an operator
    static const QRegularExpression trailingOperatorRe("[+×÷-]$");
    QRegularExpressionMatch match = trailingOperatorRe.match(expression);

    if (match.hasMatch()) { return false; }

    return true;
}
