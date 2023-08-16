#ifndef TEST_H
#define TEST_H

#include <QDockWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QLineEdit>
#include <QMainWindow>
#include <obs.h>
#include <obs-frontend-api.h>

class MainWidget : public QDockWidget {
    Q_OBJECT

    public:
        explicit MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

    private:
        QWidget *widget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(); 
        QGridLayout *gridLayout = new QGridLayout(); 
        QPushButton *fullscreenButton = new QPushButton("FullScreen");
        QPushButton *lowerthirdButton = new QPushButton("Lower Third");
        QPushButton *scriptureButton = new QPushButton("Scripture View");
        QNetworkAccessManager *manager;
        QNetworkRequest request;
        QLabel *ipLabel = new QLabel("IP Address:");
        QLineEdit *ipInput;

    private slots:
        void FullscreenButtonClicked();
        void lowerthirdButtonClicked();
        void scriptureButtonClicked();
        void ipInputEdited();
};      

#endif
