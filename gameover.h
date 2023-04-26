#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QLabel>
namespace Ui {
class gameover;
}

class gameover : public QDialog
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = nullptr);
    ~gameover();
    void ONpuntuacion();
    void tiempo();
    void openpuntuacion();

private slots:
    void on_returnMenu_clicked();

private:
    Ui::gameover *ui;

    int contador;
    QLabel *label_contador;
    int score;

};

#endif // GAMEOVER_H
