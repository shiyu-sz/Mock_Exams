#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include "qtsql_operation.h"
#include <QSqlError>
#include "main.h"

QString card_create_sql     = "create table AOPA1 (id INTEGER, subject varchar(500), option_A varchar(200), option_B varchar(200), option_C varchar(200), option_D varchar(200), answer varchar(1))";
QString card_select_max_sql = "select max(id) from AOPA1";
QString card_select_min_sql = "select min(id) from AOPA1";
QString card_insert_sql     = "insert into AOPA1 values (?, ?, ?, ?, ?, ?, ?)";
QString card_update_sql     = "update AOPA1 set card_balance = :card_balance where id = :id";
QString card_select_id_sql  = "select id, subject, option_A, option_B, option_C, option_D, answer from AOPA1 where id = ?";
QString card_select_all_sql = "select * from AOPA1";
QString card_delete_sql     = "delete from AOPA1 where id = ?";
QString card_clear_sql      = "delete from AOPA1";

//创建数据库
QSqlDatabase Creat_database(QString file)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(file);
    return database;
}

//打开数据库
void Open_database(QSqlDatabase db)
{
    if(!db.open())
    {
        qDebug()<< "database is error";
    }
    else
    {
        qDebug()<<"database is ok";
    }
}

//查找所有的表名 SELECT * FROM dbname.sqlite_master WHERE type='table';
void Find_table_name()
{

}

//关闭数据库
void Close_database(QSqlDatabase db)
{
    db.close();
}

//创建一个表
QSqlQuery Creat_sql_table(QSqlDatabase db , QString create_sql)
{
    QSqlQuery sql_query(db);

    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug()<<"table created Error!";
    }
    else
    {
        qDebug()<<"table created!";
    }
    return sql_query;
}

//插入一行CAN数据
void Insert_sql_data(QSqlQuery query, QString insert_sql, int number, QString direction, int TimeSign, QString ID, QString format, QString type, int length, QString data)
{
    query.prepare(insert_sql);
    query.addBindValue(number);
    query.addBindValue(direction);
    query.addBindValue(TimeSign);
    query.addBindValue(ID);
    query.addBindValue(format);
    query.addBindValue(type);
    query.addBindValue(length);
    query.addBindValue(data);
    if(!query.exec())
    {
        qDebug()<<"inserted Error!";
    }
    else
    {
//        qDebug()<<"inserted!";
    }
}

//插入一行card数据
void Insert_card_sql_data(QSqlQuery query, QString insert_sql, int number, int card_balance, int port_number, int card_state)
{
    query.prepare(insert_sql);
    query.addBindValue(number);
    query.addBindValue(card_balance);
    query.addBindValue(port_number);
    query.addBindValue(card_state);
    if(!query.exec())
    {
        qDebug()<<"inserted Error!";
    }
    else
    {
//        qDebug()<<"inserted!";
    }
}

//更新数据
void Updata_sql_data(QSqlQuery query, QString update_sql)
{
    //更新数据
    query.prepare(update_sql);
    query.bindValue(":direction", "Qt");
    query.bindValue(":id", 1);
    if(!query.exec())
    {
        qDebug()<<"updated Error!";
    }
    else
    {
        qDebug()<<"updated!";
    }
}

//清空表
void clear_sql_table(QSqlQuery query, QString clear_sql)
{
    query.prepare(clear_sql);
    if(!query.exec())
    {
        qDebug()<<"cleared Error!";
    }
    else
    {
        qDebug()<<"cleared";
    }
}

//删除表
void delect_tab_sql_table(QSqlQuery query, QString clear_sql)
{
    query.prepare(clear_sql);
    if(!query.exec())
    {
        qDebug()<<"cleared Error!";
    }
    else
    {
        qDebug()<<"cleared";
    }
}

//清空表的序号
void clear_sql_table_sequence(QSqlQuery query, QString clear_sql)
{
    query.prepare(clear_sql);
    if(!query.exec())
    {
        qDebug()<<"cleared sequence Error!";
    }
    else
    {
        qDebug()<<"cleared sequence!";
    }
}

//查询最大的ID
int query_MAX_ID(QSqlQuery query, QString query_sql)
{
    int max_id;
    query.prepare(query_sql);
    if(!query.exec())
    {
        qDebug()<<"query MAX ID Error!";
        return -1;
    }
    else
    {
        while(query.next())
        {
            max_id = query.value(0).toInt();
        }
    }
    return max_id;
}

//查询最小的ID
int query_MIN_ID(QSqlQuery query, QString query_sql)
{
    int min_id;
    query.prepare(query_sql);
    if(!query.exec())
    {
        qDebug()<<"query MIN ID Error!";
        return -1;
    }
    else
    {
        while(query.next())
        {
            min_id = query.value(0).toInt();
        }
    }
    return min_id;
}

//查询sqlite_sequence表的当前ID
int sqlite_sequence_current_ID()
{
    return 0;
}

//删除数据
//query:数据所在的表
//delete_sql:执行删除的语句
//sql_id:被删除数据的ID
void delete_sql_data(QSqlQuery query, QString delete_sql, int sql_id)
{
    query.prepare(delete_sql);
    query.addBindValue(sql_id);
    if(!query.exec())
    {
//        qDebug()<<query.lastError();
        qDebug()<<"delete Error!";
    }
    else
    {
        qDebug()<<"deleted!";
    }
}

//批量删除数据
void batch_delete_sql_data(QSqlQuery query, QString delete_sql, int sql_id)
{
    query.prepare(delete_sql);
    query.addBindValue(sql_id);
    if(!query.exec())
    {
        qDebug()<<"batch delete Error!";
    }
    else
    {
        qDebug()<<"batch deleted!";
    }
}

//根据ID查找卡片数据库
int sql_select_card_ID(QSqlQuery query, QString select_id_sql, int id, Test_Questions_T *card_msg)
{
    query.prepare(select_id_sql);
    query.addBindValue(id);
    if(!query.exec())
    {
        qDebug()<<"select Error!";
    }
    else
    {
//        qDebug()<<"select!";
    }
    while(query.next())
    {
        card_msg->Title_Number = query.value(0).toInt();
        card_msg->Subject = query.value(1).toString();
        card_msg->Option_A = query.value(2).toString();
        card_msg->Option_B = query.value(3).toString();
        card_msg->Option_C = query.value(4).toString();
        card_msg->Option_D = query.value(5).toString();
        card_msg->Answer = query.value(6).toString();
        return 0;
    }
    return -1;
}
