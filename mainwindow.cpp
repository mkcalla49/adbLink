#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog2.h"
#include "helpdialog.h"
#include "uninstalldialog.h"
#include "editordialog.h"
#include "keyboarddialog.h"
#include "usbfiledialog.h"
#include "kodidialog.h"
#include "cachedialog.h"
#include "datadialog.h"
#include "backupdialog.h"
#include "restdialog.h"
#include "klogdialog.h"
#include "oslogdialog.h"
#include <QtConcurrent/QtConcurrent>
#include <qtconcurrentrun.h>
#include <QMessageBox>
#include <QTableWidget>
#include <QResource>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QThread>
#include <QFile>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>
#include <QInputDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <preferencesdialog.h>
#include <QElapsedTimer>
#include <QTextStream>
#include <QStringRef>
#include <QDate>
#include <QRegularExpression>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QIcon>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QtNetwork/QNetworkInterface>
#include <adblogdialog.h>
#include <QFileInfo>
#include <QThread>
#include <QFileInfo>
#include<QClipboard>

// #include <QDebug>



#ifdef Q_OS_LINUX
 int os=0;
#elif defined(Q_OS_WIN)
  int os=1;
#elif defined(Q_OS_MAC)
int os=2;
#endif


const QString vqurl = "http://www.jocala.com/version.txt";
const QString version = "2.06";

bool isConnected = false;
bool serverRunning = false;
bool is_packageInstalled = false;

//bool mounted_op = false;
//bool firstrun=true;
//bool sshcheck = false;

bool dbexists = false;
bool updatecheck = true;
bool versioncheck = true;
bool isusb = false;




QString port = "5555";
QString filename = "";
QString adbdir =  "";
QString adb = "";
QString fastboot = "";
QString xmldir = "";
QString splashdir = "";
QString sshpassword ="";

QString hdir = "";
QString daddr="";
QString sldir = "";
QString pushdir = "";
QString pulldir = "";
QString xbmcpackage ="";
QString ostype = "";
QString data_root = "";
QString buffersize = "";
QString bufferfactor = "";
QString dbstring = "";
QString description = "";
QString filepath = "";
QString busypath = "";
QString adblog;
QString externalLocation;

QString adbstr1 = "ADB running. ";
QString adbstr2 = "ADB stopped. ";
QString devstr1 = "  Current device connected";
QString devstr2 = "  Current device not connected.";
QString devstr3 = "  USB Mode";
QString devstr4 = "  Console Mode";

QString program = "adbLink";
QString tempdir = "/data/local/tmp/";


int usbcheck;
int rootpath;
int ftvupdate;
int checkversion;
int extdata;
int buffermode = 1;
int tsvalue = 4000;
int ct = 1;
int Id = 0;
int deviceboxindex = 0;


int flag1 = 0;  // ostype: 0 Android, 1 Windows, 2 macOS, 3 Linux
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;



QString string1 = "";
QString string2 = "";
QString string3 = "";
QString string4 = "";
QString string5 = "";

QString stderrtxt;

QFutureWatcher<void> watcher;
QFutureWatcher<void> watcher1;
QProcess run_command;


QSqlDatabase db;


//////////////////////////////////////////////
 MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



     if (os == 1)
        {
         adbdir = "./";
         adb = adbdir+"adb.exe";
         adb = '"'+adb+'"';


     }



   if (os == 2)

        {
           adbdir = QCoreApplication::applicationDirPath();
           adbdir = adbdir+"/adbfiles/";


           if (QFile::exists(adbdir+"adb"))
           {
               adb = adbdir+"adb";
               adb = '"'+adb+'"';
               QProcess::execute ("chmod 0755 "+ adb);
           }

           else

           {
           QFile::copy(adbdir+"adb.osx", adbdir+"adb");
           adb = adbdir+"adb";
           adb = '"'+adb+'"';
           QProcess::execute ("chmod 0755 "+ adb);
           }


           if (QFile::exists(adbdir+"fastboot"))
           {
               fastboot = adbdir+"fastboot";
               fastboot = '"'+fastboot+'"';
               QProcess::execute ("chmod 0755 "+ fastboot);
           }

           else

           {
           QFile::copy(adbdir+"fastboot.osx", adbdir+"fastboot");
           fastboot = adbdir+"fastboot";
           fastboot = '"'+fastboot+'"';
           QProcess::execute ("chmod 0755 "+ fastboot);
           }




   }

   if (os == 0)

        {
           adbdir = QCoreApplication::applicationDirPath();
           adbdir = adbdir+"/adbfiles/";
           QProcess::execute ("chmod 0755 "+ adbdir+"adb.linux");

           if (QFile::exists(adbdir+"adb"))
           {
               adb = adbdir+"adb";
               adb = '"'+adb+'"';
               QProcess::execute ("chmod 0755 "+ adb);


           }

           else

           {
           QFile::copy(adbdir+"adb.linux", adbdir+"adb");
           adb = adbdir+"adb";
           adb = '"'+adb+'"';
           QProcess::execute ("chmod 0755 "+ adb);
           }

           if (QFile::exists(adbdir+"fastboot"))
           {
               fastboot = adbdir+"fastboot";
               fastboot = '"'+fastboot+'"';
               QProcess::execute ("chmod 0755 "+ fastboot);


           }

           else

           {
           QFile::copy(adbdir+"fastboot.linux", adbdir+"fastboot");
           adb = adbdir+"fastboot";
           adb = '"'+adb+'"';
           QProcess::execute ("chmod 0755 "+ fastboot);
           }



        }




       dbstring = adbdir+"adblink.db";
      xmldir = adbdir+"remotes/";
      splashdir = adbdir+"splash/";
//      recoverydir = adbdir+"cwmrecovery/";
//      stkrecoverydir = adbdir+"stkrecovery/";

     ui->setupUi(this);
     setFixedSize(size());




     ui->statusBar->addPermanentWidget(ui->server_running);
     ui->statusBar->addPermanentWidget( ui->progressBar);
     ui->progressBar->setHidden(true);

          #ifdef Q_OS_MAC
            //https://bugreports.qt.io/browse/QTBUG-51120
            ui->progressBar->setTextVisible(true);
          #endif //Q_OS_MAC

     QPixmap pix(":/assets/donatel.png");
     QIcon icon(pix);
     ui->donate->setIcon(icon);
     ui->donate->setText("");
     ui->donate->setIconSize(pix.size());



     ui->server_running->setText(adbstr2);


  rotate_logfile();


  logfile("adbLink "+version);

  QDateTime dateTime = QDateTime::currentDateTime();
  QString dtstr = dateTime.toString("MMddyyhhmmss");
  logfile(dtstr);

  if (os == 1)
          {
          logfile("Windows");
          }

     if (os == 2)

          {
        logfile("OS X");
          }



     if (os == 0)

          {
        logfile("Linux");

          }

 logfile("------------");


  hdir = QDir::homePath();
  open_pref_database();

   if (!dbexists)
    createTables();

     db.open();

     // addcolumn1();

    loaddevicebox();  // initial load
    description = ui->deviceBox->currentText();
    getRecord(description);

    if (ostype == "0")
      usbbuttons(isusb);

    connect(ui->deviceBox, SIGNAL(currentIndexChanged(int)),
       SLOT(readInc()));

    connect(&watcher, SIGNAL(finished()), SLOT(finishedCopy()));


    connect(&run_command,SIGNAL(readyReadStandardError()),this,SLOT( adberror() ));


    if (!(os == 1))
      {  QString cstring = "chmod 0755 "+adb;
         QString command=RunProcess(cstring);
       }

    start_server();
    logfile("starting server");
    if (serverRunning)
     { ui->server_running->setText(adbstr1);
        }

    else
    { ui->server_running->setText(adbstr2);

    }


    on_refreshConnectedDevices_clicked();

     if (checkversion==1)
          get_data();






 }


MainWindow::~MainWindow()
{



    logfile("closing program");
    kill_server();
    db.close();
    delete ui;

}



//////////////////////////////////////////////
void MainWindow::notAndroid()

{

    ui->sideload_Button->setDisabled(true);
    ui->uninstall_Button->setDisabled(true);
    ui->mvdataButton->setDisabled(true);
    ui->adbshellButton->setDisabled(true);
    ui->screencapButton->setDisabled(true);
    ui->keypadButton->setDisabled(true);

    ui->connButton->setDisabled(true);
    ui->disButton->setDisabled(true);


    ui->fpushButton->setDisabled(true);
    ui->fpullButton->setDisabled(true);
    ui->fdellButton->setDisabled(true);
    ui->fclearButton->setDisabled(true);
    ui->comboBox->setDisabled(true);
    ui->customdir->setDisabled(true);
    ui->editButton->setDisabled(true);
}


//////////////////////////////////////////////
void MainWindow::isAndroid()

{

    ui->sideload_Button->setDisabled(false);
    ui->uninstall_Button->setDisabled(false);
    ui->mvdataButton->setDisabled(false);
    ui->adbshellButton->setDisabled(false);
    ui->screencapButton->setDisabled(false);
    ui->keypadButton->setDisabled(false);

    ui->connButton->setDisabled(false);
    ui->disButton->setDisabled(false);


    ui->fpushButton->setDisabled(false);
    ui->fpullButton->setDisabled(false);
    ui->fdellButton->setDisabled(false);
    ui->fclearButton->setDisabled(false);
    ui->comboBox->setDisabled(false);
    ui->editButton->setDisabled(false);

     ui->customdir->setDisabled(false);

}



//////////////////////////////////////////////
QString MainWindow::getadb()

{
    QString gadb="";
    QString editport="";

    if (!isusb)
        editport=":"+port;

    gadb=adb+" -s "+daddr+editport+" ";


    return gadb;

}


/////////////////////////////////////////////

bool MainWindow::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

/////////////////////////////////////////
void MainWindow::delayTimer(int rdelay)
{

 QElapsedTimer rtimer;

int nMilliseconds;
 int i = 0;

 rtimer.start();

while(i == 0)
  {
    qApp->processEvents();
     nMilliseconds = rtimer.elapsed();
   if (nMilliseconds >= rdelay)
       break;
}


}

///////////////////////////////////////////////

QString MainWindow::RunProcess(QString cstring)
{


 run_command.start(cstring);
 run_command.waitForStarted();

 while(run_command.state() != QProcess::NotRunning)
 {
     qApp->processEvents();
 }

 QString command=run_command.readAllStandardOutput();

 return command;

}


//////////////////////////////////////////////
void MainWindow::adberror()
{
stderrtxt=run_command.readAllStandardError();
logfile("QPROCESS : "+stderrtxt );
}

//////////////////////////////////////////////
void MainWindow::rotate_logfile()

{

 QFile file(adbdir+"adblink.old.log");

 if( file.exists() )
     QFile::remove(adbdir+"adblink.old.log");


QFile file2(adbdir+"adblink.log");

if( file2.exists() )
    file2.rename(adbdir+"adblink.old.log");


}


//////////////////////////////////////////////
void MainWindow::logfile(QString line)

{


QFile file(adbdir+"adblink.log");
   if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
      {
       QMessageBox::critical(0, "","Can't create logfile!\n",QMessageBox::Cancel);
       return;
      }

   QTextStream out(&file);
            out  << line << endl;

 }


/////////////////////////////////////////
void MainWindow::rebootDevice(QString reboot)
{

 QElapsedTimer rtimer;
 int nMilliseconds;

QProcess reboot_device;
rtimer.start();
reboot_device.setProcessChannelMode(QProcess::MergedChannels);

QString cstring = getadb() + " " + reboot;

reboot_device.start(cstring);
reboot_device.waitForStarted();
while(reboot_device.state() != QProcess::NotRunning)
  {
    qApp->processEvents();
     nMilliseconds = rtimer.elapsed();
   if (nMilliseconds >= 5000)
       break;
}


}


/////////////////////////////////////////////////////
bool MainWindow::mount_system(QString mnt)
{
       QString cstring = getadb() + " shell su -c mount -o remount,"+mnt+ " /system";
       QString command=RunProcess(cstring);



        if (command.isEmpty())
          {
            logfile("/system mounted "+mnt);
            // logfile(cstring);
            logfile(command);
            return true;
          }
            else
          {
            logfile("/system not mounted "+mnt);
            // logfile(cstring);
            logfile(command);
            return false;
          }

}


/////////////////////////////
bool MainWindow::is_su()
{

QString cstring = getadb() + " shell ls /system/xbin/su";
QString command=RunProcess(cstring);



if (command.contains("No such file or directory"))
  {

    return false;
   }
    else
  {
     return true;
   }


}



////////////////////////////////////////////////
 QString MainWindow::strip (QString str)
{
    str = str.simplified();
    str.replace( " ", "" );
    return str;
}

 ////////////////////////////////////////////

 void MainWindow::blank_entry_form()
 {

     daddr="";
     ostype="0";
     description="";
     sldir = hdir;
     pushdir = hdir;
     pulldir = hdir;
     isusb = false;
     filepath = "/files/.kodi";
     port = "5555";
     buffermode = 1;
     buffersize = "20971520";
     bufferfactor = "1";
     versioncheck=true;
     xbmcpackage = "org.xbmc.kodi";
     data_root="/sdcard/";

 }


 //////////////////////////////////////////
 void MainWindow::kill_server()
{

 QString cstring = adb + " kill-server";
 QString command=RunProcess(cstring);
 // logfile(cstring);
 logfile("server stopped");
 serverRunning = false;

}


//////////////////////////////////////
void MainWindow::start_server()
{

    QString cstring = adb + " kill-server";
    QString command=RunProcess(cstring);


      cstring = adb + " start-server";
      command=RunProcess(cstring);

     if (command.contains("daemon started successfully"))
        {
           logfile("server started");
          // logfile(cstring);
           logfile(command);
           serverRunning = true;
          }

         else
        {
         logfile("start-server failed!");
         // logfile(cstring);
         logfile(command);
         serverRunning = false;
         }
}



/////////////////////////////////////////////////////
bool MainWindow::is_package(QString package)
{

    QString editport = ":"+port;

    if (isusb)
    editport = "";




    QString cstring = getadb() + " -s "+daddr+editport+" shell pm list packages ";
    QString command=RunProcess(cstring);
    logfile ("package: "+cstring);

        if (command.contains(package))
            {
            logfile(package+ " is installed");
            // logfile(cstring);
            // logfile(command);
            is_packageInstalled = true;
            }
            else
            {
            logfile(package+ " not found");
            // logfile(cstring);
            // logfile(command);
            is_packageInstalled = false;}

        return  is_packageInstalled;
}




