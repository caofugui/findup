#ifndef SEARCH_THREAD_H
#define SEARCH_THREAD_H

#include <QThread>
#include <QMap>
#include <QList>
#include "ResultStruct.h"

class SearchThread : public QThread
{
	Q_OBJECT

public:
	void setDirList(QStringList list);
	QList<ResultStruct>* getResult();

protected:
	void run() override;

signals:
	void resultReady();

private:
	QStringList m_dirList;
	QList<ResultStruct> m_resultList;

};


#endif //SEARCH_THREAD_H

