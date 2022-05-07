#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

struct MainWindowPrivate;
class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

        void openRepo(QString path);

    private slots:
        void on_actionExit_triggered();

        void on_actionClone_Repository_triggered();

        void on_actionOpen_Repository_triggered();

    private:
        Ui::MainWindow* ui;
        MainWindowPrivate* d;
};

#endif // MAINWINDOW_H
