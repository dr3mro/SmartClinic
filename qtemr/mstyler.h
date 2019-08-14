#ifndef MSTYLER_H
#define MSTYLER_H

#include <QObject>
#include <QSettings>
#include "staticstrings.h"
#include "dataiohelper.h"
#include "mdebug.h"
class mStyler : public QObject
{
    Q_OBJECT
public:

    struct Window
    {
        QString top_color;
        QString bottom_color;
        QString border_color;
        int border_width;
        int border_radius;
        bool operator ==(const Window& window) const
        {
            return std::tie
                    (
                        top_color,
                        bottom_color,
                        border_color,
                        border_width,
                        border_radius
                        )==std::tie
                    (
                        window.top_color,
                        window.bottom_color,
                        window.border_color,
                        window.border_width,
                        window.border_radius
                        );
        }
    };
    struct Element
    {
        QString color_normal;
        QString color_hover;
        QString color_focus;
        QString color_disabled;
        QString color_warning;
        QString color_error;
        QString border_color_normal;
        QString border_color_hover;
        QString border_color_focus;
        QString border_color_disabled;
        int border_width;
        int border_radius;

        bool operator ==(const Element& elemnt) const
        {
            return std::tie
                    (
                        color_normal,
                        color_hover,
                        color_focus,
                        color_disabled,
                        color_warning,
                        color_error,
                        border_color_normal,
                        border_color_hover,
                        border_color_focus,
                        border_color_disabled,
                        border_width,
                        border_radius
                        )==std::tie
                    (
                        elemnt.color_normal,
                        elemnt.color_hover,
                        elemnt.color_focus,
                        elemnt.color_disabled,
                        elemnt.color_warning,
                        elemnt.color_error,
                        elemnt.border_color_normal,
                        elemnt.border_color_hover,
                        elemnt.border_color_focus,
                        elemnt.border_color_disabled,
                        elemnt.border_width,
                        elemnt.border_radius
                        );
        }
    };
    struct Text
    {
        QString color_normal;
        QString color_hover;
        QString color_focus;
        QString color_disabled;
        QString color_warning;
        QString color_error;

        bool operator ==(const Text& text) const
        {
            return std::tie(
                        color_normal,
                        color_hover,
                        color_focus,
                        color_disabled,
                        color_warning,
                        color_error
                        )==std::tie
                    (
                        text.color_normal,
                        text.color_hover,
                        text.color_focus,
                        text.color_disabled,
                        text.color_warning,
                        text.color_error
                        );
        }
    };
    struct List
    {
        QString selected_item_color;
        QString selected_item_text_color;
        QString toolbutton_color_normal;
        QString messagebox_background_color;
        QString messagebox_text_color;
        bool enable3D;

        bool operator ==(const List& list) const
        {
            return std::tie(
                        selected_item_color,
                        selected_item_text_color,
                        toolbutton_color_normal,
                        messagebox_background_color,
                        messagebox_text_color,
                        enable3D
                        )==std::tie
                    (
                        list.selected_item_color,
                        list.selected_item_text_color,
                        list.toolbutton_color_normal,
                        list.messagebox_background_color,
                        list.messagebox_text_color,
                        list.enable3D
                        );
        }
    };
    struct Style
    {
        Window window;
        Window subwindow;
        Element button;
        Element input;
        Text inputText;
        Text elementText;
        List list;

        bool operator !=(const Style& style) const
        {
            return std::tie
                    (
                        window,
                        subwindow,
                        button,
                        input,
                        inputText,
                        elementText,
                        list )!=std::tie
                    (
                        style.window,
                        style.subwindow,
                        style.button,
                        style.input,
                        style.inputText,
                        style.elementText,
                        style.list
                        );

        }
    };
    explicit mStyler(QObject *parent = nullptr);
    void saveStyle(const QString& styleName,const Style& style);
    Style getStyle(const QString &theme);
    void setStyle(const QString& style);
    QString getCurrentStyle();
    QString getThemePath(QString theme);
    QStringList getPackagedThemes();
    QStringList getNonPackagedThemes();
    Style &getLoadedStyle();
signals:

public slots:
    QString getStyleSheet();

private:
    QString getBackgroundGradient(const QString &color);
    QString getBackground(const QString &color);
    QString current_style;
    Style style;
};

#endif // MSTYLER_H
