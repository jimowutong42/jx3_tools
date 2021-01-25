#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QCoreApplication>
#include "..\include\APP_j3pzCalc.h" 

#define DEL(p) { if (p != NULL) { delete p; p = NULL; } }

class MainAPP : public QMainWindow {
    Q_OBJECT

public:
    MainAPP(QWidget* parent = Q_NULLPTR)
        : tray(NULL)
        , menu(NULL)
        , j3pzCalcMenu(NULL)
        , j3pzCalcActionGroup(NULL)
        , settingAction(NULL)
        , quitAction(NULL)
        , App_j3pzCalc(NULL) {
        if (initUI()) {
            tray->showMessage(description, "��ӭ����", icon);
        }
    };
    ~MainAPP() {
        DEL(App_j3pzCalc);
    };

private:
    QIcon icon = QIcon(":/ptt.png");  // ͼ��
    QString description = QString("����3���ߺ� by��į��ͩ");  // ����
    QMap<QString, QString> KF = { { "����", "tl"}, { "����", "jy" }, { "�ر�", "off" } };  // �ķ�

    QSystemTrayIcon* tray;  // ���̶���
    QMenu* menu;  // �Ҽ��˵�����
    QMenu* j3pzCalcMenu;  // �Ҽ��˵�-�����������˵�
    QActionGroup* j3pzCalcActionGroup;  // �Ҽ��˵�-�����������˵�-ѡ����

    QAction* settingAction;  // �Ҽ��˵�-����
    QAction* quitAction;  // �Ҽ��˵�-�˳�

    APP_j3pzCalc* App_j3pzCalc;  // ����-����������

    bool initUI();
    bool initUI_j3pzCalc();
    bool initUI_setting();

private slots:  // �ۺ���
    //void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // �����ͼ��
    void on_APP_j3pzCalc(QAction* q);  // ����������
    void on_APP_j3pzCalc_main();
    void on_setting();  // ����
};