//////// DATABASE ///////////////////

////////////////////////////////
int MainWindow::getRows()
{

   int rowcount=0;
   QString sqlstatement = "SELECT Count(*) FROM device";

    QSqlQuery query;
    query.exec(sqlstatement);
    while (query.next()) {
          rowcount = query.value(0).toInt();
    }

    if (query.lastError().isValid())
     {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


    return rowcount;
}

////////////////////////////////

void MainWindow::createTables()
{
    logfile("creating adblink.db");

   QString sqlstatement = "create table device(Id INTEGER PRIMARY KEY, daddr text ,description text NOT NULL UNIQUE,sldir text,pushdir text,pulldir text, xbmcpackage text, sshpassword text , versioncheck int, buffermode int, buffersize text, bufferfactor text, filepath text, port text,isusb int, flag1 int, flag2 int, flag3 int, flag4 int, flag5 int, string1 text,string2 text,string3 text,string4 text,string5 text)";

    QSqlQuery query;
    query.exec(sqlstatement);

    if (query.lastError().isValid())
     {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }





}





////////////////////////////////

void MainWindow::insertDevice()
{

   logfile("Insert new record");

   QSqlQuery query;

    daddr.replace(QString("'"), QString("''"));
    description.replace(QString("'"), QString("''"));
    xbmcpackage.replace(QString("'"), QString("''"));
    sldir.replace(QString("'"), QString("''"));
    pushdir.replace(QString("'"), QString("''"));
    pulldir.replace(QString("'"), QString("''"));
    xbmcpackage.replace(QString("'"), QString("''"));
    filepath.replace(QString("'"), QString("''"));
    port.replace(QString("'"), QString("''"));
    data_root.replace(QString("'"), QString("''"));


    // usbck.setNum(usbcheck);
    // ftvupdt.setNum(ftvupdate);

    QString ckversion;
    QString buffermd;
    QString usbflag;

    QString fg1;
    QString fg2;
    QString fg3;
    QString fg4;
    QString fg5;


    ckversion.setNum(checkversion);
    buffermd.setNum(buffermode);
    usbflag.setNum(isusb);


     fg1.setNum(flag1);
     fg2.setNum(flag2);
     fg3.setNum(flag3);
     fg4.setNum(flag4);
     fg5.setNum(flag5);





QString sql1  = "INSERT INTO device( daddr, description, sldir, pushdir, pulldir, xbmcpackage, sshpassword, versioncheck, buffermode, buffersize, bufferfactor, filepath , port ,isusb, flag1,flag2,flag3,flag4,flag5,string1,string2,string3,string4,string5)";

QString sql2 = " VALUES  ('"+daddr+"', '"+description+"', '"+sldir+"',  '"+pushdir+"', '"+pulldir+"', '"+xbmcpackage+"','"+data_root+"', '"+ckversion+"', '"+buffermd+"',  '"+buffersize+"',  '"+bufferfactor+"', '"+filepath+"', '"+port+"','"+usbflag+"','"+fg1+"','"+fg2+"','"+fg3+"','"+fg4+"' ,'"+fg5+"' ,'"+string1+"','"+string2+"' ,'"+string3+"' ,'"+string4+"' ,'"+string5+"')";

QString sqlstatement = sql1+sql2;

      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


}



////////////////////////////////
void MainWindow::updateRoot()
{
logfile("updateRoot()");


    logfile("updating database adblink.db");

    QString sqlstatement;
    QString tempstring;

    QString idstring;
    idstring.setNum(Id);
    logfile(idstring);
    QSqlQuery query;

    QString quote = "\"";



     tempstring = data_root;
     tempstring.replace(QString("'"), QString("''"));


      sqlstatement = "UPDATE device SET sshpassword='"+tempstring+"'  WHERE Id="+ idstring;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }




}




//////////////////////////////////////////////

void MainWindow::updateDevice(QString olddescription)
{
logfile("updateDevice()");


    logfile("updating database adblink.db");

    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString str6;
    QString tempstring;
    QString sqlstatement;

    str1.setNum(usbcheck);
    str2.setNum(ftvupdate);
    str3.setNum(checkversion);
    str4.setNum(buffermode);
    str5.setNum(isusb);
    str6.setNum(flag1);


  //  int idstring = Id.t;
    QString idstring;
    idstring.setNum(Id);
    logfile(idstring);
    QSqlQuery query;

    QString quote = "\"";




    if (olddescription != description)
    {

        tempstring = description;
        tempstring.replace(QString("'"), QString("''"));

           olddescription = quote+olddescription+quote;

            sqlstatement = "UPDATE netshare SET sharedescrip='"+tempstring+"'  WHERE sharedescrip="+ olddescription;
             query.exec(sqlstatement);

             if (query.lastError().isValid())
              {
                logfile(sqlstatement);
                logfile("SqLite error:" + query.lastError().text());
                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
               }

    }


    tempstring = daddr;
    tempstring.replace(QString("'"), QString("''"));

    sqlstatement = "UPDATE device SET daddr='"+tempstring+"'  WHERE Id="+ idstring;
    logfile(sqlstatement);
    query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = sldir;
     tempstring.replace(QString("'"), QString("''"));


     sqlstatement = "UPDATE device SET sldir='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);


     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = pushdir;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE device SET pushdir='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = pulldir;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE device SET pulldir='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);


     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = xbmcpackage;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE device SET xbmcpackage='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = data_root;
     tempstring.replace(QString("'"), QString("''"));


      sqlstatement = "UPDATE device SET sshpassword='"+tempstring+"'  WHERE Id="+ idstring;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


      tempstring = str3;
      tempstring.replace(QString("'"), QString("''"));

      sqlstatement = "UPDATE device SET versioncheck='"+tempstring+"'  WHERE Id="+ idstring;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


      tempstring = str4;
      tempstring.replace(QString("'"), QString("''"));


       sqlstatement = "UPDATE device SET buffermode='"+tempstring+"'  WHERE Id="+ idstring;
       query.exec(sqlstatement);

       if (query.lastError().isValid())
        {
          logfile(sqlstatement);
          logfile("SqLite error:" + query.lastError().text());
          logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
         }


       tempstring = buffersize;
       tempstring.replace(QString("'"), QString("''"));

       sqlstatement = "UPDATE device SET buffersize='"+tempstring+"'  WHERE Id="+ idstring;
        query.exec(sqlstatement);

        if (query.lastError().isValid())
         {
           logfile(sqlstatement);
           logfile("SqLite error:" + query.lastError().text());
           logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
          }


        tempstring = bufferfactor;
        tempstring.replace(QString("'"), QString("''"));

         sqlstatement = "UPDATE device SET bufferfactor='"+tempstring+"'  WHERE Id="+ idstring;
         query.exec(sqlstatement);

         if (query.lastError().isValid())
          {
            logfile(sqlstatement);
            logfile("SqLite error:" + query.lastError().text());
            logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
           }


         tempstring = description;
         tempstring.replace(QString("'"), QString("''"));

          sqlstatement = "UPDATE device SET description='"+tempstring+"'  WHERE Id="+ idstring;
          query.exec(sqlstatement);

          if (query.lastError().isValid())
           {
             logfile(sqlstatement);
             logfile("SqLite error:" + query.lastError().text());
             logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
            }

          tempstring = filepath;
          tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET filepath='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }


           tempstring = port;
           tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET port='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }



           tempstring = str5;
           tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET isusb='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }



           tempstring = str6;
           tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET flag1='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }


}





///////////////////////////////////////////////

void MainWindow::getRecord(QString descrip)

{


  QString sqlstatement;


  logfile("getting database record");

  QString quote = "\"";

  descrip = quote+descrip+quote;
  QSqlQuery query;


   sqlstatement= "SELECT Id FROM device WHERE description=" + descrip;
   query.exec(sqlstatement);
   logfile(sqlstatement);


           while (query.next()) {
                  Id = query.value(0).toInt();
                }


             if (query.lastError().isValid())
              {
                logfile(sqlstatement);
                logfile("SqLite error:" + query.lastError().text());
                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
               }



             sqlstatement= "SELECT daddr FROM device WHERE description=" + descrip;
             query.exec(sqlstatement);
             logfile(sqlstatement);


                     while (query.next()) {
                            daddr = query.value(0).toString();
                          }


                       if (query.lastError().isValid())
                        {
                          logfile(sqlstatement);
                          logfile("SqLite error:" + query.lastError().text());
                          logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                         }





         sqlstatement="SELECT sldir FROM device  WHERE description=" + descrip;
         query.exec(sqlstatement);
           while (query.next()) {
                sldir = query.value(0).toString();
          }

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }


           sqlstatement="SELECT pushdir FROM device  WHERE description=" + descrip;
           query.exec(sqlstatement);
            while (query.next()) {
                 pushdir = query.value(0).toString();
           }

        //    logfile(sqlstatement);
         //   logfile(pushdir);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


           sqlstatement="SELECT pulldir FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  pulldir = query.value(0).toString();
            }

        //    logfile(sqlstatement);
        //    logfile(pulldir);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT xbmcpackage FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  xbmcpackage = query.value(0).toString();
            }

      //      logfile(sqlstatement);
      //      logfile(xbmcpackage);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT sshpassword FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  data_root = query.value(0).toString();
            }

         //   logfile(sqlstatement);
         //   logfile(sshpassword);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT versioncheck FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  checkversion = query.value(0).toInt();
            }

        //    logfile(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }

          //  logfile(sqlstatement);

            sqlstatement="SELECT buffermode FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  buffermode = query.value(0).toInt();
            }

        //    logfile(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT buffersize FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  buffersize = query.value(0).toString();
            }


        //      logfile(sqlstatement);
         //     logfile(buffersize);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT bufferfactor FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  bufferfactor = query.value(0).toString();
            }

        //    logfile(sqlstatement);
         //   logfile(bufferfactor);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT description FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  description = query.value(0).toString();
            }

         //   logfile(sqlstatement);
         //   logfile(description);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT filepath FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  filepath = query.value(0).toString();
            }

        //    logfile(sqlstatement);
        //    logfile(filepath);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT port FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  port = query.value(0).toString();
            }

        //    logfile(sqlstatement);
        //    logfile(filepath);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT isusb FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  isusb = query.value(0).toInt();
            }




            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }




            sqlstatement="SELECT flag1 FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  ostype = query.value(0).toString();

                if (ostype=="0")
                    isAndroid();
                  else
                    notAndroid();

            }

        //    logfile(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }





     if (sldir.isEmpty())
         sldir = hdir;

     if (pushdir.isEmpty())
      pushdir = hdir;

     if (pulldir.isEmpty())
      pulldir = hdir;

     if (xbmcpackage.isEmpty())
         xbmcpackage = "org.xbmc.kodi";

     if (data_root.isEmpty())
         data_root = "/sdcard/";

     if (checkversion==0)
         versioncheck=false;
     else
         versioncheck=true;



}



//////////////////////////////////////////////

void MainWindow::deleteRecord(QString descrip)

{


  QString sqlstatement;
  logfile("getting database record");

  QString quote = "\"";

  descrip = quote+descrip+quote;
  QSqlQuery query;


   sqlstatement= "DELETE FROM device WHERE description=" + descrip;
   query.exec(sqlstatement);
   logfile(sqlstatement);


}


//////////////////////////////////////////////
void MainWindow::open_pref_database()

{

    QFile Fout(dbstring);

    if(!Fout.exists())
    {
      dbexists = false;
    }
    else
    {
      dbexists = true;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbstring);


    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            "Database error:\n"+dbstring
                     , QMessageBox::Cancel);
     logfile("error opening database "+dbstring);

    }



}





/////////////////////////////////////

void MainWindow::addcolumn1()
{
QString sqlstatement="SELECT rootpath FROM device ";
 QSqlQuery query;
 query.exec(sqlstatement);

 if (query.lastError().number() == 1)
  {
     sqlstatement = "ALTER TABLE device ADD COLUMN rootpath int";
     query.exec(sqlstatement);


     if (query.lastError().isValid())
      {
        logfile("rootpath column NOT added to device table");
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        QMessageBox::critical(0,"","Can't alter databse. See log.");
     }
   else logfile("rootpath column added to device table");

 }

}


//////////////////////////////////

bool MainWindow::isConnectedToNetwork()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    bool result = false;

    for (int i = 0; i < ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        if ( iface.flags().testFlag(QNetworkInterface::IsUp)
             && !iface.flags().testFlag(QNetworkInterface::IsLoopBack) )
        {


            // this loop is important
            for (int j=0; j<iface.addressEntries().count(); j++)
            {

                // we have an interface that is up, and has an ip address
                // therefore the link is present

                // we will only enable this check on first positive,
                // all later results are incorrect

                if (result == false)
                    result = true;
            }
        }

    }

    return result;
}




/////////////////////////////////////

void MainWindow::delay(int secs)
{
    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


/////////////////////////////////////////////////////////////////////////
bool MainWindow::find_daddr(QString deviceid)
{
   bool usbdaddr = false;

   for(int row = 0; row < ui->listDevices->count(); row++)
   {
       if (ui->listDevices->item(row)->text()==deviceid)
           usbdaddr=true;
   }

    return usbdaddr;
}



//////////////////////////////////////////////////////////////////////
void MainWindow::loaddevicebox() {

    QString sqlstatement;

        QSqlQuery query;

       ui->deviceBox->clear();
       sqlstatement= "SELECT description FROM device";
       query.exec(sqlstatement);
           while (query.next()) {
              description = query.value(0).toString();
              ui->deviceBox->addItem(description);
           }

}

//////////////////////////////////////////////////////////////////////
void MainWindow::get_data() {
   QNetworkRequest request;
   request.setUrl(QUrl(vqurl));

   QNetworkAccessManager *nam = new QNetworkAccessManager();
   QNetworkReply *reply = nam->get(request);

   connect(reply, SIGNAL(finished()),
           this, SLOT(onReqCompleted()));



}

/////////////////////////////////
void MainWindow::onReqCompleted() {
   QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());


   if (reply->error() != QNetworkReply::NoError)
   {

       int err = reply->error();
       QString s2 = QString::number(err);
       QMessageBox::critical(0, "","Network error: " + s2,QMessageBox::Cancel);
       return;

   }

   QByteArray data = reply->readAll();

   QString s1(data);

       s1 = strip(s1);

       int err = reply->error();

       QString s2 = QString::number(err);

       if (version != s1)
       {
           QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, "", program+" version "+s1+" is ready. Download?",
                    QMessageBox::Yes|QMessageBox::No);
              if (reply == QMessageBox::Yes)
               {
                  QString link = "http://www.jocala.com";
                  QDesktopServices::openUrl(QUrl(link));
                }

       }

       delete reply;

}


