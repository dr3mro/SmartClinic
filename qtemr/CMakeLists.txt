# Generated from qtemr.pro.

#####################################################################
## smartClinic3 Binary:
#####################################################################
cmake_minimum_required(VERSION 3.19)
project(smartClinic3 VERSION 0.1 LANGUAGES CXX)
set(TARGET_NAME "smartClinic3")
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Printsupport REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WIN32_EXECUTABLE ON)

set(Qt5Core_DIR "C:/Qt/5.15.2/mingw81_32/lib/cmake/Qt5Core")
set(Qt5_DIR "C:/Qt/5.15.2/mingw81_32/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE "C:/Qt/5.15.2/mingw81_32/bin/qmake.exe")

set(SOURCES
    main.cpp
    3rdparty/pagedTextEdit/PageMetrics.cpp
    3rdparty/pagedTextEdit/PageMetrics.h
    3rdparty/pagedTextEdit/PagesTextEdit.cpp
    3rdparty/pagedTextEdit/PagesTextEdit.h
    3rdparty/simple-email/SimpleMail
    3rdparty/simple-email/emailaddress.cpp
    3rdparty/simple-email/emailaddress.h
    3rdparty/simple-email/emailaddress_p.h
    3rdparty/simple-email/mimeattachment.cpp
    3rdparty/simple-email/mimeattachment.h
    3rdparty/simple-email/mimecontentformatter.cpp
    3rdparty/simple-email/mimecontentformatter.h
    3rdparty/simple-email/mimefile.cpp
    3rdparty/simple-email/mimefile.h
    3rdparty/simple-email/mimehtml.cpp
    3rdparty/simple-email/mimehtml.h
    3rdparty/simple-email/mimeinlinefile.cpp
    3rdparty/simple-email/mimeinlinefile.h
    3rdparty/simple-email/mimemessage.cpp
    3rdparty/simple-email/mimemessage.h
    3rdparty/simple-email/mimemessage_p.h
    3rdparty/simple-email/mimemultipart.cpp
    3rdparty/simple-email/mimemultipart.h
    3rdparty/simple-email/mimemultipart_p.h
    3rdparty/simple-email/mimepart.cpp
    3rdparty/simple-email/mimepart.h
    3rdparty/simple-email/mimepart_p.h
    3rdparty/simple-email/mimetext.cpp
    3rdparty/simple-email/mimetext.h
    3rdparty/simple-email/quotedprintable.cpp
    3rdparty/simple-email/quotedprintable.h
    3rdparty/simple-email/sender.cpp
    3rdparty/simple-email/sender.h
    3rdparty/simple-email/sender_p.h
    3rdparty/simple-email/server.cpp
    3rdparty/simple-email/server.h
    3rdparty/simple-email/server_p.h
    3rdparty/simple-email/serverreply.cpp
    3rdparty/simple-email/serverreply.h
    3rdparty/simple-email/serverreply_p.h
    3rdparty/smtp/smtp.cpp
    3rdparty/smtp/smtp.h
    3rdparty/zip/zconf.h
    3rdparty/zip/zip.cpp
    3rdparty/zip/zipreader.h
    3rdparty/zip/zipwriter.h
    3rdparty/zip/zlib.h
    aboutwindow.cpp aboutwindow.h aboutwindow.ui
    addsiblings.cpp addsiblings.h addsiblings.ui
    apptrayicon.cpp apptrayicon.h
    backup.cpp backup.h backup.ui
    build.h
    button_input_widget.cpp button_input_widget.h button_input_widget.ui
    checkablesortfilterproxymodel.cpp checkablesortfilterproxymodel.h
    clickablelabel.cpp clickablelabel.h
    colorbutton.cpp colorbutton.h
    colorpicker.cpp colorpicker.h colorpicker.ui
    conditionsedit.cpp conditionsedit.h conditionsedit.ui
    conditionswidget.cpp conditionswidget.h
    datahelper.cpp datahelper.h
    dataiohelper.cpp dataiohelper.h
    dboptimizer.cpp dboptimizer.h dboptimizer.ui
    dieteditor.cpp dieteditor.h dieteditor.ui
    drugexapnder.cpp drugexapnder.h drugexapnder.ui
    drugindex.cpp drugindex.h drugindex.ui
    drugsitemmodel.cpp drugsitemmodel.h
    drugsline.cpp drugsline.h
    drugstable.cpp drugstable.h
    email.cpp email.h
    emptyprofiles.cpp emptyprofiles.h emptyprofiles.ui
    errorlogviewer.cpp errorlogviewer.h errorlogviewer.ui
    excelexport.cpp excelexport.h
    expandeasyeditor.cpp expandeasyeditor.h expandeasyeditor.ui
    expecteddeliveries.cpp expecteddeliveries.h expecteddeliveries.ui
    favouritedosedelegate.cpp favouritedosedelegate.h
    favouritedrugseditor.cpp favouritedrugseditor.h favouritedrugseditor.ui
    filegrabber.cpp filegrabber.h
    genericlineedit.cpp genericlineedit.h
    genericonlinesearch.cpp genericonlinesearch.h genericonlinesearch.ui
    getinvestigationname.cpp getinvestigationname.h getinvestigationname.ui
    globalvariables.h
    internet.cpp internet.h
    inveslist.cpp inveslist.h inveslist.ui
    investmodel.cpp investmodel.h
    investtable.cpp investtable.h
    inviconhelper.cpp inviconhelper.h
    list_style_widget.cpp list_style_widget.h list_style_widget.ui
    listeditor.cpp listeditor.h listeditor.ui
    m_ClickableLabel.cpp m_ClickableLabel.h
    m_scolorbutton.cpp m_scolorbutton.h
    mainwindow.cpp mainwindow.h mainwindow.ui
    massistant.cpp massistant.h massistant.ui
    mcalendarwidget.cpp mcalendarwidget.h
    mcashtableview.cpp mcashtableview.h
    mcheckbox.cpp mcheckbox.h
    mcolorpicker.cpp mcolorpicker.h
    mcompleter.cpp mcompleter.h
    mdebug.h
    mdialog.cpp mdialog.h
    mergedlg.cpp mergedlg.h mergedlg.ui
    mfontcombobox.cpp mfontcombobox.h
    mgraphicsview.cpp mgraphicsview.h
    microupdater.cpp microupdater.h
    miniupdater.cpp miniupdater.h miniupdater.ui
    mlabelmsg.cpp mlabelmsg.h
    mlineedit.cpp mlineedit.h
    mmessagebox.cpp mmessagebox.h
    mpatientfilter.cpp mpatientfilter.h
    mprintpreviewdialog.cpp mprintpreviewdialog.h
    mpushbutton.cpp mpushbutton.h
    mrequestviewer.cpp mrequestviewer.h mrequestviewer.ui
    msettings.cpp msettings.h
    mship.cpp mship.h
    msiblings.cpp msiblings.h
    msortfilterproxymodel.cpp msortfilterproxymodel.h
    msql.cpp msql.h
    mstyler.cpp mstyler.h
    msurgicalnotes.cpp msurgicalnotes.h
    mymessagebox.cpp mymessagebox.h
    navarrows.cpp navarrows.h
    netserver.cpp netserver.h
    notifications.cpp notifications.h notifications.ui
    optimizer.cpp optimizer.h
    patientlist.cpp patientlist.h patientlist.ui
    patientnamelineedit.cpp patientnamelineedit.h
    patientnumber.cpp patientnumber.h
    patienttable.cpp patienttable.h
    pch.h
    printbutton.cpp printbutton.h
    printdrugs.cpp printdrugs.h printdrugs.ui
    psspinbox.cpp psspinbox.h
    regapp.cpp regapp.h
    remoteassist.cpp remoteassist.h remoteassist.ui
    richtexteditor.cpp richtexteditor.h richtexteditor.ui
    roshetta.cpp roshetta.h
    searchwidget.cpp searchwidget.h searchwidget.ui
    servicemodel.cpp servicemodel.h
    setdosedrugnamewidget.cpp setdosedrugnamewidget.h
    settingsclass.cpp settingsclass.h settingsclass.ui
    showaltdrugs.cpp showaltdrugs.h showaltdrugs.ui
    simplecrypt.cpp simplecrypt.h
    singleinstance.cpp singleinstance.h
    spinboxdelegate.cpp spinboxdelegate.h
    sqlbase.cpp sqlbase.h
    sqlcore.cpp sqlcore.h
    sqlextra.cpp sqlextra.h
    squeeze.cpp squeeze.h
    staticstrings.h
    styleeditorwidget.cpp styleeditorwidget.h
    stylewidget.cpp stylewidget.h stylewidget.ui
    surgicalnoteeditor.cpp surgicalnoteeditor.h surgicalnoteeditor.ui
    surgicalnotes.cpp surgicalnotes.h surgicalnotes.ui
    switch.cpp switch.h
    text_style_editor_widget.cpp text_style_editor_widget.h text_style_editor_widget.ui
    textedit.cpp textedit.h
    themerenamer.cpp themerenamer.h themerenamer.ui
    toast.cpp toast.h
    userpass.cpp userpass.h userpass.ui
    visitboxswitch.cpp visitboxswitch.h
    visitsbox.cpp visitsbox.h visitsbox.ui
    visitslist.cpp visitslist.h
    vitalbox.cpp vitalbox.h
    vprintbutton.cpp vprintbutton.h
    vtypecombobox.cpp vtypecombobox.h
    w_development.cpp w_development.h w_development.ui
    w_obgyn.cpp w_obgyn.h w_obgyn.ui
    w_perinatal.cpp w_perinatal.h w_perinatal.ui
    welcomebanner.cpp welcomebanner.h welcomebanner.ui
    window_subwindow_widget.cpp window_subwindow_widget.h window_subwindow_widget.ui
    windowmanager.cpp windowmanager.h
    wm_add2completer.cpp wm_add2completer.h
    wm_completerloader.cpp wm_completerloader.h
    wm_drugmodelloader.cpp wm_drugmodelloader.h
    wm_investtooltiploader.cpp wm_investtooltiploader.h
    wm_invmodelloader.cpp wm_invmodelloader.h
    wm_mship.cpp wm_mship.h
    wm_patientnamescompleterloader.cpp wm_patientnamescompleterloader.h
    wm_texteditcompleterloader.cpp wm_texteditcompleterloader.h
    wm_visitlistloader.cpp wm_visitlistloader.h
    wm_visitsaver.cpp wm_visitsaver.h
    xcheckbox.cpp xcheckbox.h
    xcombobox.cpp xcombobox.h
    xdatetimeedit.cpp xdatetimeedit.h
    xlineedit.cpp xlineedit.h
    xlistwidget.cpp xlistwidget.h
    xspinbox.cpp xspinbox.h
    ztableview.cpp ztableview.h
    3rdparty/pagedTextEdit
    )

# Resources:
qt5_add_resources(SOURCES resources.qrc)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::Sql Qt5::Concurrent Qt5::Xml Qt5::PrintSupport)
# Keys ignored in scope 1:.:.:qtemr.pro:<TRUE>:
# DISTFILES = "Graphics/newAppIcon.ico" "README.md" "BLUEPRINT.txt" "Graphics/AppIcon.ico" "ionicons/whatsapp.png"
# OTHER_FILES = "MyApplication.rc" "Theme1.css" "TODO.txt"
# TEMPLATE = "app"

