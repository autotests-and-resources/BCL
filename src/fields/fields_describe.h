#ifndef FIELDS_DESCRIBE_H
#define FIELDS_DESCRIBE_H

#include <QString>
#include <QVector>

struct DescribeOneField
{
	enum FieldDataType
	{
		Int,
		Double,
		String,
		Path,
		Coord,
		Hard
	};

	enum FieldArrayType
	{
		Matrix,
		Array,
		Item,
	};

	QString name;
	QString text;

	FieldDataType type_data;
	FieldArrayType type_array;

	bool output = false;

	int minimum = -1;
	int maximum = -1;

	bool array_flexible = false;
	int array_count = 0;
	int array_count_min = -1;
	int array_count_max = -1;

	void set(QString _name, QString _text, FieldDataType _type_d,
			 FieldArrayType _type_a, bool out = false)
	{
		name = _name;
		text = _text;
		type_data = _type_d;
		type_array = _type_a;
		output = out;
	}
};

class DescribeAllFields
{
public:
	explicit DescribeAllFields() {}
	~DescribeAllFields()
	{
		for (int i = 0; i < input.size(); i++)
			if (input[i])
				delete input[i];

		for (int i = 0; i < output.size(); i++)
			if (output[i])
				delete output[i];
	}

	void addInt(QString name, QString text, bool to_output = false) {
		addField(name, text, DescribeOneField::Int, to_output);
	}

	void addDouble(QString name, QString text, bool to_output = false) {
		addField(name, text, DescribeOneField::Double, to_output);
	}

	void addCoord(QString name, QString text, bool to_output = false) {
		addField(name, text, DescribeOneField::Coord, to_output);
	}

	void addHardType(QString name, QString text, bool to_output = false) {
		addField(name, text, DescribeOneField::Hard, to_output);
	}

	void addString(QString name, QString text, bool to_output = false) {
		addField(name, text, DescribeOneField::String, to_output);
	}

	void addPath(QString name, QString text, bool to_output = false) {
		addField(name, text, DescribeOneField::Path, to_output);
	}

	void setLimitMax(QString name, int value)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->maximum = value;
	}

	void setLimitMin(QString name, int value)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->minimum = value;
	}

	void setAsItem(QString name)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->type_array = DescribeOneField::Item;
	}

	void setAsArray(QString name)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->type_array = DescribeOneField::Array;
	}

	void setAsMatrix(QString name)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->type_array = DescribeOneField::Matrix;
	}

	void setArrayRowCount(QString name, int count)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->array_count = count;
	}

	void setArrayLimitMax(QString name, int value)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->array_count_max = value;
	}

	void setArrayLimitMin(QString name, int value)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->array_count_min = value;
	}

	void setArrayFlexible(QString name, bool flexible = true)
	{
		DescribeOneField *field = getField(name);
		if (field)
			field->array_flexible = flexible;
	}

	QVector<DescribeOneField*> getFieldsInput() {
		return input;
	}

	QVector<DescribeOneField*> getFieldsOutput() {
		return output;
	}

	DescribeOneField *getField(QString name)
	{
		for (int i = 0; i < input.size(); i++)
			if (input[i]->name == name)
				return input[i];
		for (int i = 0; i < output.size(); i++)
			if (output[i]->name == name)
				return output[i];
		return nullptr;
	}

private:
	void addField(QString name, QString text,
				  DescribeOneField::FieldDataType type_data, bool to_output)
	{
		DescribeOneField *field = getField(name);
		if (field)
			return ;

		field = new DescribeOneField();
		field->name = name;
		field->text = text;
		field->type_data = type_data;
		field->type_array = DescribeOneField::Item;

		if (to_output)
		{
			field->output = true;
			output.push_back(field);
		}
		else
			input.push_back(field);
	}

	QVector<DescribeOneField*> input;
	QVector<DescribeOneField*> output;
};

#endif // FIELDS_DESCRIBE_H
