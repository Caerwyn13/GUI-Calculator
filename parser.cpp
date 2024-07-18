#include "parser.h"
#include <stdexcept>
#include <iostream>

// NumberNode Implementation
NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate() const {
    return value;
}

// OperatorNode Implementation
OperatorNode::OperatorNode(char op, ASTNodePtr left, ASTNodePtr right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

double OperatorNode::evaluate() const {
    double leftValue = left->evaluate();
    double rightValue = right->evaluate();

    switch (op) {
    case '+':
        return leftValue + rightValue;
    case '-':
        return leftValue - rightValue;
    case '*':
        return leftValue * rightValue;
    case '/':
        if (rightValue == 0) {
            throw std::runtime_error("Division by zero");
        }
        return leftValue / rightValue;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

// Parser Implementation
double Parser::evaluate(const QStringList& expression) {
    QList<QVariant> variantList = convertToQList(expression);
    QList<Token> tokens = tokenise(variantList);
    ASTNodePtr ast = parseExpression(tokens);
    return ast->evaluate();
}

QList<QVariant> Parser::convertToQList(const QStringList& stringList) {
    QList<QVariant> variantList;

    for (const QString& str : stringList) {
        bool ok;
        double number;

        // Try to convert to double
        number = str.toDouble(&ok);
        if (ok) {
            // Conversion to double succeeded
            variantList.append(QVariant(number));
        } else {
            // Conversion to double failed
            if (!str.isEmpty()) {
                QChar firstChar = str.at(0);
                if (firstChar == QChar(0x2013) || firstChar == '-') {
                    // Check if the first character is '–' (en dash) or '-'
                    QString numberStr = str.mid(1); // Extract substring without the '-' or '–'
                    number = numberStr.toDouble(&ok);
                    if (ok) {
                        // Conversion to double succeeded after removing '-' or '–'
                        variantList.append(QVariant(-number));
                    } else {
                        // Conversion to double failed even after removing '-' or '–'
                        variantList.append(QVariant(str)); // Append original string
                    }
                } else {
                    // First character is neither '–' nor '-'
                    variantList.append(QVariant(str)); // Append original string
                }
            } else {
                // String is empty, append as is
                variantList.append(QVariant(str));
            }
        }
    }

    qDebug() << "Variant List: " << variantList;
    return variantList;
}

QList<Token> Parser::tokenise(const QList<QVariant>& expression) {
    QList<Token> tokens;
    for (const QVariant& item : expression) {
        if (item.typeId() == QMetaType::Double) {
            tokens.append({Number, item.toDouble()});
            std::cout << "Tokenised number: " << item.toDouble() << std::endl;
        } else if (item.typeId() == QMetaType::QString) {
            QString str = item.toString();
            QChar ch = str.at(0);
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                tokens.append({Operator, ch});
                std::cout << "Tokenised operator: " << ch.toLatin1() << std::endl;
            } else {
                throw std::runtime_error("Unknown operator");
            }
        } else {
            throw std::runtime_error("Invalid token");
        }
    }
    return tokens;
}

int Parser::getPrecedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

std::shared_ptr<ASTNode> Parser::parseExpression(const QList<Token>& tokens) {
    QStack<std::shared_ptr<ASTNode>> values;
    QStack<char> ops;

    auto applyOperator = [&values, &ops]() {
        char op = ops.pop();
        auto right = values.pop();
        auto left = values.pop();
        std::cout << "Applying operator: " << op << " on values: " << left->evaluate() << " and " << right->evaluate() << std::endl;
        values.push(std::make_shared<OperatorNode>(op, left, right));
    };

    for (const Token& token : tokens) {
        if (token.type == Number) {
            values.push(std::make_shared<NumberNode>(token.value.toDouble()));
            std::cout << "Pushed number: " << token.value.toDouble() << " to values stack" << std::endl;
        } else if (token.type == Operator) {
            while (!ops.isEmpty() && getPrecedence(ops.top()) >= getPrecedence(token.value.toChar().toLatin1())) {
                applyOperator();
            }
            ops.push(token.value.toChar().toLatin1());
            std::cout << "Pushed operator: " << token.value.toChar().toLatin1() << " to ops stack" << std::endl;
        }
    }

    while (!ops.isEmpty()) {
        applyOperator();
    }

    // Debugging: Print final state of the stacks
    std::cout << "Final values stack size: " << values.size() << std::endl;
    std::cout << "Final ops stack size: " << ops.size() << std::endl;
    if (!values.isEmpty()) {
        auto resultNode = values.top();
        std::cout << "Result: " << resultNode->evaluate() << std::endl;
    }

    return values.top();
}
