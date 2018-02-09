#include "examination.h"
#include "ui_examination.h"
#include <QDebug>
#include "main.h"
#include "qtsql_operation.h"

examination::examination(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::examination)
{
    ui->setupUi(this);
    connect(ui->pB_examination_stop, SIGNAL(clicked()), this, SLOT(slots_on_pB_examination_stop_clicked()));
    connect(ui->pB_examination_ExamineAnswer, SIGNAL(clicked()), this, SLOT(slots_pB_examination_ExamineAnswer_clicked()));
    connect(ui->pB_examination_last, SIGNAL(clicked()), this, SLOT(slots_pB_examination_last_clicked()));
    connect(ui->pB_examination_next, SIGNAL(clicked()), this, SLOT(slots_pB_examination_next_clicked()));
    connect(ui->radioButton_A, SIGNAL(clicked()), this, SLOT(slots_radioButton_A_clicked()));
    connect(ui->radioButton_B, SIGNAL(clicked()), this, SLOT(slots_radioButton_B_clicked()));
    connect(ui->radioButton_C, SIGNAL(clicked()), this, SLOT(slots_radioButton_C_clicked()));
    connect(ui->radioButton_D, SIGNAL(clicked()), this, SLOT(slots_radioButton_D_clicked()));
    connect(ui->radioButton_abandon, SIGNAL(clicked()), this, SLOT(slots_radioButton_abandon_clicked()));
    connect(this, SIGNAL(Finish_Examination_signals()), &Result1, SLOT(slots_Finish_Examination()));

    //单选框button组
    radioButtonGroup = new QButtonGroup;
    radioButtonGroup->addButton(ui->radioButton_A, 1);
    radioButtonGroup->addButton(ui->radioButton_B, 2);
    radioButtonGroup->addButton(ui->radioButton_C, 3);
    radioButtonGroup->addButton(ui->radioButton_D, 4);
    radioButtonGroup->addButton(ui->radioButton_abandon, 5);
}

examination::~examination()
{
    delete ui;
}

//考试结束按钮
void examination::slots_on_pB_examination_stop_clicked()
{
    emit Finish_Examination_signals();
    this->hide();
    this->show();
    Result1.show();
}

//当开始考试按钮按下
void examination::slots_Start_Examination()
{
    //显示考试信息
    ui->radioButton_abandon->setChecked(true);
    ui->label_examination_sum->setText(QString::number(Management_Information.Questions_Number, 10));
    ui->label_examinstion_subject->setText(Management_Information.Subject);
    ui->label_examinstion_name->setText(Management_Information.Name);
    ui->label_examinstion_num->setText(Management_Information.ID_card);
    ui->label_examinstion_type->setText(Management_Information.Examination_type);

    //从题库中找出试题
    if(sql_select_card_ID(my_sql_tab,card_select_id_sql,Random_Qid[0],&Test_Questions) == 0)
//        qDebug()<<"select succeed!\n";
//    else
//        qDebug()<<"select failure!\n";
    //把试题显示出来
    ui->label_examination_CurrentQid->setText(QString::number(Management_Information.Current_Qid+1, 10));
    ui->label_examination_CurrentQid_2->setText(QString::number(Test_Questions.Title_Number, 10));
    ui->textEdit_examinati_title->setText(Test_Questions.Subject);
    ui->textEdit_answer_A->setText(Test_Questions.Option_A);
    ui->textEdit_answer_B->setText(Test_Questions.Option_B);
    ui->textEdit_answer_C->setText(Test_Questions.Option_C);
    ui->textEdit_answer_D->setText(Test_Questions.Option_D);
}

//查看本题答
void examination::slots_pB_examination_ExamineAnswer_clicked()
{
    ui->lE_examination_ExamineAnswer->setText(Test_Questions.Answer);   //显示答案
    Management_Information.is_abandon[Management_Information.Current_Qid] = LOOK;   //加锁，不能再更改答案
}

//上一题
int examination::slots_pB_examination_last_clicked()
{
    ui->lE_examination_ExamineAnswer->setText("");  //清空答案栏
    Management_Information.Current_Qid --;          //当前题号--
    if(Management_Information.Current_Qid < 0)      //不能小示0
    {
        Management_Information.Current_Qid ++;      //否则++
        return 0;
    }

    if(Management_Information.Current_Qid >= 0)
    {   //显示已经作答过的题的答案
        switch(Management_Information.Candidates_Select[Management_Information.Current_Qid])
        {
            case 1:ui->radioButton_A->setChecked(true);break;
            case 2:ui->radioButton_B->setChecked(true);break;
            case 3:ui->radioButton_C->setChecked(true);break;
            case 4:ui->radioButton_D->setChecked(true);break;
            case 5:ui->radioButton_abandon->setChecked(true);break;
            default : break;
        }
    }

    //从数据库中找一题
    if(sql_select_card_ID(my_sql_tab,card_select_id_sql,Random_Qid[Management_Information.Current_Qid],&Test_Questions) == 0)
//        qDebug()<<"select succeed!\n";
//    else
//        qDebug()<<"select failure!\n";
    ui->label_examination_CurrentQid->setText(QString::number(Management_Information.Current_Qid+1, 10));
    ui->label_examination_CurrentQid_2->setText(QString::number(Test_Questions.Title_Number, 10));
    ui->textEdit_examinati_title->setText(Test_Questions.Subject);
    ui->textEdit_answer_A->setText(Test_Questions.Option_A);
    ui->textEdit_answer_B->setText(Test_Questions.Option_B);
    ui->textEdit_answer_C->setText(Test_Questions.Option_C);
    ui->textEdit_answer_D->setText(Test_Questions.Option_D);

    return 0;
}

