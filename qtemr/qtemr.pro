#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T03:16:41
#
#-------------------------------------------------
QT += core gui xml network printsupport sql widgets multimedia concurrent
DEFINES += "MEMLEAK=0"
msvc:QMAKE_CFLAGS_RELEASE += /O2
msvc:QMAKE_CXXFLAGS_RELEASE += /O2

gcc:QMAKE_CFLAGS_RELEASE += -s -O2 -m32 -mtune=generic -fomit-frame-pointer
gcc:QMAKE_CXXFLAGS_RELEASE += -s -O2 -m32 -mtune=generic -fomit-frame-pointer -fno-exceptions
gcc:QMAKE_CXXFLAGS = -std=c++14
gcc:QMAKE_LFLAGS += -static-libgcc -static-libstdc++ --enable-stdcall-fixup -Wl,--enable-auto-import -Wl,--enable-runtime-pseudo-reloc

msvc:LIBS += -L$$PWD/zlib/msvc2017 -lzlib
gcc:LIBS += -L$$PWD/zlib/mingw730 -llibz

win32-g++ {
   QMAKE_CXXFLAGS += -Werror
}
win32-msvc*{
    QMAKE_CXXFLAGS += /WX
    INCLUDEPATH    += "C:/Program Files (x86)/Visual Leak Detector/include/"
    LIBS           += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win32"
}

CONFIG += -static openssl-linked c++14
CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

TARGET = smartClinic3
TEMPLATE = app

SOURCES += main.cpp\
    3rdparty/smtp/smtp.cpp \
    3rdparty/zip/zip.cpp \
    expecteddeliveries.cpp \
    mainwindow.cpp \
    aboutwindow.cpp \
    mcashtableview.cpp \
    netserver.cpp \
    squeeze.cpp \
    settingsclass.cpp \
    emptyprofiles.cpp \
    regapp.cpp \
    patientlist.cpp \
    visitsbox.cpp \
    userpass.cpp \
    listeditor.cpp \
    inveslist.cpp \
    mymessagebox.cpp \
    textedit.cpp \
    drugindex.cpp \
    backup.cpp \
    printdrugs.cpp \
    drugstable.cpp \
    apptrayicon.cpp \
    patienttable.cpp \
    sqlbase.cpp \
    visitslist.cpp \
    sqlcore.cpp \
    sqlextra.cpp \
    mcompleter.cpp \
    mlineedit.cpp \
    datahelper.cpp \
    dataiohelper.cpp \
    investtable.cpp \
    massistant.cpp \
    singleinstance.cpp \
    mcheckbox.cpp \
    addsiblings.cpp \
    msiblings.cpp \
    surgicalnotes.cpp \
    msurgicalnotes.cpp \
    surgicalnoteeditor.cpp \
    email.cpp \
    internet.cpp \
    richtexteditor.cpp \
    colorpicker.cpp \
    colorbutton.cpp \
    printbutton.cpp \
    msortfilterproxymodel.cpp \
    simplecrypt.cpp \
    m_scolorbutton.cpp \
    wm_completerloader.cpp \
    wm_drugmodelloader.cpp \
    wm_invmodelloader.cpp \
    wm_visitlistloader.cpp \
    drugexapnder.cpp \
    mcalendarwidget.cpp \
    excelexport.cpp \
    vitalbox.cpp \
    mpatientfilter.cpp \
    vtypecombobox.cpp \
    mlabelmsg.cpp \
    getinvestigationname.cpp \
    miniupdater.cpp \
    filegrabber.cpp \
    mship.cpp \
    wm_mship.cpp \
    ztableview.cpp \
    xcheckbox.cpp \
    xlineedit.cpp \
    xspinbox.cpp \
    xdatetimeedit.cpp \
    xlistwidget.cpp \
    xcombobox.cpp \
    navarrows.cpp \
    patientnumber.cpp \
    mpushbutton.cpp \
    favouritedrugseditor.cpp \
    favouritedosedelegate.cpp \
    servicemodel.cpp \
    spinboxdelegate.cpp \
    showaltdrugs.cpp \
    wm_visitsaver.cpp \
    wm_add2completer.cpp \
    genericonlinesearch.cpp \
    clickablelabel.cpp \
    conditionsedit.cpp \
    checkablesortfilterproxymodel.cpp \
    conditionswidget.cpp \
    errorlogviewer.cpp \
    mdialog.cpp \
    welcomebanner.cpp \
    mmessagebox.cpp \
    msettings.cpp \
    microupdater.cpp \
    msql.cpp \
    dboptimizer.cpp \
    toast.cpp \
    notifications.cpp \
    dieteditor.cpp \
    w_development.cpp \
    w_perinatal.cpp \
    w_obgyn.cpp \
    psdoublespinbox.cpp \
    switch.cpp \
    printdialogtab.cpp \
    mprintpreviewdialog.cpp \
    psspinbox.cpp \
    vprintbutton.cpp \
    drugsitemmodel.cpp \
    mfontcombobox.cpp \
    mcolorpicker.cpp \
    visitboxswitch.cpp \
    searchwidget.cpp \
    setdosedrugnamewidget.cpp \
    optimizer.cpp \
    mstyler.cpp \
    stylewidget.cpp \
    window_subwindow_widget.cpp \
    button_input_widget.cpp \
    text_style_editor_widget.cpp \
    list_style_widget.cpp \
    styleeditorwidget.cpp \
    themerenamer.cpp \
    drugsline.cpp \
    investmodel.cpp \
    wm_texteditcompleterloader.cpp \
    patientnamelineedit.cpp \
    wm_patientnamescompleterloader.cpp \
    genericlineedit.cpp \
    inviconhelper.cpp \
    wm_investtooltiploader.cpp \
    mrequestviewer.cpp \
    mgraphicsview.cpp \
    windowmanager.cpp \
    mergedlg.cpp

