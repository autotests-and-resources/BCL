#include "button.h"

UI_Button::UI_Button(QWidget *parent, BUTTON_TYPE btn_type,
					   QString text, QString obj_name)
	: QPushButton(parent)
{
	if (!obj_name.isEmpty())
		setObjectName(obj_name);
	setText(text);
	setFocusPolicy(Qt::FocusPolicy::NoFocus);

	switch (btn_type)
	{
	case BTN_PRIMARY:
		{
			QFont font = this->font();
			font.setBold(true);
			setFont(font);
		}
		setStyleSheet(UI_Styles::button_primary());
		break;
	case BTN_DANGER:
		setStyleSheet(UI_Styles::button_danger());
		break;
	case BTN_DEFAULT:
		setStyleSheet(UI_Styles::button_default());
		break;
	}

	setMinimumSize(QSize(120, 40));
	setMaximumSize(QSize(200, 16777215));
}