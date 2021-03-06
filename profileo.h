#ifndef PROFILEO_H
#define PROFILEO_H

#include <QDialog>

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

    static QString filePath;

private slots:


    void on_btnSaveProfile_clicked();

    void on_btnExit_clicked();

private:
    Ui::Profile *ui;
};

#endif // PROFILEO_H
