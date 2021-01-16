#include "..\include\MainAPP.h"

MainAPP::MainAPP(QWidget* parent) : QMainWindow(parent) {
    if (!initUI()) {
        tray->showMessage(description, "��ӭ����", icon);
    }
}

int MainAPP::initUI() {
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint);  // ������ȫ����
    this->setWindowOpacity(0);  // ��͸����

    createActions();
    createTrayIcon();

    App_j3pzCalc = new APP_j3pzCalc();
    //connect(tray, &QSystemTrayIcon::activated, this, &MainAPP::onIconClicked);  // �������ͼ����źźͲ�����

    tray->show();
    return 0;
}

void MainAPP::createActions() {
    j3pzCalcAction = new QAction("����������", this);
    j3pzCalcAction->setToolTip("��ѱ�������ڼ�����xlsxͬĿ¼��\nĿǰ��֧�����޼�����");
    j3pzCalcAction->setCheckable(true);
    connect(j3pzCalcAction, &QAction::toggled, this, &MainAPP::on_APP_j3pzCalc);

    settingAction = new QAction("����", this);
    settingAction->setEnabled(false);
    settingAction->setToolTip("������������");
    connect(settingAction, &QAction::triggered, this, &MainAPP::setting);

    quitAction = new QAction("�˳�", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainAPP::createTrayIcon() {
    menu = new QMenu(this);

    funcMenu = menu->addMenu("����");
    funcMenu->addAction(j3pzCalcAction);
    funcMenu->setToolTipsVisible(true);

    menu->addAction(settingAction);
    menu->addAction(quitAction);
    menu->setToolTipsVisible(true);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(icon);  // ����ͼ��
    tray->setToolTip(description);  // ��ͣ��ʾ
    tray->setContextMenu(menu);
}

void MainAPP::onIconClicked(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        //tray->showMessage(description, "˫�����", icon);
        //break;
    case QSystemTrayIcon::Trigger:
        //tray->showMessage(description, "�������", icon);
        tray->showMessage(description, "������", icon);
        break;
    case QSystemTrayIcon::MiddleClick:
        tray->showMessage(description, "����м�", icon);
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
            tray->showMessage(App_j3pzCalc->description, "�����������\n��װ����������-����ΪJSON����", icon);
        } else {
            tray->showMessage(App_j3pzCalc->description, ret, icon);
        }
    } else {
        QString ret = App_j3pzCalc->off();
        if (ret.isEmpty()) {
            disconnect(App_j3pzCalc->clipboard, 0, 0, 0);
            tray->showMessage(App_j3pzCalc->description, "�ѹر�", icon);
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