## Scopes:
#####################################################################

#qt5_extend_target(smartClinic3 CONDITION MSVC
#    PUBLIC_LIBRARIES
#    # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/zlib/msvc2017
#    WrapZLIB::WrapZLIB
#    )

# Keys ignored in scope 2:.:.:qtemr.pro:MSVC:
# QMAKE_CFLAGS_RELEASE = "/O2"

#qt_internal_extend_target(smartClinic3 CONDITION GCC
#    PUBLIC_LIBRARIES
#    # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/zlib/mingw730
#    libz
#    COMPILE_OPTIONS
#    -std=c++14
#    LINK_OPTIONS
#    "-static-libgcc"
#    "-static-libstdc++"
#    "--enable-stdcall-fixup"
#    "-Wl,--enable-auto-import"
#    "-Wl,--enable-runtime-pseudo-reloc"
#    )

# Keys ignored in scope 4:.:.:qtemr.pro:GCC:
# QMAKE_CFLAGS_RELEASE = "-s" "-O2" "-m32" "-mtune=generic" "-fomit-frame-pointer"

#qt_internal_extend_target(smartClinic3 CONDITION win32-msvc_x_
#    INCLUDE_DIRECTORIES
#        C:/Program Files (x86)/Visual Leak Detector/include
#    PUBLIC_LIBRARIES
#        # Remove: L"C:/Program
#        (
#        )
#        /Visual
#        Detector/lib/Win32"
#        Files
#        Leak
#        x86
#)

# Keys ignored in scope 11:.:.:qtemr.pro:WIN32:
# RC_FILE = "MyApplication.rc"
