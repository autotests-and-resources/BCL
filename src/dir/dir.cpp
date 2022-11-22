#include "dir.h"
#include <QDir>
#include <QErrorMessage>

bool Dir::copyDirectory(const QString &src, const QString &dest, bool recursive)
{
	QDir dir(src);
	if (!dir.exists())
	{
		//LS_WARN("Source directory '" << src << "' not exists");
		QErrorMessage errorMessage;
		errorMessage.showMessage("Source directory '" + src + "' not exists");
		errorMessage.exec();
		return false;
	}

	if (!dir.exists(dest))
		if (!dir.mkdir(dest))
		{
			//LS_WARN("Can't create destination directory '" << dest << "'");
			QErrorMessage errorMessage;
			errorMessage.showMessage("Can't create destination directory '" + dest + "'");
			errorMessage.exec();
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
			//LS_WARN("Can't copy '" << src_path << "' to '" << dest_path << "'");
			QErrorMessage errorMessage;
			errorMessage.showMessage("Can't copy '" + src_path + "' to '" + dest_path + "'");
			errorMessage.exec();
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
//			LS_WARN("Can't remove " << (info.isFile() ? "file" : "directory" )
//					<< " '" << info.absoluteFilePath() << "'");
			QErrorMessage errorMessage;
			const char *file_or_directory = info.isFile() ? "file" : "directory";
			errorMessage.showMessage((QString)"Can't remove " + file_or_directory
							+ " '" + info.absoluteFilePath() + "'");
			errorMessage.exec();
			return false;
		}
	}
	ok = dir.rmdir(dir_path);
	if (!ok)
	{
		//LS_WARN("Can't remove directory '" << dir_path << "'");
		QErrorMessage errorMessage;
		errorMessage.showMessage("Can't remove directory '" + dir_path + "'");
		errorMessage.exec();
	}
	return ok;
}
