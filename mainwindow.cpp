#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include "qtsql_operation.h"
#include <QSqlError>
#include "main.h"
#include "File_Operations.h"

Management_Information_T Management_Information;    //考生信息管理数据结构
QString Test_Library_Path;          //题库文件路径
QSqlDatabase my_sql;                //数据库
QSqlQuery my_sql_tab;               //数据库中的表
Test_Questions_T Test_Questions;    //题库结构体
int sql_max, sql_min;               //题库中最大题号和最小题号
int Random_Qid[100];                //保存随机题号
int repeat_in_flag = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pB_MainWindow_open, SIGNAL(clicked()), this, SLOT(slots_on_pB_MainWindow_open_clicked()));
    connect(ui->pB_MainWindow_Start, SIGNAL(clicked()), this, SLOT(slots_on_pB_MainWindow_start_clicked()));
    connect(this, SIGNAL(Start_Examination_signals()), &examination1, SLOT(slots_Start_Examination()));
    connect(ui->pB_MainWindow_Import, SIGNAL(clicked()), this, SLOT(slots_on_pB_MainWindow_Import_clicked()));

//    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开按钮
void MainWindow::slots_on_pB_MainWindow_open_clicked()
{
//    QString desktop_path = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);    //获取桌面路径
    QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString Path = QFileDialog::getOpenFileName(this, tr("Open File"), desktop_path, tr("Text files (*.db)"));
    if (!Path.isEmpty())
    {
        ui->lE_MainWindow_Path->setText(Path);
        Test_Library_Path = Path;
    }
}

//导入题库
void MainWindow::slots_on_pB_MainWindow_Import_clicked()
{
//    QFile::remove("db.db");             //删除数据库
    my_sql = Creat_database(":memory:");   //连接数据库
    Open_database(my_sql);              //打开数据库
    my_sql_tab = Creat_sql_table(my_sql , card_create_sql); //创建一个名为AOPA1的表
    clear_sql_table(my_sql_tab, card_clear_sql);        //先清空表
    char source_path[200];
    char *ch;
    QByteArray ba = Test_Library_Path.toLatin1();
    ch = ba.data();
    sprintf(source_path, "ATTACH DATABASE '%s' AS 'BACKUP'", ch);
//    qDebug()<<source_path;
//    qDebug()<<QString(QLatin1String(source_path)).length();
    my_sql.exec(QString(QLatin1String(source_path)));     //附加一个数据库
//    my_sql.exec("ATTACH DATABASE 'qtsql.db' AS 'BACKUP'");  //附加一个数据库
//    qDebug()<<my_sql.lastError();
    my_sql.exec("insert into AOPA1 select * from BACKUP.AOPA"); //从附加的数据库中复制数据到之前创建的表AOPA1中
//    qDebug()<<my_sql.lastError();

    sql_max = query_MAX_ID(my_sql_tab, card_select_max_sql);
    sql_min = query_MIN_ID(my_sql_tab, card_select_min_sql);
    qDebug() << sql_max << sql_min;
    ui->lE_MainWindow_TitleNumber_2->setText(QString::number(sql_max-sql_min+1, 10));   //显示题库中的题目总数
}

//开始考试按钮
void MainWindow::slots_on_pB_MainWindow_start_clicked()
{
    bool ok;

    //初始化
    for(int i=0; i<100; i++)
    {
        Management_Information.is_abandon[i] = NO_LOOK;
        Management_Information.Candidates_Select[i] = 5;
        Management_Information.Examination_Result[i] = ABANDON;
    }

    //获得各个文本框的字符串
    Management_Information.Subject = ui->comboBox_subject->currentText();
    Management_Information.Name = ui->lE_MainWindow_name->text();
    Management_Information.ID_card = ui->lE_MainWindow_number->text();
    Management_Information.Examination_type = ui->comboBox_type->currentText();
    Management_Information.Questions_Number = (ui->lE_MainWindow_TitleNumber->text()).toInt(&ok, 10);
    //初始化当前题号
    Management_Information.Current_Qid = 0;
    //题量要在范围之内
    if((Management_Information.Questions_Number > 0)&&(Management_Information.Questions_Number <= 100))
    {
        if((sql_max - sql_min > Management_Information.Questions_Number)&&(sql_max>0))
        {
            create_Random_Qid(sql_max, sql_min, Management_Information.Questions_Number, Random_Qid);
            emit Start_Examination_signals();
            this->hide();
            this->show();
            examination1.show();
        }
        else
        {
            QMessageBox::critical(this,tr("错误"),tr("题库为空或题库题目数少于设定的题目数量!"));
        }
    }
    else
    {
        QMessageBox::critical(this,tr("错误"),tr("题目数量太少或太多!"));
    }
//    this->show();
}

//生产特点条件的随机数
//max:生成随机数的最大值
//min:生成随机数的最小值
//number:生成随机数的个数
//random_qid:保存随机数
void create_Random_Qid(int max, int min, int number, int *random_qid)
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    for(int i=0;i<number; )
    {
        int xxx;
        do
        {
            xxx = qrand()%max+1; //产生一个1~max的整数
        }
        while((xxx<min)||(xxx>max));    //如果产生的随机数不在min和max之前则再生成
        int m=0;
        while(m<i&&random_qid[m]!=xxx) m++; //比较已有的元素和t是否相同
        if(m==i)
        {
            //上面的while循环是因为m达到i而退出的
            random_qid[i]=xxx; //这个整数t是不重复的，可用
//            qDebug()<<random_qid[i]<<"\n";
            i++;  //增加了一个不重复的整数
        }
    }
}
