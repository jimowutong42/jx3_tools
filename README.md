# jx3_tools
剑网3工具盒（挖个大坑慢慢填）

！！！有人知道应该加个啥LICENSE吗！！！

## 功能

- 系统托盘 `剑网3工具盒 by寂寞梧桐`
  - 功能
    - 代按计算器 `请把本软件放在计算器xlsx同目录下\n目前仅支持天罗计算器` [剑网3配装器](https://www.j3pz.com/) [【奉天证道】天罗诡道DPS计算器](https://www.jx3box.com/tool/?pid=20255#/)
  - 设置 `在做了在做了`
  - 退出

## 构建

### Qt, yyds!

源码编译Qt，善用官方文档，善用搜索工具

可参考：[Qt最新版5.15.1在Win10环境静态编译安装和部署的完整过程](https://www.cnblogs.com/yangwenli/p/11419842.html)

分享本人编译命令行：

> `..\..\qt_everywhere_src_5151\configure.bat -static -prefix "D:\qt_5_15_1\win32_msvc2019_static" -confirm-license -opensource -debug-and-release -platform win32-msvc -nomake examples -nomake tests -plugin-sql-sqlite -plugin-sql-odbc -qt-zlib -qt-libpng -qt-libjpeg -opengl desktop -qt-freetype -skip qtwebengine -mp`

### 3rdparty

- #### [QtXlsxWriter](https://github.com/dbzhang800/QtXlsxWriter)

  .xlsx file reader and writer for Qt5
  
  Documentation: http://qtxlsx.debao.me

### VS 2019

- [Qt VS Tools](https://mirrors.tuna.tsinghua.edu.cn/qt/archive/vsaddin/)
- 具体项目设置参考 `.vcxproj` 与 `.vcxproj.filters`

## 联系：
### 剑网3
双线一区  天鹅坪  寂寞梧桐