#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>
#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>
#include <QtCore/QCoreApplication>
#include <QtCore/QDIR>
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
    QString sheet_name = QString("DPS������");  // ����������������
    QAction* settingAction;  // �Ҽ��˵�-����
    QAction* quitAction;  // �Ҽ��˵�-�˳�
    QClipboard* clipboard;  // ���������

    int initUI();
    void createActions();
    void createTrayIcon();
    void clipbordListenerON();
    void clipbordListenerOFF();

private slots:  // �ۺ���
    void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // �����ͼ��
    void onClipboradChanged();  // �������¼�
    void j3pzCalc(bool checked);  // ����������
    void setting();  // ����
};