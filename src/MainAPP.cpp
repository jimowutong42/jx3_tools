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

    //connect(tray, &QSystemTrayIcon::activated, this, &MainAPP::onIconClicked);  // �������ͼ����źźͲ�����

    tray->show();
    return 0;
}

void MainAPP::createActions() {
    j3pzCalcAction = new QAction("���������", this);
    j3pzCalcAction->setToolTip("��ѱ�������ڼ�����xlsxͬĿ¼��\nĿǰ��֧�����޼�����");
    j3pzCalcAction->setCheckable(true);
    connect(j3pzCalcAction, &QAction::toggled, this, &MainAPP::j3pzCalc);

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

void MainAPP::j3pzCalc(bool checked) {
    if (checked) {
        clipbordListenerON();
        tray->showMessage(description, "�����������\n��װ����������-����ΪJSON����", icon);
    } else {
        clipbordListenerOFF();
        tray->showMessage(description, "��������������ѹر�", icon);
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
        if (xlsx_files.count() == 1) {  // TODO ���xlsx �ļ������� �汾���� switch
            QString dps = APP_j3pzCalc::APP_j3pzCalc(xlsx_files[0], sheet_name, text);
            tray->showMessage("���������", dps, icon);
        } else {
            tray->showMessage("�Ҳ���������Orz", "�뽫��exe�ͼ�����xlsx��һ��Ŷ\n" + xlsx_files[0], icon);
        }
    }
}


void MainAPP::setting() {

}