//////////////////////////////////////////////////////////////////////
void MainWindow::on_actionQuit_triggered()
{

    QCoreApplication::quit();

}


/////////////////////////////////////////////////////
void MainWindow::TimerEvent()
{
  int value = ui->progressBar->value();

  if (value >= 100)
      {
         value = 0;
         ui->progressBar->reset();
     }


  ui->progressBar->setValue(value+1);


}


/////////////////////////////////////////////////////
void MainWindow::readInc()
{


     description = ui->deviceBox->currentText();
     getRecord(description);

     QString lookup=daddr;


     if(!isusb)
          lookup=lookup+":"+port;

     if (ostype == "0")
       usbbuttons(isusb);


     isConnected=find_daddr(lookup);


      if (isConnected)
           is_busybox();



}

////////////////////////////////////////////////////////////////////////////
void MainWindow::on_sideload_Button_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
          //on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }


    QString cstring;
    QString command;

    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();

   QString fileName = QFileDialog::getOpenFileName(this,
          tr("Select app to install"), sldir , tr("APK Files (*.apk)"));


    if (!fileName.isEmpty() )
    {

    QFileInfo finfo(fileName);
    sldir = finfo.absolutePath();

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Install", "Install "+fileName+"?\n",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {


          ui->progressBar->setHidden(false);
          ui->progressBar->setValue(0);


          QTimer *timer = new QTimer(this);
          connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
          timer->start(tsvalue);

           cstring = getadb() + " install -r " + '"'+ fileName+'"';


           QString command=RunProcess(cstring);

           ui->progressBar->setHidden(true);

           // logfile(cstring);
           logfile(command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


           if (command.contains("Success"))

               QMessageBox::information(this,"","Installed");
              else      
               QMessageBox::critical(this,"","Install failed");

    }

  }


}


///////////////////////////////////////////////////////////////////////////
void MainWindow::on_uninstall_Button_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    //if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }

QString package = "";
QString cstring;
bool keepbox = false;




    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();




    logfile("open uninstall dialog");



    uninstallDialog dialog(port,daddr);

    // dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
    {

    package = dialog.packageName();
    keepbox = dialog.keepBox();

    }

    else return;


    if (package.isEmpty())
       {
        QMessageBox::critical(this,"","No file selected");
        return;
        }



            if ( !is_package(package))
               { QMessageBox::critical(
                     this,
                     "",
                     package +" not installed");
                  return;

            logfile("Error: "+ package +" not installed");
            }


            QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(this, "Uninstall", "Uninstall "+package+"?",
                     QMessageBox::Yes|QMessageBox::No);
                  if (reply == QMessageBox::Yes) {

                      ui->progressBar->setHidden(false);
                      ui->progressBar->setValue(0);

                      QTimer *timer = new QTimer(this);
                      connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                      timer->start(tsvalue);


                      if (!keepbox)
                      cstring = getadb()+" shell pm uninstall " + package;
                      else
                      cstring = getadb()+" shell pm uninstall -k " + package;

                      logfile("uninstall: "+cstring);

                      QString command=RunProcess(cstring);


                      ui->progressBar->setHidden(true);

                      // logfile(cstring);

                      nMilliseconds = rtimer.elapsed();
                      logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


                      if (!command.contains("Success"))

                         {   logfile(command);
                          QMessageBox::critical(
                                      this,
                                     "",
                                      "Uninstall failed");
                        }
                          else
                      {
                            logfile(command);
                             QMessageBox::information(
                                      this,
                                      "",
                                      "Uninstalled");
                       }


                  }
}


/////////////////////////////////////////////////////////////////////////
void MainWindow::on_connButton_clicked()
{


    QString cstring;
    QString command;
    QString pkg1 = "package:com.amazon.device.software.ota";
    QString pkg2 = "package:com.amazon.dcp";




    if (isusb )
      {

          QMessageBox::critical(
               this,
               tr("adbLink"),
               tr("Inactive for USB connections"));
            return;
      }

    if (daddr.isEmpty())
    {

        QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device address required."));
          return;
    }


    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


    QString sambastring;
    QString sambacheck;

      cstring = adb + " connect "+daddr+":"+port;
      command=RunProcess(cstring);
      logfile("connect"+command);
      logfile("");

    logfile("connection attempt");
    // logfile(cstring);
    logfile(command);


    if (command.contains("connected to"))
    {   isConnected=true;


           on_refreshConnectedDevices_clicked();


    }
       else
        isConnected=false;

     if(isConnected)
       {



         ui->server_running->setText(adbstr1);
         serverRunning = true;



      }

     // firstrun=false;

     nMilliseconds = rtimer.elapsed();
     logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );

}





////////////////////////////////////////////////////////////////
void MainWindow::on_disButton_clicked()
{



    if (isusb )
      {
          QMessageBox::critical(
               this,
               tr("adbLink"),
               tr("Inactive for USB connections"));
            return;
      }


    if (daddr.isEmpty())
    {

        QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device address required."));
          return;
    }



    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();



         QString cstring = adb + " disconnect "+daddr+":"+port ;
         QString command=RunProcess(cstring);

         logfile("disconnect: "+daddr);
         // logfile(cstring);

        isConnected=false;



         //ui->update_status->setText("");
         //on_utilityButton_clicked();

         on_refreshConnectedDevices_clicked();
         nMilliseconds = rtimer.elapsed();
         logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}


/////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionAbout_triggered()
{


    Dialog2 dialog2;
    dialog2.setModal(true);
    dialog2.setvLabel(version);
    dialog2.exec();

}


//////////////////////////////////////////////
void MainWindow::on_actionHelp_triggered()
{
    logfile("opening help");
    helpDialog helpdialog;
    helpdialog.setModal(true);
    helpdialog.exec();
}



/////////////////////////////////////////////
void MainWindow::backupAndroid()
{



 QString lookup=daddr;
 QString cstring;
 QString command;
 QString mcpath;
 QString thpath;
 QString envpath;
 QString rootpath;
 QString thumbpath;



  if(!isusb)
   lookup=lookup+":"+port;

 isConnected=find_daddr(lookup);

 //if (!isConnected && !isusb)
       //on_connButton_clicked();

  if (!isConnected)
        { QMessageBox::critical(0,"",devstr2);
           return;
        }

  if(!is_busybox())
  {
      QMessageBox::critical(0,"","Busybox installation failed.");
     return;
    }

    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
       }


   backupDialog dialog;

    dialog.setadb_backup(getadb(),data_root);

    dialog.setModal(true);

if(dialog.exec() == QDialog::Accepted)
{

     QString n_data_root = dialog.return_data_root();

     if(!n_data_root.startsWith("/"))
        n_data_root.prepend("/");

     if(!n_data_root.endsWith("/"))
        n_data_root.append("/") ;


     thumbpath = dialog.returnthumb();

     rootpath=n_data_root+"Android/data/"+xbmcpackage;
     thumbpath=rootpath+filepath+"/userdata/";



   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();



 QString hdir = QDir::homePath();


 mcpath = rootpath+filepath;

 cstring = getadb() + " shell ls "+mcpath;
 command=RunProcess(cstring);

 if (command.contains("No such file or directory"))
  {
    QMessageBox::critical(this,"","Kodi's files not found on "+n_data_root);
    logfile("backup result: "+command+"/n"+cstring);
    return;
 }


 cstring = getadb() + " shell ls "+thumbpath+"/Thumbnails";
 command=RunProcess(cstring);
 logfile("backup: "+command);
 if (command.contains("No such file or directory"))
  {
   logfile("Thumbnails not found");
   QMessageBox::critical(this,"","Thumbnails not found.  "+thumbpath );
   return;
 }


 QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Backup Destination"),
                                               hdir,
                                               QFileDialog::ShowDirsOnly
                                               | QFileDialog::DontResolveSymlinks);

if (!dir.isEmpty() )
 {
  QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Backup", "backup Kodi to "+dir,
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes)
   {
    logfile("backup function started");
       QString udir = dir+"/userdata";
       ui->progressBar->setHidden(false);
       ui->progressBar->setValue(0);

       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
       timer->start(tsvalue);

       mcpath=mcpath+"/";
       dir = dir + "/";

       if (os == 1)
       {
           dir.replace("/","\\");
           udir.replace("/","\\");
       }


     


      

       cstring = getadb() + " pull "+mcpath+".  "+'"'+dir+'"';
       command=RunProcess(cstring);
       logfile("backup: "+cstring);




       QString dbfile=dir+"userdata/Database/Addons16.db";
       QString thfile=dir+"userdata/Thumbnails";
       QString udfile=dir+"userdata";

       if (!QDir(thfile).exists())
       {

           cstring = getadb() +  " pull "+thumbpath+" "+'"'+dir+'"'+"/userdata";
            command=RunProcess(cstring);
           logfile("backup: "+cstring);
           QFile::rename(dir+"/userdata/advancedsettings.xml", dir+"/userdata/advancedsettings.backup");

       }


        if  (QDir(udfile).exists())
         QMessageBox::information(this,"","Backup Complete!");
        else
          QMessageBox::critical(this,"","Backup Failed. See Log.");


   } //end of do backup
 } // end of !dir

nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
ui->progressBar->setHidden(true);
logfile("Backup complete");

}  // end-dialog-accepted.

}  // end function



/////////////////////////////////////////////////
void MainWindow::restoreAndroid()

{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }


    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }


   QString cstring;
   QString command;
   QString rootpath;
   QString thumbpath;
   QString envpath;
   QString mcpath;



   cstring = cstring = getadb() +  " shell ps | grep "+xbmcpackage;
   command=RunProcess(cstring);


   if (command.contains(xbmcpackage))
      { QMessageBox::critical(this,"","Cannot restore while\n"+xbmcpackage+" is running!");
        logfile(xbmcpackage+" running. Restore failed");
        return;
       }




   restDialog dialog;

    dialog.setModal(true);

    dialog.setadb_restore(getadb());

   if(dialog.exec() == QDialog::Accepted)
   {



       data_root = dialog.restore_data_root();

       // QMessageBox::critical(0,"",data_root );


        if(!data_root.startsWith("/"))
          data_root.prepend("/");

       if(!data_root.endsWith("/"))
          data_root.append("/") ;




        rootpath=data_root+"Android/data/"+xbmcpackage;

          //QMessageBox::critical(this,"",rootpath);
          //return;


              envpath=rootpath+"/files/";
              mcpath=rootpath+filepath;



   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();


// extra rms





 QString dir = QFileDialog::getExistingDirectory(this, tr("Choose backup folder"),
  hdir,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);




 if (!dir.isEmpty() )
 {


   if (!QDir(dir+"/userdata").exists() )

     {
       QMessageBox::critical(0,"","Invalid backup folder!" );
       return;
     }


 QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Restore", "Restore Kodi from "+dir+" to "+data_root+" ?"+"\nThis will overwrite the existing setup!",
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes) {


       logfile("Restoring Android Kodi");

       ui->progressBar->setHidden(false);
       ui->progressBar->setValue(0);

       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
       timer->start(tsvalue);


     // nuke existing

       cstring = getadb() + " shell rm -r /sdcard/Android/data/"+xbmcpackage;
       command=RunProcess(cstring);
       logfile(command);

       cstring = getadb() + " shell rm -r "+rootpath;
       command=RunProcess(cstring);
       logfile(command);

       cstring = getadb() + " shell ls "+mcpath;
       command=RunProcess(cstring);
       logfile(command);

       if (command.contains("No such file or directory"))
        {
           cstring = getadb() + " shell mkdir -p "+mcpath;
           command=RunProcess(cstring);
           logfile(command);
           QString errorp = command;
           cstring = getadb() + " shell ls "+mcpath;
           command=RunProcess(cstring);

           if (command.contains("No such file or directory"))
            {
               QMessageBox::critical(this,"","Error creating restore point");
               logfile("Restore error:"+ errorp);
               return;
             }

        } // nuke existing

       cstring = getadb() + " shell rm /sdcard/xbmc_env.properties";
       command=RunProcess(cstring);

       cstring = getadb() + " shell rm -r "+mcpath + "/*";

       command=RunProcess(cstring);

       cstring = getadb() + " push "+'"'+dir+'"'+ " "+mcpath;

        command=RunProcess(cstring);

        ui->progressBar->setHidden(true);

        // logfile(cstring);
        logfile(command);

        nMilliseconds = rtimer.elapsed();
        logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



        if (stderrtxt.contains("bytes"))

       {


            stderrtxt="";

            QMessageBox::information(
                       this,
                      "",
                      "Restore complete." );

           if (data_root != "/sdcard/")
             {
               cstring = getadb() + " shell echo xbmc.data="+envpath+" > /sdcard/xbmc_env.properties";
               command=RunProcess(cstring);
               logfile("create /sdcard/xbmc_env.properties");
               // logfile(cstring);
               logfile(command);
           }

        }
           else

       {

           QMessageBox::critical(
                       this,
                       "",
                    "Restore failed ");
       }




   }

}

}

}

///////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pushRemote_other()
{

QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();



QString mcpath=filepath;


mcpath = mcpath+"/userdata/keymaps/";

if (!QFileInfo::exists(mcpath))
{
     QMessageBox::information(this,"","userdata/keymaps folder not found" );
     return;
}


 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose remote xml file", xmldir, tr("Files (*.xml)"));

 if (!fileName.isEmpty() )
 {


     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {

           QFileInfo fileInfo(fileName);
           QString filename(fileInfo.fileName());




          QFile::copy(fileName, mcpath+"/"+"keyboard.xml");

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


           if (QFileInfo::exists(mcpath+"/"+"keyboard.xml"))
           {
                QMessageBox::information(this,"","Remote xml installed." );
               }

         else {
           QMessageBox::information(this,"","Copy failed. See log." );
           logfile("Copy of "+fileName);
           logfile("to folder "+mcpath);
           logfile("failed for "+filename);

           }



           }


}

}

///////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pushRemote_android()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }

    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }




QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();


if (data_root.isEmpty())
    data_root="/sdcard/";

QString cstring;
QString command;
QString hidden;
QString xpath = "";
QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;


