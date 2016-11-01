#ifndef UNINSTALLDIALOG_H
#define UNINSTALLDIALOG_H

#include <QDialog>

namespace Ui {
class uninstallDialog;
}

class uninstallDialog : public QDialog
{
    Q_OBJECT


public:
    explicit uninstallDialog(const QString &port, const QString &daddr,QWidget *parent = 0);
    ~uninstallDialog();


private:
        QString m_daddr;
        QString m_port;

        //   explicit uninstallDialog(const QString &port, QString &daddr, QWidget *parent = 0);
  //  ~uninstallDialog();



public:
   QString packageName();


public:
   bool keepBox();



private slots:

   void on_applyButton_clicked();
   void loadList();
   void makeFile();
   void loadBox();

private:
    Ui::uninstallDialog *ui;
};

#endif // UNINSTALLDIALOG_H
