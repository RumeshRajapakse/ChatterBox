#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

    static QString filePath;

private slots:
    void on_btnLogin_clicked();

    void on_btnGoToSignUp_clicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
