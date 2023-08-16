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

class MainWidget : public QDockWidget {
    Q_OBJECT

    public:
        explicit MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

    private:
        QWidget *parent = nullptr;
        QGridLayout *layout = new QGridLayout(); // Declare a QGridLayout
        QPushButton *fullscreenButton = new QPushButton("FullScreen");
        QNetworkAccessManager *manager;
        QNetworkRequest request;
        QLineEdit *ipInput;

    private slots:
        void FullscreenButtonClicked();
        void lowerthirdButtonClicked();
        void scriptureButtonClicked();
};      

#endif
