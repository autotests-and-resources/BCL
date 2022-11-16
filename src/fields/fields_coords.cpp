#include "fields.h"

/* ========== COORD FIELD ========== */

UI_Field_Coord::UI_Field_Coord(DescribeOneField field, QWidget *parent)
	: UI_Field(field, parent)
	, format(CoordFormat::RADIANS)
{
	if (content)
		delete content;
	content = createContent();
	form_layout->addRow(label, content);
}

void UI_Field_Coord::updateTable()
{
	//проход по вектору с радианами
	for (int row = 0; row < coord_storage.size(); row++)
	{
		//запись в структуру точки содержания строки с номером row
		Coord current_coord = coord_storage[row];

		switch (format)
		{
		//радианы
		case CoordFormat::RADIANS:
			//заполнение таблицы
			fillTable(current_coord, table, row);
			break;
			//десятичные градусы
		case CoordFormat::DECIMAL:
			//перевод в деятичные градусы
			current_coord.Lat = TransformCoords::radiansToDecimalDegrees(current_coord.Lat);
			current_coord.Long = TransformCoords::radiansToDecimalDegrees(current_coord.Long);
			//заполнение таблицы
			fillTable(current_coord, table, row);
			break;
			//градусы/минуты/секунды
		case CoordFormat::DEGREES:
			//перевод широты
			TransformCoords::Degrees degrees_lat;
			degrees_lat = TransformCoords::radiansToDegrees(current_coord.Lat);
			//перевод долготы
			TransformCoords::Degrees degrees_long;
			degrees_long = TransformCoords::radiansToDegrees(current_coord.Long);
			//заполнение таблицы
			QTableWidgetItem *item_lat = table->item(row, 0);
			if (item_lat)
			{
				item_lat->setText(QString::number(degrees_lat.degrees) + degrees_token
								  + QString::number(degrees_lat.minutes) + minutes_token
								  + QString::number(degrees_lat.seconds) + seconds_token);
			}
			QTableWidgetItem *item_long = table->item(row, 1);
			if (item_long)
			{
				item_long->setText(QString::number(degrees_long.degrees) + degrees_token
								   + QString::number(degrees_long.minutes) + minutes_token
								   + QString::number(degrees_long.seconds) + seconds_token);
			}
			break;
		}
	}
}

void UI_Field_Coord::setDelegate(bool is_special_degrees)
{
	if (is_special_degrees)
	{
		table->setItemDelegateForColumn(0, new CoordDelegate);
		table->setItemDelegateForColumn(1, new CoordDelegate);
		table->setItemDelegateForColumn(2, new DoubleValidatorDelegate);
	}
	else
	{
		table->setItemDelegateForColumn(0, nullptr);
		table->setItemDelegateForColumn(1, nullptr);
		table->setItemDelegateForColumn(2, nullptr);
	}
}

void UI_Field_Coord::fillTable(Coord current_coord, QTableWidget *table, int row)
{
	QTableWidgetItem *item_lat = table->item(row, 0);
	if (item_lat)
		item_lat->setText(QString::number(current_coord.Lat));

	QTableWidgetItem *item_long = table->item(row, 1);
	if (item_long)
		item_long->setText(QString::number(current_coord.Long));

	QTableWidgetItem *item_h = table->item(row, 2);
	if (item_h)
		item_h->setText(QString::number(current_coord.H));
}

void UI_Field_Coord::updateValue(int row, int col)
{
	if (!isUnlockedChangedSignal())
		return;

	QTableWidgetItem *item = nullptr;

	if (col == 2)
	{
		//элемент с высотой существует
		item = table->item(row, col);
		if (item)
			//считывание высоты в вектор
			coord_storage[row].H = item->text().toDouble();
	}
	else
	{
		//если элементы широты и долготы существуют
		item = table->item(row, col);
		if (!item)
			return;

		double new_value = 0;

		switch (format)
		{
		//если выбраны радианы
		case CoordFormat::RADIANS:
			//считываем значение без изменений
			new_value = item->text().toDouble();
			break;
			//если выбраны градусы/минуты/секунды
		case CoordFormat::DEGREES:
		{
			QString cell_text = item->text();
			if (cell_text.isEmpty())
				return;
			cell_text.replace("\xB0", " ");
			cell_text.replace("\x27", " ");
			cell_text.replace("\x22", "");

			QStringList dms = cell_text.split(" ");

			TransformCoords::Degrees degrees_struct;
			degrees_struct.degrees = dms[0].toDouble();
			degrees_struct.minutes = dms[1].toDouble();
			degrees_struct.seconds = dms[2].toDouble();

			new_value = TransformCoords::degreesToRadians(degrees_struct);
			break;
		}
			//если выбраны десятичные градусы
		case CoordFormat::DECIMAL:
			//считываем значение
			new_value = item->text().toDouble();
			//переводим в радианы
			new_value = TransformCoords::decimalDegreesToRadians(new_value);
			break;
		default:
			break;
		}
		//добавление широты и долготы в вектор
		if (col == 0)
			coord_storage[row].Lat = new_value;
		else if (col == 1)
			coord_storage[row].Long = new_value;
	}

	qDebug() << coord_storage[row].Lat << "/" << coord_storage[row].Long << "/"
			 << coord_storage[row].H;

	emit changedValue(_field.name, coord_storage, _field.output);
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

void UI_Field_Coord::clearField()
{
	table->clearContents();
}

void UI_Field_Coord::addRow()
{
	int new_row = table->rowCount();
	table->insertRow(new_row);
	coord_storage.push_back({});
}

void UI_Field_Coord::deleteRow()
{
	int old_row = table->rowCount() - 1;
	table->removeRow(old_row);
	coord_storage.pop_back();
}

void UI_Field_Coord::switchToDecimal()
{
	format = CoordFormat::DECIMAL;
	setDelegate(false);
	updateTable();
}

void UI_Field_Coord::switchToDegrees()
{
	format = CoordFormat::DEGREES;
	setDelegate(true);
	updateTable();
}

void UI_Field_Coord::switchToRadians()
{
	format = CoordFormat::RADIANS;
	setDelegate(false);
	updateTable();
}

QWidget *UI_Field_Coord::createContent()
{
	QWidget *content;
	table = create_table();

	//	if (_field.array_flexible)
	//		content = createFlexibleTable();
	//	else
	content = table;

	table->setRowCount(0);
	if (_field.array_count > 0)
		table->setRowCount(_field.array_count);

	table->setColumnCount(3);
	table->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromUtf8("Широта")));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromUtf8("Долгота")));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromUtf8("Высота")));

	connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(updateValue(int, int)));

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
