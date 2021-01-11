#include "..\include\APP_j3pzCalc.h"

QString APP_j3pzCalc::APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json) {
    QXlsx::Document xlsx(xlsx_name);
    if (xlsx.selectSheet(sheet_name)) {
        QString ret;
        ret = xlsx.read("V7").toString() + " DPS: " + xlsx.cellAt("V8")->value().toString().split(".")[0];
        return ret;
    } else {
        return "打开计算器xlsx失败：未找到【DPS计算器】";
    }
}
