#ifndef COORDDELEGATE_H
#define COORDDELEGATE_H

#include <QItemDelegate>
#include <QLineEdit>

/*!
 * @brief Класс, реализующий "кастомный" QItemDelegate для ввода координат
 *
 * Данный класс наследуется от QItemDelegate и переопределяет метод createEditor,
 * чтобы ограничить ввод ячейки (разрешить только ввод строки определенного формата)
 * с помощью маски в QTableWidget, к которому относится объект данного класса.
 */
class CoordDelegate : public QItemDelegate
{
public:
	CoordDelegate(QObject *parent = 0){}
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
						  const QModelIndex &index) const;
};

/*!
 * @brief Класс, реализующий "кастомный" QItemDelegate для ввода чисел
 *
 * Данный класс наследуется от QItemDelegate и переопределяет метод createEditor,
 * чтобы ограничить ввод ячейки (разрешить только числа с плавающей запятой)
 * с помощью регулярного выражения в QTableWidget, к которому относится объект
 * данного класса.
 */
class DoubleValidatorDelegate : public QItemDelegate
{
public:
	DoubleValidatorDelegate(QObject *parent = 0){}
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
						  const QModelIndex &index) const;
};

#endif // COORDDELEGATE_H
