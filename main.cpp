#include "login.h"
#include "chatdashboard.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
  //  ChatDashboard w;
  //  w.show();
    return a.exec();
}
