#include <QtGui>
#include <QString>
#include <QStringList>
#include <QSignalMapper>

class ButtonWidget: public QWidget
{
	Q_OBJECT
public:
	ButtonWidget(QStringList texts,QWidget* parent=0);
signals:
	void clicked(const QString& text);
private slots:
	void onClicked(const QString& text);
private:
	QSignalMapper* signalMapper;
};
