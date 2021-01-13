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
    auto WPS_Application = new QAxObject("KET.Application");
    if (WPS_Application->isNull()) return "QAxObject(\"KET.Application\") ERROR!";
    auto WPS_Application_Workbooks = WPS_Application->querySubObject("Workbooks");
    if (WPS_Application_Workbooks->isNull()) return "WPS_Application_Workbooks ERROR!";
    QFileInfo xlsx_file(xlsx_name);
    if (!xlsx_file.exists()) return "!" + xlsx_name + ".exists()";
    // Open Ȩ�����⣿
    auto WPS_Application_Workbooks_Open = WPS_Application_Workbooks->querySubObject("Open (const QString&)", xlsx_file.absolutePath());
    if (WPS_Application_Workbooks_Open->isNull()) return "WPS_Application_Workbooks_Open ERROR!";
    auto WPS_Application_ActiveWorkbook = WPS_Application->querySubObject("ActiveWorkBook");
    if (WPS_Application_ActiveWorkbook->isNull()) return "WPS_Application_ActiveWorkbook ERROR!";
    auto wps_sheets = WPS_Application_ActiveWorkbook->querySubObject("Worksheets");
    auto wps_sheet = WPS_Application_ActiveWorkbook->querySubObject("Sheets(int)", 8);
    if (wps_sheet->isNull()) return "Sheets(8) ERROR";
    wps_sheet->dynamicCall("activate()");
    return wps_sheet->property("Name").toString();
    //QXlsx::Document xlsx(xlsx_name);
    //if (xlsx.selectSheet(sheet_name)) {
    //    // TODO: std::for_each lambda
    //    QString test = xlsx.read(cells[0]).toString() + "," + xlsx.cellAt(dps_cells[1])->value().toString() + ",";
    //    //for (auto cell : cells) {
    //    //    if (!xlsx.write(cell, p[cells.indexOf(cell)])) {
    //    //        return "��д������xlsxʧ�ܣ�" + cell + ": " + p[cells.indexOf(cell)].toString();
    //    //    } else {
    //    //        test += xlsx.read(cell).toString() + ",";  // TODO
    //    //    }
    //    //}
    //    if (!xlsx.write(cells[0], p[0])) {
    //        return "err";
    //    } else {
    //        test += xlsx.read(cells[0]).toString() + "," + xlsx.cellAt(dps_cells[1])->value().toString();
    //    }
    //    return test;
    //    //return xlsx.read(dps_cells[0]).toString() + " DPS: " + QString::number(xlsx.cellAt(dps_cells[1])->value().toDouble(), 'f', 0);
    //} else {
    //    return "�򿪼�����xlsxʧ�ܣ�δ�ҵ���DPS��������";
    //}
}
