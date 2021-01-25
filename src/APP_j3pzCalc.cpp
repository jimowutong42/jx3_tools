#include "..\include\APP_j3pzCalc.h"

QString APP_j3pzCalc::on(QString xlsx_path) {
    QDir xlsx_dir(xlsx_path);
    QStringList xlsx_files = xlsx_dir.entryList(QStringList("*.xlsx"), QDir::Files | QDir::Readable);
    switch (xlsx_files.count()) {
    case 1:
        return init(xlsx_files[0]);
    case 0:
        return "找不到计算器Orz\n请将本exe和计算器xlsx放一起哦";
    default:
        return "找到多个xlsx\n暂不支持自动识别哪一个Orz\n请将本exe和计算器xlsx单独放一起哦";
    }
}

QString APP_j3pzCalc::init(QString xlsx_name) {
    clipboard = QGuiApplication::clipboard();
    Application = new QAxObject("KET.Application");  // Kingsoft WPS
    if (!Application->isNull()) {
        ERR_APP = QString("[KET]");
    } else {
        Application = new QAxObject("Excel.Application");  // Microsoft Excel
        if (!Application->isNull()) {
            ERR_APP = QString("[Excel]");
        } else {
            return ERR(0);
        }
    }
    // TODO: 用户手动结束Application进程
    if (!Application->setProperty("DisplayAlerts", false)) return ERR(1);
    Workbooks = Application->querySubObject("Workbooks");
    if (Workbooks->isNull()) return ERR(2);
    auto Workbooks_Count = Workbooks->property("Count");
    if (!Workbooks_Count.isValid()) return ERR(3);
    if (Workbooks_Count.toInt() != 0) return ERR(4) + Workbooks_Count.toString();
    QFileInfo xlsx_file(xlsx_name);
    Workbook = Workbooks->querySubObject("Open (QVariant)", QVariant(xlsx_file.absolutePath() + "/" + xlsx_name));
    if (Workbook->isNull()) return ERR(5);
    Workbooks_Count = Workbooks->property("Count");
    if (!Workbooks_Count.isValid()) return ERR(6);
    if (Workbooks_Count.toInt() != 1) return ERR(7) + Workbooks_Count.toString();
    Worksheets = Workbook->querySubObject("Worksheets");
    if (Worksheets->isNull()) return ERR(8);
    auto Worksheets_Count = Worksheets->property("Count");
    if (!Worksheets_Count.isValid()) return ERR(9);
    if (Worksheets_Count.toInt() != 9) return ERR(10) + Worksheets_Count.toString();
    Worksheet = Worksheets->querySubObject("Item (QVariant)", QVariant(sheet_name[kf]));
    if (Worksheet->isNull()) return ERR(11);
    return "";
}

QString APP_j3pzCalc::off() {
    if (clipboard != NULL) {
        clipboard->destroyed();
    }
    //auto WPS_Workbook_Close = WPS_Workbook->dynamicCall("Close (QVariant)", QVariant(false));
    //auto WPS_Workbooks_Close = WPS_Workbooks->querySubObject("Close");
    //if (WPS_Workbooks_Close->isNull()) return "KET.Application: Workbooks.Close ERROR!";
    //auto WPS_Application_Quit = WPS_Application->dynamicCall("Quit(void)");
    //if (WPS_Application_Quit.isValid()) return "KET.Application: Application.Quit ERROR!";
    if (Application != NULL) {
        Application->dynamicCall("Quit(void)");  // TODO: 真的Quit了吗？
        Application->destroyed();
        return "已关闭";
    }
    return "";
}

QString APP_j3pzCalc::main() {
    clipboard = QGuiApplication::clipboard();
    QString text = clipboard->text();
    if (!text.isEmpty()) {
        return main_xlsx(main_json(text));
    } else {
        return "";
    }
}

QVector<QVariant> APP_j3pzCalc::main_json(QString json_string) {
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) return { ERR(12) + err.errorString() };
    QVariantMap json_map = json_doc.toVariant().toMap();
    QVector<QVariant> p;
    for (auto i : keys[kf]) {
        QString k = all_keys[i];
        if (!json_map.contains(k)) {
            return { ERR(13) + k };
        } else {
            QVariant v = json_map.value(k);
            if (v.type() != QVariant::Type::String) {
                return { ERR(14) + k + "." + QString::number(v.type()) };
            }
            p.append(QVariant(v.toString().right(1) == "%" ? v.toString().split('%')[0].toDouble() / 100 : v.toDouble()));
        }
    }
    return p;
}

QString APP_j3pzCalc::main_xlsx(QVector<QVariant> p) {
    if (p.count() != keys[kf].count()) return p[0].toString();
    QString ret;
    for (auto cell : cells[kf]) {
        auto Range = Worksheet->querySubObject("Range (QVariant)", QVariant(cell));
        if (Range->isNull()) return ERR(15) + cell;
        if (!Range->setProperty("Value2", p[cells[kf].indexOf(cell)])) {
            return ERR(16) + cell + "." + p[cells[kf].indexOf(cell)].toString();
        } else {
            auto Range_Value2 = Range->property("Value2");
            if (!Range_Value2.isValid()) return ERR(17) + cell;
            if (Range_Value2.toDouble() != p[cells[kf].indexOf(cell)].toDouble())
                return all_keys[keys[kf][cells[kf].indexOf(cell)]] + ":" + Range_Value2.toString() + "!=" + p[cells[kf].indexOf(cell)].toString();
        }
    }
    //auto WPS_Worksheet_Calculate = WPS_Application->dynamicCall("Calculate ()");
    //if (!WPS_Worksheet_Calculate.isValid()) return "KET.Application: Worksheet.Calculate() ERROR!";
    auto DPS_Range0 = Worksheet->querySubObject("Range (QVariant)", QVariant(dps_cells[kf][0]));
    if (DPS_Range0->isNull()) return ERR(15) + dps_cells[kf][0];
    auto DPS_Range0_Value2 = DPS_Range0->property("Value2");
    if (!DPS_Range0_Value2.isValid()) return ERR(17) + dps_cells[kf][0];
    auto DPS_Range1 = Worksheet->querySubObject("Range (QVariant)", QVariant(dps_cells[kf][1]));
    if (DPS_Range1->isNull()) return ERR(15) + dps_cells[kf][1];
    auto DPS_Range1_Value2 = DPS_Range1->property("Value2");
    if(!DPS_Range1_Value2.isValid()) return ERR(17) + dps_cells[kf][1];
    return DPS_Range0_Value2.toString() + " DPS: " + QString::number(DPS_Range1_Value2.toDouble(), 'f', 0);

    // TODO: QXlsx方法
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
