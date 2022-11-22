#include "dir.h"
#include <QDir>
#include <QErrorMessage>

bool Dir::copyDirectory(const QString &src, const QString &dest, bool recursive)
{
	QDir dir(src);
	if (!dir.exists())
	{
		return false;
	}

	if (!dir.exists(dest))
		if (!dir.mkdir(dest))
		{
			return false;
		}

	bool ok;

	QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System
										   | QDir::Hidden | QDir::AllDirs
										   | QDir::Files, QDir::DirsFirst);
	for (QFileInfo &info : list)
	{
		QString src_path = src + QDir::separator() + info.fileName();
		QString dest_path = dest + QDir::separator() + info.fileName();
		if (info.isDir())
			ok = copyDirectory(src_path, dest_path, recursive);
		else
			ok = QFile::copy(src_path, dest_path);
		if (!ok)
		{
			return false;
		}
	}

	return true;
}

bool Dir::removeDirectory(const QString &dir_path)
{
	QDir dir(dir_path);
	if (!dir.exists(dir_path))
		return true;

	bool ok = true;
	QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System
										   | QDir::Hidden | QDir::AllDirs
										   | QDir::Files, QDir::DirsFirst);
	for (QFileInfo &info : list)
	{
		if (info.isDir())
			ok = removeDirectory(info.absoluteFilePath());
		else
			ok = QFile::remove(info.absoluteFilePath());

		if (!ok)
		{
			return false;
		}
	}
	ok = dir.rmdir(dir_path);
	return ok;
}
