#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    remote_url=ui->lineEdit->text();

}

void MainWindow::ReqRemote(const QString &path)
{
    if(!reply)
    {
        QNetworkRequest request;
        request.setUrl(QUrl(remote_url+path));
        reply=net_mgr.get(request);
        connect(reply, &QNetworkReply::finished, this, &MainWindow::onNetworkFinished);
    }
}

void MainWindow::ReqText(const QString &path)
{
    net_callback=[this](){
        ui->label_info->setText(reply->readAll());
    };
    ReqRemote(path);
}

void MainWindow::onNetworkFinished()
{
    if(reply)
    {
        if(net_callback)
            net_callback();
        reply->deleteLater();
        reply=nullptr;
    }
}

void MainWindow::ReqFile(const QString &path, const QString &local)
{
    net_callback=[this,local](){
        QByteArray data=reply->readAll();
        QFile f(local);
        if(f.open(QIODevice::WriteOnly))
        {
            f.write(data);
        }
    };
    ReqRemote(path);
}

void MainWindow::ReqImage(const QString &path, const QString &local)
{
    net_callback=[this,local](){
        QByteArray data=reply->readAll();
        QFile f(local);
        if(f.open(QIODevice::WriteOnly))
        {
            f.write(data);
        }
        QPicture pic;
        pic.load(local);
        ui->label_pic->setPicture(pic);
    };
    ReqRemote(path);
}

void MainWindow::on_pushButton_3_clicked()
{
    ReqText("/status");
}

void MainWindow::on_pushButton_2_clicked()
{
    ReqText("/capture");
}

void MainWindow::on_pushButton_4_clicked()
{
    ReqImage("/get_cap","here2.jpg");
}

void MainWindow::on_pushButton_5_clicked()
{
    ReqImage("/get/here1.jpg","here1.jpg");
}

void MainWindow::on_pushButton_6_clicked()
{
    ReqFile("/get/faces.txt","faces.txt");
}
