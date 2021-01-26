#include "..\include\MainAPP.h"

void MainAPP::initUI() {
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint);  // 主窗体全隐藏
    this->setWindowOpacity(0);  // 不透明度

    initUI_j3pzCalc();
    initUI_slSudoku();
    initUI_keju();
    initUI_kaifu();
    initUI_wujia();
    initUI_about();

    quitAction = new QAction("退出", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    menu = new QMenu(this);
    menu->addMenu(j3pzCalcMenu);
    menu->addAction(slSudokuAction);
    menu->addAction(kejuAction);
    menu->addAction(kaifuAction);
    menu->addAction(wujiaAction);
    menu->addAction(aboutAction);
    menu->addAction(quitAction);
    menu->setToolTipsVisible(true);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(icon);  // 托盘图标
    tray->setToolTip(description);  // 悬停提示
    tray->setContextMenu(menu);

    //connect(tray, &QSystemTrayIcon::activated, this, &MainAPP::onIconClicked);  // 把鼠标点击图标的信号和槽连接

    tray->show();
    tray->showMessage(description, "欢迎大侠", icon);
}

void MainAPP::initUI_j3pzCalc() {
    QList<QAction*> j3pzCalcActionList;
    j3pzCalcActionGroup = new QActionGroup(this);

    std::for_each(KF.keyBegin(), KF.keyEnd(), [&](QString text) { j3pzCalcActionList.prepend(new QAction(text, this)); });
    std::for_each(j3pzCalcActionList.begin(), j3pzCalcActionList.end(), [&](QAction* q) { 
        q->setIcon(QIcon(":/kongfu/" + KF[q->text()] + ".png"));
        q->setCheckable(true);
        j3pzCalcActionGroup->addAction(q);
    });
    j3pzCalcActionGroup->setExclusive(true);
    j3pzCalcActionGroup->actions().last()->setChecked(true);
    connect(j3pzCalcActionGroup, &QActionGroup::triggered, this, &MainAPP::on_APP_j3pzCalc);

    j3pzCalcMenu = new QMenu("代按计算器", this);
    j3pzCalcMenu->addActions(j3pzCalcActionList);
    j3pzCalcMenu->setToolTip("请把本软件放在计算器xlsx同目录下\n目前仅支持唐门计算器");
    j3pzCalcMenu->setToolTipsVisible(true);
}

void MainAPP::initUI_slSudoku() {
    slSudokuAction = new QAction("试炼之地九宫格计算器", this);
    slSudokuAction->setEnabled(false);
    slSudokuAction->setToolTip("在做了在做了");
    connect(slSudokuAction, &QAction::triggered, this, &MainAPP::on_APP_slSudoku);
}

void MainAPP::initUI_keju() {
    kejuAction = new QAction("科举助手", this);
    kejuAction->setEnabled(false);
    kejuAction->setToolTip("在做了在做了");
    connect(kejuAction, &QAction::triggered, this, &MainAPP::on_APP_keju);
}

void MainAPP::initUI_kaifu() {
    kaifuAction = new QAction("开服监控", this);
    kaifuAction->setEnabled(false);
    kaifuAction->setToolTip("在做了在做了");
    connect(kaifuAction, &QAction::triggered, this, &MainAPP::on_APP_kaifu);
}

void MainAPP::initUI_wujia() {
    wujiaAction = new QAction("物价查询", this);
    wujiaAction->setEnabled(false);
    wujiaAction->setToolTip("在做了在做了");
    connect(wujiaAction, &QAction::triggered, this, &MainAPP::on_APP_wujia);
}

void MainAPP::initUI_about() {
    aboutAction = new QAction("关于", this);
    aboutAction->setEnabled(false);
    aboutAction->setToolTip("在做了在做了");
    connect(aboutAction, &QAction::triggered, this, &MainAPP::on_about);
}

void MainAPP::on_APP_j3pzCalc(QAction* q) {
    for (auto a : j3pzCalcActionGroup->actions()) {
        if (q->text().compare(a->text()) == 0) {
            if (q->text().compare(j3pzCalcActionGroup->actions().last()->text()) == 0) {  // 关闭
                if (App_j3pzCalc != NULL) {  // 开启->关闭
                    QString ret = App_j3pzCalc->off();
                    if (!ret.isEmpty()) {
                        disconnect(App_j3pzCalc->clipboard, 0, 0, 0);
                        tray->showMessage(App_j3pzCalc->description, ret, icon);
                    }
                    DEL(App_j3pzCalc);
                }
            } else {  // 开启
                // TODO: 切换心法，不结束进程进行切换
                if (App_j3pzCalc == NULL) {  // 关闭->开启
                    App_j3pzCalc = new APP_j3pzCalc(KF[q->text()]);
                } else {  // 开启->开启
                    if (KF[q->text()].compare(App_j3pzCalc->kf) != 0) {  // 切换了心法
                        DEL(App_j3pzCalc);
                        App_j3pzCalc = new APP_j3pzCalc(KF[q->text()]);
                    }
                }
                QString ret = App_j3pzCalc->on(QCoreApplication::applicationDirPath());
                if (ret.isEmpty()) {
                    connect(App_j3pzCalc->clipboard, &QClipboard::dataChanged, this, &MainAPP::on_APP_j3pzCalc_main);
                    tray->showMessage(App_j3pzCalc->description, "剪贴板监听中\n配装器导出数据-复制为JSON即可\n请检查计算器xlsx是否为" + q->text() + "DPS计算器", icon);
                } else {
                    j3pzCalcActionGroup->actions().last()->setChecked(true);
                    tray->showMessage(App_j3pzCalc->description, ret, icon);
                }
            }
        }
    }
}

void MainAPP::on_APP_j3pzCalc_main() {
    QString ret = App_j3pzCalc->main();
    if (!ret.isEmpty())
        tray->showMessage(App_j3pzCalc->description, ret, icon);
}

void MainAPP::on_APP_slSudoku() {

}

void MainAPP::on_APP_keju() {

}

void MainAPP::on_APP_kaifu() {

}

void MainAPP::on_APP_wujia() {

}

void MainAPP::on_about() {

}

//void MainAPP::onIconClicked(QSystemTrayIcon::ActivationReason reason) {
//    switch (reason) {
//    case QSystemTrayIcon::DoubleClick:
//        //tray->showMessage(description, "双击左键", icon);
//        //break;
//    case QSystemTrayIcon::Trigger:
//        //tray->showMessage(description, "单击左键", icon);
//        tray->showMessage(description, "点击左键", icon);
//        break;
//    case QSystemTrayIcon::MiddleClick:
//        tray->showMessage(description, "点击中键", icon);
//        break;
//    default:
//        break;
//    }
//}