#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScence; }
QT_END_NAMESPACE

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    MainScence(QWidget *parent = nullptr);
    ~MainScence();

private:
    Ui::MainScence *ui;

public slots:
    void HelpAction();
    void PlayAction();
};
#endif // MAINSCENCE_H
