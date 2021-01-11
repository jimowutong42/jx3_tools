#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include "../3rdparty/QtXlsxWriter/src/xlsx/xlsxdocument.h"

namespace APP_j3pzCalc {
    QString APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json);
}
