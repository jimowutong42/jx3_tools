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
    QIcon icon = QIcon(":/ptt.png");  // 图标
    QString description = QString("剑网3工具盒 by寂寞梧桐");  // 描述
    QSystemTrayIcon* tray;  // 托盘对象
    QMenu* menu;  // 右键菜单对象
    QMenu* funcMenu;  // 右键菜单-功能菜单对象
    QAction* j3pzCalcAction;  // 右键菜单-功能菜单-代按计算器
    QAction* settingAction;  // 右键菜单-设置
    QAction* quitAction;  // 右键菜单-退出

    APP_j3pzCalc* App_j3pzCalc;  // 功能-代按计算器

    int initUI();
    void createActions();
    void createTrayIcon();

private slots:  // 槽函数
    void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // 鼠标点击图标
    void setting();  // 设置
    void on_APP_j3pzCalc(bool checked);  // 代按计算器
    void on_APP_j3pzCalc_main();
};