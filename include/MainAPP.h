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
            tray->showMessage(description, "欢迎大侠", icon);
        }
    };
    ~MainAPP() {
        DEL(App_j3pzCalc);
    };

private:
    QIcon icon = QIcon(":/ptt.png");  // 图标
    QString description = QString("剑网3工具盒 by寂寞梧桐");  // 描述
    QMap<QString, QString> KF = { { "天罗", "tl"}, { "惊羽", "jy" }, { "关闭", "off" } };  // 心法

    QSystemTrayIcon* tray;  // 托盘对象
    QMenu* menu;  // 右键菜单对象
    QMenu* j3pzCalcMenu;  // 右键菜单-代按计算器菜单
    QActionGroup* j3pzCalcActionGroup;  // 右键菜单-代按计算器菜单-选项组

    QAction* settingAction;  // 右键菜单-设置
    QAction* quitAction;  // 右键菜单-退出

    APP_j3pzCalc* App_j3pzCalc;  // 功能-代按计算器

    bool initUI();
    bool initUI_j3pzCalc();
    bool initUI_setting();

private slots:  // 槽函数
    //void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // 鼠标点击图标
    void on_APP_j3pzCalc(QAction* q);  // 代按计算器
    void on_APP_j3pzCalc_main();
    void on_setting();  // 设置
};