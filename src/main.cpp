#include "..\include\MainAPP.h"   
#include <QtWidgets/QApplication>
//#include <QtCore/QTextCodec>

int main(int argc, char* argv[]) {
    ////���ó����Ĭ���ַ�����
    //QTextCodec* textcodec = QTextCodec::codecForName("UTF-8");
    //if (textcodec) {
    //    QTextCodec::setCodecForLocale(textcodec);
    //}
    // TODO �࿪���
    QApplication QApp(argc, argv);
    MainAPP MainAPP;
    MainAPP.show();
    return QApp.exec();
}