//下一题
int examination::slots_pB_examination_next_clicked()
{
    ui->lE_examination_ExamineAnswer->setText("");  //设置答案栏为空
    Management_Information.Current_Qid ++;
    if(Management_Information.Current_Qid > Management_Information.Questions_Number-1)
    {
        Management_Information.Current_Qid --;
        return 0;
    }

    qDebug()<<"Current_Qid = "<<Management_Information.Current_Qid;
    if(Management_Information.Current_Qid <= Management_Information.Questions_Number-1)
    {
        switch(Management_Information.Candidates_Select[Management_Information.Current_Qid])
        {
            case 1:ui->radioButton_A->setChecked(true);break;
            case 2:ui->radioButton_B->setChecked(true);break;
            case 3:ui->radioButton_C->setChecked(true);break;
            case 4:ui->radioButton_D->setChecked(true);break;
            case 5:ui->radioButton_abandon->setChecked(true);break;
            default : break;
        }
    }

    //load下一题
    if(sql_select_card_ID(my_sql_tab,card_select_id_sql,Random_Qid[Management_Information.Current_Qid],&Test_Questions) == 0)
//        qDebug()<<"select succeed!\n";
//    else
//        qDebug()<<"select failure!\n";
    ui->label_examination_CurrentQid->setText(QString::number(Management_Information.Current_Qid+1, 10));
    ui->label_examination_CurrentQid_2->setText(QString::number(Test_Questions.Title_Number, 10));
    ui->textEdit_examinati_title->setText(Test_Questions.Subject);
    ui->textEdit_answer_A->setText(Test_Questions.Option_A);
    ui->textEdit_answer_B->setText(Test_Questions.Option_B);
    ui->textEdit_answer_C->setText(Test_Questions.Option_C);
    ui->textEdit_answer_D->setText(Test_Questions.Option_D);

    return 0;
}

//选择A
void examination::slots_radioButton_A_clicked()
{
//    qDebug()<<"select A!\n";
    Management_Information.Candidates_Select[Management_Information.Current_Qid] = radioButtonGroup->checkedId();
    if(Management_Information.is_abandon[Management_Information.Current_Qid] != LOOK)
    {
        if(Test_Questions.Answer == "A")
            Management_Information.Examination_Result[Management_Information.Current_Qid] = CORRECT;
        else
            Management_Information.Examination_Result[Management_Information.Current_Qid] = FAULT;
    }
    else
        Management_Information.Examination_Result[Management_Information.Current_Qid] = ABANDON;
}

//选择B
void examination::slots_radioButton_B_clicked()
{
//    qDebug()<<"select B!\n";
    Management_Information.Candidates_Select[Management_Information.Current_Qid] = radioButtonGroup->checkedId();
    if(Management_Information.is_abandon[Management_Information.Current_Qid] != LOOK)
    {
        if(Test_Questions.Answer == "B")
            Management_Information.Examination_Result[Management_Information.Current_Qid] = CORRECT;
        else
            Management_Information.Examination_Result[Management_Information.Current_Qid] = FAULT;
    }
    else
        Management_Information.Examination_Result[Management_Information.Current_Qid] = ABANDON;
}

//选择C
void examination::slots_radioButton_C_clicked()
{
//    qDebug()<<"select C!\n";
    Management_Information.Candidates_Select[Management_Information.Current_Qid] = radioButtonGroup->checkedId();
    if(Management_Information.is_abandon[Management_Information.Current_Qid] != LOOK)
    {
        if(Test_Questions.Answer == "C")
            Management_Information.Examination_Result[Management_Information.Current_Qid] = CORRECT;
        else
            Management_Information.Examination_Result[Management_Information.Current_Qid] = FAULT;
    }
    else
        Management_Information.Examination_Result[Management_Information.Current_Qid] = ABANDON;
}

//选择D
void examination::slots_radioButton_D_clicked()
{
//    qDebug()<<"select D!\n";
    Management_Information.Candidates_Select[Management_Information.Current_Qid] = radioButtonGroup->checkedId();
    if(Management_Information.is_abandon[Management_Information.Current_Qid] != LOOK)
    {
        if(Test_Questions.Answer == "D")
            Management_Information.Examination_Result[Management_Information.Current_Qid] = CORRECT;
        else
            Management_Information.Examination_Result[Management_Information.Current_Qid] = FAULT;
    }
    else
        Management_Information.Examination_Result[Management_Information.Current_Qid] = ABANDON;
}

//选择放弃
void examination::slots_radioButton_abandon_clicked()
{
//    qDebug()<<"select abandon!\n";
    Management_Information.Candidates_Select[Management_Information.Current_Qid] = radioButtonGroup->checkedId();
    Management_Information.Examination_Result[Management_Information.Current_Qid] = ABANDON;
}

//清除radioButton的状态
void examination::clean_radioButton_state()
{
    ui->radioButton_abandon->setChecked(true);
}

