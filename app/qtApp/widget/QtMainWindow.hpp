#pragma once
#include <QMainWindow>
#include <QWidget>

namespace app
{
    class QtMainWindow final : public QMainWindow
    {
    public:
        explicit QtMainWindow(QWidget* parent = nullptr);
        ~QtMainWindow() override;



    private:
        Q_OBJECT
    };
}
