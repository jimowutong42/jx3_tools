#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include "../3rdparty/QtXlsxWriter/src/xlsx/xlsxdocument.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QDir>
#include <ActiveQt/QAxObject>
#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>

#define DEL(p) { if (p != NULL) { delete p; p = NULL; } }

// ����-����������
class APP_j3pzCalc {

public:
    QString description;  // ��������
    QClipboard* clipboard;  // ���������
    QAxObject* Application;
    QAxObject* Workbooks;
    QAxObject* Workbook;
    QAxObject* Worksheets;
    QAxObject* Worksheet;

    // TODO: ������ ��
#define ERR(e) ERR_APP + ERR_CODE[e]
    QString ERR_APP;
    QStringList ERR_CODE;

    QString kf;  // �ķ�
    QMap<QString, QString> sheet_name;  // �ķ���Ӧ����������������
    QStringList all_keys;  // ��������
    QMap<QString, QVector<qint32>> keys;  // �ķ���Ӧ�������
    QMap<QString, QStringList> cells;  // �ķ���Ӧ���Ե�Ԫ��
    QMap<QString, QStringList> dps_cells;  // �ķ���ӦDPS��Ԫ��

public:
    APP_j3pzCalc(QString kongfu)
        : description(QString("����������"))
        , clipboard(NULL)
        , Application(NULL)
        , Workbooks(NULL)
        , Workbook(NULL)
        , Worksheets(NULL)
        , Worksheet(NULL)
        , ERR_APP(QString("[?]"))
        , ERR_CODE(QStringList({
            "[E0] Application.isNull",
            "[E1] Application.DisplayAlerts.isNull",
            "[E2] Application.Workbooks.isNull",
            "[E3] Workbooks.Count.!isValid",
            "[E4] Workbooks.Count.!0.",
            "[E5] Workbook.isNull",
            "[E6] (O)Workbooks.Count.!isValid",
            "[E7] (O)Workbooks.Count.!1.",
            "[E8] Workbook.Worksheets.isNull",
            "[E9] Worksheets.Count.!isValid",
            "[E10] Worksheets.Count.!9.",
            "[E11] Worksheet.isNull",
            "[E12] QJsonParseError.",
            "[E13] json_map.!contains.",
            "[E14] json_map.value.type.!String.",
            "[E15] Range.isNull.",
            "[E16] Range.Value2.w.",
            "[E17] Range.Value2.r.!isValid."
            }))
        , kf(kongfu)
        , sheet_name({
            { QString("tl"), QString("DPS������") },
            { QString("jy"), QString("DPS������") }
            })
        , all_keys(QStringList({
            // "��Ѫ", "����", "��������", "����", "�����", "����ȼ�", "�ڷ���", "�ڷ��ȼ�", "������", "���ܵȼ�",
            // "�м���", "�мܵȼ�", "����", "������", "�����ȼ�", "������", "�����ȼ�", "װ��",
            "Ԫ��", "����", "����", "��", "��������", "����", "������", "���ĵȼ�", "����Ч��", "����Ч���ȼ�",
            "��˫��", "��˫�ȼ�", "�Ʒ���", "�Ʒ��ȼ�", "����", "������", "���ٵȼ�"
            }))
        , keys({
            { QString("tl"), { 0, 4, 5, 6, 8, 10, 13, 14, 16 } },
            { QString("jy"), { 2, 4, 5, 14, 13, 16, 6, 8, 10 } }
            })
        , cells({
            { QString("tl"), QStringList({ "H3", "H4", "H5", "H7", "H8", "H9", "H10", "H11", "F10" }) },
            { QString("jy"), QStringList({ "H3", "H4", "H5", "H7", "H8", "H9", "F5", "F6", "F7" }) }
            })
        , dps_cells({
            { QString("tl"), QStringList({ "V7","V8" }) },
            { QString("jy"), QStringList({ "V7","V8" }) }
            }) {
    };
    ~APP_j3pzCalc() {
        off();
        DEL(Application);
    }
    QString on(QString xlsx_path);  // ����
    QString init(QString xlsx_name);
    QString main();  // ������
    QVector<QVariant> main_json(QString json_string);
    QString main_xlsx(QVector<QVariant> p);
    QString off();  // �ر�
    // TODO: APP_j3pzCalc::setting()
};
