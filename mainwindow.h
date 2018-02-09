#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "examination.h"

void create_Random_Qid(int max, int min, int number, int *random_qid);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void Start_Examination_signals();
    
private slots:
    void slots_on_pB_MainWindow_open_clicked();
    void slots_on_pB_MainWindow_start_clicked();
    void slots_on_pB_MainWindow_Import_clicked();

private:
    Ui::MainWindow *ui;
    examination examination1;
};

#endif // MAINWINDOW_H
