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

    //connect(tray, &QSystemTrayIcon::activated, this, &MainAPP::onIconClicked);  // 把鼠标点击图标的信号和槽连接

    tray->show();
    return 0;
}

void MainAPP::createActions() {
    j3pzCalcAction = new QAction("代填计算器", this);
    j3pzCalcAction->setToolTip("请把本软件放在计算器xlsx同目录下\n目前仅支持天罗计算器");
    j3pzCalcAction->setCheckable(true);
    connect(j3pzCalcAction, &QAction::toggled, this, &MainAPP::j3pzCalc);

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

void MainAPP::j3pzCalc(bool checked) {
    if (checked) {
        clipbordListenerON();
        tray->showMessage(description, "剪贴板监听中\n配装器导出数据-复制为JSON即可", icon);
    } else {
        clipbordListenerOFF();
        tray->showMessage(description, "代填计算器——已关闭", icon);
    }
}

void MainAPP::clipbordListenerON() {
    clipboard = QGuiApplication::clipboard();
    connect(clipboard, &QClipboard::dataChanged, this, &MainAPP::onClipboradChanged);
}

void MainAPP::clipbordListenerOFF() {
    disconnect(clipboard, 0, 0, 0);
    clipboard->destroyed();
}

void MainAPP::onClipboradChanged() {
    clipboard = QGuiApplication::clipboard();
    QString text = clipboard->text();
    if (!text.isEmpty()) {
        QDir xlsx_dir(QCoreApplication::applicationDirPath());
        QStringList xlsx_files = xlsx_dir.entryList(QStringList("*.xlsx"), QDir::Files | QDir::Readable);
        if (xlsx_files.count() == 1) {  // TODO 多个xlsx 文件名检验 版本检验 switch
            QString dps = APP_j3pzCalc::APP_j3pzCalc(xlsx_files[0], sheet_name, text);
            tray->showMessage("代填计算器", dps, icon);
        } else {
            tray->showMessage("找不到计算器Orz", "请将本exe和计算器xlsx放一起哦\n" + xlsx_files[0], icon);
        }
    }
}


void MainAPP::setting() {

}