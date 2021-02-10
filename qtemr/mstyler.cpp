// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mstyler.h"

mStyler::mStyler(QObject *parent) : QObject(parent)
{

}

void mStyler::saveStyle(const QString &styleName, const mStyler::Style &_style)
{
    current_style = styleName;
    QSettings styler(getThemePath(current_style),QSettings::IniFormat);
    styler.beginGroup(_th_window);
    styler.setValue(_th_top_color,_style.window.top_color);
    styler.setValue(_th_bottom_color,_style.window.bottom_color);
    styler.setValue(_th_border_color,_style.window.border_color);
    styler.setValue(_th_border_width,_style.window.border_width);
    styler.setValue(_th_border_radius,_style.window.border_radius);
    styler.endGroup();

    styler.beginGroup(_th_subwindow);
    styler.setValue(_th_top_color,_style.subwindow.top_color);
    styler.setValue(_th_bottom_color,_style.subwindow.bottom_color);
    styler.setValue(_th_border_color,_style.subwindow.border_color);
    styler.setValue(_th_border_width,_style.subwindow.border_width);
    styler.setValue(_th_border_radius,_style.subwindow.border_radius);
    styler.endGroup();

    styler.beginGroup(_th_button);
    styler.setValue(_th_color_normal,_style.button.color_normal);
    styler.setValue(_th_color_hover,_style.button.color_hover);
    styler.setValue(_th_color_focus,_style.button.color_focus);
    styler.setValue(_th_color_disabled,_style.button.color_disabled);
    styler.setValue(_th_color_warning,_style.button.color_warning);
    styler.setValue(_th_color_error,_style.button.color_error);
    styler.setValue(_th_border_color_normal,_style.button.border_color_normal);
    styler.setValue(_th_border_color_hover,_style.button.border_color_hover);
    styler.setValue(_th_border_color_focus,_style.button.border_color_focus);
    styler.setValue(_th_border_color_diabled,_style.button.border_color_disabled);
    styler.setValue(_th_border_width,_style.button.border_width);
    styler.setValue(_th_border_radius,_style.button.border_radius);
    styler.endGroup();

    styler.beginGroup(_th_input);
    styler.setValue(_th_color_normal,_style.input.color_normal);
    styler.setValue(_th_color_hover,_style.input.color_hover);
    styler.setValue(_th_color_focus,_style.input.color_focus);
    styler.setValue(_th_color_disabled,_style.input.color_disabled);
    styler.setValue(_th_color_warning,_style.input.color_warning);
    styler.setValue(_th_color_error,_style.input.color_error);
    styler.setValue(_th_border_color_normal,_style.input.border_color_normal);
    styler.setValue(_th_border_color_hover,_style.input.border_color_hover);
    styler.setValue(_th_border_color_focus,_style.input.border_color_focus);
    styler.setValue(_th_border_color_diabled,_style.input.border_color_disabled);
    styler.setValue(_th_border_width,_style.input.border_width);
    styler.setValue(_th_border_radius,_style.input.border_radius);
    styler.endGroup();

    styler.beginGroup(_th_elementtext);
    styler.setValue(_th_color_normal,_style.elementText.color_normal);
    styler.setValue(_th_color_hover,_style.elementText.color_hover);
    styler.setValue(_th_color_focus,_style.elementText.color_focus);
    styler.setValue(_th_color_disabled,_style.elementText.color_disabled);
    styler.setValue(_th_color_warning,_style.elementText.color_warning);
    styler.setValue(_th_color_error,_style.elementText.color_error);
    styler.endGroup();

    styler.beginGroup(_th_inputtext);
    styler.setValue(_th_color_normal,_style.inputText.color_normal);
    styler.setValue(_th_color_hover,_style.inputText.color_hover);
    styler.setValue(_th_color_focus,_style.inputText.color_focus);
    styler.setValue(_th_color_disabled,_style.inputText.color_disabled);
    styler.setValue(_th_color_warning,_style.inputText.color_warning);
    styler.setValue(_th_color_error,_style.inputText.color_error);
    styler.endGroup();

    styler.beginGroup(_th_list);
    styler.setValue(_th_selected_item_color,_style.list.selected_item_color);
    styler.setValue(_th_selected_item_text_color,_style.list.selected_item_text_color);
    styler.setValue(_th_messagebox_background_color,_style.list.messagebox_background_color);
    styler.setValue(_th_toolbutton_color,_style.list.toolbutton_color_normal);
    styler.setValue(_th_messagebox_text_color,_style.list.messagebox_text_color);
    styler.setValue(_th_enable3D,_style.list.enable3D);
    styler.endGroup();
}

