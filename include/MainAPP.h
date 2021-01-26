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
        , slSudokuAction(NULL)
        , kejuAction(NULL)
        , kaifuAction(NULL)
        , wujiaAction(NULL)
        , aboutAction(NULL)
        , quitAction(NULL)
        , App_j3pzCalc(NULL) {
        initUI();
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

    // 右键菜单-代按计算器
    QMenu* j3pzCalcMenu;
    QActionGroup* j3pzCalcActionGroup;

    // 右键菜单-试炼之地九宫格计算器
    QAction* slSudokuAction;

    // 右键菜单-科举助手
    QAction* kejuAction;

    // 右键菜单-开服监控
    QAction* kaifuAction;

    // 右键菜单-物价查询
    QAction* wujiaAction;

    // 右键菜单-关于
    QAction* aboutAction;

    // 右键菜单-退出
    QAction* quitAction;

    APP_j3pzCalc* App_j3pzCalc;  // 功能-代按计算器

    void initUI();
    void initUI_j3pzCalc();
    void initUI_slSudoku();
    void initUI_keju();
    void initUI_kaifu();
    void initUI_wujia();
    void initUI_about();

private slots:  // 槽函数
    // 代按计算器
    void on_APP_j3pzCalc(QAction* q);
    void on_APP_j3pzCalc_main();

    // 试炼之地九宫格计算器
    void on_APP_slSudoku();

    // 科举助手
    void on_APP_keju();

    // 开服监控
    void on_APP_kaifu();

    // 物价查询
    void on_APP_wujia();

    // 关于
    void on_about();
    //void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // 鼠标点击图标
};