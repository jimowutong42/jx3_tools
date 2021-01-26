#include "..\include\MainAPP.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
//#include <QtCore/QTextCodec>
#include <Windows.h>
#include <Tlhelp32.h>

bool already_running(void) {
    int count = 0;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE process_snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (process_snapshot_handle == INVALID_HANDLE_VALUE) {
        exit(-1);
    }
    BOOL is_exist = ::Process32First(process_snapshot_handle, &pe32);
    while (is_exist) {
        if (wcsicmp((wchar_t*)L"jx3_tools.exe", pe32.szExeFile) == 0) {
            count++;
        }
        is_exist = Process32Next(process_snapshot_handle, &pe32);
    }
    if (count > 1) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    // 设置程序的默认字符编码
    //QTextCodec* textcodec = QTextCodec::codecForName("UTF-8");
    //if (textcodec) {
    //    QTextCodec::setCodecForLocale(textcodec);
    //}
    // 检测进程是否已在运行
    // TODO: 更改文件名就失效了，能否识别原始文件名
    QApplication QApp(argc, argv);
    if (already_running()) {
        QMessageBox::warning(NULL, "警告", "剑网3工具盒已在运行中！");
        return -1;
    }
    MainAPP MainAPP;
    MainAPP.show();
    return QApp.exec();
}