mStyler::Style mStyler::getStyle(const QString& theme)
{
    QSettings styler(getThemePath(theme),QSettings::IniFormat);

    styler.beginGroup(_th_window);
    style.window.top_color = styler.value(_th_top_color).toString();
    style.window.bottom_color = styler.value(_th_bottom_color).toString();
    style.window.border_color = styler.value(_th_border_color).toString();
    style.window.border_width = styler.value(_th_border_width).toInt();
    style.window.border_radius = styler.value(_th_border_radius).toInt();
    styler.endGroup();

    styler.beginGroup(_th_subwindow);
    style.subwindow.top_color = styler.value(_th_top_color).toString();
    style.subwindow.bottom_color = styler.value(_th_bottom_color).toString();
    style.subwindow.border_color = styler.value(_th_border_color).toString();
    style.subwindow.border_width = styler.value(_th_border_width).toInt();
    style.subwindow.border_radius = styler.value(_th_border_radius).toInt();
    styler.endGroup();

    styler.beginGroup(_th_button);
    style.button.color_normal = styler.value(_th_color_normal).toString();
    style.button.color_hover = styler.value(_th_color_hover).toString();
    style.button.color_focus = styler.value(_th_color_focus).toString();
    style.button.color_disabled = styler.value(_th_color_disabled).toString();
    style.button.color_warning = styler.value(_th_color_warning).toString();
    style.button.color_error = styler.value(_th_color_error).toString();
    style.button.border_color_normal = styler.value(_th_border_color_normal).toString();
    style.button.border_color_hover = styler.value(_th_border_color_hover).toString();
    style.button.border_color_focus = styler.value(_th_border_color_focus).toString();
    style.button.border_color_disabled = styler.value(_th_border_color_diabled).toString();
    style.button.border_width = styler.value(_th_border_width).toInt();
    style.button.border_radius = styler.value(_th_border_radius).toInt();
    styler.endGroup();

    styler.beginGroup(_th_input);
    style.input.color_normal = styler.value(_th_color_normal).toString();
    style.input.color_hover = styler.value(_th_color_hover).toString();
    style.input.color_focus = styler.value(_th_color_focus).toString();
    style.input.color_disabled = styler.value(_th_color_disabled).toString();
    style.input.color_warning = styler.value(_th_color_warning).toString();
    style.input.color_error = styler.value(_th_color_error).toString();
    style.input.border_color_normal = styler.value(_th_border_color_normal).toString();
    style.input.border_color_hover = styler.value(_th_border_color_hover).toString();
    style.input.border_color_focus = styler.value(_th_border_color_focus).toString();
    style.input.border_color_disabled = styler.value(_th_border_color_diabled).toString();
    style.input.border_width = styler.value(_th_border_width).toInt();
    style.input.border_radius = styler.value(_th_border_radius).toInt();
    styler.endGroup();

    styler.beginGroup(_th_elementtext);
    style.elementText.color_normal = styler.value(_th_color_normal).toString();
    style.elementText.color_hover = styler.value(_th_color_hover).toString();
    style.elementText.color_focus = styler.value(_th_color_focus).toString();
    style.elementText.color_disabled = styler.value(_th_color_disabled).toString();
    style.elementText.color_warning = styler.value(_th_color_warning).toString();
    style.elementText.color_error = styler.value(_th_color_error).toString();
    styler.endGroup();

    styler.beginGroup(_th_inputtext);
    style.inputText.color_normal = styler.value(_th_color_normal).toString();
    style.inputText.color_hover = styler.value(_th_color_hover).toString();
    style.inputText.color_focus = styler.value(_th_color_focus).toString();
    style.inputText.color_disabled = styler.value(_th_color_disabled).toString();
    style.inputText.color_warning = styler.value(_th_color_warning).toString();
    style.inputText.color_error = styler.value(_th_color_error).toString();
    styler.endGroup();


    styler.beginGroup(_th_list);
    style.list.selected_item_color = styler.value(_th_selected_item_color).toString();
    style.list.selected_item_text_color = styler.value(_th_selected_item_text_color).toString();
    style.list.messagebox_background_color = styler.value(_th_messagebox_background_color).toString();
    style.list.toolbutton_color_normal = styler.value(_th_toolbutton_color).toString();
    style.list.messagebox_text_color = styler.value(_th_messagebox_text_color).toString();
    style.list.enable3D = styler.value(_th_enable3D).toBool();
    styler.endGroup();
    return style;
}

