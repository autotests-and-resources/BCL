#ifndef STYLES_H
#define STYLES_H

#include <QString>

#define COLOR_BLACK "#000000"
#define COLOR_WHITE "#FFFFFF"

#define COLOR_MAINWINDOW "#E7E7E9"
#define COLOR_MENU_BAR "#DADADA"
#define COLOR_ACTIVE_TAB "#EEF0F5"

#define COLOR_FIELD "#F6F8FA"

#define COLOR_BTN_DEFAULT_BACKGROUND			"#F6F8FA"
#define COLOR_BTN_DEFAULT_BORDER				"#B4D2F3"
#define COLOR_BTN_DEFAULT_PRESSED_BACKGROUND	"#EEEFF2"
#define COLOR_BTN_DEFAULT_PRESSED_BORDER		"#CFD0D3"

#define COLOR_BTN_PRIMARY_BACKGROUND			"#2DA44E"
#define COLOR_BTN_PRIMARY_BORDER				"#2A9147"
#define COLOR_DTN_PRIMARY_HOVER_BORDER			"#ABDBB9"
#define COLOR_BTN_PRIMARY_PRESSED_BACKGROUND	"#298E46"
#define COLOR_BTN_PRIMARY_PRESSED_BORDER		"#277E41"
#define COLOR_BTN_PRIMARY_DISABLED_BACKGROUND	"#94D3A2"
#define COLOR_BTN_PRIMARY_DISABLED_BORDER		"#82B98F"


/*!
 * @brief Класс, содержащий описания стилей объектов GUI
 */
class UI_Styles
{
protected:
	UI_Styles() {};

public:
/********************* MAIN WINDOW *********************/
	static QString main_window();
	static QString input_dialog();
	static QString menu_bar();

/********************* TAB WIDGET AND TAB BAR *********************/
	static QString tab_bar();
	static QString tab_widget();
	static QString tab_item();

/********************* START PAGE *********************/
	static QString frame_start();
	static QString label_title();
	static QString label_parameter();
	static QString line_edit();
	static QString spin_box();
	static QString combo_box();

private:
	static QString _field_background();
	static QString _field_color();
	static QString _field_border();

public:
	static QString radio_button();
	static QString start_list_widget();

/********************* BUTTONS *********************/
private:
	static QString button_main();

public:
	static QString button_default();
	static QString button_primary();
	static QString button_danger();
	static QString tool_button();

};

#endif // STYLES_H
