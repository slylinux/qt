
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    para_list=new QStringList;
    ice_para_list=new QStringList;
    registry_para_list=new QStringList;
    edit_map["smv"]="edit_";
    edit_map["goose"]="gedit_";
    edit_map["mms"]="medit_";
    edit_map["ptp"]="pedit_";
    edit_map["db"]="dedit_";
    edit_map["ntop"]="nedit_";
    edit_map["datasvr"]="dsedit_";
    edit_map["appsvr"]="aedit_";
    system_store();
    ui->tabWidget->setCurrentIndex(0);
    read_collector_config("smv");
    setWindowTitle("Gridnt Configration");
}
int Widget::system_store()
{
    QFile bakfile("/home/cfgbak");
    if(bakfile.exists())
    {
        qDebug()<<"bakfile exists,do nothing!";
        return -1;
    }
    QStringList list;
    list<<"mkdir -p /home/cfgbak/"<<"mkdir -p /home/cfgbak/collector"<<"mkdir -p /home/cfgbak/datasvr"<<"mkdir -p /home/cfgbak/appsvr"<<
          "cp -rf /gridnt/bin/collector/*.cfg /home/cfgbak/collector/"<<"cp -rf /gridnt/bin/collector/icegridcnf /home/cfgbak/collector/"<<
          "cp -rf /gridnt/bin/datasvr/*.cfg /home/cfgbak/datasvr/"<<"cp -rf /gridnt/bin/datasvr/icegridcnf /home/cfgbak/datasvr/"<<
          "cp -rf /gridnt/bin/appsvr/app_config /home/cfgbak/appsvr/"<<"cp -rf /gridnt/bin/appsvr/icegridcnf /home/cfgbak/appsvr/";
    QString str;
    foreach(str,list){
    system(str.toStdString().c_str());
    }
    return 0;
}
void Widget::display_ice_cfg(void)
{
    QString str;
    foreach(str,*ice_para_list){
        QStringList qlist =str.split("=");
        QString textname="iedit_"+qlist.front().remove(QChar('-'),Qt::CaseInsensitive).remove(QChar('.'),Qt::CaseInsensitive).remove(QChar('#'),Qt::CaseInsensitive);
        QTextEdit *tedit=ui->tabWidget->currentWidget()->findChild<QTextEdit*>(textname);
        if(tedit)
        tedit->setText(qlist.back());
    }
    foreach(str,*registry_para_list){
        QStringList qlist =str.split("=");
        if(qlist.front()=="Ice.Default.Locator")
            qlist.front()+="2";
        QString textname="iedit_"+qlist.front().remove(QChar('-'),Qt::CaseInsensitive).remove(QChar('.'),Qt::CaseInsensitive).remove(QChar('#'),Qt::CaseInsensitive);
        QTextEdit *tedit=ui->tabWidget->currentWidget()->findChild<QTextEdit*>(textname);
        if(tedit)
        tedit->setText(qlist.back());
    }
}
void Widget::display_cfg(const QString &adaptor)
{
    QString str;
    foreach(str,*para_list)
     {
      QStringList qlist =str.split("=");
      QString textname=edit_map[adaptor]+qlist.front().remove(QChar('-'),Qt::CaseInsensitive).remove(QChar('.'),Qt::CaseInsensitive).remove(QChar('#'),Qt::CaseInsensitive);
      QTextEdit *tedit=ui->tabWidget->currentWidget()->findChild<QTextEdit*>(textname);
      qlist.pop_front();
      QString para;
      while(!qlist.empty())
      {
        para+=qlist.front();
        if(para.contains("jdbc:mysql")&&qlist.size()>1)
        para+="=";
        qlist.pop_front();
      }
      if(tedit)
      tedit->setText(para);
      }
}

 int Widget::read_ice_config()
 {
     int ret;
     QDir::setCurrent("/gridnt/bin/appsvr/icegridcnf");
     QFile ice("icebox.node");
     QFile registry("registry.grid");
     ret=ice.open(QFile::ReadOnly)|registry.open(QFile::ReadOnly);
     if(ret)
     {
         registry_para_list->clear();
         ice_para_list->clear();
         QTextStream ice_stream(&ice);
         while(!ice_stream.atEnd())
         {
            ice_para_list->push_back(ice_stream.readLine());
         }
         QTextStream registry_stream(&registry);
         while(!registry_stream.atEnd())
         {
            registry_para_list->push_back(registry_stream.readLine());
         }
         display_ice_cfg();
         ice.close();
         registry.close();
     }
     else
     {
         QMessageBox::about(this,"","open file failed!");
         if(ui->tabWidget->currentIndex()<ui->tabWidget->count())
         ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
         else
         ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
     }
     return 0;
 }
 int Widget::read_collector_config(const QString &adaptor)
 {
   int ret;
   if(adaptor=="datasvr")
     QDir::setCurrent("/gridnt/bin/datasvr/");
     else
     QDir::setCurrent("/gridnt/bin/collector/");

   QFile cfg_file(adaptor+".cfg");
   QFile config_bin("icegridcnf/config.bin");
   QFile node("icegridcnf/"+adaptor+".node");

     if(adaptor=="appsvr")
       {
        cfg_file.setFileName("/gridnt/bin/appsvr/app_config/gridnt.properties");
        config_bin.setFileName("/gridnt/bin/appsvr/app_config/config.sub");
        node.setFileName("/gridnt/bin/appsvr/icegridcnf/appsvr.node");
       }

      ret=cfg_file.open(QFile::ReadOnly)|config_bin.open(QFile::ReadOnly)|node.open(QFile::ReadOnly);

     if(ret)
     {
       para_list->clear();
       QTextStream stream(&cfg_file);
       while(!stream.atEnd())
     {
       para_list->push_back(stream.readLine());
     }
       QTextStream config_bin_stream(&config_bin);
       while(!config_bin_stream.atEnd())
     {
       para_list->push_back(config_bin_stream.readLine());
     }
       QTextStream node_stream(&node);
       while(!node_stream.atEnd())
     {
       para_list->push_back(node_stream.readLine());
     }
       display_cfg(adaptor);
       cfg_file.close();
       config_bin.close();
       node.close();
     }
     else
       {
         QMessageBox::about(this,"","open file failed!");
         if(ui->tabWidget->currentIndex()<ui->tabWidget->count())
         ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()+1);
         else
         ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex()-1);
       }
     return 0;
 }

