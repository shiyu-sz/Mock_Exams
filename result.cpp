#include "result.h"
#include "ui_result.h"
#include "main.h"
#include <QDebug>

Result::Result(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    connect(ui->pB_Result_OK, SIGNAL(clicked()), this, SLOT(slots_on_pB_Result_OK_clicked()));

}

Result::~Result()
{
    delete ui;
}

//确定
void Result::slots_on_pB_Result_OK_clicked()
{
    this->close();
}

//当结束考试键按下
void Result::slots_Finish_Examination()
{
    int Answer_Correct = 0;
    int Answer_Error = 0;
    int Ansswer_Abandon = 0;
    ui->label_Result_total->setText(QString::number(Management_Information.Questions_Number, 10));
    for(int i=0; i<Management_Information.Questions_Number; i++)
    {
        switch(Management_Information.Examination_Result[i])
        {
            case ABANDON:Ansswer_Abandon++; break;
            case CORRECT:Answer_Correct++;  break;
            case FAULT:Answer_Error++;      break;
            default : break;
        }
    }
    ui->label_Result_correct->setText(QString::number(Answer_Correct, 10));
    ui->label_Result_error->setText(QString::number(Answer_Error, 10));
    ui->label_Result_abandon->setText(QString::number(Ansswer_Abandon, 10));
}
