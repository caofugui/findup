#include "SearchThread.h"
#include "ResultStruct.h"

#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QCryptographicHash>

void SearchThread::setDirList(QStringList list)
{
	m_dirList = list;
}

QList<ResultStruct>* SearchThread::getResult()
{
	return &m_resultList;
}

void SearchThread::run()
{
	char buffer[1024];
	qint64 nRead;
	QMap<qint64, QStringList> map;

	for (size_t i = 0; i < m_dirList.length(); i++)
	{
		QDir dir(m_dirList.at(i));
		if (!dir.exists())
			continue;
		dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
		QFileInfoList list = dir.entryInfoList();
		for (size_t i = 0; i < list.length(); i++)
		{
			QFileInfo fi = list.at(i);
			if (fi.isFile())
			{
				if (map.contains(fi.size()))
				{
					map[fi.size()] << fi.filePath();
				}
				else
				{
					QStringList fileList;
					fileList << fi.filePath();
					map[fi.size()] = fileList;
				}
			}
		}
	}

	QMap<QByteArray, QStringList> hashMap;
	for (auto it = map.constBegin(); it != map.constEnd(); ++it)
	{
		QStringList list = it.value();

		for (auto it = list.constBegin(); it != list.constEnd(); ++it)
		{
			QCryptographicHash hash(QCryptographicHash::Sha256);
			QByteArray hashResult;
			QFile file(*it);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				continue;
			while (!file.atEnd()) {
				nRead = file.read(buffer, 1024);
				hash.addData(buffer, nRead);
			}
			hashResult = hash.result();
			if (hashMap.contains(hashResult))
			{
				hashMap[hashResult] << *it;
			}
			else
			{
				QStringList list;
				list << *it;
				hashMap[hashResult] = list;
			}
		}
	}

	for (auto it = hashMap.constBegin(); it != hashMap.constEnd(); ++it)
	{
		ResultStruct rs;
		if (it.value().length() > 1)
		{
			rs.fileShaValue = it.key();
			rs.fileList << it.value();
			m_resultList << rs;
		}
	}

	emit resultReady();
/*
	qDebug() << m_resultList.length();
	for (size_t i = 0; i < m_resultList.length(); i++)
	{
		qDebug() << "  " << m_resultList.at(i);
	}
*/
}
