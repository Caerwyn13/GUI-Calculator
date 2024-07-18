#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QStack>
#include <memory>

enum TokenType {
    Number,
    Operator
};

struct Token {
    TokenType type;
    QVariant value;
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

class NumberNode : public ASTNode {
public:
    NumberNode(double value);
    double evaluate() const override;

private:
    double value;
};

class OperatorNode : public ASTNode {
public:
    OperatorNode(char op, ASTNodePtr left, ASTNodePtr right);
    double evaluate() const override;

private:
    char op;
    ASTNodePtr left;
    ASTNodePtr right;
};

class Parser {
public:
    double evaluate(const QStringList& expression);

private:
    QList<QVariant> convertToQList(const QStringList& expression);
    QList<Token> tokenise(const QList<QVariant>& expression);
    int getPrecedence(char op);
    ASTNodePtr parseExpression(const QList<Token>& tokens);
};

#endif // PARSER_H
