#include "main-widget.hpp"

MainWidget::MainWidget(QWidget *widgetParent)
	: QDockWidget("Propresenter Controller", widgetParent)
{
	this->parent = widgetParent;

	ipInput = new QLineEdit();

	gridLayout->addWidget(fullscreenButton, 0, 0);
	gridLayout->addWidget(lowerthirdButton, 0, 1);
	gridLayout->addWidget(scriptureButton, 1, 0);

	QHBoxLayout *ipLayout = new QHBoxLayout();
	ipLayout->addWidget(ipLabel);
	ipLayout->addWidget(ipInput);

	mainLayout->addLayout(gridLayout);
	mainLayout->addLayout(ipLayout);

	widget->setLayout(mainLayout);

	setWidget(widget);

	setVisible(false);
	setFloating(true);
	resize(300, 300);

	std::string profilePath = obs_frontend_get_current_profile_path();
	profilePath.append("/obs-propresenter.json");

	// get the value of the ip from the obs data file if it exists
	obs_data_t *settings =
		obs_data_create_from_json_file_safe(profilePath.c_str(), "bak");
	if (settings) {
		const char *ip = obs_data_get_string(settings, "ip");
		if (ip) {
			ipInput->setText(ip);
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

	QObject::connect(ipInput, SIGNAL(editingFinished()),
			 SLOT(ipInputEdited()));

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

void MainWidget::ipInputEdited()
{
	// save the ipText to the obs data file
	obs_data_t *settings = obs_data_create();
	obs_data_set_string(settings, "ip",
			    ipInput->text().toStdString().c_str());
	// now save it to json

	//get a string from the obs_frontend_get_current_profile_path()
	//then append the file name to it then save it
	std::string profilePath = obs_frontend_get_current_profile_path();
	profilePath.append("/obs-propresenter.json");

	obs_data_save_json(settings, profilePath.c_str());
	obs_data_release(settings);
}

void MainWidget::FullscreenButtonClicked()
{
	request.setUrl(
		QUrl("http://" + ipInput->text() + ":1025/v1/look/0/trigger"));
	manager->get(request);
}

void MainWidget::lowerthirdButtonClicked()
{
	request.setUrl(
		QUrl("http://" + ipInput->text() + ":1025/v1/look/1/trigger"));
	manager->get(request);
}

void MainWidget::scriptureButtonClicked()
{
	request.setUrl(
		QUrl("http://" + ipInput->text() + ":1025/v1/look/2/trigger"));
	manager->get(request);
}
