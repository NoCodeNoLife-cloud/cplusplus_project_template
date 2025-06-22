#include <QLabel>
#include <type/container/Queue.hpp>
#include <widget/MainWindow.hpp>

namespace app
{
    MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
    {
        const QString str = "Hello World!";
        const auto label = new QLabel(str, this);;
        setCentralWidget(label);
        setWindowTitle("MainWindow");
    }

    MainWindow::~MainWindow() = default;
}
