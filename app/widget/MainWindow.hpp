#pragma once
#include <QMainWindow>

namespace app
{
    class MainWindow final : public QMainWindow
    {
    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow() override;

    private:
        Q_OBJECT
    };
}
