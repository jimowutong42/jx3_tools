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

// 功能-代按计算器
class APP_j3pzCalc {

public:
    QString description;  // 功能名称
    QClipboard* clipboard;  // 剪贴板对象
    QAxObject* Application;
    QAxObject* Workbooks;
    QAxObject* Workbook;
    QAxObject* Worksheets;
    QAxObject* Worksheet;

    // TODO: 错误码 简化
#define ERR(e) ERR_APP + ERR_CODE[e]
    QString ERR_APP;
    QStringList ERR_CODE;

    QString kf;  // 心法
    QMap<QString, QString> sheet_name;  // 心法对应计算器工作簿名称
    QStringList all_keys;  // 所有属性
    QMap<QString, QVector<qint32>> keys;  // 心法对应属性序号
    QMap<QString, QStringList> cells;  // 心法对应属性单元格
    QMap<QString, QStringList> dps_cells;  // 心法对应DPS单元格

public:
    APP_j3pzCalc(QString kongfu)
        : description(QString("代按计算器"))
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
            { QString("tl"), QString("DPS计算器") },
            { QString("jy"), QString("DPS计算器") }
            })
        , all_keys(QStringList({
            // "气血", "体质", "基础治疗", "治疗", "外防率", "外防等级", "内防率", "内防等级", "闪避率", "闪避等级",
            // "招架率", "招架等级", "拆招", "御劲率", "御劲等级", "化劲率", "化劲等级", "装分",
            "元气", "根骨", "力道", "身法", "基础攻击", "攻击", "会心率", "会心等级", "会心效果", "会心效果等级",
            "无双率", "无双等级", "破防率", "破防等级", "破招", "加速率", "加速等级"
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
    QString on(QString xlsx_path);  // 开启
    QString init(QString xlsx_name);
    QString main();  // 主程序
    QVector<QVariant> main_json(QString json_string);
    QString main_xlsx(QVector<QVariant> p);
    QString off();  // 关闭
    // TODO: APP_j3pzCalc::setting()
};
