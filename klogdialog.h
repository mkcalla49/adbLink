#ifndef KLOGDIALOG_H
#define KLOGDIALOG_H

#include <QDialog>

namespace Ui {
class klogDialog;
}

class klogDialog : public QDialog
{
    Q_OBJECT

private:

   QString cstring;
   QString command;
   QString kfilepath;
   QString kdataroot;
   QString kadbpath;
   QString kcontent;

public:
    void passdata(const QString &adbpath, const QString &dataroot, const QString &filepath);

public:
    explicit klogDialog(QWidget *parent = 0);
    ~klogDialog();

private slots:
    void on_kswapButton_clicked();

    void on_kcopyButton_clicked();


private:
    Ui::klogDialog *ui;

};

#endif // KLOGDIALOG_H
