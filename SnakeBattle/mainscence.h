#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScence; }
QT_END_NAMESPACE

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    MainScence(QWidget *parent = nullptr);
    ~MainScence();

    QLineEdit *InputNameEdit;
    QLineEdit *InputNum1Edit;
    QLineEdit *InputNum2Edit;
    QPushButton *ButtonPlay;

    QString name;
    int Ai_1_num, Ai_2_num; // 因为不知道如何使用信号与槽传递参数。想了好久才决定把name和num定义在这里面...迫不得已

private:
    Ui::MainScence *ui;

public slots:
    void HelpAction();
    void PlayAction();
    void EnterTheGame();
};
#endif // MAINSCENCE_H
