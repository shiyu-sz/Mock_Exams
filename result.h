#ifndef RESULT_H
#define RESULT_H

#include <QMainWindow>

namespace Ui {
class Result;
}

class Result : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Result(QWidget *parent = 0);
    ~Result();

private slots:
    void slots_on_pB_Result_OK_clicked();
    void slots_Finish_Examination();
    
private:
    Ui::Result *ui;
};

#endif // RESULT_H