cstring = getadb() + " shell ls "+mcpath;

command=RunProcess(cstring);

if (command.contains("No such file or directory"))
{
   QMessageBox::critical(
               this,
              "",
               "Destination path missing "+mcpath);
               return;
}

mcpath = mcpath+"/userdata/keymaps/";

cstring = getadb() + " shell ls "+mcpath;

command=RunProcess(cstring);

if (command.contains("No such file or directory"))
 {
   //// logfile(cstring);
   //logfile(command);

    QMessageBox::critical(
                this,
               "",
                "Destination path missing");
                return;
}




 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose remote xml file", xmldir, tr("Files (*.xml)"));

 if (!fileName.isEmpty() )
 {


     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+mcpath+"/keyboard.xml";

           command=RunProcess(cstring);

           // logfile(cstring);
           logfile("push remote:"+command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



           if (stderrtxt.contains("bytes"))


           {

               stderrtxt="";

               QMessageBox::information(
                           this,
                          "",
                          "Remote xml installed." );
           }
               else

           {

               QMessageBox::critical(
                           this,
                           "",
                        "Remote xml installation failed.");}


   }

}

}


///////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pushRemote_clicked()
{

  if (ostype=="0")
    on_pushRemote_android();
 else
  on_pushRemote_other();

}


////////////////////////////////////////////////
void MainWindow::on_adbshellButton_clicked()
{

   QString lookup=daddr;

    if(!isusb)
     lookup=lookup+":"+port;

   isConnected=find_daddr(lookup);


    if (!isConnected)
          { QMessageBox::critical(0,"",devstr2);
             return;
          }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }



    description = ui->deviceBox->currentText();
    getRecord(description);






    logfile("detaching console process");
    logfile(daddr+":"+port);

    QString cstring = "";


    if (os == 1)

       {

       if (isusb)
           { cstring = "cmd /k  adb -s "+daddr+" shell";
             // logfile(cstring);
              QProcess::startDetached(cstring);
            }
        else
          {   cstring = "cmd /k  adb -s "+daddr+":"+port+ " shell";
              // logfile(cstring);
              QProcess::startDetached(cstring);
           }
     }


     else

       {

        QString commstr = adbdir+"console.sh";
        QFile::remove(commstr);
        QFile file(commstr);



                 if(!file.open(QFile::WriteOnly))

             {
                logfile("error creating console.sh!");
                 QMessageBox::critical(this,"","Error creating command file!");
                 return;
             }



       QTextStream out(&file);

       out  << "#!/bin/sh" << endl;
       out  <<  getadb()+ " shell " << endl;
       cstring = getadb()+ " shell";
       // logfile(cstring);

             file.flush();
             file.close();

       cstring = "chmod 0755 " + commstr ;
       QString command=RunProcess(cstring);

      //  cstring = "gnome-terminal -e "+adbdir+"console.sh";
      //  cstring = "x-terminal-emulator -e "+adbdir+"console.sh";

       if (os == 0)
         cstring = "x-terminal-emulator -e "+adbdir+"console.sh";
       if (os == 2)
       cstring = "open -a Terminal.app "+adbdir+"console.sh";



        QProcess::startDetached(cstring);
        }


}


////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionReboot_triggered()
{

     QString cstring;

     QString lookup=daddr;

      if(!isusb)
       lookup=lookup+":"+port;

     isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
          // on_connButton_clicked();

      if (!isConnected)
            { QMessageBox::critical(0,"",devstr2);
               return;
            }




   QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Reboot Device", "Reboot Device?",
         QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
         isConnected=false;
        logfile("rebooting device");
        rebootDevice(" reboot");
     }

}

///////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionRecovery_triggered()
{
    QString cstring;
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

  //  if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }




   QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "", "Reboot Recovery?",
         QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
         isConnected=false;


         logfile("rebooting device recovery");
         rebootDevice(" reboot recovery");
        }

}





/////////////////////////////////////////
void MainWindow::on_donate_clicked()
{
    QString link = "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=JA5E5UP3ZSWBN";
   QDesktopServices::openUrl(QUrl(link));

    //QString link = "http://www.jocala.com/tr.apk";
    //QDesktopServices::openUrl(QUrl(link));

}



////////////////////////////////////////////////

void MainWindow::on_actionDownload_Kodi_triggered()
{

    QString link = "http://kodi.tv/download/";
    QDesktopServices::openUrl(QUrl(link));

    //kodiDialog kodidialog;
    //kodidialog.setModal(true);
    //kodidialog.exec();
}

/////////////////////////////////////////////

void MainWindow::on_editRecord_clicked()
{

    int row;
      description = ui->deviceBox->currentText();

     if (!description.isEmpty())
      {


         QString lookup=daddr;

          if(!isusb)
           lookup=lookup+":"+port;

         isConnected=find_daddr(lookup);

      if (isConnected)
           is_busybox();


         row = ui->deviceBox->currentIndex();
         getRecord(description);
         dataentry(0);
         loaddevicebox();
         ui->deviceBox->setCurrentIndex(row);
     }




}

////////////////////////////////////////////////////////
void MainWindow::external_thumb()
{


    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device not connected"));
          return;
    }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }


    QString cstring;
    QString command;

    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbLink"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }



    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);


    QString l1 = "<advancedsettings>";
    QString l2 = "  <pathsubstitution>";
    QString l3 = "    <substitute>";
    QString l4 = "       <from>special://profile/Thumbnails/</from>";
    QString l5 = "        <to>"+externalLocation+xbmcpackage+"/Thumbnails/</to>";
    QString l6 = "     </substitute>";
    QString l7 = "   </pathsubstitution>";
    QString l8 = "</advancedsettings>";



    QString mvpath;
    QString mcpath = "/sdcard/Android/data/"+xbmcpackage+filepath;


    cstring = getadb() + " shell ls "+mcpath;

    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
     {

        QMessageBox::critical(
                    this,
                   "",
                    "Internal Kodi directory missing");
                    return;
    }



    cstring = getadb() +" shell ls "+externalLocation+ xbmcpackage +"/Thumbnails";
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {
       mvpath = externalLocation+"mcfiles/"+hidden;
       }

       else
       {
        mvpath = externalLocation+"mcfiles/";
       }



        cstring = getadb() +" shell ls "+mvpath+"/Thumbnails";
        command=RunProcess(cstring);

        if (!command.contains("No such file or directory"))
          {
             QMessageBox::critical(
                         this,
                         tr("adbLink"),
                         tr("Thumnails already moved"));

                 // logfile(cstring);
                 logfile(command);

                return;
      }

// reset mvpath.

 mvpath = externalLocation+"mcfiles/"+hidden;


QMessageBox::StandardButton reply1;
reply1 = QMessageBox::question(this, "", "Move Thumbnails to external storage?",
                            QMessageBox::Yes|QMessageBox::No);
if (reply1 == QMessageBox::No)
 {
   return;}


QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();

              QString filename1 = "advancedsettings.xml";
              QString filename2 = adbdir+filename1;

              cstring = getadb() + " shell ls "+mcpath+"/userdata/"+filename1;
              command=RunProcess(cstring);

              // logfile(cstring);
              logfile(command);

               if (!command.contains("No such file or directory"))
                  {
                   logfile("advancedsettings.xml exists");

                   QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "XML", "advancedsettings.xml exists. Overwrite?\n(will backup original)",
                                                  QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::No) {
                        logfile("abort xml write");
                        return;
                       } else {

                       cstring = getadb() + " shell mv "+mcpath+"/userdata/"+filename1+" "+mcpath+"/userdata/"+filename1+".backup";
                       command=RunProcess(cstring);
                       // logfile(cstring);
                       logfile(command);



                    }
                   }  // end if exists





    QFile file(filename2);


    if(!file.open(QFile::WriteOnly))
         {
           logfile("error creating advancedsettings.xml.");
           QMessageBox::critical(this,"","Unknown error creating xml file!");
            return;
          }

           QTextStream out(&file);

           out  << l1 << endl;
           out  << l2 << endl;
           out  << l3 << endl;
           out  << l4 << endl;
           out  << l5 << endl;
           out  << l6 << endl;
           out  << l7 << endl;
           out  << l8 << endl;


           file.flush();
           file.close();



    ui->progressBar->setHidden(false);
    ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

    cstring = getadb() +" shell mkdir -p "+externalLocation+xbmcpackage;
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);

    cstring = getadb() +" shell cp -R /sdcard/Android/data/"+xbmcpackage+filepath+"/userdata/Thumbnails " + externalLocation+xbmcpackage;
    command=RunProcess(cstring);


    // logfile(cstring);
    logfile(command);


    cstring = getadb() +" shell ls "+externalLocation+ xbmcpackage +"/Thumbnails";
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {
        QMessageBox::critical(this,"","Error copying Thumbnails. See Log.");
        return;
       }




    cstring = getadb() + " push "+filename2+ " "+mcpath+"/userdata/"+filename1;
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);


    if (!stderrtxt.contains("bytes"))
        {

        stderrtxt="";

          logfile("error pushing xml script to device!");
          QMessageBox::critical(this,"","Error pushing xml from PC to device!");
          return;
        }

    cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage+filepath+"/userdata/Thumbnails";
    command=RunProcess(cstring);
    // logfile(cstring);
    logfile(command);


   if (fileExists(filename2))
     QFile::remove(filename2);

   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


  ui->progressBar->setHidden(true);



  QMessageBox::information(
                 this,
                "",
                 "Thumbnails moved to external storage");

}



////////////////////////////////////////////////////////
void MainWindow::internal_thumb()
{


    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbShield"),
             tr("Device not connected"));
          return;
    }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }



    QString cstring;
    QString command;
    QString mvpath;
    QString userdatapath = "/sdcard/Android/data/"+xbmcpackage+filepath+"/userdata/";

    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbLink"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }



    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);



       cstring = getadb() +" shell ls "+externalLocation+xbmcpackage+"/Thumbnails";
       command=RunProcess(cstring);

       if (command.contains("No such file or directory"))
         {
           QMessageBox::critical(this,"","Thumbnails not found.");
           return;
          }

          else
          {
           mvpath = externalLocation+xbmcpackage;
          }




    cstring = getadb() + " shell ls "+userdatapath;

    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
     {

        QMessageBox::critical(
                    this,
                   "",
                    "userdata directory missing");
                    return;
    }


QMessageBox::StandardButton reply1;
reply1 = QMessageBox::question(this, "", "Move Thumbnails to internal storage?",
                            QMessageBox::Yes|QMessageBox::No);
if (reply1 == QMessageBox::No)
 {
   return;}


QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();

              QString filename1 = "advancedsettings.xml";
              QString filename2 = adbdir+filename1;

              cstring = getadb() + " shell ls "+userdatapath+filename1;
              command=RunProcess(cstring);

              // logfile(cstring);
              logfile(command);

               if (!command.contains("No such file or directory"))
                  {
                   logfile("advancedsettings.xml exists. renamed.");



                       cstring = getadb() + " shell mv "+userdatapath+filename1+" "+userdatapath+"advancedsettings.backup";
                       command=RunProcess(cstring);
                       // logfile(cstring);
                       logfile(command);


                   }  // end if exists


    ui->progressBar->setHidden(false);
    ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);


    cstring = getadb() +" shell cp -R "+mvpath+"/Thumbnails "+userdatapath;
    command=RunProcess(cstring);


    // logfile(cstring);
    logfile(command);


    cstring = getadb() + " shell ls "+userdatapath+"/Thumbnails";
    command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
     {
        cstring = getadb() +" shell rm -r "+mvpath;
        command=RunProcess(cstring);
        // logfile(cstring);
        logfile(command);

    }

   if (fileExists(filename2))
     QFile::remove(filename2);

   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


  ui->progressBar->setHidden(true);



  QMessageBox::information(
                 this,
                "",
                 "Thumbnails moved to internal storage\nadvancedsettings.xml renamed.");

}



////////////////////////////////////////////////////////
void MainWindow::data_external()
{


    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device not connected"));
          return;
    }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }


    QString cstring;
    QString command;

    QString mcfiles=xbmcpackage+"/files/";
    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    //QMessageBox::critical(0,"",root);

    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbFiles"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }

    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);

   cstring = getadb() +" shell ls /sdcard/xbmc_env.properties";
   command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
       {

          QMessageBox::critical(
                this,
                 tr("adbLink"),
                   tr("xbmc_env.properties already exists!"));

                // logfile(cstring);
                 logfile(command);

               return;

               }

    cstring = getadb() +" shell ls "+externalLocation+"/mcfiles/"+hidden;
    command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbFiles"),
                         tr("Data found at external location. Already moved?"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }

    QMessageBox::StandardButton reply1;
       reply1 = QMessageBox::question(this, "", "Move Kodi data to "+externalLocation+"?",
                                    QMessageBox::Yes|QMessageBox::No);
       if (reply1 == QMessageBox::No)
         {
           return;}

logfile("Moving kodi data to external storage");

   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();

    ui->progressBar->setHidden(false);
    ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

    cstring = getadb() +" shell mkdir -p "+externalLocation+mcfiles;
    command=RunProcess(cstring);

   // cstring = getadb() +" shell cp -R /sdcard/Android/data/"+xbmcpackage+"/files/"+hidden + " /"+ externalLocation+mcfiles;

    cstring = getadb() +" shell cp -R /sdcard/Android/data/"+xbmcpackage + " /"+ externalLocation+"/";

    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);


    data_root = root;
    updateRoot();

    cstring = getadb() + " shell echo xbmc.data="+externalLocation+mcfiles+ " > /sdcard/xbmc_env.properties";
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);

    cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage+"/files/";
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);

  ui->progressBar->setHidden(true);

  nMilliseconds = rtimer.elapsed();
  logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


  QMessageBox::information(
                 this,
                "",
                 "Data moved to external storage");

}

/////////////////////////////////////////////////////////
void MainWindow::data_internal()
{

    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device not connected"));
          return;
    }

    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }

    // /mnt/shell/emulated
    // /storage/usbdrive

    QString cstring;
    QString command;
    QString mcfiles= xbmcpackage +"/files/";
    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);


    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbFiles"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }



    cstring = getadb() +" shell ls "+externalLocation+mcfiles+hidden;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(0,"","Kodi data not found   "+cstring);

                 // logfile(cstring);
                 logfile(command);

                return;

       }




    cstring = getadb() +" shell ls /sdcard/Android/data/"+xbmcpackage+filepath;
    command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
      {

            QMessageBox::critical(0,"","Kodi data has already been restored");

                 // logfile(cstring);
                 logfile(command);

                return;

       }


    QMessageBox::StandardButton reply1;
       reply1 = QMessageBox::question(this, "", "Move Kodi data to internal storage?",
                                    QMessageBox::Yes|QMessageBox::No);
       if (reply1 == QMessageBox::No)
         {
           return;}

