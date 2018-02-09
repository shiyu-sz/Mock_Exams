#ifndef EXAMINATION_H
#define EXAMINATION_H

#include <QMainWindow>
#include "result.h"
#include <QButtonGroup>

namespace Ui {
class examination;
}

class examination : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit examination(QWidget *parent = 0);
    ~examination();
    void clean_radioButton_state();

signals:
    void Finish_Examination_signals();
    
private slots:
    void slots_on_pB_examination_stop_clicked();
    void slots_Start_Examination();
    void slots_pB_examination_ExamineAnswer_clicked();
    int slots_pB_examination_last_clicked();
    int slots_pB_examination_next_clicked();
    void slots_radioButton_A_clicked();
    void slots_radioButton_B_clicked();
    void slots_radioButton_C_clicked();
    void slots_radioButton_D_clicked();
    void slots_radioButton_abandon_clicked();

private:
    Ui::examination *ui;
    Result Result1;
    QButtonGroup *radioButtonGroup;
};

#endif // EXAMINATION_H
