#include "styles.h"

QString UI_Styles::button_main()
{
	return
			"	color: #24292F;"
			"	background-color: " COLOR_BTN_DEFAULT_BACKGROUND ";"
			"	border: 2px solid #D5D8DA;"
			"	border-radius: 6%;"
			"	padding: 8px;";
}

QString UI_Styles::button_default()
{
	QString button =
			QString("QPushButton {")
			+ button_main()
			+ "}\n";
	QString hover =
			"QPushButton:hover {"
			"	background-color: " COLOR_BTN_DEFAULT_BACKGROUND ";"
			"	border-color: " COLOR_BTN_DEFAULT_BORDER ";"
			"}\n";
	QString pressed =
			"QPushButton:pressed {"
			"	background-color: #EEEFF2;"
			"	border-color: #CFD0D3;"
			"}\n";
	QString disabled =
			"QPushButton:disabled {"
			"	color: #959da5;"
			"}\n";

	return button + hover + pressed + disabled;
}

QString UI_Styles::button_primary()
{
	QString button =
			QString("QPushButton {")
			+ button_main() +
			"	color: " COLOR_WHITE ";"
			"	background-color: " COLOR_BTN_PRIMARY_BACKGROUND ";"
			"	border-color: " COLOR_BTN_PRIMARY_BORDER ";"
			"}\n";
	QString hover =
			"QPushButton:hover {"
			"	border-color: " COLOR_DTN_PRIMARY_HOVER_BORDER ";"
			"}\n";
	QString pressed =
			"QPushButton:pressed {"
			"	background-color: " COLOR_BTN_PRIMARY_PRESSED_BACKGROUND ";"
			"	border-color: " COLOR_BTN_PRIMARY_PRESSED_BORDER ";"
			"}\n";
	QString disabled =
			"QPushButton:disabled {"
			"	background-color: " COLOR_BTN_PRIMARY_DISABLED_BACKGROUND ";"
			"	border-color: " COLOR_BTN_PRIMARY_DISABLED_BORDER ";"
			"}\n";

	return button + hover + pressed + disabled;
}

QString UI_Styles::button_danger()
{
	QString button =
			QString("QPushButton {")
			+ button_main() +
			"	color: #D1303B;"
			"}\n";
	QString hover =
			"QPushButton:hover {"
			"	border-color: #EAA7AD;"
			"}\n";
	QString pressed =
			"QPushButton:pressed {"
			"	color: " COLOR_WHITE ";"
			"	background-color: #A40E26;"
			"	border-color: #901125;"
			"}\n";
	QString disabled =
			"QPushButton:disabled {"
			"	color: #E28D94;"
			"}\n";

	return button + hover + pressed + disabled;
}

QString UI_Styles::tool_button()
{
	return
			"QToolButton {"
			"	color: " COLOR_BLACK ";"
			"	background: none;"
			"	border: none;"
			"}\n";
}
