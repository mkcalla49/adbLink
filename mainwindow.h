#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

void downloadFile(const QString &url, const QString &path);

    void on_actionAbout_triggered();

    void on_connButton_clicked();

    void TimerEvent();

    void readInc();

    void on_sideload_Button_clicked();

    void on_disButton_clicked();

    void on_actionQuit_triggered();

    void on_uninstall_Button_clicked();

    bool installAPK(QString filename);

    void on_actionHelp_triggered();

    void on_backupButton_clicked();

    void on_fpushButton_clicked();

    void on_fpullButton_clicked();

    void on_restoreButton_clicked();


    void  cacheButton_other();
    void  cacheButton_android();

    void on_pushRemote_clicked();

    void on_adbshellButton_clicked();

    void splashButton_android();

  void splashButton_other();

    void finishedCopy();

    void notAndroid();
    void isAndroid();

    void delay(int secs);

   void insertDevice();

   void backupAndroid();

   void createTables();

    void editAndroid();

    void editOther();

   QString getadb();

   void delayTimer(int rdelay);

   QString RunProcess(QString cstring);

   void usbbuttons(bool isusb);

   void editGeneric();

   void rotate_logfile();

   void logfile(QString line);

   void rebootDevice(QString reboot);

   bool mount_system(QString mnt);

   bool fileExists(QString path);

   bool is_su();

   bool is_busybox();


    QString strip (QString str);


    void blank_entry_form();

    void kill_server();

   void start_server();

  //  void adberror();

   bool is_package(QString package);


   int getRows();


    bool find_daddr(QString);

    void updateRoot();

    void androidLog();

    void updateDevice(QString olddescription);

    void copyFolder(QString sourceFolder, QString destFolder);

    void kodiFolder(QString sourceFolder, QString destFolder);

    void getRecord(QString descrip);

    void on_actionReboot_triggered();

    void otherLog();

    void deleteRecord(QString descrip);

    void open_pref_database();

    bool isConnectedToNetwork();

    void addcolumn1();

    void on_actionRecovery_triggered();


    void on_fdellButton_clicked();

    void onArmCompleted();


    void on_donate_clicked();

    void get_data();

     void get_kodi_address(QString mcurl);

    void onReqCompleted();

    void on_actionView_Log_triggered();

    void on_actionDownload_Kodi_triggered();

    void on_editRecord_clicked();


    void dataentry(int flag);

    void data_external();

    void data_internal();

    void external_thumb();

    void internal_thumb();

    void loaddevicebox();


    void on_actionSplash_Screen_triggered();

    void on_doConsole_clicked();

    void on_killServer_clicked();

    void on_refreshConnectedDevices_clicked();


   void on_listDevices_doubleClicked();

   void on_newRecord_clicked();

  void  on_pushRemote_android();
  void  on_pushRemote_other();

   void on_delRecord_clicked();


   void on_cacheButton_clicked();

   void on_splashButton_clicked();

   void on_mvdataButton_clicked();

   void on_actionView_Kodi_Log_triggered();

   void on_actionView_adbLink_Log_triggered();

   void on_screencapButton_clicked();

   void on_actionMount_R_W_triggered();

   void on_actionMount_filesystem_R_O_triggered();

  void restoreAndroid();

   void on_fclearButton_clicked();

   void backupOther();
   void restoreOther();

   void on_actionEdit_XML_files_triggered();

   void on_editButton_clicked();



   void on_actionPaste_path_triggered();

   void on_actionTest_adb_connection_triggered();

   void on_actionStop_Application_triggered();

   void on_actionStart_Application_triggered();

   void on_getkodiButton_clicked();

   void on_keypadButton_clicked();

   void on_actionDownload_SPMC_triggered();

private:
    Ui::MainWindow *ui;



};




#endif // MAINWINDOW_H
