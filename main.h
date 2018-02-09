#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

enum e_select_state
{
    ABANDON = 0x00, //放弃
    CORRECT,        //正确
    FAULT,          //错误
};

enum e_is_Look
{
    NO_LOOK = 0x00, //不放弃
    LOOK,           //放弃
};

//管理信息数据结构
typedef struct
{
    QString Subject;            //考试科目
    QString Name;               //考生姓名
    QString ID_card;            //考生身份证号
    QString Examination_type;   //考试类型
    int Questions_Number;       //题目数量
    int Current_Qid;            //当前题号
    int Examination_Time;       //考试用时
    e_is_Look is_abandon[100];       //是否放弃
    int Candidates_Select[100];     //考生的选择
    e_select_state Examination_Result[100];   //保存考试结果

}Management_Information_T;

//试题数据结构
typedef struct
{
    int Title_Number;   //题库题号
    QString Subject;    //题目
    QString Option_A;   //选项A
    QString Option_B;   //选项B
    QString Option_C;   //选项C
    QString Option_D;   //选项D
    QString Answer;     //答案
}Test_Questions_T;

extern Management_Information_T Management_Information;    //考生信息管理数据结构
extern QString Test_Library_Path;          //题库文件路径
extern QSqlDatabase my_sql;                //数据库
extern QSqlQuery my_sql_tab;               //数据库中的表
extern Test_Questions_T Test_Questions;    //题库结构体
extern int sql_max, sql_min;               //题库中最大题号和最小题号
extern int Random_Qid[100];                //保存随机题号

#endif // MAIN_H
