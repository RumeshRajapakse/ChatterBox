#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

    static QString filePath;
    void saveProfileJson();
    bool addLogs(QString, QString);

private slots:

    void on_btnUploadImage_clicked();

    void on_btnSignUp_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