HEADERS  += mainwindow.h \
    3rdparty/smtp/smtp.h \
    3rdparty/zip/zconf.h \
    3rdparty/zip/zipreader.h \
    3rdparty/zip/zipwriter.h \
    3rdparty/zip/zlib.h \
    aboutwindow.h \
    build.h \
    expecteddeliveries.h \
    mcashtableview.h \
    netserver.h \
    pch.h \
    squeeze.h \
    settingsclass.h \
    emptyprofiles.h \
    regapp.h \
    patientlist.h \
    visitsbox.h \
    userpass.h \
    listeditor.h \
    inveslist.h \
    mymessagebox.h \
    textedit.h \
    drugindex.h \
    backup.h \
    printdrugs.h \
    drugstable.h \
    apptrayicon.h \
    patienttable.h \
    sqlbase.h \
    visitslist.h \
    sqlcore.h \
    sqlextra.h \
    mcompleter.h \
    mlineedit.h \
    datahelper.h \
    dataiohelper.h \
    investtable.h \
    massistant.h \
    singleinstance.h \
    globalvariables.h \
    mcheckbox.h \
    addsiblings.h \
    msiblings.h \
    surgicalnotes.h \
    msurgicalnotes.h \
    surgicalnoteeditor.h \
    email.h \
    internet.h \
    richtexteditor.h \
    colorpicker.h \
    colorbutton.h \
    printbutton.h \
    msortfilterproxymodel.h \
    simplecrypt.h \
    m_scolorbutton.h \
    wm_completerloader.h \
    wm_drugmodelloader.h \
    wm_invmodelloader.h \
    wm_visitlistloader.h \
    drugexapnder.h \
    mcalendarwidget.h \
    excelexport.h \
    vitalbox.h \
    mpatientfilter.h \
    vtypecombobox.h \
    mlabelmsg.h \
    getinvestigationname.h \
    miniupdater.h \
    filegrabber.h \
    mship.h \
    wm_mship.h \
    ztableview.h \
    xcheckbox.h \
    xlineedit.h \
    xspinbox.h \
    xdatetimeedit.h \
    xlistwidget.h \
    xcombobox.h \
    navarrows.h \
    patientnumber.h \
    mpushbutton.h \
    favouritedrugseditor.h \
    favouritedosedelegate.h \
    servicemodel.h \
    spinboxdelegate.h \
    showaltdrugs.h \
    wm_visitsaver.h \
    wm_add2completer.h \
    genericonlinesearch.h \
    clickablelabel.h \
    conditionsedit.h \
    checkablesortfilterproxymodel.h \
    conditionswidget.h \
    errorlogviewer.h \
    mdialog.h \
    welcomebanner.h \
    mmessagebox.h \
    msettings.h \
    staticstrings.h \
    mdebug.h \
    microupdater.h \
    msql.h \
    dboptimizer.h \
    toast.h \
    notifications.h \
    dieteditor.h \
    w_development.h \
    w_perinatal.h \
    w_obgyn.h \
    psdoublespinbox.h \
    switch.h \
    printdialogtab.h \
    mprintpreviewdialog.h \
    psspinbox.h \
    vprintbutton.h \
    drugsitemmodel.h \
    mfontcombobox.h \
    mcolorpicker.h \
    visitboxswitch.h \
    searchwidget.h \
    setdosedrugnamewidget.h \
    optimizer.h \
    mstyler.h \
    stylewidget.h \
    window_subwindow_widget.h \
    button_input_widget.h \
    text_style_editor_widget.h \
    list_style_widget.h \
    styleeditorwidget.h \
    themerenamer.h \
    drugsline.h \
    investmodel.h \
    wm_texteditcompleterloader.h \
    patientnamelineedit.h \
    wm_patientnamescompleterloader.h \
    genericlineedit.h \
    inviconhelper.h \
    wm_investtooltiploader.h \
    mrequestviewer.h \
    mgraphicsview.h \
    windowmanager.h \
    mergedlg.h

FORMS    += mainwindow.ui \
    aboutwindow.ui \
    expecteddeliveries.ui \
    settingsclass.ui \
    emptyprofiles.ui \
    patientlist.ui \
    visitsbox.ui \
    userpass.ui \
    listeditor.ui \
    inveslist.ui \
    drugindex.ui \
    backup.ui \
    printdrugs.ui \
    massistant.ui \
    addsiblings.ui \
    surgicalnotes.ui \
    surgicalnoteeditor.ui \
    richtexteditor.ui \
    colorpicker.ui \
    drugexapnder.ui \
    getinvestigationname.ui \
    miniupdater.ui \
    favouritedrugseditor.ui \
    showaltdrugs.ui \
    genericonlinesearch.ui \
    conditionsedit.ui \
    errorlogviewer.ui \
    welcomebanner.ui \
    dboptimizer.ui \
    notifications.ui \
    dieteditor.ui \
    w_development.ui \
    w_perinatal.ui \
    w_obgyn.ui \
    searchwidget.ui \
    stylewidget.ui \
    window_subwindow_widget.ui \
    button_input_widget.ui \
    text_style_editor_widget.ui \
    list_style_widget.ui \
    themerenamer.ui \
    mrequestviewer.ui \
    mergedlg.ui

win32:RC_FILE = MyApplication.rc

OTHER_FILES += \
    MyApplication.rc \
    Theme1.css \
    TODO.txt


RESOURCES += \
    resources.qrc

DISTFILES += \
    Graphics/newAppIcon.ico \
    README.md \
    BLUEPRINT.txt \
    Graphics/AppIcon.ico
