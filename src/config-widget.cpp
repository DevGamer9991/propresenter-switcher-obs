#include "config-widget.hpp"
#include "main-widget.hpp"

ConfigWidget::ConfigWidget(QWidget *widgetParent)
	: QDockWidget("Propresenter Controller Config", widgetParent)
{
	this->parent = widgetParent;

	setFeatures(QDockWidget::DockWidgetFloatable |
		    QDockWidget::DockWidgetMovable);

	mainLayout->addWidget(new QLabel("Config Widget"));

	mainLayout->addWidget(ipInput);

	exitButtonsLayout->addWidget(okButton);
	exitButtonsLayout->addWidget(cancelButton);

	mainLayout->addLayout(exitButtonsLayout);

	widget->setLayout(mainLayout);

	setWidget(widget);

	setVisible(false);
	setFloating(true);
	resize(150, 75);

	QObject::connect(okButton, SIGNAL(clicked()), SLOT(okButtonClicked()));
	QObject::connect(cancelButton, SIGNAL(clicked()),
			 SLOT(cancelButtonClicked()));
}

ConfigWidget::~ConfigWidget(){

};

void ConfigWidget::okButtonClicked()
{

	MainWidget *mainWidget = (MainWidget *)parent;

	mainWidget->setIP(ipInput->text());

	setVisible(false);
}

void ConfigWidget::cancelButtonClicked()
{
	setVisible(false);
}
