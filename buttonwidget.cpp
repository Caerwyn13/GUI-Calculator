#include "buttonwidget.h"
#include "expressionevaluator.h"
#include "parser.h"

#include <QGridLayout>
#include <QMessageBox>

// Helper function to create and setup buttons
QPushButton* createButton(const QString& text, const QString& stylesheet, const QFont& font, int width, int height, QWidget* parent) {
    QPushButton* button = new QPushButton(text, parent);
    button->setFixedSize(width, height);
    button->setStyleSheet(stylesheet);
    button->setFont(font);
    return button;
}

ButtonWidget::ButtonWidget(QTextEdit *textBox, QWidget *parent) : QWidget(parent), textBox(textBox)
{
    setupUI();

    // Connect buttons
    connect(addText_0, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "0");
    });

    connect(addText_1, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "1");
    });

    connect(addText_2, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "2");
    });

    connect(addText_3, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "3");
    });

    connect(addText_4, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "4");
    });

    connect(addText_5, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "5");
    });

    connect(addText_6, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "6");
    });

    connect(addText_7, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "7");
    });

    connect(addText_8, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "8");
    });

    connect(addText_9, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + "9");
    });

    connect(negate, &QPushButton::clicked, this, [this]() {
        if (this->textBox->toPlainText().endsWith("–"))
        {
            QString tempString = this->textBox->toPlainText();
            this->textBox->setPlainText(tempString.left(tempString.length() - 1));
        }
        else
        {
            this->textBox->setPlainText(this->textBox->toPlainText() + "–");
        }
    });

    connect(addText_plus, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + " + ");
    });

    connect(addText_minus, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + " - ");
    });

    connect(addText_multiply, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + " " + QString::fromUtf8("\U000000D7") + " ");
    });

    connect(addText_divide, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + " " + QString::fromUtf8("\U000000F7") + " ");
    });

    connect(addText_decimal, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText(this->textBox->toPlainText() + ".");
    });

    connect(removeText, &QPushButton::clicked, this, [this]() {
        if (this->textBox->toPlainText().length() != 0) {
            if (this->textBox->toPlainText().endsWith(" ")) {
                this->textBox->setPlainText(this->textBox->toPlainText().chopped(3));
            } else {
                this->textBox->setPlainText(this->textBox->toPlainText().chopped(1));
            }
        }
    });

    connect(clearText, &QPushButton::clicked, this, [this]() {
        this->textBox->setPlainText("");
    });

    connect(evaluate, &QPushButton::clicked, this, [this]() {
        if (!this->textBox->toPlainText().isEmpty())
        {
            QString expression = this->textBox->toPlainText();

            if (ExpressionEvaluator::validateExpression(expression))
            {
                QStringList seperatedExpression = ExpressionEvaluator::splitExpression(expression);
                qDebug() << seperatedExpression; // Print the result to the console

                if (seperatedExpression[0] == "-")
                {
                    QMessageBox::warning(
                        this,
                        tr("Qt Calculator | Warning"),
                        tr("An error has occured when parsing your equation."
                           "\nAn equation cannot begin with an operator."
                           " Use the '+/-' button for negatives."));
                }
                else if (seperatedExpression[0] == "+" || seperatedExpression[0] == "*" || seperatedExpression[0] == "/")
                {
                    QMessageBox::warning(
                        this,
                        tr("Qt Calculator | Warning"),
                        tr("An error has occured when parsing your equation."
                           "\nAn equation cannot begin with an operator."));
                }
                else
                {
                    try
                    {
                        Parser parser;
                        double result = parser.evaluate(seperatedExpression);
                        qDebug() << result;

                        if (result < 0)
                        {
                            this->textBox->setPlainText(QString::fromStdString("–" + std::to_string(std::abs(result))));
                        }
                        else
                        {
                            this->textBox->setPlainText(QString::number(result));
                        }
                    }
                    catch (const std::exception &e)
                    {
                        QMessageBox::warning(
                            this,
                            tr("Qt Calculator | Warning"),
                            tr("An error has occured when parsing your equation."
                               "\n%1").arg(e.what()));
                    }
                }
            }
            else
            {
                QMessageBox::warning(
                    this,
                    tr("Qt Calculator | Warning"),
                    tr("An error has occured when parsing your equation:"
                       "\nEnsure you have no operators directly next to one another and no trailing operators."));
            }
        }
    });
}

