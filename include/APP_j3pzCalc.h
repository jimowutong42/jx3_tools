#pragma once
#if _MSC_VER >= 1600 //MSVC2015>1899, MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif
#include "../3rdparty/QtXlsxWriter/src/xlsx/xlsxdocument.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QtCore/QStringList>
//#include <QtCore/QMetaType>
#include <ActiveQt/QAxObject>
#include <QtCore/QFileInfo>

namespace APP_j3pzCalc {
    // TODO: class
    static QStringList keys = { "Ԫ��", "��������", "����", "������", "����Ч��", "��˫��", "�Ʒ��ȼ�", "����", "���ٵȼ�" };
    // TODO: ����ת��
    // QMetaType::Type types[] = { QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double,
    //     QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int };
    // TODO: APP_j3pzCalc::setting()
    static QStringList cells = {"H3", "H4", "H5", "H7", "H8", "H9", "H10", "H11", "F10"};
    static QStringList dps_cells = {"V7", "V8"};
    QString APP_j3pzCalc(QString xlsx_name, QString sheet_name, QString json);
}
