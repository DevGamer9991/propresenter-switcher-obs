#ifndef MAIN_HPP
#define MAIN_HPP

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
#include <QString>
#include <obs.h>
#include <obs-frontend-api.h>
#include "config-widget.hpp"

class MainWidget : public QDockWidget {
	Q_OBJECT

public:
	explicit MainWidget(QWidget *widgetParent = nullptr);
	~MainWidget();

private:
	QWidget *parent = nullptr;
	QWidget *widget = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QGridLayout *gridLayout = new QGridLayout();
	QPushButton *fullscreenButton = new QPushButton("FullScreen");
	QPushButton *lowerthirdButton = new QPushButton("Lower Third");
	QPushButton *scriptureButton = new QPushButton("Scripture View");
	QNetworkAccessManager *manager;
	QNetworkRequest request;
	QLineEdit *ipInput = new QLineEdit();
	QPushButton *configButton = new QPushButton("Configure");
	QString ip;

public slots:
	void setIP(QString newIP);

private slots:
	void FullscreenButtonClicked();
	void lowerthirdButtonClicked();
	void scriptureButtonClicked();
	void configButtonClicked();
};

#endif
