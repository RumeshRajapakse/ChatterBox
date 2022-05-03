#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr, QString userName="");
    ~Profile();

    static QString filePath;

private slots:


    void on_btnSaveProfile_clicked();

    void on_btnExit_clicked();

private:
    Ui::Profile *ui;

    void loaduserdata();
};

#endif // PROFILE_H
