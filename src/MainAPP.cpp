#include "..\include\MainAPP.h"

MainAPP::MainAPP(QWidget* parent) : QMainWindow(parent) {
    if (!initUI()) {
        tray->showMessage(description, "欢迎大侠", icon);
    }
}

int MainAPP::initUI() {
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint);  // 主窗体全隐藏
    this->setWindowOpacity(0);  // 不透明度

    createActions();
    createTrayIcon();

    App_j3pzCalc = new APP_j3pzCalc();
    //connect(tray, &QSystemTrayIcon::activated, this, &MainAPP::onIconClicked);  // 把鼠标点击图标的信号和槽连接

    tray->show();
    return 0;
}

void MainAPP::createActions() {
    j3pzCalcAction = new QAction("代按计算器", this);
    j3pzCalcAction->setToolTip("请把本软件放在计算器xlsx同目录下\n目前仅支持天罗计算器");
    j3pzCalcAction->setCheckable(true);
    connect(j3pzCalcAction, &QAction::toggled, this, &MainAPP::on_APP_j3pzCalc);

    settingAction = new QAction("设置", this);
    settingAction->setEnabled(false);
    settingAction->setToolTip("在做了在做了");
    connect(settingAction, &QAction::triggered, this, &MainAPP::setting);

    quitAction = new QAction("退出", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainAPP::createTrayIcon() {
    menu = new QMenu(this);

    funcMenu = menu->addMenu("功能");
    funcMenu->addAction(j3pzCalcAction);
    funcMenu->setToolTipsVisible(true);

    menu->addAction(settingAction);
    menu->addAction(quitAction);
    menu->setToolTipsVisible(true);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(icon);  // 托盘图标
    tray->setToolTip(description);  // 悬停提示
    tray->setContextMenu(menu);
}

void MainAPP::onIconClicked(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        //tray->showMessage(description, "双击左键", icon);
        //break;
    case QSystemTrayIcon::Trigger:
        //tray->showMessage(description, "单击左键", icon);
        tray->showMessage(description, "点击左键", icon);
        break;
    case QSystemTrayIcon::MiddleClick:
        tray->showMessage(description, "点击中键", icon);
        break;
    default:
        break;
    }
}

void MainAPP::on_APP_j3pzCalc(bool checked) {
    if (checked) {
        QString ret = App_j3pzCalc->on(QCoreApplication::applicationDirPath());
        if (ret.isEmpty()) {
            connect(App_j3pzCalc->clipboard, &QClipboard::dataChanged, this, &MainAPP::on_APP_j3pzCalc_main);
            tray->showMessage(App_j3pzCalc->description, "剪贴板监听中\n配装器导出数据-复制为JSON即可", icon);
        } else {
            tray->showMessage(App_j3pzCalc->description, ret, icon);
        }
    } else {
        QString ret = App_j3pzCalc->off();
        if (ret.isEmpty()) {
            disconnect(App_j3pzCalc->clipboard, 0, 0, 0);
            tray->showMessage(App_j3pzCalc->description, "已关闭", icon);
        } else {
            tray->showMessage(App_j3pzCalc->description, ret, icon);
        }
    }
}

void MainAPP::on_APP_j3pzCalc_main() {
    QString ret = App_j3pzCalc->main();
    if (!ret.isEmpty())
        tray->showMessage(App_j3pzCalc->description, ret, icon);
}

void MainAPP::setting() {

}