#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <functional>
#include <QPicture>
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
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QString remote_url;
    QNetworkAccessManager net_mgr;
    QNetworkReply*reply;
    std::function<void()> net_callback;

    void ReqRemote(const QString&path);
    void ReqText(const QString& path);
    void ReqFile(const QString& path,const QString&local);
    void ReqImage(const QString& path,const QString&local);
    void onNetworkFinished();
};

#endif // MAINWINDOW_H
