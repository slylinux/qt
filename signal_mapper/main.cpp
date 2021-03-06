#include <QtGui>
#include <QApplication>
#include "mapper.h"

ButtonWidget::ButtonWidget(QStringList texts, QWidget *parent)
	: QWidget(parent)
{
	signalMapper = new QSignalMapper(this);
	
	QGridLayout *gridLayout = new QGridLayout;
	for (int i = 0; i < texts.size(); ++i) {
		QPushButton *button = new QPushButton(texts[i]);
		connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(button, texts[i]);
		gridLayout->addWidget(button, i / 3, i % 3);
	}
	
	connect(signalMapper, SIGNAL(mapped(const QString &)),
			this, SLOT(onClicked(const QString &)));

//	connect(this,SIGNAL(clicked(const QString &)),this,SLOT(onClicked(const QString&)));
	setWindowTitle("SignalMapper");
	setLayout(gridLayout);
}
void ButtonWidget::onClicked(const QString& text)
{
	qDebug()<<text<<" clicked";
	QProcess* process=new QProcess(this);
	process->setWorkingDirectory("/home/sly/work/mmslite/mvl/usr/scl_srvr");
	QString appName="./scl_srvr_ld";
	QStringList args;
	process->start(appName,args);
}
int main(int argc,char* argv[])
{
	QApplication app(argc,argv);
	QStringList texts;
	texts<<"button1"<<"button2"<<"button3";
	ButtonWidget* bw=new ButtonWidget(texts);
	bw->show();
	return app.exec();
}