void mStyler::setStyle(const QString &_style)
{
    current_style = _style;
}


QString mStyler::getCurrentStyle()
{
    return current_style;
}

QString mStyler::getThemePath(QString theme)
{
    foreach(QString t, getPackagedThemes() )
    {
        if(theme == t.remove(QRegExp(".ini$")))
            return QString(":/Themes/%1.ini").arg(theme);
    }
    return QString("%1\\themes\\%2.ini").arg(dataIOhelper::getCurrentFolder()).arg(theme);
}

QStringList mStyler::getPackagedThemes()
{
    QStringList packagedThemes;
    foreach(QString t, QDir(":/Themes/").entryList() )
    {
        if(!t.endsWith(".css"))
        packagedThemes << t.remove(QRegExp(".ini$"));
    }
    return packagedThemes;
}

QStringList mStyler::getNonPackagedThemes()
{
    QStringList nonPackagedThemes;
    foreach(QString t, QDir(QString("%1\\themes\\").arg(dataIOhelper::getCurrentFolder())).entryList() )
    {
        if(t.endsWith(".ini"))
            nonPackagedThemes << t.remove(QRegExp(".ini$"));
    }
    return nonPackagedThemes;
}

mStyler::Style &mStyler::getLoadedStyle()
{
    return style;
}

