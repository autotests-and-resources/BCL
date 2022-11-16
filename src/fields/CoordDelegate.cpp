#include "CoordDelegate.h"

QWidget *CoordDelegate::createEditor(
		QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
	QLineEdit *editor = new QLineEdit(parent);
	editor->setInputMask("90\xB0\90\x27\90.000\x22");
	return editor;
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
