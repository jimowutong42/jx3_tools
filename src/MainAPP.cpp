#include "..\include\MainAPP.h"

void MainAPP::initUI() {
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint);  // ������ȫ����
    this->setWindowOpacity(0);  // ��͸����

    initUI_j3pzCalc();
    initUI_slSudoku();
    initUI_keju();
    initUI_kaifu();
    initUI_wujia();
    initUI_about();

    quitAction = new QAction("�˳�", this);
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
    tray->setIcon(icon);  // ����ͼ��
    tray->setToolTip(description);  // ��ͣ��ʾ
    tray->setContextMenu(menu);

    //connect(tray, &QSystemTrayIcon::activated, this, &MainAPP::onIconClicked);  // �������ͼ����źźͲ�����

    tray->show();
    tray->showMessage(description, "��ӭ����", icon);
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

    j3pzCalcMenu = new QMenu("����������", this);
    j3pzCalcMenu->addActions(j3pzCalcActionList);
    j3pzCalcMenu->setToolTip("��ѱ�������ڼ�����xlsxͬĿ¼��\nĿǰ��֧�����ż�����");
    j3pzCalcMenu->setToolTipsVisible(true);
}

void MainAPP::initUI_slSudoku() {
    slSudokuAction = new QAction("����֮�ؾŹ��������", this);
    slSudokuAction->setEnabled(false);
    slSudokuAction->setToolTip("������������");
    connect(slSudokuAction, &QAction::triggered, this, &MainAPP::on_APP_slSudoku);
}

void MainAPP::initUI_keju() {
    kejuAction = new QAction("�ƾ�����", this);
    kejuAction->setEnabled(false);
    kejuAction->setToolTip("������������");
    connect(kejuAction, &QAction::triggered, this, &MainAPP::on_APP_keju);
}

void MainAPP::initUI_kaifu() {
    kaifuAction = new QAction("�������", this);
    kaifuAction->setEnabled(false);
    kaifuAction->setToolTip("������������");
    connect(kaifuAction, &QAction::triggered, this, &MainAPP::on_APP_kaifu);
}

void MainAPP::initUI_wujia() {
    wujiaAction = new QAction("��۲�ѯ", this);
    wujiaAction->setEnabled(false);
    wujiaAction->setToolTip("������������");
    connect(wujiaAction, &QAction::triggered, this, &MainAPP::on_APP_wujia);
}

void MainAPP::initUI_about() {
    aboutAction = new QAction("����", this);
    aboutAction->setEnabled(false);
    aboutAction->setToolTip("������������");
    connect(aboutAction, &QAction::triggered, this, &MainAPP::on_about);
}

void MainAPP::on_APP_j3pzCalc(QAction* q) {
    for (auto a : j3pzCalcActionGroup->actions()) {
        if (q->text().compare(a->text()) == 0) {
            if (q->text().compare(j3pzCalcActionGroup->actions().last()->text()) == 0) {  // �ر�
                if (App_j3pzCalc != NULL) {  // ����->�ر�
                    QString ret = App_j3pzCalc->off();
                    if (!ret.isEmpty()) {
                        disconnect(App_j3pzCalc->clipboard, 0, 0, 0);
                        tray->showMessage(App_j3pzCalc->description, ret, icon);
                    }
                    DEL(App_j3pzCalc);
                }
            } else {  // ����
                // TODO: �л��ķ������������̽����л�
                if (App_j3pzCalc == NULL) {  // �ر�->����
                    App_j3pzCalc = new APP_j3pzCalc(KF[q->text()]);
                } else {  // ����->����
                    if (KF[q->text()].compare(App_j3pzCalc->kf) != 0) {  // �л����ķ�
                        DEL(App_j3pzCalc);
                        App_j3pzCalc = new APP_j3pzCalc(KF[q->text()]);
                    }
                }
                QString ret = App_j3pzCalc->on(QCoreApplication::applicationDirPath());
                if (ret.isEmpty()) {
                    connect(App_j3pzCalc->clipboard, &QClipboard::dataChanged, this, &MainAPP::on_APP_j3pzCalc_main);
                    tray->showMessage(App_j3pzCalc->description, "�����������\n��װ����������-����ΪJSON����\n���������xlsx�Ƿ�Ϊ" + q->text() + "DPS������", icon);
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
//        //tray->showMessage(description, "˫�����", icon);
//        //break;
//    case QSystemTrayIcon::Trigger:
//        //tray->showMessage(description, "�������", icon);
//        tray->showMessage(description, "������", icon);
//        break;
//    case QSystemTrayIcon::MiddleClick:
//        tray->showMessage(description, "����м�", icon);
//        break;
//    default:
//        break;
//    }
//}