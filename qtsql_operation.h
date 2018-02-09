#ifndef QTSQL_OPERATION_H
#define QTSQL_OPERATION_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "main.h"

extern QString card_create_sql;
extern QString card_select_max_sql;
extern QString card_select_min_sql;
extern QString card_insert_sql;
extern QString card_update_sql;
extern QString card_select_id_sql;
extern QString card_select_all_sql;
extern QString card_delete_sql;
extern QString card_clear_sql;

QSqlDatabase Creat_database(QString file);
void Open_database(QSqlDatabase db);
void Close_database(QSqlDatabase db);
QSqlQuery Creat_sql_table(QSqlDatabase db , QString create_sql);
void Insert_sql_data(QSqlQuery query, QString insert_sql, int number, QString direction, int TimeSign, QString ID, QString format, QString type, int length, QString data);
void Updata_sql_data(QSqlQuery query, QString update_sql);
void clear_sql_table(QSqlQuery query, QString clear_sql);
int query_MAX_ID(QSqlQuery query, QString clear_sql);
int query_MIN_ID(QSqlQuery query, QString query_sql);
void Insert_card_sql_data(QSqlQuery query, QString insert_sql, int number, int card_balance, int port_number, int card_state);
int sql_select_card_ID(QSqlQuery query, QString select_id_sql, int id, Test_Questions_T *card_msg);
void delete_sql_data(QSqlQuery query, QString delete_sql, int sql_id);
void batch_delete_sql_data(QSqlQuery query, QString delete_sql, int sql_id);
void clear_sql_table_sequence(QSqlQuery query, QString clear_sql);

#endif // QTSQL_OPERATION_H
