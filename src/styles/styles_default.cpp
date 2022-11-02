#include "styles.h"

QString UI_Styles::main_window()
{
	return
			"QMainWindow {"
			"	background-color: " COLOR_MAINWINDOW ";"
			"	color: " COLOR_BLACK ";"
			"}\n";
}

QString UI_Styles::input_dialog()
{
	return
			"QInputDialog {"
			"	background-color: " COLOR_MAINWINDOW ";"
			"	color: " COLOR_BLACK ";"
			"}\n"
			"QComboBox {"
			"  color: " COLOR_BLACK ";"
			"}"
			"QComboBox:editable {"
			"  color: " "#ff00ff" ";"
			"}"
			"QLineEdit {"
			"  color: " "#13579a" ";"
			"}"
			"QComboBox:on {"
			"  color: " COLOR_WHITE ";"
			"  background: #777777;"
			"}";
}

QString UI_Styles::menu_bar()
{
	return
			"QMenuBar {"
			"	background-color: " COLOR_MENU_BAR ";"
			"}\n";
}

/********************* TAB WIDGET AND TAB BAR *********************/
QString UI_Styles::tab_bar()
{
	return
			"QTabBar::tab {"
			"	color: " COLOR_BLACK ";"
			"}\n";
}

QString UI_Styles::tab_widget()
{
	return
			"QWidget {"
			"	background-color: " COLOR_ACTIVE_TAB ";"
			"	border: none;"
			"}\n";
}

QString UI_Styles::tab_item()
{
	return
			"QWidget {"
			"	background-color: " COLOR_ACTIVE_TAB ";"
			"	border: none;"
			"}\n";
}

/********************* START PAGE *********************/
QString UI_Styles::frame_start()
{
	return
			"QFrame {"
			"	background-color: " COLOR_ACTIVE_TAB ";"
			"	border: 1px solid rgb(0, 0, 0);"
			"}\n";
}

QString UI_Styles::label_title()
{
	return
			"QLabel {"
			"	color: " COLOR_BLACK ";"
			"	font-size: 26px;"
			"	font-weight: bold;"
			"}\n";
};

QString UI_Styles::label_parameter()
{
	return
			"QLabel {"
			"  color: " COLOR_BLACK ";"
			"  font-size: 14px;"
			"}\n";
};

QString UI_Styles::line_edit()
{
	return
			"QLineEdit {"
			+ _field_background()
			+ _field_border()
			+ _field_color()
			+ "}\n";
}

QString UI_Styles::spin_box()
{
	return
			"QSpinBox {"
			+ _field_background()
			+ _field_border()
			+ _field_color()
			+ "}\n";
}

QString UI_Styles::combo_box()
{
	return
			"QComboBox {"
			+ _field_background()
			+ _field_border()
			+ _field_color()
			+ "}\n";
}

QString UI_Styles::_field_background() {
	return "  background: " COLOR_FIELD ";";
}

QString UI_Styles::_field_color() {
	return "  color: " COLOR_BLACK ";";
}

QString UI_Styles::_field_border() {
	return "  border: 1px solid rgba(27, 31, 36, 0.15);"
		   "  border-radius: 6px";
}

QString UI_Styles::radio_button()
{
	return
			"QRadioButton {"
			"	color: " COLOR_BLACK ";"
			"}\n"
//			"QRadioButton::indicator {"
//			"	"
//			"}\n"
//			"QRadioButton::indicator:checked {"
//			"	border: 2px solid red;"
//			"}\n"
//			"QRadioButton::indicator:unchecked {"
//			"	background-color: yellow;"
//			"}\n";
			;
}

QString UI_Styles::start_list_widget()
{
	return
			"QListWidget {"
			"	color: " COLOR_BLACK ";"
			"	background-color: " COLOR_FIELD ";"
			"}\n"
			"QListWidget::item:hover {"
			"	background-color: #EEEFF2;"
			"}\n";
}
