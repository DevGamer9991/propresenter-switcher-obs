#include "main-widget.hpp"

MainWidget::MainWidget(QWidget *widgetParent)
	: QDockWidget("Propresenter Controller", widgetParent)
{
	this->parent = widgetParent;

	setFeatures(QDockWidget::DockWidgetFloatable |
		    QDockWidget::DockWidgetMovable);

	gridLayout->addWidget(fullscreenButton, 0, 0);
	gridLayout->addWidget(lowerthirdButton, 0, 1);
	gridLayout->addWidget(scriptureButton, 1, 0);

	mainLayout->addLayout(gridLayout);

	mainLayout->addWidget(configButton);

	widget->setLayout(mainLayout);

	setWidget(widget);

	setVisible(false);
	setFloating(true);
	resize(300, 150);

	std::string profilePath = obs_frontend_get_current_profile_path();
	profilePath.append("/obs-propresenter.json");

	// get the value of the ip from the obs data file if it exists
	obs_data_t *settings =
		obs_data_create_from_json_file_safe(profilePath.c_str(), "bak");
	if (settings) {
		const char *ipSetting = obs_data_get_string(settings, "ip");
		if (ipSetting) {
			ip = ipSetting;
		}
	}

	obs_data_release(settings);

	manager = new QNetworkAccessManager();
	QObject::connect(manager, &QNetworkAccessManager::finished, this,
			 [=](QNetworkReply *reply) {
				 if (reply->error()) {
					 QMessageBox::information(
						 widgetParent, "reply",
						 reply->errorString());
					 return;
				 }

				 QString answer = reply->readAll();
			 });

	QObject::connect(configButton, SIGNAL(clicked()),
			 SLOT(configButtonClicked()));
	QObject::connect(fullscreenButton, SIGNAL(clicked()),
			 SLOT(FullscreenButtonClicked()));
	QObject::connect(lowerthirdButton, SIGNAL(clicked()),
			 SLOT(lowerthirdButtonClicked()));
	QObject::connect(scriptureButton, SIGNAL(clicked()),
			 SLOT(scriptureButtonClicked()));
}

MainWidget::~MainWidget()
{
	delete manager;
};

void MainWidget::setIP(QString newIP)
{
	obs_data_t *settings = obs_data_create();
	obs_data_set_string(settings, "ip", newIP.toStdString().c_str());

	std::string profilePath = obs_frontend_get_current_profile_path();
	profilePath.append("/obs-propresenter.json");

	obs_data_save_json(settings, profilePath.c_str());
	obs_data_release(settings);

	ip = newIP;
}

void MainWidget::FullscreenButtonClicked()
{
	request.setUrl(QUrl("http://" + ip + ":1025/v1/look/0/trigger"));
	manager->get(request);
}

void MainWidget::lowerthirdButtonClicked()
{
	request.setUrl(QUrl("http://" + ip + ":1025/v1/look/1/trigger"));
	manager->get(request);
}

void MainWidget::scriptureButtonClicked()
{
	request.setUrl(QUrl("http://" + ip + ":1025/v1/look/2/trigger"));
	manager->get(request);
}

void MainWidget::configButtonClicked()
{
	ConfigWidget *configWidget = new ConfigWidget(this);
	configWidget->ipInput->setText(ip);
	configWidget->show();
}