logfile("Moving kodi data to internal storage");

       QElapsedTimer rtimer;
       int nMilliseconds;
       rtimer.start();

       ui->progressBar->setHidden(false);
       ui->progressBar->setValue(0);



       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
       timer->start(tsvalue);

      // cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage+"/files/"+hidden;
       cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage;
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

       // cstring = getadb() +" shell cp -R "+externalLocation+mcfiles+hidden + " /sdcard/Android/data/"+xbmcpackage+"/files/";
       cstring = getadb() +" shell cp -R "+externalLocation+"/"+xbmcpackage + " /sdcard/Android/data/";
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

       cstring = getadb() +" shell ls /sdcard/Android/data/"+xbmcpackage+filepath;
       command=RunProcess(cstring);

       if (!command.contains("No such file or directory"))
         {


           cstring = getadb() + " shell rm /sdcard/xbmc_env.properties";
           command=RunProcess(cstring);
           // logfile(cstring);
           logfile(command);

           cstring = getadb() +" shell rm -r "+externalLocation+xbmcpackage;
           command=RunProcess(cstring);
           // logfile(cstring);
           logfile(command);

           data_root="/sdcard/";
           updateRoot();

           QMessageBox::information(this,"","Data moved to internal storage");

       }


       else
       {
           QMessageBox::critical(this,"","Error moving data to internal storage");

       }


     ui->progressBar->setHidden(true);
     nMilliseconds = rtimer.elapsed();
     logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );





}


///////////////////////////////////////////////////
void MainWindow::on_actionSplash_Screen_triggered()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
     }

    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }

QString cstring;
QString command;

QString mcpath = "";
QString adpath="/Android/data/"+xbmcpackage+filepath;
QString root1="/sdcard/";
QString root2= "/storage/extUsb/";
QString root3= "/storage/sdcard1/";
QString root4=  "/storage/usbotg/";
QString root5= "/storage/usbdisk/";


cstring = getadb() + " shell ls "+root1+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root1+adpath;
}

cstring = getadb() + " shell ls "+root2+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root2+adpath;
}

cstring = getadb() + " shell ls "+root3+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root3+adpath;
}


cstring = getadb() + " shell ls "+root4+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root4+adpath;
}


cstring = getadb() + " shell ls "+root5+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root5+adpath;
}


   mcpath=mcpath+"/media";


   cstring = getadb() + " shell ls "+mcpath;

   command=RunProcess(cstring);

   if (command.contains("No such file or directory"))
    {
       QMessageBox::critical(
                   this,
                  "",
                   "Destination path missing\n"+mcpath);
                    logfile("missing path: "+mcpath);
                    return;

   }



QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();



 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose splash screen file", splashdir, tr("Files (*.png)"));

 if (!fileName.isEmpty() )
 {




     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+mcpath+"/splash.png";

           command=RunProcess(cstring);

           // logfile(cstring);
           logfile(command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



           if (stderrtxt.contains("bytes"))


           {

               stderrtxt="";

               QMessageBox::information(
                           this,
                          "",
                          "Splash screen installed." );
           }
               else

           {

               QMessageBox::critical(
                           this,
                           "",
                        "Splash screen installation failed.");}


   }

}

}

////////////////////////////////////////

void MainWindow::on_doConsole_clicked()
{

    // set PATH=%PATH%;C:\xampp\php

    logfile("detaching console process");

     QString cstring = "";


     if (os == 1)

        {

        QString commstr = adbdir+"cpath.bat";
        QFile file(commstr);

            if(!file.open(QFile::WriteOnly |
                          QFile::Text))
            {
                logfile("error creating cpath.bat!");
                QMessageBox::critical(this,"","Error creating bat file!");
                return;
            }



            QTextStream out(&file);
            out  << "set PATH=%PATH%;"+QDir::currentPath()+";"<< endl;



            file.flush();
            file.close();

            cstring = "cmd /k " +QDir::currentPath()+"/cpath.bat";
            QProcess::startDetached(cstring);



     }

     QString pathdir = QCoreApplication::applicationDirPath() +"/adbfiles";

       if (os == 2 || os == 0)
         {

           QString commstr = adbdir+"cpath.sh";


           QFile file(commstr);

               if(!file.open(QFile::WriteOnly |
                             QFile::Text))
               {
                   logfile("error creating cpath!");
                   QMessageBox::critical(this,"","Error creating sh file!");
                   return;
               }



               QTextStream out(&file);
                out  << "#!/bin/sh" << endl;
                out  << "export PATH="+pathdir+":$PATH" << endl;
                out  << "/bin/sh" << endl;


               file.flush();
               file.close();


               cstring = "chmod 0755 " + commstr ;
               QString command=RunProcess(cstring);



       }


       if (os == 2)
        {
       QString cstring = "open -a Terminal.app "+adbdir+"cpath.sh";
       // logfile(cstring);
       QProcess::startDetached(cstring);
        }




       if (os == 0)
        {
           // cstring = "x-terminal-emulator --working-directory="+adbdir+"/adbfiles";
            cstring = "gnome-terminal --working-directory="+adbdir+ " -x "+adbdir+"cpath.sh";
           QProcess::startDetached(cstring);

         }


}


////////////////////////////////////////

void MainWindow::on_killServer_clicked()
{
    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


    QString cstring = adb + "  disconnect "+daddr+":"+port ;
    QString command=RunProcess(cstring);

    isConnected=false;


    kill_server();

    if (serverRunning)
      ui->server_running->setText(adbstr1);
    else
     ui->server_running->setText(adbstr2);

  ui->listDevices->clear();
  ui->listDevicesStatus->clear();

    nMilliseconds = rtimer.elapsed();
    logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}

///////////////////////////////////////////////////
void MainWindow::on_refreshConnectedDevices_clicked()
{
    int i;
    QString isdevice;
    QString usbid;
    QString cstring = "";
    QString command = "";
    QString litem;


     ui->listDevices->clear();
     ui->listDevicesStatus->clear();

     cstring = adb + " devices";
     command=RunProcess(cstring);

        if (command.contains("device"))
           {
              //logfile("device(s) found");
              //logfile(command);

              serverRunning=true;
              ui->server_running->setText(adbstr1);



              QFile file21(adbdir+"temp.txt");

                if(!file21.open(QFile::WriteOnly))
                  {
                     QMessageBox::critical(0, "","Error creating daddr file!\n",QMessageBox::Cancel);
                      // logfile(cstring);
                      logfile(command);
                      logfile("error creating "+adbdir+ "device file");
                      return;
                  }

                QTextStream out1(&file21);
                out1  << command << endl;

                file21.flush();
                file21.close();



                QString tmpstr2 = adbdir+"temp.txt";
                QString fline2;

                   QFile file32(tmpstr2);
                     if (!file32.open(QIODevice::ReadOnly | QIODevice::Text))
                       {QMessageBox::critical(0,"","Error reading file!");
                          return; }

                     QTextStream in1(&file32);
                      while (!in1.atEnd())
                       {

                        fline2 = in1.readLine();

                          if (!fline2.isEmpty()  &&  (!fline2.contains("List of devices") &&
                                 (!fline2.contains("* daemon"))))

                           {


                              i =  fline2.indexOf("\t");

                              usbid =fline2.mid(0,i);
                              isdevice = fline2.mid(i+1);


                              if (isdevice.contains("unauthorized"))
                                  QMessageBox::critical(0,"","Device unauthorized\n\nPress 'Refresh ADB' or see help topic 'Device unauthorized' ");

                              if (isdevice.contains("offline"))
                                  QMessageBox::critical(0,"","Device offline\n\nPress 'Refresh ADB' or see help topic 'Device Offline' ");



                              is_busybox();

                              logfile("device:"+usbid);



                              litem = litem+isdevice;
                              ui->listDevices->addItem(usbid);
                               ui->listDevicesStatus->addItem(isdevice);
                          }

                      }

            file32.close();


            QFile::remove(tmpstr2);

        }


        delay(3);

}



///////////////////////////////////////////////
void MainWindow::on_listDevices_doubleClicked()
    {


    // check for port, bail if so.
    QString checktype = ui->listDevices->currentItem()->text();
      if (checktype.contains(":"))
        {  QMessageBox::critical(
                      this,
                     "",
                      "Not a USB device!");
            return;
      }



    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(0, "", "Create new record with this ID?",
          QMessageBox::Yes|QMessageBox::No);

      if (reply == QMessageBox::No)
        return;



        blank_entry_form();
        isusb=true;
       daddr = ui->listDevices->currentItem()->text();
       dataentry(1);
       loaddevicebox();
     }

//////////////////////////////////////////
void MainWindow::on_newRecord_clicked()
{


  logfile("go to dataentry -- new record");

  blank_entry_form();
  dataentry(1);
  loaddevicebox();

}


//////////////////////////////////////////////////
void MainWindow::dataentry(int flag)
{

// flag = 0 edit record
// flag = 1 new record

  ui->deviceBox->currentIndex();

logfile("opening preferences dialog");

    QString cstring;
    QString command;
    QString oldpass;
    QString olddaddr;
    QString olddescription;
    QString pkg;
    QString device_name;

    data_root = sshpassword;

    olddaddr = daddr;

    //sshcheck = false;
    //mountcheck = false;

    updatecheck = true;
    olddescription=description;

    //bool sshstate;
    //bool updatestate;
   // bool mountstate;

    //check_update_status();
    //updatestate = updatecheck;

    preferencesDialog dialog;

    dialog.setPackagename(xbmcpackage);
    dialog.setPulldir(pulldir);

    //dialog.setftvUpdate(updatecheck);
    //dialog.setsshBoot(sshcheck);
   // dialog.setmountBoot(mountcheck);


    //  if (ostype=="0")
     // {

     // }
    //  else
     // {
     //     dialog.setfilepath("");
      //    dialog.setdataroot("");

     // }

    dialog.setfilepath(filepath);
    dialog.setdataroot(data_root);
    dialog.setversioncheck(versioncheck);
    dialog.setversionLabel(version);
    dialog.setostype(ostype);
    dialog.setdescription(description);

    dialog.setdeviceindex(ui->deviceBox->currentIndex());


    dialog.setadb_pref(getadb());




    if (isusb)
        dialog.setport("");
      else
        dialog.setport(port);

    dialog.setdaddr(daddr);


    dialog.setisusb(isusb);
    dialog.setModal(true);


    if(dialog.exec() == QDialog::Accepted)
    {



    int x = dialog.returnval1();

//    QString s  = QString::number(x);
//    QMessageBox::critical(this,"",s); //updatecheck = dialog.updatecheck();
//    sshcheck = dialog.sshcheck();
//    mountcheck = dialog.mountcheck();

    sshpassword = dialog.data_root();
    xbmcpackage = dialog.xbmcpackageName();
    pulldir = dialog.pulldir();
    versioncheck = dialog.versioncheck();
    description = dialog.description();
    data_root = dialog.data_root();
    filepath = dialog.filepath();
    port = dialog.port();
    daddr = dialog.daddr();
    isusb = dialog.isusb();
    ostype = dialog.ostype();
    flag1 = ostype.toInt();


    if (ostype=="0")
        isAndroid();
    else
        notAndroid();


    if (versioncheck)
        checkversion = 1;
    else
        checkversion = 0;

    if (x == 1 && flag == 1)
    {logfile("go insert a record");
      insertDevice();
    }

    if (x == 1 && flag == 0)
           {
             logfile("Saving Device Record");
              updateDevice(olddescription);

           }  // end x1



  }




 }


////////////////////////////////////////
void MainWindow::on_delRecord_clicked()
{

    description = ui->deviceBox->currentText();

    if (!description.isEmpty())
     {

    QString descrip = description;

    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(0, "", " Delete "+descrip+"?",
             QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::No)
        {
          return;
         }

       deleteRecord(descrip);
       loaddevicebox();


       logfile(descrip+ " is deleted");
  }
}


//////////////////////////////////////////////////
void MainWindow::on_actionView_Log_triggered()
{


    //logfile("opening adblog dialog");

     adblogDialog dialog;
     dialog.setModal(true);
     dialog.exec();


}


//////////////////////////////////////////////////////////////////////
void MainWindow::cacheButton_other()
{

    bool oldxml = false;


    QString line1;
    QString line2;
    QString line3;
    QString line4;
    QString line5;
    QString line6;
    QString line7;



QString mcpath=filepath;

mcpath = mcpath+"/userdata/";

if (!QFileInfo::exists(mcpath))
{
     QMessageBox::information(this,"","userdata folder not found" );
     return;
}

logfile("opening cache dialog");

   cacheDialog dialog;

    dialog.setxmlcheck(false);
    dialog.setcbuffermode(buffermode);
    dialog.setcbuffersize(buffersize);
    dialog.setcbufferfactor(bufferfactor);

    dialog.setModal(true);


    if(dialog.exec() == QDialog::Accepted)
    {

     int x = dialog.returncval1();


    buffermode = dialog.cbuffermode();
    buffersize = dialog.cbuffersize();
    bufferfactor = dialog.cbufferfactor();
    oldxml = dialog.xmlcheck();

    QString str1;
    str1.setNum(buffermode-1);

    if (oldxml)
      {
          line1 ="<advancedsettings>";
          line2 ="  <network>";
          line3 ="    <buffermode>"+str1+"</buffermode>";
          line4 ="    <cachemembuffersize>"+buffersize+"</cachemembuffersize>";
          line5 ="    <readbufferfactor>"+bufferfactor+"</readbufferfactor>";
          line6 ="  </network>";
          line7 ="</advancedsettings>";
      }

    else

      {
         line1 ="<advancedsettings>";
         line2 ="  <cache>";
         line3 ="    <buffermode>"+str1+"</buffermode>";
         line4 ="    <memorysize>"+buffersize+"</memorysize>";
         line5 ="    <readfactor>"+bufferfactor+"</readfactor>";
         line6 ="  </cache>";
         line7 ="</advancedsettings>";
      }





    /*
    <cachemembuffersize> and <readbufferfactor>
     - In v17 <cachemembuffersize> is renamed to  <memorysize>
     and <readbufferfactor> is renamed to <readfactor>.
    In addition, all three buffer related settings in <network>
    are moved out of <network> and
    into a new <cache> parent tag.

    */



   if (x == 2)
          {


         QString str1;
         str1.setNum(buffermode-1);

              QString filename1 = "advancedsettings.xml";
              QString filename2 = mcpath+"/"+filename1;

              if (QFileInfo::exists(filename2))   // does file exist

              {
                    logfile("advancedsettings.xml exists");
                          QMessageBox::StandardButton reply;
                           reply = QMessageBox::question(this, "XML", "advancedsettings.xml exists. Overwrite?\n(will backup original)",
                                                         QMessageBox::Yes|QMessageBox::No);
                           if (reply == QMessageBox::No) {
                               logfile("abort xml write");
                               return;
                              } else
                              {
                              logfile("continue xml write");
                              logfile("backup advancedsettings.xml");
                              QFile::rename(filename2, mcpath+"/"+"advancedsettings.old.xml");
                              }
                          }  // end if exists


         QFile file(filename2);

          if(!file.open(QFile::WriteOnly))
                {
                  logfile("error creating advancedsettings.xml.");
                  QMessageBox::critical(this,"","Unknown error creating xml file!");
                   return;
                 }

                  QTextStream out(&file);

                  out  << line1 << endl;
                  out  << line2 << endl;
                  out  << line3 << endl;
                  out  << line4 << endl;
                  out  << line5 << endl;
                  out  << line6 << endl;
                  out  << line7 << endl;

                  file.flush();
                  file.close();


       }

  }  //end accepted


} // end  other cache

