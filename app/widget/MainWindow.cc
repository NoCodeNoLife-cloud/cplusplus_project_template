#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <type/container/Queue.hpp>
#include <widget/MainWindow.hpp>

namespace app
{
    MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
    {
        setWindowTitle("MainWindow");
        resize(300, 200);

        const auto centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        const QString str{"Hello World!"};
        const auto label = new QLabel(str, centralWidget);

        const auto okButton = new QPushButton("OK", centralWidget);
        connect(okButton, &QPushButton::clicked, [] { QCoreApplication::quit(); });

        const auto layout = new QVBoxLayout(centralWidget);
        layout->addWidget(label);
        layout->addWidget(okButton);
    }

    MainWindow::~MainWindow() = default;
}
