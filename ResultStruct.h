#ifndef RESULT_STRUCT_H
#define RESULT_STRUCT_H

#include <QByteArray>
#include <QStringList>
	
struct ResultStruct
{
	QByteArray fileShaValue;
	QStringList fileList;
};

#endif