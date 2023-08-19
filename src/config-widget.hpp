#ifndef CONFIG_WIDGET_HPP
#define CONFIG_WIDGET_HPP

#include <QDockWidget>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

class ConfigWidget : public QDockWidget {
	Q_OBJECT

public:
	explicit ConfigWidget(QWidget *widgetParent = nullptr);
	~ConfigWidget();
	QLineEdit *ipInput = new QLineEdit();

private:
	QWidget *parent = nullptr;
	QWidget *widget = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *exitButtonsLayout = new QHBoxLayout();
	QPushButton *okButton = new QPushButton("OK");
	QPushButton *cancelButton = new QPushButton("Cancel");

private slots:
	void okButtonClicked();
	void cancelButtonClicked();
};

#endif