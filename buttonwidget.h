#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

class ButtonWidget : public QWidget
{
    Q_OBJECT

public:
    ButtonWidget(QTextEdit *textBox, QWidget *parent = nullptr);

private:
    QPushButton *addText_0;
    QPushButton *addText_1;
    QPushButton *addText_2;
    QPushButton *addText_3;
    QPushButton *addText_4;
    QPushButton *addText_5;
    QPushButton *addText_6;
    QPushButton *addText_7;
    QPushButton *addText_8;
    QPushButton *addText_9;
    QPushButton *addText_plus;
    QPushButton *addText_minus;
    QPushButton *addText_multiply;
    QPushButton *addText_divide;
    QPushButton *addText_decimal;
    QPushButton *negate;            // Allows for negative numbers
    QPushButton *removeText;        // Removes most recent char
    QPushButton *clearText;         // Clears textbox
    QPushButton *evaluate;

    QTextEdit *textBox;

    QLabel *copyright;

    void setupUI();
};

#endif // BUTTONWIDGET_H