void ButtonWidget::setupUI()
{
    // Fonts
    QFont buttonFont("Arial", 14);
    QFont textFont("Monospace", 6);


    // Styles
    QString numberButtonStyle = "QPushButton {"
                                "border-radius: 5px;"
                                "border: 2px solid black;"
                                "background-color: #FFFFFF;"
                                "color: black;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: #CCCCCC;"
                                "}";

    QString operatorButtonStyle = "QPushButton {"
                                  "border-radius: 5px;"
                                  "border: 2px solid black;"
                                  "background-color: #FFFFFF;"
                                  "color: black;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: #CCCCCC;"
                                  "}";

    QString clearButtonStyle = "QPushButton {"
                               "border-radius: 5px;"
                               "border: 2px solid black;"
                               "background-color: #FF0000;"
                               "color: white;"
                               "}"
                               "QPushButton:pressed {"
                               "background-color: #BB0000;"
                               "}";

    QString evaluateButtonStyle = "QPushButton {"
                                  "border-radius: 5px;"
                                  "border: 2px solid black;"
                                  "background-color: #4CAF50;"
                                  "color: black;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: #45A049;"
                                  "}";

    // Grid layout for buttons
    QGridLayout *buttonLayout = new QGridLayout(this);

    // Create and add buttons
    addText_0 = createButton("0", numberButtonStyle, buttonFont, 100, 50, this);
    addText_1 = createButton("1", numberButtonStyle, buttonFont, 100, 50, this);
    addText_2 = createButton("2", numberButtonStyle, buttonFont, 100, 50, this);
    addText_3 = createButton("3", numberButtonStyle, buttonFont, 100, 50, this);
    addText_4 = createButton("4", numberButtonStyle, buttonFont, 100, 50, this);
    addText_5 = createButton("5", numberButtonStyle, buttonFont, 100, 50, this);
    addText_6 = createButton("6", numberButtonStyle, buttonFont, 100, 50, this);
    addText_7 = createButton("7", numberButtonStyle, buttonFont, 100, 50, this);
    addText_8 = createButton("8", numberButtonStyle, buttonFont, 100, 50, this);
    addText_9 = createButton("9", numberButtonStyle, buttonFont, 100, 50, this);

    addText_plus = createButton("+", operatorButtonStyle, buttonFont, 100, 50, this);
    addText_minus = createButton("-", operatorButtonStyle, buttonFont, 100, 50, this);
    addText_multiply = createButton(QString::fromUtf8("\U000000D7"), operatorButtonStyle, buttonFont, 100, 50, this);
    addText_divide = createButton(QString::fromUtf8("\U000000F7"), operatorButtonStyle, buttonFont, 100, 50, this);
    addText_decimal = createButton(".", operatorButtonStyle, buttonFont, 100, 50, this);
    negate = createButton("+/-", operatorButtonStyle, buttonFont, 100, 50, this);

    removeText = createButton(QString::fromUtf8("\U0000232B"), numberButtonStyle, buttonFont, 100, 50, this);
    clearText = createButton("C", clearButtonStyle, buttonFont, 100, 50, this);
    evaluate = createButton("=", evaluateButtonStyle, buttonFont, 100, 50, this);

    copyright = new QLabel(this);
    copyright->setStyleSheet("font: 8pt;");
    copyright->setText("©2024\nCaerwyn Sabin-Rees\nAll rights reserved.");
    copyright->setFont(textFont);

    // Add buttons to layout from top-left to bottom-right
    buttonLayout->addWidget(copyright, 1, 1);
    buttonLayout->addWidget(addText_decimal, 1, 2);
    buttonLayout->addWidget(negate, 1, 3);
    buttonLayout->addWidget(evaluate, 1, 4);
    buttonLayout->addWidget(addText_1, 2, 1);
    buttonLayout->addWidget(addText_2, 2, 2);
    buttonLayout->addWidget(addText_3, 2, 3);
    buttonLayout->addWidget(addText_divide, 2, 4);
    buttonLayout->addWidget(addText_4, 3, 1);
    buttonLayout->addWidget(addText_5, 3, 2);
    buttonLayout->addWidget(addText_6, 3, 3);
    buttonLayout->addWidget(addText_multiply, 3, 4);
    buttonLayout->addWidget(addText_7, 4, 1);
    buttonLayout->addWidget(addText_8, 4, 2);
    buttonLayout->addWidget(addText_9, 4, 3);
    buttonLayout->addWidget(addText_minus, 4, 4);
    buttonLayout->addWidget(clearText, 5, 1);
    buttonLayout->addWidget(addText_0, 5, 2);
    buttonLayout->addWidget(removeText, 5, 3);
    buttonLayout->addWidget(addText_plus, 5, 4);
}
