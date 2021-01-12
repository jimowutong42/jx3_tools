#include "..\include\APP_j3pzCalc.h"

QString APP_j3pzCalc::APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json_string) {
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) return "����JSONʧ�ܣ�" + err.errorString();
    QVariantMap json_map = json_doc.toVariant().toMap();
    QVector<QVariant> p;
    for (QString k : keys) {
        if (!json_map.contains(k)) {
            return "����JSONʧ�ܣ�json_map.contains(\"" + k + "\") = false";
        } else {
            QVariant v = json_map.value(k);
            // if (v.type() != QVariant::Type::String || !v.convert(types[i]))  // TODO: ����ת��
            if (v.type() != QVariant::Type::String)
                return "����JSONʧ�ܣ�" + k + "���ʹ��� (" + QString::number(v.type()) + ")";
            p.append(v);
        }
    }
    QXlsx::Document xlsx(xlsx_name);
    if (xlsx.selectSheet(sheet_name)) {
        // TODO: std::for_each lambda
        QVariant t;
        for (auto cell : cells) {
            if (!xlsx.write(cell, p[cells.indexOf(cell)])) {
                return "��д������xlsxʧ�ܣ�" + cell + ": " + p[cells.indexOf(cell)].toString();
            } else {
                t = xlsx.read(cell);  // TODO
            }
        }
        return xlsx.read(dps_cells[0]).toString() + " DPS: " + QString::number(xlsx.cellAt(dps_cells[1])->value().toDouble(), 'f', 0);
    } else {
        return "�򿪼�����xlsxʧ�ܣ�δ�ҵ���DPS��������";
    }
}
