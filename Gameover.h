
#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QDialog>
#include "Gameover.h"
#include "ui_flappyproject.h"

namespace Ui {
class Gameover;
}

class Gameover : public QDialog
{
    Q_OBJECT

public:
    explicit Gameover(QWidget *parent = nullptr);
    ~Gameover();

private slots:
    void openGameWindow();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void onFlappyProjectDestroyed();

private:
    Ui::Gameover *ui;
    QString selectedImagePath;
    void applySelectedStyle(QPushButton *button);
    void applyUnselectedStyle(QPushButton *button);
};
#endif // GAMEOVER_H
