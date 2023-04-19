//#include "flappyproject.h"
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow startWindow;
    startWindow.show();
    return a.exec();
}