//////////////////////////////////////////////////////////////////////
void MainWindow::cacheButton_android()

{

    bool oldxml = false;
    QString lookup=daddr;

    QString line1;
    QString line2;
    QString line3;
    QString line4;
    QString line5;
    QString line6;
    QString line7;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


    if (!isConnected)
          { QMessageBox::critical(0,"",devstr2);
             return;
          }

    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }



logfile("opening cache dialog");

if (data_root.isEmpty())
    data_root="/sdcard/";

QString cstring;
QString command;
QString hidden;
QString xpath = "";
QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;
xpath = mcpath+"/userdata/";

cstring = getadb() + " shell ls "+mcpath;

command=RunProcess(cstring);

if (command.contains("No such file or directory"))
{
   QMessageBox::critical(
               this,
              "",
               "Destination path missing");
               return;
}

   cacheDialog dialog;

    dialog.setxmlcheck(false);
    dialog.setcbuffermode(buffermode);
    dialog.setcbuffersize(buffersize);
    dialog.setcbufferfactor(bufferfactor);

    dialog.setModal(true);


    if(dialog.exec() == QDialog::Accepted)
    {

 int x = dialog.returncval1();


    buffermode = dialog.cbuffermode();
    buffersize = dialog.cbuffersize();
    bufferfactor = dialog.cbufferfactor();
    oldxml = dialog.xmlcheck();

    QString str1;
    str1.setNum(buffermode-1);




    /*
    <cachemembuffersize> and <readbufferfactor>
     - In v17 <cachemembuffersize> is renamed to  <memorysize>
     and <readbufferfactor> is renamed to <readfactor>.
    In addition, all three buffer related settings in <network>
    are moved out of <network> and
    into a new <cache> parent tag.

    */

             if (oldxml)
               {
                   line1 ="<advancedsettings>";
                   line2 ="  <network>";
                   line3 ="    <buffermode>"+str1+"</buffermode>";
                   line4 ="    <cachemembuffersize>"+buffersize+"</cachemembuffersize>";
                   line5 ="    <readbufferfactor>"+bufferfactor+"</readbufferfactor>";
                   line6 ="  </network>";
                   line7 ="</advancedsettings>";
               }

             else

               {
                  line1 ="<advancedsettings>";
                  line2 ="  <cache>";
                  line3 ="    <buffermode>"+str1+"</buffermode>";
                  line4 ="    <memorysize>"+buffersize+"</memorysize>";
                  line5 ="    <readfactor>"+bufferfactor+"</readfactor>";
                  line6 ="  </cache>";
                  line7 ="</advancedsettings>";
               }



    if (x == 2)
          {


   logfile("write advancedsettings.xml");



         cstring = getadb() + " shell ls "+mcpath;


              QString filename1 = "advancedsettings.xml";
              QString filename2 = adbdir+filename1;



             cstring = getadb() + " shell ls "+mcpath;
             command=RunProcess(cstring);
              if (command.contains("No such file or directory"))
                      {
                         QMessageBox::critical(this,"","Destination path missing");
                          return;
                     }



                     cstring = getadb() + " shell ls "+xpath+filename1;
                     command=RunProcess(cstring);

                     // logfile(cstring);
                     logfile(command);

                      if (!command.contains("No such file or directory"))
                         {
                          logfile("advancedsettings.xml exists");

                          QMessageBox::StandardButton reply;
                           reply = QMessageBox::question(this, "XML", "advancedsettings.xml exists. Overwrite?\n(will backup original)",
                                                         QMessageBox::Yes|QMessageBox::No);
                           if (reply == QMessageBox::No) {
                               logfile("abort xml write");
                               return;
                              } else {
                              logfile("continue xml write");
                              logfile("backup advancedsettings.xml");
                              cstring = getadb() + " shell cp "+xpath+filename1+" "+xpath+filename1+".old";
                              command=RunProcess(cstring);
                              }
                          }  // end if exists


          QFile file(filename2);


          if(!file.open(QFile::WriteOnly))
                {
                  logfile("error creating advancedsettings.xml.");
                  QMessageBox::critical(this,"","Unknown error creating xml file!");
                   return;
                 }

                  QTextStream out(&file);

                  out  << line1 << endl;
                  out  << line2 << endl;
                  out  << line3 << endl;
                  out  << line4 << endl;
                  out  << line5 << endl;
                  out  << line6 << endl;
                  out  << line7 << endl;

                  file.flush();
                  file.close();

                  cstring = getadb() + " push "+filename2+ " "+xpath+filename1;
                  command=RunProcess(cstring);

                   if (!stderrtxt.contains("bytes"))
                      {
                        stderrtxt="";
                        logfile(command);
                        logfile("error pushing xml script to device!");
                        QMessageBox::critical(this,"","Error pushing xml from PC to device!");
                        return;
                      }
                    else {
                       QMessageBox::information(this,"","advancedsettings.xml written");
                   }



           }


  }


} // end  android cache



///////////////////////////////////////////
void MainWindow::on_cacheButton_clicked()

{
    if (ostype=="0")
     cacheButton_android();
   else
    cacheButton_other();
 }

/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::splashButton_android()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
     }

    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }

   if (data_root.isEmpty())
       data_root="/sdcard/";

  QString cstring;
  QString command;
  QString hidden;
  QString xpath = "";
  QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;

  mcpath=mcpath+"/media";

  cstring = getadb() + " shell ls "+mcpath;

  command=RunProcess(cstring);

  if (command.contains("No such file or directory"))
   {
      QMessageBox::critical(
                  this,
                 "",
                  "Destination path missing: "+mcpath);
                  return;
  }





QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();



 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose splash screen file", splashdir, tr("Files (*.png)"));

 if (!fileName.isEmpty() )
 {


     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+mcpath+"/splash.png";

           command=RunProcess(cstring);

           // logfile(cstring);
           logfile(command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



           if (stderrtxt.contains("bytes"))


           {

               stderrtxt="";

               QMessageBox::information(
                           this,
                          "",
                          "Splash screen installed." );
           }
               else

           {

               QMessageBox::critical(
                           this,
                           "",
                        "Splash screen installation failed.");}


   }

}

}



///////////////////////////////////////////////////////////////////////////////////////
void MainWindow::splashButton_other()
{

QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();



QString mcpath=filepath;

 mcpath=mcpath+"/media/";


if (!QFileInfo::exists(mcpath))
{
     QMessageBox::information(this,"","Media folder not found" );
     return;
}


 QString fileName = QFileDialog::getOpenFileName(this,
"Choose splash screen file", splashdir, tr("Files (*.png)"));

 if (!fileName.isEmpty() )
 {


     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {

           QFileInfo fileInfo(fileName);
           QString filename(fileInfo.fileName());




          QFile::copy(fileName, mcpath+"/"+"splash.png");

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


           if (QFileInfo::exists(mcpath+"/"+"splash.png"))
           {
                QMessageBox::information(this,"","Splash screen installed." );
               }

         else
           {
           QMessageBox::information(this,"","Copy failed. See log." );
           logfile("Copy of "+fileName);
           logfile("to folder "+mcpath);
           logfile("failed for "+filename);

              }
           }


}

}

/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_splashButton_clicked()
{

    if (ostype=="0")
     splashButton_android();
   else
    splashButton_other();

}

//////////////////////////////////////////////
void MainWindow::on_mvdataButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
        //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
     }

    QString cstring = getadb() + " shell ps | grep "+xbmcpackage;
    QString command=RunProcess(cstring);


    if (command.contains(xbmcpackage))
       { QMessageBox::critical(this,"","Cannot move data while\n"+xbmcpackage+" is running!");
         return;
    }


    //cstring=getadb()+" shell /data/local/tmp/adblink/find /storage/ -type d -maxdepth 2 -perm 0771";
    //command=RunProcess(cstring);



    dataDialog dialog;

    dialog.setadb_data(getadb());

   dialog.setadb_dir(adbdir);

     dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {

        externalLocation = dialog.externalLocation();

        if(!externalLocation.startsWith("/"))
           externalLocation.prepend("/");

        if(!externalLocation.endsWith("/"))
           externalLocation.append("/") ;

        // updateLocation();

        int x = dialog.returnval2();

      switch(x){

      case 1:
      data_external();
      break;

      case 2:
      data_internal();
      break;

      case 3:
       external_thumb();
      break;

      case 4:
       internal_thumb();
      break;


      default:
       data_external();
      break;
      }




    }


}

/////////////////////////////////////////////////
void MainWindow::on_keypadButton_clicked()
{
    if (!isConnected)
          { QMessageBox::critical(0,"",devstr2);
             return;
          }

     QString cstring = getadb() + " shell input keyevent ";
     keyboardDialog dialog;
     dialog.setdaddressLabel(cstring);
     dialog.exec();

}


//////////////////////////////////////////////////
void MainWindow::on_actionView_Kodi_Log_triggered()
{


   int x = ostype.toInt();

    switch(x)
    {
    case 0:
      // android
      androidLog();
    break;

    case 1:
      // windows
        otherLog();
    break;

    case 2:
      // macos
        otherLog();
     break;

    case 3:
      // linux
        otherLog();
    break;


    default:
     androidLog();
    break;
    }




}

//////////////////////////////////////////////////
void MainWindow::androidLog()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }


    QString cstring = getadb()+" shell "+busypath+"find "+data_root+"Android/data/"+xbmcpackage+"/"+filepath+"/temp/"+" -name kodi.log";
    QString command=RunProcess(cstring);
    logfile(command);

    if (!command.contains("kodi.log"))
     {
       QMessageBox::critical(0,"","Kodi.log not found.");
        return;
      }

    logfile("opening kodi log");
    klogDialog klogdialog;
    klogdialog.passdata(getadb(),data_root,filepath);
    klogdialog.setModal(true);
    klogdialog.exec();

}


//////////////////////////////////////////////////
void MainWindow::otherLog()
{


   // iOS/ATV2	/private/var/mobile/Library/Preferences/kodi.log
   // Linux	$HOME/.kodi/temp/kodi.log
  //   Mac OS X	/Users/<username>/Library/Logs/kodi.log
  //  Windows	%APPDATA%\Kodi\kodi.log


    logfile("opening kodi log");
    oslogDialog oslogdialog;
    oslogdialog.ospassdata(ostype);
    oslogdialog.setModal(true);
    oslogdialog.exec();

}


////////////////////////////////////////////////////
void MainWindow::on_actionView_adbLink_Log_triggered()
{
    adblogDialog dialog;
    dialog.setModal(true);
    dialog.exec();

}

/////////////////////////////////////////////
void MainWindow::on_screencapButton_clicked()
{
    QString lookup=daddr;

      if(!isusb)
       lookup=lookup+":"+port;

     isConnected=find_daddr(lookup);

      if (!isConnected)
            { QMessageBox::critical(0,"",devstr2);
               return;
            }

      if(!is_busybox())
      {
          QMessageBox::critical(0,"","Busybox installation failed.");
         return;
        }

     QElapsedTimer rtimer;
     int nMilliseconds;
     rtimer.start();

         QDateTime dateTime = QDateTime::currentDateTime();
         QString dtstr = dateTime.toString("MMddyyhhmmss");

         QString cstring = getadb() + " shell screencap -p " +tempdir+dtstr+".png";


     QString command=RunProcess(cstring);

     if (!command.isEmpty())

     {
         // logfile(cstring);
         logfile(command);

         QMessageBox::critical(
                     this,
                    "",
                     "Screenshot failed");
     }

     else
     {

         // logfile(cstring);
         logfile(command);

         QString cstring = getadb() + " pull "+tempdir+dtstr+".png "  +'"'+pulldir+'"';

         command=RunProcess(cstring);


         logfile(command);


         if (!stderrtxt.contains("bytes"))
          {
             stderrtxt="";
             logfile(command);
             QMessageBox::critical(
                         this,
                        "",
                         "Screenshot failed");
         }
         else
         {
             // logfile(cstring);
             logfile(command);

             QMessageBox::information(
                            this,
                           "",
                            "Screenshot "+dtstr+ " copied to "+pulldir);
         }

         cstring = getadb() + " shell rm "+tempdir+dtstr+".png " ;
         command=RunProcess(cstring);
         // logfile(cstring);


     }

     nMilliseconds = rtimer.elapsed();
     logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



}


///////////////////////////////////////////////////////////////
void MainWindow::on_actionMount_R_W_triggered()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
     }



   //

   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();



   if (mount_system("rw"))

      {

       logfile("filesystem remounted r/w");
       QMessageBox::information(
                   this,
                  "",
                   "Filesystem mounted r/w");}
    else

   {

       logfile("filesystem not remounted!");
       QMessageBox::critical(
                      this,
                     "",
                      "Error: Filesystem not remounted r/w!");}


   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}


