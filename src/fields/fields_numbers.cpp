#include "fields.h"

/* ========== INT FIELD ========== */

UI_Field_Int::UI_Field_Int(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_Int::updateValue(int value)
{
	if (!isUnlockedChangedSignal())
		return;
	emit changedValue(_field.name, value, _field.output);
}

void UI_Field_Int::updateField(int value)
{
	lockChangedSignal();
	spin_box->setValue(value);
	unlockChangedSignal();
}

void UI_Field_Int::clearField() {
	spin_box->clear();
}

QWidget *UI_Field_Int::createContent()
{
	spin_box = create_spinBox();
	connect(spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateValue(int)));
	return spin_box;
}




/* ========== DOUBLE FIELD ========== */

UI_Field_Double::UI_Field_Double(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_Double::updateValue(double value)
{
	if (!isUnlockedChangedSignal())
		return;
	emit changedValue(_field.name, value, _field.output);
}

void UI_Field_Double::updateField(double value)
{
	lockChangedSignal();
	spin_box->setValue(value);
	unlockChangedSignal();
}

void UI_Field_Double::clearField() {
	spin_box->clear();
}

QWidget *UI_Field_Double::createContent()
{
	spin_box = create_spinBox();
	connect(spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateValue(double)));
	return spin_box;
}
