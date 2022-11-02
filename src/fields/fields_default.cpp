#include "fields.h"

/* ========== DEFAULT FIELD ========== */

UI_Field::UI_Field(DescribeOneField field, QWidget *parent)
	: QWidget{parent}
	, _field(field)
	, is_unlocked_changed_signal(true)
{
	label = new QLabel(this);
	label->setText(field.text);
	label->setAlignment(Qt::AlignLeft);

	content = createContent();

	form_layout = new QFormLayout(this);
	form_layout->setRowWrapPolicy(QFormLayout::WrapAllRows);
	form_layout->addRow(label, content);
}

QString UI_Field::key() {
	return _field.name;
}

QWidget *UI_Field::createContent() {
	return defaultLabel();
}

QLabel *UI_Field::defaultLabel()
{
	QLabel *label = new QLabel(this);
	label->setText("[default]");
	label->setStyleSheet(UI_Styles::line_edit());
	return label;
}

QLineEdit *UI_Field::create_lineEdit(QWidget *parent)
{
	if (!parent)
		parent = this;
	QLineEdit *line = new QLineEdit(parent);
	line->setStyleSheet(UI_Styles::line_edit());
	return line;
}

QTableWidget *UI_Field::create_table()
{
	QTableWidget *tw = new QTableWidget(this);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(tw->sizePolicy().hasHeightForWidth());
	tw->setSizePolicy(sizePolicy);

	tw->setStyleSheet(
		"QWidget {"
		"	color: #000000;"
		"}"
		"QHeaderView::section {"
//			"	background-color: #646464;"
//			"	padding: 4px;"
//			"	border: 1px solid #fffff8;"
//			"	font-size: 14pt;"
		"}"
		"QTableWidget {"
		"	gridline-color: #fffff8;"
//			"	font-size: 12pt;"
		"}"
		""
		"QTableWidget QTableCornerButton::section {"
		"	background-color: #646464;"
		"	border: 1px solid #fffff8;"
		"}"
	);

	return tw;
}

QComboBox *UI_Field::create_comboBox()
{
	QComboBox *combo = new QComboBox(this);
	combo->setStyleSheet(UI_Styles::combo_box());
	return combo;
}

QSpinBox *UI_Field::create_spinBox()
{
	QSpinBox *spin = new QSpinBox(this);
	spin->setFocusPolicy(Qt::StrongFocus);
	spin->setSingleStep(1);
	spin->setStyleSheet(UI_Styles::spin_box());
	spin->setValue(0);
	return spin;
}




/* ========== BOOL FIELD ========== */

UI_Field_Bool::UI_Field_Bool(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_Bool::updateValue(QString text)
{
	if (!isUnlockedChangedSignal())
		return;
	bool value = (text == "true");
	emit changedValue(_field.name, value, _field.output);
}

void UI_Field_Bool::updateField(bool value)
{
	lockChangedSignal();
	combo_box->setCurrentIndex(value ? 1 : 2);
	unlockChangedSignal();
}

void UI_Field_Bool::clearField() {
	combo_box->setCurrentIndex(0);
}

QWidget *UI_Field_Bool::createContent()
{
	combo_box = create_comboBox();
	combo_box->addItem("---");
	combo_box->addItem("true");
	combo_box->addItem("false");
	combo_box->setCurrentIndex(0);
	connect(combo_box, SIGNAL(activated(QString)), this, SLOT(updateValue(QString)));
	return combo_box;
}
