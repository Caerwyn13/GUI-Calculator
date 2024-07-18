#include "mainwindow.h"
#include "buttonwidget.h"

#include <QFont>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) //, ui(new Ui::MainWindow)
{
    // Fonts
    QFont textFont("Arial", 12, QFont::Bold);

    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Input box
    QTextEdit *textBox = new QTextEdit(this);
    textBox->setAlignment(Qt::AlignRight);
    textBox->setReadOnly(true);
    textBox->setFont(textFont);
    textBox->setFontPointSize(41);
    layout->addWidget(textBox);

    // Add Buttons
    ButtonWidget *buttonWidget = new ButtonWidget(textBox, this);
    layout->addWidget(buttonWidget);

    // Setup window
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowTitle("Qt Calculator");
    resize(400, 600);
}

MainWindow::~MainWindow()
{
    // delete ui;
}
