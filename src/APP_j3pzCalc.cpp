#include "..\include\APP_j3pzCalc.h"

QString APP_j3pzCalc::APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json_string) {
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) return "解析JSON失败：" + err.errorString();
    QVariantMap json_map = json_doc.toVariant().toMap();
    QVector<QVariant> p;
    for (QString k : keys) {
        if (!json_map.contains(k)) {
            return "解析JSON失败：json_map.contains(\"" + k + "\") = false";
        } else {
            QVariant v = json_map.value(k);
            // if (v.type() != QVariant::Type::String || !v.convert(types[i]))  // TODO: 类型转换
            if (v.type() != QVariant::Type::String)
                return "解析JSON失败：" + k + "类型错误 (" + QString::number(v.type()) + ")";
            p.append(v);
        }
    }
    QString ret;
    auto WPS_Application = new QAxObject("KET.Application");
    if (WPS_Application->isNull()) return "找不到WPS：暂时仅支持WPS Orz";
    if (!WPS_Application->setProperty("DisplayAlerts", false)) return "KET.Application: Application.DisplayAlerts ERROR!";
    auto WPS_Workbooks = WPS_Application->querySubObject("Workbooks");
    if (WPS_Workbooks->isNull()) return "KET.Application: Application.Workbooks ERROR!";
    auto WPS_Workbooks_Count = WPS_Workbooks->property("Count");
    if (!WPS_Workbooks_Count.isValid()) return "KET.Application: Workbooks.Count ERROR!";
    if (WPS_Workbooks_Count.toInt() != 0) return "KET.Application: Workbooks.Count(=" + WPS_Workbooks_Count.toString() + ")!=0 ERROR!";
    QFileInfo xlsx_file(xlsx_name);
    if (!xlsx_file.exists()) return "找不到" + xlsx_name;
    auto WPS_Workbook = WPS_Workbooks->querySubObject("Open (QVariant)", QVariant(xlsx_file.absolutePath() + "/" + xlsx_name));
    if (WPS_Workbook->isNull()) return "KET.Application: Workbooks.Open ERROR!";
    WPS_Workbooks_Count = WPS_Workbooks->property("Count");
    if (!WPS_Workbooks_Count.isValid()) return "KET.Application: (After open)Workbooks.Count ERROR!";
    if (WPS_Workbooks_Count.toInt() != 1) return "KET.Application: (After open)Workbooks.Count(=" + WPS_Workbooks_Count.toString() + ")!=1 ERROR!";
    auto WPS_Worksheets = WPS_Workbook->querySubObject("Worksheets");
    if (WPS_Worksheets->isNull()) return "KET.Application: Workbook.Worksheets ERROR!";
    auto WPS_Worksheets_Count = WPS_Worksheets->property("Count");
    if (!WPS_Worksheets_Count.isValid()) return "KET.Application: Worksheets.Count ERROR!";
    if (WPS_Worksheets_Count.toInt() != 9) return "KET.Application: Worksheets.Count(=" + WPS_Worksheets_Count.toString() + ")!=9 ERROR!";
    auto WPS_Worksheet = WPS_Worksheets->querySubObject("Item (QVariant)", QVariant(sheet_name));
    if (WPS_Worksheet->isNull()) return "KET.Application: Worksheets.Item(" + sheet_name + ") ERROR!";
    auto WPS_Worksheet_Name = WPS_Worksheet->property("Name");  // 
    if (!WPS_Worksheet_Name.isValid()) return "KET.Application: Worksheet.Name ERROR!";  // 
    for (auto cell : cells) {
        auto WPS_Range = WPS_Worksheet->querySubObject("Range (QVariant)", QVariant(cell));
        if (WPS_Range->isNull()) return "KET.Application: Worksheet.Range(" + cell + ") ERROR!";
        if (!WPS_Range->setProperty("Value2", p[cells.indexOf(cell)])) {
            return "代按计算器失败：" + cell + ": " + p[cells.indexOf(cell)].toString();
        } else {
            auto WPS_Range_Value2 = WPS_Range->property("Value2");
            if (!WPS_Range_Value2.isValid()) return "KET.Application: Range(\"" + cell + "\").Value2 ERROR!";
            if (WPS_Range_Value2 != p[cells.indexOf(cell)])
                ret += keys[cells.indexOf(cell)] + ":" + WPS_Range_Value2.toString() + "!=" + p[cells.indexOf(cell)].toString();
        }
    }
    auto DPS_Range0 = WPS_Worksheet->querySubObject("Range (QVariant)", QVariant(dps_cells[0]));
    if (DPS_Range0->isNull()) return "KET.Application: Worksheet.Range(" + dps_cells[0] + ") ERROR!";
    auto DPS_Range0_Value2 = DPS_Range0->property("Value2");
    auto DPS_Range1 = WPS_Worksheet->querySubObject("Range (QVariant)", QVariant(dps_cells[1]));
    if (DPS_Range1->isNull()) return "KET.Application: Worksheet.Range(" + dps_cells[1] + ") ERROR!";
    auto DPS_Range1_Value2 = DPS_Range1->property("Value2");
    ret = DPS_Range0_Value2.toString() + " DPS: " + QString::number(DPS_Range1_Value2.toDouble(), 'f', 0);
    //auto WPS_Worksheet_Calculate = WPS_Application->dynamicCall("Calculate ()");
    //if (!WPS_Worksheet_Calculate.isValid()) return "KET.Application: Worksheet.Calculate() ERROR!";
    //auto WPS_Workbook_Close = WPS_Workbook->dynamicCall("Close (QVariant)", QVariant(false));
    //auto WPS_Workbooks_Close = WPS_Workbooks->querySubObject("Close");
    //if (WPS_Workbooks_Close->isNull()) return "KET.Application: Workbooks.Close ERROR!";
    WPS_Application->dynamicCall("Quit(void)");  // TODO: 真的Quit了吗？
    delete WPS_Application;
    //auto WPS_Application_Quit = WPS_Application->dynamicCall("Quit(void)");
    //if (WPS_Application_Quit.isValid()) return "KET.Application: Application.Quit ERROR!";
    return ret;
    // QXlsx方法
    //QXlsx::Document xlsx(xlsx_name);
    //if (xlsx.selectSheet(sheet_name)) {
    //    // TODO: std::for_each lambda
    //    QString test = xlsx.read(cells[0]).toString() + "," + xlsx.cellAt(dps_cells[1])->value().toString() + ",";
    //    //for (auto cell : cells) {
    //    //    if (!xlsx.write(cell, p[cells.indexOf(cell)])) {
    //    //        return "代按计算器失败：" + cell + ": " + p[cells.indexOf(cell)].toString();
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
    //    return "代按计算器失败：未找到【DPS计算器】";
    //}
}
