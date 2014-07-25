#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QtGui>
#define disp_para(x) (ui->edit_##x)
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    int read_collector_config(const QString &adaptor);
    int write_collector_config(const QString &adaptor);

    int read_ice_config();
    int write_ice_config();

    void on_tabWidget_selected(const QString &arg1);

    void on_smv_ok_clicked();

    void on_goose_ok_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_mms_ok_clicked();

    void on_ptp_ok_clicked();

    void on_ntop_ok_clicked();

    void on_db_ok_clicked();

    void on_datasvr_ok_clicked();

    void on_appsvr_ok_clicked();

    void on_ice_ok_clicked();

private:
    Ui::Widget *ui;
    QMap<QString,QString> edit_map;

    QStringList *para_list;
    QStringList *ice_para_list;
    QStringList *registry_para_list;
    void display_cfg(const QString &adaptor);
    void display_ice_cfg();
    int system_store();
};

#endif // WIDGET_H
