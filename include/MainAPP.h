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
    QIcon icon = QIcon(":/ptt.png");  // ͼ��
    QString description = QString("����3���ߺ� by��į��ͩ");  // ����
    QMap<QString, QString> KF = { { "����", "tl"}, { "����", "jy" }, { "�ر�", "off" } };  // �ķ�

    QSystemTrayIcon* tray;  // ���̶���
    QMenu* menu;  // �Ҽ��˵�����

    // �Ҽ��˵�-����������
    QMenu* j3pzCalcMenu;
    QActionGroup* j3pzCalcActionGroup;

    // �Ҽ��˵�-����֮�ؾŹ��������
    QAction* slSudokuAction;

    // �Ҽ��˵�-�ƾ�����
    QAction* kejuAction;

    // �Ҽ��˵�-�������
    QAction* kaifuAction;

    // �Ҽ��˵�-��۲�ѯ
    QAction* wujiaAction;

    // �Ҽ��˵�-����
    QAction* aboutAction;

    // �Ҽ��˵�-�˳�
    QAction* quitAction;

    APP_j3pzCalc* App_j3pzCalc;  // ����-����������

    void initUI();
    void initUI_j3pzCalc();
    void initUI_slSudoku();
    void initUI_keju();
    void initUI_kaifu();
    void initUI_wujia();
    void initUI_about();

private slots:  // �ۺ���
    // ����������
    void on_APP_j3pzCalc(QAction* q);
    void on_APP_j3pzCalc_main();

    // ����֮�ؾŹ��������
    void on_APP_slSudoku();

    // �ƾ�����
    void on_APP_keju();

    // �������
    void on_APP_kaifu();

    // ��۲�ѯ
    void on_APP_wujia();

    // ����
    void on_about();
    //void onIconClicked(QSystemTrayIcon::ActivationReason reason);  // �����ͼ��
};