#ifndef FIELDS_H
#define FIELDS_H

#include "fields_describe.h"
#include "styles.h"
#include "button.h"
#include "coord.h"
#include "transform_coords.h"
#include "CoordDelegate.h"

#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QScrollArea>
#include <QDebug>
#include <QStringList>
/*!
 * @brief Класс для создания поля ввода параметров (по умолчанию)
 */
class UI_Field : public QWidget
{
	Q_OBJECT
public:
	explicit UI_Field(DescribeOneField field, QWidget *parent = nullptr);
	virtual ~UI_Field() {};

	QString key();
	virtual void clearField() {};
	virtual void initInStorage() {};

protected:
	//! @todo add rules for forbidden symbols for children fields
	QWidget *createContent();
	QLabel *defaultLabel();

	QLineEdit *create_lineEdit(QWidget *parent = nullptr);
	QTableWidget *create_table();
	QComboBox *create_comboBox();
	QSpinBox *create_spinBox();

	bool isUnlockedChangedSignal() {
		return is_unlocked_changed_signal;
	}
	void lockChangedSignal() {
		is_unlocked_changed_signal = false;
	}
	void unlockChangedSignal() {
		is_unlocked_changed_signal = true;
	}

	bool output() {
		return _field.output;
	}

protected:
	DescribeOneField _field;
	QLabel *label;
	QWidget *content;
	QFormLayout *form_layout;

	bool is_unlocked_changed_signal;
};


/*!
 * @brief Класс для создания поля ввода целочисленных параметров
 */
class UI_Field_Int : public UI_Field
{
	Q_OBJECT
public:
	explicit UI_Field_Int(DescribeOneField field, QWidget *parent = nullptr);
	~UI_Field_Int() {};

	void initInStorage()
	{
		emit changedValue(key(), spin_box->value(), output());
		UI_Field::initInStorage();
	};

signals:
	void changedValue(QString key, int value, bool output);

public slots:
	void updateValue(int value);
	void updateField(int value);
	void clearField();

private:
	QWidget *createContent();

	QSpinBox *spin_box;
};


/*!
 * @brief Класс для создания поля ввода логических параметров
 */
class UI_Field_Bool : public UI_Field
{
	Q_OBJECT
public:
	explicit UI_Field_Bool(DescribeOneField field, QWidget *parent = nullptr);
	~UI_Field_Bool() {};

	void initInStorage()
	{
		bool value = (combo_box->currentText() == "true");
		emit changedValue(key(), value, output());
		UI_Field::initInStorage();
	};

signals:
	void changedValue(QString key, bool value, bool output);

public slots:
	void updateValue(QString text);
	void updateField(bool value);
	void clearField();

private:
	QWidget *createContent();

	QComboBox *combo_box;
};


/*!
 * @brief Класс для создания поля ввода вещественных чисел
 */
class UI_Field_Double : public UI_Field
{
	Q_OBJECT
public:
	explicit UI_Field_Double(DescribeOneField field, QWidget *parent = nullptr);
	~UI_Field_Double() {};

	void initInStorage()
	{
		emit changedValue(key(), spin_box->value(), output());
		UI_Field::initInStorage();
	};

signals:
	void changedValue(QString key, double value, bool output);

public slots:
	void updateValue(double value);
	void updateField(double value);
	void clearField();

private:
	QWidget *createContent();

	QSpinBox *spin_box;
};


/*!
 * @brief Класс для создания поля ввода строковых параметров
 */
class UI_Field_String : public UI_Field
{
	Q_OBJECT
public:
	explicit UI_Field_String(DescribeOneField field, QWidget *parent = nullptr);
	~UI_Field_String() {};

	void initInStorage()
	{
		emit changedValue(key(), line_edit->text(), output());
		UI_Field::initInStorage();
	};

signals:
	void changedValue(QString key, QString value, bool output);

public slots:
	void updateValue(QString value);
	void updateField(QString value);
	void clearField();

private:
	QWidget *createContent();

	QLineEdit *line_edit;
};


/*!
 * @brief Класс для создания поля ввода пути к файлу
 */
class UI_Field_Path : public UI_Field
{
	Q_OBJECT
public:
	explicit UI_Field_Path(DescribeOneField field, QWidget *parent = nullptr);
	~UI_Field_Path() {};

	void initInStorage()
	{
		emit changedValue(key(), line_edit->text(), output());
		UI_Field::initInStorage();
	};

signals:
	void pathToFile(QString path);
	void changedValue(QString key, QString value, bool output);

public slots:
	void fileDialog();
	void updateValue(QString value);
	void updateField(QString value);
	void clearField();

private:
	QWidget *createContent();

	QLineEdit *line_edit;
};


/*!
 * @brief Класс для создания поля ввода координат
 */
class UI_Field_Coord : public UI_Field
{
	Q_OBJECT
public:
	explicit UI_Field_Coord(DescribeOneField field, QWidget *parent = nullptr);
	~UI_Field_Coord() {};

	void initInStorage()
	{
		emit changedValue(key(), readTable(), output());
		UI_Field::initInStorage();
	};

signals:
	void changedValue(QString key, QVector<Coord> value, bool output);

public slots:
	void updateValue(int row, int col);
	void updateField(Coord value);
	void updateField(QVector<Coord> value);
	void clearField();
	void addRow();
	void deleteRow();
	//! изменение значения флага в десятичные градусы
	void switchToDecimal();
	//! изменение значения флага градусы/минуты/секунды
	void switchToDegrees();
	//! изменение значения флага в радианы
	void switchToRadians();

private:
	QWidget *createContent();

	QWidget *createFlexibleTable();

	QVector<Coord> readTable();
	Coord readCoordFromTable(QTableWidget *tw, int row);
	void writeCoordToTable(QTableWidget *tw, Coord coord, int row);

	bool isFullTable(QTableWidget *tw);
	void updateTable();
	void setDelegate(bool is_special_degrees);
	//! заполнение таблицы значениями в радианах/десятичных градусах
	void fillTable(Coord current_coord, QTableWidget *table, int row);

	QTableWidget *table;
	//!хранилище координат (в радианах)
	QVector<Coord> coord_storage;
	CoordFormat format;
	const QString degrees_token = "\xB0";
	const QString minutes_token = "\x27";
	const QString seconds_token = "\x22";

};

#endif // FIELDS_H
