#include <QLabel>
#include <widget/MainWindow.hpp>

namespace app
{
    MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
    {
        const auto label = new QLabel("Hello World", this);;
        setCentralWidget(label);
        setWindowTitle("MainWindow");
    }

    MainWindow::~MainWindow() = default;
}
