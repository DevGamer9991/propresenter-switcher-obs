#include "main-widget.hpp"

MainWidget::MainWidget(QWidget *parent) : QDockWidget("Propresenter Controller", parent) {
this->parent = parent;

    QWidget *widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(); // create a vertical layout
    QGridLayout *gridLayout = new QGridLayout(); // create a grid layout
    QPushButton *fullscreenButton = new QPushButton("FullScreen");
    QPushButton *lowerthirdButton = new QPushButton("Lower Third");
    QPushButton *scriptureButton = new QPushButton("Scripture View");
    QLineEdit *ipInput = new QLineEdit(); // create a QLineEdit for the IP input
    QPushButton *setIPButton = new QPushButton("Set IP");

    gridLayout->addWidget(fullscreenButton, 0, 0);
    gridLayout->addWidget(lowerthirdButton, 0, 1);
    gridLayout->addWidget(scriptureButton, 1, 0);

    QHBoxLayout *ipLayout = new QHBoxLayout(); // create a horizontal layout for the IP input and Set IP button
    ipLayout->addWidget(ipInput); // add the IP input to the layout
    ipLayout->addWidget(setIPButton); // add the Set IP button to the layout

    mainLayout->addLayout(gridLayout); // add the grid layout to the vertical layout
    mainLayout->addLayout(ipLayout); // add the IP input and Set IP button layout to the vertical layout

    widget->setLayout(mainLayout); // set the main layout as the widget's layout

    setWidget(widget);

    setVisible(false);
    setFloating(true);
    resize(300, 300);

    manager = new QNetworkAccessManager();
    QObject::connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                QMessageBox::information(parent, "reply", reply->errorString());
                return;
            }

            QString answer = reply->readAll();

            QMessageBox::information(parent, "reply", answer);
        }
    );

    QObject::connect(fullscreenButton, SIGNAL(clicked()), SLOT(FullscreenButtonClicked()));
}

MainWidget::~MainWidget() {
    delete manager;
};

void MainWidget::FullscreenButtonClicked() {
    request.setUrl(QUrl("http://localhost:8000"));
    manager->get(request);
}