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
    QIcon icon = QIcon(":/ptt.png");  // 图标
    QString description = QString("剑网3工具盒 by寂寞梧桐");  // 描述
    QSystemTrayIcon* tray;  // 托盘对象
    QMenu* menu;  // 右键菜单对象
    QMenu* funcMenu;  // 右键菜单-功能菜单对象
    QAction* j3pzCalcAction;  // 右键菜单-功能菜单-代按计算器
    QString sheet_name = QString("DPS计算器");  // 计算器工作簿名称
    QAction* settingAction;  // 右键菜单-设置
    QAction* quitAction;  // 右键菜单-退出
    QClipboard* clipboard;  // 剪贴板对象

    int initUI();
    void createActions();
    void createTrayIcon();
    void clipbordListenerON();
    void clipbordListenerOFF();

private slots:  // 槽函数
    void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // 鼠标点击图标
    void onClipboradChanged();  // 剪贴板事件
    void j3pzCalc(bool checked);  // 代按计算器
    void setting();  // 设置
};