/////////////////////////////////////////////////////////////
void MainWindow::on_actionMount_filesystem_R_O_triggered()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    //if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
     }



 //

   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();




   if (mount_system("ro"))
    {

       logfile("filesystem remounted r/o");

       QMessageBox::information(
                   this,
                  "",
                   "Filesystem mounted r/o");}
    else

   {
       logfile("filesystem not remounted r/o!");
       QMessageBox::critical(
                      this,
                     "",
                      "Error: Filesystem not remounted r/o!");}


   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}


///////////////////////////////////////////////
bool MainWindow::is_busybox()
{

QString cstring;
QString command;
busypath="/data/local/tmp/adblink/";

cstring = getadb() + " shell ls /data/local/tmp/adbfire";
command=RunProcess(cstring);


if (!command.contains("No such file or directory"))
   {
    cstring = getadb() + " shell rm -r /data/local/tmp/adbfire";
    command=RunProcess(cstring);
   }


cstring = getadb() + " shell ls /data/local/tmp/adblink";
command=RunProcess(cstring);


if (command.contains("No such file or directory"))
   {
    cstring = getadb() + " shell mkdir -p /data/local/tmp/adblink";
    command=RunProcess(cstring);
   }

  cstring = getadb() + " shell ls /data/local/tmp/adblink/busybox";
  command=RunProcess(cstring);


  if (command.contains("No such file or directory"))
     {
      QString busybox = adbdir+"busybox";
      QString cstring = getadb() + " push "+busybox+ " /data/local/tmp/adblink/";
      QString command=RunProcess(cstring);
      if (!stderrtxt.contains("bytes"))
        {
          stderrtxt="";
          logfile("busybox install failed ");
           logfile(command);
           busypath="";
           QMessageBox::critical(0,"","busybox install failed. See log.");
           return false;
          }
     else
      {
          // logfile(cstring);

          stderrtxt="";

          logfile(command);

          cstring = getadb() + " shell chmod 755 /data/local/tmp/adblink/busybox";
          command=RunProcess(cstring);

          // logfile(cstring);
          logfile(command);

           cstring = getadb() + " shell /data/local/tmp/adblink/busybox --install -s /data/local/tmp/adblink";
           command=RunProcess(cstring);

           // logfile(cstring);
           logfile(command);

      }


  }

  return true;

}



//////////////////////////////////////////////////////////
void MainWindow::on_fpushButton_clicked()

{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }




     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }


     QElapsedTimer rtimer;
     int nMilliseconds;
     rtimer.start();

     if (data_root.isEmpty())
         data_root="/sdcard/";

    QString cstring;
    QString command;
    QString hidden;
    QString xpath = "";
    QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;

/*
    cstring = getadb() + " shell ls "+mcpath;

    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
     {
        QMessageBox::critical(
                    this,
                   "",
                    "Destination path missing");
                    return;
    }

*/

switch(ui->comboBox->currentIndex() ){
case 0:
xpath = mcpath+"/addons/";
break;

case 1:
xpath = mcpath+"/userdata/keymaps/";
break;

case 2:
xpath = mcpath+"/media/";
break;

case 3:
xpath = mcpath+"/sounds/";
break;

case 4:
xpath = mcpath+"/system/";
break;

case 5:
xpath = mcpath+"/userdata/";
break;

case 6:
xpath = mcpath+"/temp/";
break;

case 7:
xpath = "/sdcard/";
break;



default:
xpath = mcpath+"/addons/";
break;
}

QString cname = ui->comboBox->currentText();


QString dirpath = ui->customdir->text();
if (!dirpath.isEmpty())

{
    if(!dirpath.startsWith("/"))
       dirpath.prepend("/");

    if(!dirpath.endsWith("/"))
       dirpath.append("/") ;

       xpath=dirpath;
       cname = xpath;

}

 QString fileName = QFileDialog::getOpenFileName(this,
 "Push file to "+cname, pushdir, tr("Files (*)"));


 if (!fileName.isEmpty() )
 {

     QFileInfo finfo(fileName);
     pushdir = finfo.absolutePath();

     QString cstring = getadb() + " shell ls "+xpath;

     QString command=RunProcess(cstring);

     // logfile(cstring);

      if (command.contains("No such file or directory"))
       { QMessageBox::critical(
                      this,
                     "",
                      "Destination path missing. Check the Kodi partition setting in the device record, or run Kodi to set up internal folders.");
          logfile(xpath);
          logfile("Destination path missing. Check the Kodi partition setting in the device record, or run Kodi to set up internal folders.");
          return;
      }




     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", "Push "+fileName+" to "+cname+"?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           ui->progressBar->setHidden(false);
           ui->progressBar->setValue(0);


           QTimer *timer = new QTimer(this);
           connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
           timer->start(tsvalue);

           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+xpath;

           command=RunProcess(cstring);

           logfile(command);


           if (stderrtxt.contains("bytes"))
            {
               stderrtxt="";

               QMessageBox::information(
                           this,
                          "",
                          "File Pushed." );
           }
               else
           {

               stderrtxt="";

               QMessageBox::critical(
                           this,
                           "",
                        "Push failed ");
           }

   }

}

 ui->progressBar->setHidden(true);
 nMilliseconds = rtimer.elapsed();
 logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



}



////////////////////////////////////////////////////////
void MainWindow::on_fpullButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }



       if (!QDir(pulldir).exists())
         {  QMessageBox::critical(
             this,
             "adbLink",
             "Pull directory not found");
          return ;
       }



    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


    if (data_root.isEmpty())
        data_root="/sdcard/";


     QString xpath = "";
     QString cname = ui->comboBox->currentText();
     QString fileName;
     QString cstring;
    QString command;
    QString hidden;
    QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;


       switch(ui->comboBox->currentIndex() ){
       case 0:
       xpath = mcpath+"/addons/";
       break;

       case 1:
       xpath = mcpath+"/userdata/keymaps/";
       break;

       case 2:
       xpath = mcpath+"/media/";
       break;

       case 3:
       xpath = mcpath+"/sounds/";
       break;

       case 4:
       xpath = mcpath+"/system/";
       break;

       case 5:
       xpath = mcpath+"/userdata/";
       break;

       case 6:
       xpath = mcpath+"/temp/";
       break;

       case 7:
       xpath = "/sdcard/";
       break;

       default:
       xpath = mcpath+"/addons/";
       break;
       }



     QString dirpath = ui->customdir->text();
     if (!dirpath.isEmpty())

     {
         if(!dirpath.startsWith("/"))
            dirpath.prepend("/");

         if(!dirpath.endsWith("/"))
            dirpath.append("/") ;

            xpath=dirpath;


     }





     cstring = getadb() + " shell "+busypath+"busybox find " +xpath+ " -type f ";

     // cstring = getadb() + " shell ls " +xpath;

     command=RunProcess(cstring);


     if (command.isEmpty() || command.contains("No such file or directory"))
        { QMessageBox::critical(this,"","No files found");

         // logfile(cstring);
         logfile(command);
         logfile("no files found!");
         return;
         }


     QFile file21(adbdir+"temp.txt");

       //if(!file21.open(QFile::WriteOnly |
       //              QFile::Text))

     if(!file21.open(QFile::WriteOnly))

       {
           QMessageBox::critical(this,"","Error creating file!");
           logfile("error creating file: "+adbdir+"temp.txt");

           return;
       }


       QTextStream out1(&file21);
       out1  << command << endl;

       file21.flush();
       file21.close();



     usbfileDialog sddialog;
     sddialog.setModal(true);
     sddialog.setData("Select file to pull");
     if(sddialog.exec() == QDialog::Accepted)
     fileName = sddialog.binfileName();
     else return;

     if (fileName.isEmpty())
        {
         QMessageBox::critical(this,"","No file selected");
         logfile("no file selected");
         return;
         }


     // QMessageBox::critical(this,"",xpath+"\n"+fileName);



     ui->progressBar->setHidden(false);
     ui->progressBar->setValue(0);


     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
     timer->start(tsvalue);


             // cstring = getadb() + " pull "+xpath+fileName+" " +'"'+pulldir+'"';

             cstring = getadb() + " pull "+'"'+fileName+'"'+" "+'"'+pulldir+'"';
             command=RunProcess(cstring);
             logfile(command);
             //QMessageBox::critical(this,"",command);


             if (!stderrtxt.contains("bytes"))
              {

                 stderrtxt="";
                 logfile("pull failed");
                 QMessageBox::critical(
                             this,
                            "",
                             "Pull failed");}
                 else
             {

                 logfile("pull succeeded");
                 QMessageBox::information(
                             this,
                             "",
                             "Pull succeeded");}

             ui->progressBar->setHidden(true);
             nMilliseconds = rtimer.elapsed();
             logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}



////////////////////////////////////////////////////////////////
void MainWindow::on_fdellButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
          // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
      }


    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();




    if (data_root.isEmpty())
        data_root="/sdcard/";


     QString xpath = "";
     QString cname = ui->comboBox->currentText();
     QString fileName;
     QString pullfile;
     QString cstring;
    QString command;
    QString hidden;
    QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;

       switch(ui->comboBox->currentIndex() ){
       case 0:
       xpath = mcpath+"/addons/";
       break;

       case 1:
       xpath = mcpath+"/userdata/keymaps";
       break;

       case 2:
       xpath = mcpath+"/media/";
       break;

       case 3:
       xpath = mcpath+"/sounds/";
       break;

       case 4:
       xpath = mcpath+"/system/";
       break;

       case 5:
       xpath = mcpath+"/userdata/";
       break;

       case 6:
       xpath = mcpath+"/temp/";
       break;

       case 7:
       xpath = "/sdcard/";
       break;

       default:
       xpath = mcpath+"/addons/";
       break;
       }


    QString dirpath = ui->customdir->text();
       if (!dirpath.isEmpty())

       {
           if(!dirpath.startsWith("/"))
              dirpath.prepend("/");

           if(!dirpath.endsWith("/"))
              dirpath.append("/") ;

              xpath=dirpath;
              cname = xpath;
       }




    cstring = getadb() + " shell "+busypath+"busybox find " +xpath+ " -type f ";
   // cstring = getadb() + " shell "+busypath+"busybox find " +xpath;

  // cstring = getadb() + " shell ls " +xpath;

  command=RunProcess(cstring);

  if (command.isEmpty() || command.contains("No such file or directory"))
     { QMessageBox::critical(this,"","No files found");

      // logfile(cstring);
      logfile(command);
      logfile("no files found!");
      return;
      }

  QFile file21(adbdir+"temp.txt");

        if(!file21.open(QFile::WriteOnly))
    {

        logfile(adbdir+"temp.txt");
        logfile("error creating file");
        QMessageBox::critical(this,"","Error creating file!");
        return;
    }


    QTextStream out1(&file21);
    out1  << command << endl;

    file21.flush();
    file21.close();

  usbfileDialog sddialog;
  sddialog.setModal(true);
  sddialog.setData("Select file to delete");
  if(sddialog.exec() == QDialog::Accepted)
  pullfile = sddialog.binfileName();
  else return;

  if (pullfile.isEmpty())
     {
      QMessageBox::critical(this,"","No file selected");
      return;
      }


  QMessageBox::StandardButton reply3;
    reply3 = QMessageBox::question(this, "", "Delete "+pullfile,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply3 == QMessageBox::No)
        return;


             // cstring = getadb() + " shell rm "+pullfile;
                cstring = getadb() + " shell rm -r "+'"'+pullfile+'"';
             //   cstring = getadb() + " push "+'"'+fileName+'"'+ " "+xpath;



             command=RunProcess(cstring);

             if (command.contains("exist"))
              {
                 // logfile(cstring);
                 logfile(command);
                 logfile( "Deletion failed");
                 QMessageBox::critical(
                             this,
                            "",
                             "Deletion failed");}
                 else
                  {
                    // logfile(cstring);
                    logfile(command);
                    logfile("Deletion succeeded");
                    QMessageBox::information(
                             this,
                             "",
                             "Deletion succeeded");}


 nMilliseconds = rtimer.elapsed();
 logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}




void MainWindow::on_fclearButton_clicked()
{
     ui->customdir->setText("");
}


////////////////////////////////////////////
void MainWindow::on_backupButton_clicked()

{
    if (ostype=="0")
      backupAndroid();
   else
       backupOther();

}


/////////////////////////////////////////////
void MainWindow::on_restoreButton_clicked()

{
    if (ostype=="0")
      restoreAndroid();
   else
      restoreOther();

}

///////////////////////////////////////////
void MainWindow::backupOther()
{


    QString filecheck = filepath+"/userdata";


   if(!QDir(filecheck).exists())
    {
       QMessageBox::information(this,"",filecheck+" not found. Can't proceed.");
       logfile("BACKUP: "+ filecheck+" not found. Can't proceed.");
       return;
    }

    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Backup Destination"),
                                                  hdir,
                                                  QFileDialog::ShowDirsOnly
                                        | QFileDialog::DontResolveSymlinks);

   if (!dir.isEmpty() )
    {
     QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Backup", "backup Kodi to "+dir+"?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No)
      {
          return;
      }
   }

logfile("Backing up Kodi");

   ui->progressBar->setHidden(false);
   ui->progressBar->setValue(0);


   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
   timer->start(tsvalue);


   QFuture <void> future1 = QtConcurrent::run(this,&MainWindow::copyFolder,filepath,dir);
   watcher.setFuture(future1);


}



///////////////////////////////////////////
void MainWindow::restoreOther()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Backup Folder"),
                                                  hdir,
                                                  QFileDialog::ShowDirsOnly
                                        | QFileDialog::DontResolveSymlinks);

   if (!dir.isEmpty() )
    {
     QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Restore", "restore Kodi from "+dir+"?\nThis will delete the current setup.",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No)
      {
          return;
      }
   }


   logfile("Restoring Kodi");

   ui->progressBar->setHidden(false);
   ui->progressBar->setValue(0);


   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
   timer->start(tsvalue);


   QFuture <void> future1 = QtConcurrent::run(this,&MainWindow::kodiFolder,dir,filepath);
   watcher.setFuture(future1);


}





/////////////////////////////////////////////////////////////////////

void MainWindow::copyFolder(QString sourceFolder, QString destFolder)
{
QDir sourceDir(sourceFolder);
if(!sourceDir.exists())
return;

QDir destDir(destFolder);
if(!destDir.exists())
{
destDir.mkdir(destFolder);
}

QStringList files = sourceDir.entryList(QDir::Files);
for(int i = 0; i< files.count(); i++)
{
QString srcName = sourceFolder + "/" + files[i];
QString destName = destFolder + "/" + files[i];
QFile::copy(srcName, destName);
}
files.clear();
files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
for(int i = 0; i< files.count(); i++)
{
QString srcName = sourceFolder + "/" + files[i];
QString destName = destFolder + "/" + files[i];
copyFolder(srcName, destName);
}
}



