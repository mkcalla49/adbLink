#include "klogdialog.h"
#include "ui_klogdialog.h"
#include <QProcess>
#include <QMessageBox>
#include<QClipboard>




#ifdef Q_OS_LINUX
 int kos1=0;
#elif defined(Q_OS_WIN)
  int kos1=1;
#elif defined(Q_OS_MAC)
int kos1=2;
#endif

bool kgetfile = true;
QString klogfile1 = "kodi.log";
QString klogfile2 = "kodi.old.log";

QClipboard *kclipboard = QApplication::clipboard();

QString kRunProcess(QString cstring)
{
 QProcess run_command;
 run_command.setProcessChannelMode(QProcess::MergedChannels);
 run_command.start(cstring);

 run_command.waitForStarted();

 while(run_command.state() != QProcess::NotRunning)
     qApp->processEvents();

 QString command=run_command.readAll();

 return command;
}

klogDialog::klogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::klogDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);



}

klogDialog::~klogDialog()
{
    delete ui;
}



void klogDialog::passdata(const QString &adbpath, const QString &dataroot, const QString &filepath)
{

    kfilepath = filepath;
    kdataroot = dataroot;
    kadbpath  = adbpath;

QString cstring = adbpath + " shell cat "+dataroot+"Android/data/org.xbmc.kodi/"+filepath+"/temp/"+klogfile1;
QString command=kRunProcess(cstring);
ui->klogfileName->setText("kodi.log");
ui->klogBrowser->setPlainText(command);
kcontent = command;

}


void klogDialog::on_kswapButton_clicked()
{


    kgetfile = !kgetfile;

    if (kgetfile)
        ui->klogfileName->setText("kodi.log");
    else
     ui->klogfileName->setText("kodi.old.log");

    QString cstring = kadbpath + " shell cat "+kdataroot+"Android/data/org.xbmc.kodi/"+kfilepath+"/temp/"+ui->klogfileName->text();
    QString command=kRunProcess(cstring);
    ui->klogBrowser->setPlainText(command);
    kcontent = command;

}

void klogDialog::on_kcopyButton_clicked()
{
    kclipboard->setText(kcontent);
    klogDialog::accept();

}