QString mStyler::getStyleSheet()
{
    Style mStyle = getStyle(current_style);
    QString stylebase = dataIOhelper::getTextFileContents(":/Themes/styleSheet.css");
    QVector<QPair<QString,QString> > theme;

    theme <<   qMakePair(QString("window_top_color"),mStyle.window.top_color) <<
               qMakePair(QString("window_bottom_color"),mStyle.window.bottom_color) <<
               qMakePair(QString("window_border_color"),mStyle.window.border_color) <<
               qMakePair(QString("window_border_width"),QString::number(mStyle.window.border_width)) <<
               qMakePair(QString("window_border_radius"),QString::number(mStyle.window.border_radius) ) <<
               qMakePair(QString("subWindow_top_color"),mStyle.subwindow.top_color) <<
               qMakePair(QString("subWindow_bottom_color"),mStyle.subwindow.bottom_color) <<
               qMakePair(QString("subWindow_border_color"),mStyle.subwindow.border_color) <<
               qMakePair(QString("subWindow_border_width"),QString::number(mStyle.subwindow.border_width)) <<
               qMakePair(QString("subWindow_border_radius"),QString::number(mStyle.subwindow.border_radius)) <<
               qMakePair(QString("button_color_normal"),mStyle.button.color_normal ) <<
               qMakePair(QString("button_color_hover"),mStyle.button.color_hover) <<
               qMakePair(QString("button_color_focus"),mStyle.button.color_focus) <<
               qMakePair(QString("button_color_disabled"),mStyle.button.color_disabled) <<
               qMakePair(QString("button_color_warning"),mStyle.button.color_warning ) <<
               qMakePair(QString("button_color_error"),mStyle.button.color_error) <<
               qMakePair(QString("button_border_color_normal"),mStyle.button.border_color_normal) <<
               qMakePair(QString("button_border_color_hover"),mStyle.button.border_color_hover) <<
               qMakePair(QString("button_border_color_focus"),mStyle.button.border_color_focus ) <<
               qMakePair(QString("button_border_color_diabled"),mStyle.button.border_color_disabled) <<
               qMakePair(QString("button_border_width"),QString::number(mStyle.button.border_width)) <<
               qMakePair(QString("button_border_radius"),QString::number(mStyle.button.border_radius) ) <<
               qMakePair(QString("input_color_normal"),mStyle.input.color_normal) <<
               qMakePair(QString("input_color_hover"),mStyle.input.color_hover) <<
               qMakePair(QString("input_color_focus"),mStyle.input.color_focus) <<
               qMakePair(QString("input_color_disabled"),mStyle.input.color_disabled) <<
               qMakePair(QString("input_color_warning"),mStyle.input.color_warning) <<
               qMakePair(QString("input_color_error"),mStyle.input.color_error) <<
               qMakePair(QString("input_border_color_normal"),mStyle.input.border_color_normal) <<
               qMakePair(QString("input_border_color_hover"),mStyle.input.border_color_hover) <<
               qMakePair(QString("input_border_color_focus"),mStyle.input.border_color_focus) <<
               qMakePair(QString("input_border_color_diabled"),mStyle.input.border_color_disabled) <<
               qMakePair(QString("input_border_width"),QString::number(mStyle.input.border_width)) <<
               qMakePair(QString("input_border_radius"),QString::number(mStyle.input.border_radius)) <<
               qMakePair(QString("elementText_color_normal"),mStyle.elementText.color_normal) <<
               qMakePair(QString("elementText_color_hover"),mStyle.elementText.color_hover) <<
               qMakePair(QString("elementText_color_focus"),mStyle.elementText.color_focus) <<
               qMakePair(QString("elementText_color_disabled"),mStyle.elementText.color_disabled) <<
               qMakePair(QString("elementText_color_warning"),mStyle.elementText.color_warning) <<
               qMakePair(QString("elementText_color_error"),mStyle.elementText.color_error) <<
               qMakePair(QString("inputText_color_normal"),mStyle.inputText.color_normal) <<
               qMakePair(QString("inputText_color_hover"),mStyle.inputText.color_hover) <<
               qMakePair(QString("inputText_color_focus"),mStyle.inputText.color_focus) <<
               qMakePair(QString("inputText_color_disabled"),mStyle.inputText.color_disabled) <<
               qMakePair(QString("inputText_color_warning"),mStyle.inputText.color_warning) <<
               qMakePair(QString("inputText_color_error"),mStyle.inputText.color_error ) <<
               qMakePair(QString("list_selected_item_color"),mStyle.list.selected_item_color ) <<
               qMakePair(QString("messagebox_background_color"),mStyle.list.messagebox_background_color) <<
               qMakePair(QString("messagebox_text_color"),mStyle.list.messagebox_text_color) <<
               qMakePair(QString("toolbutton_color_normal"),mStyle.list.toolbutton_color_normal) <<
               qMakePair(QString("selected_item_text_color"),mStyle.list.selected_item_text_color) <<
               qMakePair(QString("background_Flat_3D_hover"),getBackground(mStyle.button.color_hover)) <<
               qMakePair(QString("background_Flat_3D_focus"),getBackground(mStyle.button.color_focus)) <<
               qMakePair(QString("background_Flat_3D_disabled"),getBackground(mStyle.button.color_disabled)) <<
               qMakePair(QString("background_Flat_3D"),getBackground(mStyle.button.color_normal));


    QString ss_content;

    QPair<QString,QString> pair;
    foreach (pair, theme) {
        ss_content = stylebase.replace(pair.first,pair.second);
    }
    //mDebug() << ss_content;
    return ss_content;
}

QString mStyler::getBackgroundGradient(const QString& color)
{
    QColor c(color);
    return QString("qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                   "stop: 0 %1, stop: 0.4 %2,"
                   "stop: 0.5 %3, stop: 1.0 %4)")
            .arg(c.lighter(110).name())
            .arg(c.lighter(105).name())
            .arg(c.darker(105).name())
            .arg(c.darker(110).name()) ;
}

QString mStyler::getBackground(const QString &color)
{
    if(style.list.enable3D)
        return getBackgroundGradient(color);
    else
        return color;
}
