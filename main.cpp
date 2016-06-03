#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog *mainWindow = new Dialog();
    mainWindow->show();

    return a.exec();
}