/////////////////////////////////////////////////////////////////////

void MainWindow::kodiFolder(QString sourceFolder, QString destFolder)
{
QDir sourceDir(sourceFolder);
if(!sourceDir.exists())
return;

QDir destDir(destFolder);

if(destDir.exists())
    destDir.removeRecursively();

if(!destDir.exists())
{
destDir.mkdir(destFolder);
}

QStringList files = sourceDir.entryList(QDir::Files);
for(int i = 0; i< files.count(); i++)
{
QString srcName = sourceFolder + "/" + files[i];
QString destName = destFolder + "/" + files[i];
QFile::copy(srcName, destName);
}
files.clear();
files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
for(int i = 0; i< files.count(); i++)
{
QString srcName = sourceFolder + "/" + files[i];
QString destName = destFolder + "/" + files[i];
copyFolder(srcName, destName);
}
}



/////////////////////////////////////////////
void MainWindow::finishedCopy()
{
  ui->progressBar->setHidden(true);
  logfile("Finished successfully");
  QMessageBox::information(this,"","Finished successfully");
}




///////////////////////////////////////////
void MainWindow::editOther()
{


    QString mcpath=filepath;

     mcpath=mcpath+"/userdata/";


    if (!QFileInfo::exists(mcpath))
    {
         QMessageBox::information(this,"","userdata folder not found" );
         return;
    }


     QString fileName = QFileDialog::getOpenFileName(this,
    "Choose XML file", mcpath, tr("Files (*.xml)"));



     QFile file1(fileName);

     if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     if (!fileName.isEmpty() )
     {




                 QFileInfo fileInfo(fileName);
                 QString filename(fileInfo.fileName());
                 QString xmlfile = file1.readAll();
                 editorDialog dialog;
                 dialog.seteditor(xmlfile);
                 dialog.setfilename(filename);

                dialog.setModal(true);

                  if(dialog.exec() == QDialog::Accepted)
                    {


                      QMessageBox::StandardButton reply;
                        reply = QMessageBox::question(this, "Save","Save "+ fileName+"?",
                            QMessageBox::Yes|QMessageBox::No);
                        if (reply == QMessageBox::No)
                          return;


                      xmlfile = dialog.xmlfile();





                       //QMessageBox::information(this,"",xmlfile);


                       QFile::copy(fileName, fileName+".bak");

                       QFile caFile(fileName);
                           caFile.open(QIODevice::WriteOnly | QIODevice::Text);


                           QTextStream outStream(&caFile);
                           outStream << xmlfile;
                           caFile.close();

              }

   }


}




////////////////////////////////////////////////////////
void MainWindow::editAndroid()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }


    if (data_root.isEmpty())
        data_root="/sdcard/";

    QString tempfile1;
    QString tempfile2;
     QString xpath = "";
     QString fileName;
     QString cstring;
    QString command;
    QString mcpath=data_root+ "Android/data/"+xbmcpackage+filepath;


       xpath = mcpath+"/userdata/";



      cstring = getadb() + " shell "+busypath+"busybox find " +xpath+ " -maxdepth 1 -name *.xml ";
      command=RunProcess(cstring);


     if (command.isEmpty() || command.contains("No such file or directory"))
        { QMessageBox::critical(this,"","No files found");

         // logfile(cstring);
         logfile(command);
         logfile("no files found!");
         return;
         }


     QFile file21(adbdir+"temp.txt");

     if(!file21.open(QFile::WriteOnly))

       {
           QMessageBox::critical(this,"","Error creating temp file!");
           logfile("error creating file: "+adbdir+"temp.txt");

           return;
       }


       QTextStream out1(&file21);
       out1  << command << endl;

       file21.flush();
       file21.close();



     usbfileDialog sddialog;
     sddialog.setModal(true);
     sddialog.setData("Select file to edit");
     if(sddialog.exec() == QDialog::Accepted)
     fileName = sddialog.binfileName();
     else return;

     if (fileName.isEmpty())
        {
         QMessageBox::critical(this,"","No file selected");
         logfile("no file selected");
         return;
         }


     // QMessageBox::critical(this,"","");


     QString filename(fileName.mid(fileName.lastIndexOf("/")+1,fileName.length()));

             cstring = getadb() + " pull "+'"'+fileName+'"'+" "+'"'+adbdir+'"'+"/"+filename;
             command=RunProcess(cstring);


             if (!stderrtxt.contains("bytes"))
              {

                 //stderrtxt="";
                 logfile("edit failed");
                 logfile(command);
                 QMessageBox::critical(
                             this,
                            "",
                             "Edit failed "+stderrtxt);
                 return;
             }



             QFile file1(adbdir+filename);

             if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
                 return;

             QString xmlfile = file1.readAll();
             editorDialog dialog;
             dialog.seteditor(xmlfile);
             dialog.setfilename(filename);

             tempfile2 = adbdir+"/"+filename;
             tempfile1 = adbdir+"/"+filename+".bak";


              dialog.setModal(true);

              if(dialog.exec() == QDialog::Accepted)
                {


                  QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "Save","Save "+ fileName+"?",
                        QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::No)
                      return;


                  xmlfile = dialog.xmlfile();


                   //QMessageBox::information(this,"",xmlfile);



                   QFile::copy(adbdir+"/"+filename, adbdir+filename+".bak");
                   QFile caFile( adbdir+"/"+filename);
                   caFile.open(QIODevice::WriteOnly | QIODevice::Text);
                   QTextStream outStream(&caFile);
                   outStream << xmlfile;
                   caFile.close();

                   cstring = getadb() + " push "+'"'+tempfile1+'"'+ " "+xpath;
                   command=RunProcess(cstring);
                   logfile(command);

                   if (!stderrtxt.contains("bytes"))
                    { stderrtxt="";
                       QMessageBox::critical(this,"","Backup of "+filename+ "failed. Edit abandoned." );
                      logfile("Backup of "+filename+ "failed");
                       return;
                   }



                   cstring = getadb() + " push "+'"'+tempfile2+'"'+ " "+xpath;
                   command=RunProcess(cstring);
                   logfile(command);

                   if (!stderrtxt.contains("bytes"))
                    { stderrtxt="";
                      QMessageBox::critical(this,"","Problem replacing "+filename+ ". Edit abandoned." );
                      logfile("Problem replacing "+filename+ ". Edit abandoned." );
                       return;
                   }


              }



              QFile file2 (tempfile1);
              file2.remove();

              QFile file3 (tempfile2);
              file3.remove();




}


////////////////////////////////////////////////////
void MainWindow::on_actionEdit_XML_files_triggered()
{

    if (ostype=="0")
      editAndroid();
   else
       editOther();

}

////////////////////////////////////////////////////////
void MainWindow::editGeneric()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }


    if (data_root.isEmpty())
        data_root="/sdcard/";

    QString tempfile1;
    QString tempfile2;
     QString xpath = "";
     QString fileName;
     QString cstring;
    QString command;


       QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;


          switch(ui->comboBox->currentIndex() ){
          case 0:
          xpath = mcpath+"/addons/";
          break;

          case 1:
          xpath = mcpath+"/userdata/keymaps/";
          break;

          case 2:
          xpath = mcpath+"/media/";
          break;

          case 3:
          xpath = mcpath+"/sounds/";
          break;

          case 4:
          xpath = mcpath+"/system/";
          break;

          case 5:
          xpath = mcpath+"/userdata/";
          break;

          case 6:
          xpath = mcpath+"/temp/";
          break;

          case 7:
          xpath = "/sdcard/";
          break;

          default:
          xpath = mcpath+"/addons/";
          break;
          }



        QString dirpath = ui->customdir->text();
        if (!dirpath.isEmpty())

        {
            if(!dirpath.startsWith("/"))
               dirpath.prepend("/");

            if(!dirpath.endsWith("/"))
               dirpath.append("/") ;

               xpath=dirpath;


        }


      cstring = getadb() + " shell "+busypath+"busybox find " +xpath+" -type f";


      command=RunProcess(cstring);
      logfile(cstring);
      logfile(command);


     if (command.isEmpty() || command.contains("No such file or directory"))
        { QMessageBox::critical(this,"","No files found");

         // logfile(cstring);
         logfile(command);
         logfile("no files found!");
         return;
         }


     QFile file21(adbdir+"temp.txt");

     if(!file21.open(QFile::WriteOnly))

       {
           QMessageBox::critical(this,"","Error creating temp file!");
           logfile("error creating file: "+adbdir+"temp.txt");

           return;
       }


       QTextStream out1(&file21);
       out1  << command << endl;

       file21.flush();
       file21.close();



     usbfileDialog sddialog;
     sddialog.setModal(true);
     sddialog.setData("Select file to edit");
     if(sddialog.exec() == QDialog::Accepted)
     fileName = sddialog.binfileName();
     else return;

     if (fileName.isEmpty())
        {
         QMessageBox::critical(this,"","No file selected");
         logfile("no file selected");
         return;
         }


     // QMessageBox::critical(this,"","");


     QString filename(fileName.mid(fileName.lastIndexOf("/")+1,fileName.length()));

              cstring = getadb() + " pull "+'"'+fileName+'"'+" "+'"'+adbdir+'"'+"/"+filename;
              command=RunProcess(cstring);

             logfile(command);


             if (!stderrtxt.contains("bytes"))
              {
                 stderrtxt="";
                 logfile("edit failed");
                 logfile(command);
                 QMessageBox::critical(
                             this,
                            "",
                             "Edit failed");
                 return;
             }



             QFile file1(adbdir+filename);

             if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
                 return;

             QString xmlfile = file1.readAll();
             editorDialog dialog;
             dialog.seteditor(xmlfile);
             dialog.setfilename(filename);

            tempfile2 = adbdir+"/"+filename;
            tempfile1 = adbdir+"/"+filename+".bak";

              dialog.setModal(true);

              if(dialog.exec() == QDialog::Accepted)
                {


                  QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "Save","Save "+ fileName+"?",
                        QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::No)
                      return;


                  xmlfile = dialog.xmlfile();

                   QFile::copy(adbdir+"/"+filename, adbdir+filename+".bak");
                   QFile caFile( adbdir+"/"+filename);
                   caFile.open(QIODevice::WriteOnly | QIODevice::Text);
                   QTextStream outStream(&caFile);
                   outStream << xmlfile;
                   caFile.close();


                   tempfile2 = adbdir+"/"+filename;
                   tempfile1 = adbdir+"/"+filename+".bak";

                   cstring = getadb() + " push "+'"'+tempfile1+'"'+ " "+xpath;
                   command=RunProcess(cstring);
                   logfile(command);

                   if (!stderrtxt.contains("bytes"))
                    { stderrtxt="";
                      QMessageBox::critical(this,"","Backup of "+filename+ "failed. Edit abandoned." );
                      logfile("Backup of "+filename+ "failed");
                       return;
                   }



                   cstring = getadb() + " push "+'"'+tempfile2+'"'+ " "+xpath;
                   command=RunProcess(cstring);
                   logfile(command);

                   if (!stderrtxt.contains("bytes"))
                    { QMessageBox::critical(this,"","Problem replacing "+filename+ ". Edit abandoned." );
                      logfile("Problem replacing "+filename+ ". Edit abandoned." );
                       return;
                   }


              }


              QFile file2 (tempfile1);
              file2.remove();

              QFile file3 (tempfile2);
              file3.remove();


}

/////////////////////////////////////////

void MainWindow::on_editButton_clicked()
{
editGeneric();
}

//////////////////////////////////////////////////////////
void MainWindow::on_actionPaste_path_triggered()
{
    QClipboard *pathClipboard = QApplication::clipboard();
    pathClipboard->setText("PATH=$PATH:/data/local/tmp/adblink\n");
}


//////////////////////////////////////////////////////////
void MainWindow::on_actionTest_adb_connection_triggered()
{


    if (ostype !="0")
    { QMessageBox::critical(0,"","Android devices only");
       return;
    }



    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

    // set PATH=%PATH%;C:\xampp\php



     QString bstring = getadb() + " logcat";



    logfile("detaching console process");

     QString cstring = "";


     if (os == 1)

        {

        QString commstr = adbdir+"adbtest.bat";
        QFile file(commstr);

            if(!file.open(QFile::WriteOnly |
                          QFile::Text))
            {
                logfile("error creating adbtest.bat!");
                QMessageBox::critical(this,"","Error creating bat file!");
                return;
            }



            QTextStream out(&file);
            out  << "set PATH=%PATH%;"+QDir::currentPath()+";"<< endl;
            out << bstring << endl;



            file.flush();
            file.close();

            cstring = "cmd /k " +QDir::currentPath()+"/adbtest.bat";
            QProcess::startDetached(cstring);



     }

     QString pathdir = QCoreApplication::applicationDirPath() +"/adbfiles";

       if (os == 2 || os == 0)
         {

           QString commstr = adbdir+"adbtest.sh";


           QFile file(commstr);

               if(!file.open(QFile::WriteOnly |
                             QFile::Text))
               {
                   logfile("error creating adbtest!");
                   QMessageBox::critical(this,"","Error creating sh file!");
                   return;
               }



               QTextStream out(&file);
                out  << "#!/bin/sh" << endl;
                out  << "export PATH="+pathdir+":$PATH" << endl;
                out  << bstring << endl;
                out  << "/bin/sh" << endl;


               file.flush();
               file.close();


               cstring = "chmod 0755 " + commstr ;
               QString command=RunProcess(cstring);



       }


       if (os == 2)
        {
       QString cstring = "open -a Terminal.app "+adbdir+"adbtest.sh";
       QProcess::startDetached(cstring);
        }




       if (os == 0)
        {
           // cstring = "x-terminal-emulator --working-directory="+adbdir+"/adbfiles";
            cstring = "gnome-terminal --working-directory="+adbdir+ " -x "+adbdir+"adbtest.sh";
           QProcess::startDetached(cstring);

         }


}



//////////////////////////////////////////////////////////
void MainWindow::usbbuttons(bool isusb)
{

    if(!isusb)
           {
              ui->connButton->setDisabled(false);
              ui->disButton->setDisabled(false);
              }
          else
              {
                ui->connButton->setDisabled(true);
                ui->disButton->setDisabled(true);
              }

}
