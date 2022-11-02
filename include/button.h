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
					   QString text = "", QString obj_name = "");
};

#endif // BUTTON_H
