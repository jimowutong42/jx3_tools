#include "..\include\APP_j3pzCalc.h"

QString APP_j3pzCalc::APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json_string) {
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        return "����JSONʧ�ܣ�" + err.errorString();
    } else {
        /*
        {"��Ѫ":"199073","����":"13915","Ԫ��":"2844","����":"150","����":"149","��":"150","����":"13357","��������":"8380",
        "������":"23.76%","���ĵȼ�":"8490","����Ч��":"175.58%","����Ч���ȼ�":"72","����":"6468","������":"0.00%","���ٵȼ�":"0",
        "�Ʒ���":"18.16%","�Ʒ��ȼ�":"6491","��˫��":"20.32%","��˫�ȼ�":"7002","��������":"0","����":"0","�����":"5.06%",
        "����ȼ�":"1017","�ڷ���":"7.88%","�ڷ��ȼ�":"1633","������":"0.00%","���ܵȼ�":"0","�м���":"3.00%","�мܵȼ�":"0",
        "����":"0","������":"0.00%","�����ȼ�":"0","������":"25.00%","�����ȼ�":"1725","װ��":"69083"}*/
        QJsonObject json_obj = json_doc.object();
        params p = { json_obj["Ԫ��"], json_obj["��������"], json_obj["����"], json_obj["������"], json_obj["����Ч��"], 
            json_obj["��˫��"], json_obj["�Ʒ��ȼ�"], json_obj["����"], json_obj["���ٵȼ�"] };
        //if (check_params(p)) {
        //    return "��ȡ����ʧ�ܣ�����ȱʧ���ֶ�";
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
        //if (json_obj.contains("Ԫ��")) {
        //    //return "!" + json_obj["Ԫ��"].toString() + "!";
        //    return "!" + QString::number(json_obj["Ԫ��"].isUndefined()) + "!";
        //}
        QXlsx::Document xlsx(xlsx_name);
        if (xlsx.selectSheet(sheet_name)) {
            return xlsx.read("V7").toString() + " DPS: " + QString::number(xlsx.cellAt("V8")->value().toDouble(), 'f', 0);
        } else {
            return "�򿪼�����xlsxʧ�ܣ�δ�ҵ���DPS��������";
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
