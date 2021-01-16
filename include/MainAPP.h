#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QCoreApplication>
#include "..\include\APP_j3pzCalc.h" 

class MainAPP : public QMainWindow {
    Q_OBJECT

public:
    MainAPP(QWidget* parent = Q_NULLPTR);

private:
    QIcon icon = QIcon(":/ptt.png");  // ͼ��
    QString description = QString("����3���ߺ� by��į��ͩ");  // ����
    QSystemTrayIcon* tray;  // ���̶���
    QMenu* menu;  // �Ҽ��˵�����
    QMenu* funcMenu;  // �Ҽ��˵�-���ܲ˵�����
    QAction* j3pzCalcAction;  // �Ҽ��˵�-���ܲ˵�-����������
    QAction* settingAction;  // �Ҽ��˵�-����
    QAction* quitAction;  // �Ҽ��˵�-�˳�

    APP_j3pzCalc* App_j3pzCalc;  // ����-����������

    int initUI();
    void createActions();
    void createTrayIcon();

private slots:  // �ۺ���
    void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // �����ͼ��
    void setting();  // ����
    void on_APP_j3pzCalc(bool checked);  // ����������
    void on_APP_j3pzCalc_main();
};