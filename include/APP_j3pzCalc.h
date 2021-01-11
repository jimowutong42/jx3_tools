#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include "../3rdparty/QtXlsxWriter/src/xlsx/xlsxdocument.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

namespace APP_j3pzCalc {
    struct params {
        QJsonValue JiChuYuanQi;
        QJsonValue JiChuGongJi;
        QJsonValue ZuiZhongGongJi;
        QJsonValue HuiXin;
        QJsonValue HuiXiao;
        QJsonValue WuShuang;
        QJsonValue NeiGongPoFang;
        QJsonValue PoZhao;
        QJsonValue JiaSu;
    };
    QString APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json);
    bool check_params(params p);
}
