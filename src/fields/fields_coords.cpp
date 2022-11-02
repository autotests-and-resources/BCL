#include "fields.h"

/* ========== COORD FIELD ========== */

UI_Field_Coord::UI_Field_Coord(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_Coord::updateValue(int row, int col)
{
	if (!isUnlockedChangedSignal())
		return;
	if (!isFullTable(table))
		return;

	QVector<Coord> coords = readTable();
	emit changedValue(_field.name, coords, _field.output);

	(void)row;
	(void)col;
}

void UI_Field_Coord::updateField(Coord value)
{
	QVector<Coord> coords({value});
	updateField(coords);
}

void UI_Field_Coord::updateField(QVector<Coord> value)
{
	lockChangedSignal();
	table->setRowCount(value.size());
	for (int row = 0; row < value.size(); row++)
		writeCoordToTable(table, value[row], row);
	unlockChangedSignal();
}

void UI_Field_Coord::clearField() {
	table->clearContents();
}

void UI_Field_Coord::addRow()
{
	int new_row = table->rowCount();
	table->insertRow(new_row);
}

void UI_Field_Coord::deleteRow()
{
	int old_row = table->rowCount() - 1;
	table->removeRow(old_row);
}

QWidget *UI_Field_Coord::createContent()
{
	QWidget *content;
	table = create_table();

//	if (_field.array_flexible)
//		content = createFlexibleTable();
//	else
	content = table;

	table->setRowCount(1);
	if (_field.array_count > 0)
		table->setRowCount(_field.array_count);

	table->setColumnCount(3);
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Широта"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Долгота"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Высота"));

	connect(table, SIGNAL(cellChanged(int,int)),
			this, SLOT(updateValue(int,int)));

	return content;
}

QWidget *UI_Field_Coord::createFlexibleTable()
{
	QWidget *flex_table = new QWidget(this);
	QVBoxLayout *v_layout = new QVBoxLayout(flex_table);

	QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Maximum, QSizePolicy::Maximum);

	v_layout->addWidget(table);
	v_layout->addSpacerItem(spacer);

	QWidget *buttons = new QWidget(this);
	QHBoxLayout *h_layout = new QHBoxLayout(buttons);

	QPushButton *plus = new QPushButton("+", this);
	h_layout->addWidget(plus);
	h_layout->addStretch();
	connect(plus, SIGNAL(clicked()), this, SLOT(addRow()));

	QPushButton *minus = new QPushButton("-", this);
	h_layout->addWidget(minus);
	h_layout->addStretch();
	connect(minus, SIGNAL(clicked()), this, SLOT(deleteRow()));

	v_layout->addWidget(buttons);
	v_layout->addSpacerItem(spacer);

	return flex_table;
}

QVector<Coord> UI_Field_Coord::readTable()
{
	if (!isFullTable(table))
		return QVector<Coord>();

	QVector<Coord> coords;
	for (int row = 0; row < table->rowCount(); row++)
	{
		Coord coord = readCoordFromTable(table, row);
		coords.push_back(coord);
	}
	return coords;
}

Coord UI_Field_Coord::readCoordFromTable(QTableWidget *tw, int row)
{
	Coord coord;
	coord.Lat = tw->item(row, 0)->text().toDouble();
	coord.Long = tw->item(row, 1)->text().toDouble();
	coord.H = tw->item(row, 2)->text().toDouble();
	return coord;
}

void UI_Field_Coord::writeCoordToTable(QTableWidget *tw, Coord coord, int row)
{
	QTableWidgetItem *item = new QTableWidgetItem(QString::number(coord.Lat));
	tw->setItem(row, 0, item);
	item = new QTableWidgetItem(QString::number(coord.Long));
	tw->setItem(row, 1, item);
	item = new QTableWidgetItem(QString::number(coord.H));
	tw->setItem(row, 2, item);
}

bool UI_Field_Coord::isFullTable(QTableWidget *tw)
{
	for (int row = 0; row < tw->rowCount(); row++)
		for (int col = 0; col < tw->columnCount(); col++)
		{
			QTableWidgetItem *item = tw->item(row, col);
			if (!item || item->text().isEmpty())
				return false;
		}
	return true;
}
