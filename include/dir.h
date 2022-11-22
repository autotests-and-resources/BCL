#ifndef DIR_H
#define DIR_H

#include <QTextStream>
#include <QDir>

class Dir
{
public:
	Dir() {};
	~Dir() {};

	static bool copyDirectory(const QString &src, const QString &dest, bool recursive);
	static bool removeDirectory(const QString &dir_path);
};

#endif // DIR_H
