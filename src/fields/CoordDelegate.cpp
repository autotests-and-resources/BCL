#include "CoordDelegate.h"

CoordDelegate::CoordDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

QWidget *CoordDelegate::createEditor(
		QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
	QLineEdit *editor = new QLineEdit(parent);
	editor->setInputMask("90\xB0\90\x27\90.000\x22");
	return editor;
}

DoubleValidatorDelegate::DoubleValidatorDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

QWidget *DoubleValidatorDelegate::createEditor(
		QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &
		) const
{
	QLineEdit *editor = new QLineEdit(parent);
	editor->setValidator(
				new QRegExpValidator(
					QRegExp("^[-+]?[0-9]*[.,][0-9]+(?:[eE][-+]?[0-9]+)?$"),
					editor)
				);
	return editor;
}
