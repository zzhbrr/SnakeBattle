#include "mainscence.h"
#include "ui_mainscence.h"
#include <QLabel>
#include <QTimer>
#include <QAction>
#include <QMenuBar>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QByteArray>
#include <QDialog>
#include <QWidget>
#include <QFont>
#include <QPalette>
#include <QLineEdit>
#include <QIntValidator>

#include "game.h"

// 注意要把game声明在外面，当成全局变量
// 后面游戏所有的操作都是基于game的
Game *game;

MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{
    ui->setupUi(this);
    //设置 窗口名称和图像
    this->setWindowTitle(tr("SnakeBattle_1.0"));
    this->setWindowIcon(QIcon(":/images/picture/icon.jpg"));
    this->setWindowIcon(QIcon(":/images/picture/Snake.png"));

    //背景
    QPalette backg;
    backg.setBrush(QPalette::Background, QBrush(QPixmap(":/images/picture/mainscence_back.jpg").scaled(this->width(), this->height())));
    this->setPalette(backg);

    //按钮的字体颜色
    QPalette buttonpal; // 调色板
    buttonpal.setColor(QPalette::ButtonText, QColor(128,0,0));

    //Help选项
    QPushButton *MainScence_Help = new QPushButton(this);
    MainScence_Help->setText(tr("Help"));
    MainScence_Help->setFlat(true);
    MainScence_Help->setPalette(buttonpal);
    connect(MainScence_Help, &QPushButton::clicked, this, &MainScence::HelpAction);

    //Play选项
    QPushButton *MainScence_Play = new QPushButton(this);
    MainScence_Play->setText(tr("Play"));
    MainScence_Play->setFlat(true);
    MainScence_Play->setPalette(buttonpal);
    connect(MainScence_Play, &QPushButton::clicked, this, &MainScence::PlayAction);
    MainScence_Play->move(1, 30);

    // 设置默认name和num
    name = "BriMon";
    Ai_1_num = 5, Ai_2_num = 10;
}

void MainScence::HelpAction() {
    //创建Dialog
    QDialog *HelpDialog = new QDialog(this);
    HelpDialog->resize(300, 250);
    HelpDialog->setWindowTitle(tr("Help"));
    //创建Widget
    QWidget *HelpWidget = new QWidget(HelpDialog);
    HelpWidget->resize(600, 250);


    //创建里面的文字
    QLabel *HelpText1 = new QLabel(HelpWidget);
    HelpText1->setText(tr("采集食物可以积攒分数并且变长"));
    HelpText1->move(15, 20);
    QLabel *HelpText2 = new QLabel(HelpWidget);
    HelpText2->setText(tr("蛇的头部碰触到其他蛇的身体将会死亡"));
    HelpText2->move(15, 60);
    QLabel *HelpText3 = new QLabel(HelpWidget);
    HelpText3->move(15, 100);
    HelpText3->setText(tr("按Ctrl键可以加速 Shift键可以减速"));
    QLabel *HelpText4 = new QLabel(HelpWidget);
    HelpText4->move(15, 140);
    HelpText4->setText(tr("按Space以开始或暂停 按Esc退出"));

    //创建Pushbutton
    QPushButton *HelpOKButton = new QPushButton(HelpWidget);
    HelpOKButton->setText(tr("OK"));
    HelpOKButton->move(60, 160);
    connect(HelpOKButton, &QPushButton::clicked, HelpDialog, &QDialog::close);

    HelpDialog->show();
}

void MainScence::PlayAction() {
    // 输入玩家名字和ai蛇的数量
    // 创建QDialog
    QDialog *OptionDialog = new QDialog(this);
    QWidget *OptionWidget = new QWidget(OptionDialog);
    OptionDialog->resize(300, 250);
    OptionWidget->resize(300, 250);
    OptionDialog->setWindowTitle(tr("Settings"));

    InputNameEdit = new QLineEdit(OptionWidget);
    InputNameEdit->resize(100, 25);
    InputNameEdit->move(10, 40);
    InputNameEdit->setPlaceholderText(tr("BriMon"));

    InputNum1Edit = new QLineEdit(OptionWidget);
    InputNum1Edit->resize(100, 25);
    InputNum1Edit->move(10, 90);
    InputNum1Edit->setPlaceholderText(tr("默认5"));
    InputNum1Edit->setValidator(new QIntValidator(0,20,this));

    InputNum2Edit = new QLineEdit(OptionWidget);
    InputNum2Edit->resize(100, 25);
    InputNum2Edit->move(10, 140);
    InputNum2Edit->setPlaceholderText(tr("默认10"));
    InputNum2Edit->setValidator(new QIntValidator(0,20,this));

    QLabel *Tip1 = new QLabel(OptionWidget);
    Tip1->setText(tr("请输入名字"));
    Tip1->move(10, 10);
    Tip1->resize(150, 30);

    QLabel *Tip2 = new QLabel(OptionWidget);
    Tip2->setText(tr("请输入Ai蛇(简单)的数量[0, 20]"));
    Tip2->move(10, 60);
    Tip2->resize(250, 30);

    QLabel *Tip3 = new QLabel(OptionWidget);
    Tip3->setText(tr("请输入Ai蛇(困难)的数量[0, 20]"));
    Tip3->move(10, 110);
    Tip3->resize(250, 30);

    ButtonPlay = new QPushButton(OptionWidget);
    ButtonPlay->resize(60, 20);
    ButtonPlay->setText(tr("PLAY"));
    ButtonPlay->move(100, 175);
    connect(ButtonPlay, &QPushButton::clicked, this, &MainScence::EnterTheGame);

    OptionDialog->show();

}

void MainScence::EnterTheGame() {
    //开始游戏
    if (!InputNameEdit->text().isEmpty())
        name = InputNameEdit->text();
    if (!InputNum1Edit->text().isEmpty())
        Ai_1_num = InputNum1Edit->text().toInt();
    if (!InputNum2Edit->text().isEmpty())
        Ai_2_num = InputNum2Edit->text().toInt();
    game = new Game(name, Ai_1_num, Ai_2_num);
    game->show();
}

MainScence::~MainScence()
{
    delete ui;
}

