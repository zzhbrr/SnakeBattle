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

#include "game.h"

// 注意要把game声明在外面，当成全局变量
// 后面游戏所有的操作都是基于game的
Game *game;

MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{
    ui->setupUi(this);
    //设置
    this->setWindowTitle(tr("SnakeBattle_1.0"));
    this->setWindowIcon(QIcon(":/images/picture/icon.jpg"));
    this->setWindowIcon(QIcon(":/images/picture/Snake.png"));

    //背景
    QPalette backg;
    backg.setBrush(QPalette::Background, QBrush(QPixmap(":/images/picture/mainscence_back.jpg").scaled(this->width(), this->height())));
    this->setPalette(backg);

    //按钮的字体颜色
    QPalette buttonpal;
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

    //创建Pushbutton
    QPushButton *HelpOKButton = new QPushButton(HelpWidget);
    HelpOKButton->setText(tr("OK"));
    HelpOKButton->move(60, 150);
    connect(HelpOKButton, &QPushButton::clicked, HelpDialog, &QDialog::close);

    HelpDialog->show();
}

void MainScence::PlayAction() {
    QString name;
    //输入玩家名字


    //创建画布 开始游戏
    game = new Game(name);
    game->show();
}

MainScence::~MainScence()
{
    delete ui;
}

