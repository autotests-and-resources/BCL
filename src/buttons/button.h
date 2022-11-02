#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include "styles.h"

enum BUTTON_TYPE
{
	BTN_DEFAULT,
	BTN_PRIMARY,
	BTN_DANGER
};

/*!
 * @brief Класс для создания кнопок приложения
 */
class UI_Button : public QPushButton
{
public:
	explicit UI_Button(QWidget *parent = nullptr, BUTTON_TYPE btn_type = BTN_DEFAULT,
					   QString text = "", QString obj_name = "")
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
};

#endif // BUTTON_H
