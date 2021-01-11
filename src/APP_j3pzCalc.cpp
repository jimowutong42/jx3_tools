#include "..\include\APP_j3pzCalc.h"

QString APP_j3pzCalc::APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json_string) {
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        return "解析JSON失败：" + err.errorString();
    } else {
        /*
        {"气血":"199073","体质":"13915","元气":"2844","根骨":"150","力道":"149","身法":"150","攻击":"13357","基础攻击":"8380",
        "会心率":"23.76%","会心等级":"8490","会心效果":"175.58%","会心效果等级":"72","破招":"6468","加速率":"0.00%","加速等级":"0",
        "破防率":"18.16%","破防等级":"6491","无双率":"20.32%","无双等级":"7002","基础治疗":"0","治疗":"0","外防率":"5.06%",
        "外防等级":"1017","内防率":"7.88%","内防等级":"1633","闪避率":"0.00%","闪避等级":"0","招架率":"3.00%","招架等级":"0",
        "拆招":"0","御劲率":"0.00%","御劲等级":"0","化劲率":"25.00%","化劲等级":"1725","装分":"69083"}*/
        QJsonObject json_obj = json_doc.object();
        params p = { json_obj["元气"], json_obj["基础攻击"], json_obj["攻击"], json_obj["会心率"], json_obj["会心效果"], 
            json_obj["无双率"], json_obj["破防等级"], json_obj["破招"], json_obj["加速等级"] };
        //if (check_params(p)) {
        //    return "读取参数失败：存在缺失的字段";
        //}
        //QJsonValue* v = (QJsonValue*)&p;
        //QString ret;
        //for (int i = 0; i < sizeof(params) / sizeof(QJsonValue); i++) {
        //    ret += " !" + QString::number((*v++).type());
        //}
        //return ret;
        //return "!" + json_obj.keys()[0] + "!";
        QStringList json_keys = json_obj.keys();
        return json_keys.join("!");
        //if (json_obj.contains("元气")) {
        //    //return "!" + json_obj["元气"].toString() + "!";
        //    return "!" + QString::number(json_obj["元气"].isUndefined()) + "!";
        //}
        QXlsx::Document xlsx(xlsx_name);
        if (xlsx.selectSheet(sheet_name)) {
            return xlsx.read("V7").toString() + " DPS: " + QString::number(xlsx.cellAt("V8")->value().toDouble(), 'f', 0);
        } else {
            return "打开计算器xlsx失败：未找到【DPS计算器】";
        }
    }
}

bool APP_j3pzCalc::check_params(params p) {
    QJsonValue* v = (QJsonValue*)&p;
    bool ret = false;
    for (int i = 0; i < sizeof(params) / sizeof(QJsonValue); i++) {
        ret = ret || ((*v++).type() == QJsonValue::Null);
    }
    return ret;
}
