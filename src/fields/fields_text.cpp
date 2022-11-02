#include "fields.h"

/* ========== STRING FIELD ========== */

UI_Field_String::UI_Field_String(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_String::updateValue(QString value)
{
	if (!isUnlockedChangedSignal())
		return;
	emit changedValue(_field.name, value, _field.output);
}

void UI_Field_String::updateField(QString value)
{
	lockChangedSignal();
	line_edit->setText(value);
	unlockChangedSignal();
}

void UI_Field_String::clearField() {
	line_edit->clear();
}

QWidget *UI_Field_String::createContent()
{
	line_edit = create_lineEdit();
	connect(line_edit, SIGNAL(textChanged(QString)), this, SLOT(updateValue(QString)));
	connect(line_edit, SIGNAL(textEdited(QString)), this, SLOT(updateValue(QString)));
	return line_edit;
}



/* ========== PATH FIELD ========== */

UI_Field_Path::UI_Field_Path(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_Path::fileDialog()
{
	QString filename = QFileDialog::getOpenFileName(
				this, _field.text, QDir::homePath());
	emit pathToFile(filename);
}

void UI_Field_Path::updateValue(QString value)
{
	if (!isUnlockedChangedSignal())
		return;
	emit changedValue(_field.name, value, _field.output);
}

void UI_Field_Path::updateField(QString value)
{
	lockChangedSignal();
	line_edit->setText(value);
	unlockChangedSignal();
}

void UI_Field_Path::clearField() {
	line_edit->clear();
}

QWidget *UI_Field_Path::createContent()
{
	QWidget *path = new QWidget(this);
	QHBoxLayout *layout = new QHBoxLayout(path);

	line_edit = create_lineEdit(path);
	layout->addWidget(line_edit);

	QPushButton *btn_browse = new UI_Button(path, BTN_DEFAULT, "Обзор");
	layout->addWidget(btn_browse);

	connect(btn_browse, SIGNAL(clicked()), this, SLOT(fileDialog()));
	connect(this, SIGNAL(pathToFile(QString)), line_edit, SLOT(setText(QString)));
	connect(line_edit, SIGNAL(textChanged(QString)), this, SLOT(updateValue(QString)));
	connect(line_edit, SIGNAL(textEdited(QString)), this, SLOT(updateValue(QString)));

	return path;
}
