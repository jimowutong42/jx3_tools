# jx3_tools
剑网3工具盒（挖个大坑慢慢填）

## License

- 关于Qt的许可证：[Qt 许可证(GPL/LGPL/商业协议)](https://blog.csdn.net/zhouqt/article/details/91975943)
- 本工具为了方便（单文件），使用了静态编译的Qt，应遵循[LGPL协议](https://github.com/jslyxyc/jx3_tools/blob/master/LICENSE)
- 本工具代码全部开源，禁止将本工具用于商业用途，欢迎二次开发，欢迎[反馈](#feedback)

## 功能

- 系统托盘 `剑网3工具盒 by寂寞梧桐` 

  > 右键打开菜单，鼠标悬停会有提示

  - 代按计算器 `请把本软件放在计算器xlsx同目录下\n目前仅支持唐门计算器` 

    > 默认关闭，将计算器xlsx文件放在同目录下，选择心法即可。目前仅支持从配装器导出JSON自动计算DPS，配装器上没有的属性和选项需要自己事先填好。
    >
    > [剑网3配装器](https://www.j3pz.com/) [【奉天证道】天罗诡道DPS计算器](https://www.jx3box.com/tool/20255) [【奉天证道】惊羽诀DPS计算器](https://www.jx3box.com/tool/20320) 
    >
    > 目前暂时只能后台调用WPS（Office好像也行）进行xlsx操作，直接解析xlsx文件卡在最后重算公式这一步（有无大佬捞我Orz）。
  >
    > **Warning:** 使用此功能的同时，人为地打开、操作、关闭xlsx有可能会导致程序异常，本工具理论上不会保存xlsx，但不排除xlsx数据丢失的可能。

  - 试炼之地九宫格计算器 `在做了在做了` 
  - 科举助手 `在做了在做了` 
  - 开服监控 `在做了在做了` 
  - 物价查询 `在做了在做了` 
  - 关于 `在做了在做了` 
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
  
- #### [WPS 开放平台](https://open.wps.cn/docs/office) 

- #### [Office VBA 参考](https://docs.microsoft.com/zh-cn/office/vba/api/overview/) 

### VS 2019

- [Qt VS Tools](https://mirrors.tuna.tsinghua.edu.cn/qt/archive/vsaddin/) 
- 具体项目设置参考 `.vcxproj` 与 `.vcxproj.filters` 

## <span id="feedback">联系：</span>

### 剑网3

双线一区  天鹅坪  寂寞梧桐

### QQ

3416815649

1946225331