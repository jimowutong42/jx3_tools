#include "..\include\MainAPP.h"   
#include <QtWidgets/QApplication>
//#include <QtCore/QTextCodec>

int main(int argc, char* argv[]) {
    ////设置程序的默认字符编码
    //QTextCodec* textcodec = QTextCodec::codecForName("UTF-8");
    //if (textcodec) {
    //    QTextCodec::setCodecForLocale(textcodec);
    //}
    // TODO 多开监测
    QApplication QApp(argc, argv);
    MainAPP MainAPP;
    MainAPP.show();
    return QApp.exec();
}