int Widget::write_ice_config()
{
    QDir::setCurrent("/gridnt/bin/appsvr/icegridcnf");
    QFile ice_node("icebox.node");
    QFile registry_grid("registry.grid");
    int ret=ice_node.open(QIODevice::WriteOnly)|registry_grid.open(QIODevice::WriteOnly);
    if(ret)
      {
        QTextStream node_stream(&ice_node);
        QTextStream grid_stream(&registry_grid);
        QString str;
        foreach(str,*ice_para_list)
        {
	  QStringList qlist =str.split("=");
	  QString para_name=qlist.front();
	  
	  QString editname="iedit_"+
	    qlist.front().remove(QChar('-'),Qt::CaseInsensitive).remove(QChar('.'),Qt::CaseInsensitive).remove(QChar('#'),Qt::CaseInsensitive);
	  QTextEdit *tedit=ui->tabWidget->currentWidget()->findChild<QTextEdit*>(editname);
	  if(para_name.contains("#"))
	    {
	      node_stream<<str<<endl;
	      continue;
	    }
	  if(tedit)
	    {
	      node_stream<<para_name<<"=";
	      node_stream<<tedit->toPlainText()<<endl;
	    }
	  else
	    {
	      qDebug()<<para_name<<":para not found,set to default!";	      
	      node_stream<<para_name<<"="<<qlist.back()<<endl;
	    }	  
        }
     foreach(str,*registry_para_list)
        {
	  QStringList qlist =str.split("=");
	  QString para_name=qlist.front();

	  if(qlist.front()=="Ice.Default.Locator")
            qlist.front()+="2";	  
	  QString editname="iedit_"+
	    qlist.front().remove(QChar('-'),Qt::CaseInsensitive).remove(QChar('.'),Qt::CaseInsensitive).remove(QChar('#'),Qt::CaseInsensitive);
	  QTextEdit *tedit=ui->tabWidget->currentWidget()->findChild<QTextEdit*>(editname);
	  if(para_name.contains("#"))
	    {
	      grid_stream<<str<<endl;
	      continue;
	    }
	  if(tedit)
	    {
	      grid_stream<<para_name<<"=";
	      grid_stream<<tedit->toPlainText()<<endl;
	    }
	  else
	    {
	      qDebug()<<para_name<<":para not found,set to default!";	      
	      grid_stream<<para_name<<"="<<qlist.back()<<endl;
	    }
	  
        }

	
      }
    else
      {
        QMessageBox::about(this,"","open config file failed!");
      }
    return 0;
}
int Widget::write_collector_config(const QString &adaptor)
{
    if(adaptor=="datasvr")
    QDir::setCurrent("/gridnt/bin/datasvr/");
    else
    QDir::setCurrent("/gridnt/bin/collector/");
    QFile cfg_file(adaptor+".cfg");
    QFile config_bin("icegridcnf/config.bin");
    QFile node("icegridcnf/"+adaptor+".node");

    if(adaptor=="appsvr")
      {
        cfg_file.setFileName("/gridnt/bin/appsvr/app_config/gridnt.properties");
        config_bin.setFileName("/gridnt/bin/appsvr/app_config/config.sub");
        node.setFileName("/gridnt/bin/appsvr/icegridcnf/appsvr.node");
      }
    
    int ret=cfg_file.open(QIODevice::WriteOnly)|
    config_bin.open(QIODevice::WriteOnly)|
    node.open(QIODevice::WriteOnly);
    if(ret)
      {
	QTextStream stream(&cfg_file);
	QTextStream config_bin_stream(&config_bin);
	QTextStream node_stream(&node);
	QString str;
	foreach(str,*para_list){
	  QStringList qlist =str.split("=");
	  QString para_name=qlist.front();
	  
	  QString editname=edit_map[adaptor]+
	    qlist.front().remove(QChar('-'),Qt::CaseInsensitive).remove(QChar('.'),Qt::CaseInsensitive).remove(QChar('#'),Qt::CaseInsensitive);
	  QTextEdit *tedit=ui->tabWidget->currentWidget()->findChild<QTextEdit*>(editname);
	  if(para_name.contains("#"))
	    {
	      if(para_name.contains("TopicManager")||para_name.contains("Subscriber"))
		config_bin_stream<<str<<endl;
	      else if(para_name.contains("Ice"))
		node_stream<<str<<endl;
	      else
		stream<<str<<endl;
	      continue;
	    }
	  
	  if(tedit)
	    {
	      if(para_name.contains("TopicManager")||para_name.contains("Subscriber"))
		{
		  config_bin_stream<<para_name<<"=";
		  config_bin_stream<<tedit->toPlainText()<<endl;
		}
	      else if(para_name.contains("Ice"))
		{
		  
		  node_stream<<para_name<<"=";
		  node_stream<<tedit->toPlainText()<<endl;
		}
	      else
		{
		  stream<<para_name<<"=";
		  stream<<tedit->toPlainText()<<endl;
		}
	    }
	  else
	    {
	      qDebug()<<para_name<<":para not found,set to default!";
              if(para_name.contains("TopicManager")||para_name.contains("Subscriber"))
		{
		  config_bin_stream<<para_name<<"="<<qlist.back()<<endl;
		}
              else if(para_name.contains("Ice"))
		{
		  
		  node_stream<<para_name<<"="<<qlist.back()<<endl;
		}
              else
		{
		  stream<<para_name<<"="<<qlist.back()<<endl;
		}
	    }
	  
	}
	cfg_file.close();
	config_bin.close();
	node.close();
      }
    else
      {
	QMessageBox::about(this,"","open config file failed!");
      }
    return 0;
    
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_tabWidget_selected(const QString &arg1)
{
    if(arg1=="ice")
        read_ice_config();
    else
    read_collector_config(arg1);
}

void Widget::on_smv_ok_clicked()
{
    write_collector_config("smv");
}

void Widget::on_goose_ok_clicked()
{
    write_collector_config("goose");
}

void Widget::on_tabWidget_currentChanged(int index)
{

}

void Widget::on_mms_ok_clicked()
{
    write_collector_config("mms");
}

void Widget::on_ptp_ok_clicked()
{
    write_collector_config("ptp");
}

void Widget::on_ntop_ok_clicked()
{
    write_collector_config("ntop");
}

void Widget::on_db_ok_clicked()
{
    write_collector_config("db");
}

void Widget::on_datasvr_ok_clicked()
{
    write_collector_config("datasvr");
}

void Widget::on_appsvr_ok_clicked()
{
    write_collector_config("appsvr");
}

void Widget::on_ice_ok_clicked()
{
    write_ice_config();
}
