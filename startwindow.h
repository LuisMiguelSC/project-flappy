#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void openGameWindow();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void onFlappyProjectDestroyed();

private:
    Ui::StartWindow *ui;
    QString selectedImagePath;
    void applySelectedStyle(QPushButton *button);
    void applyUnselectedStyle(QPushButton *button);
};

#endif // STARTWINDOW_H

