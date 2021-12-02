#ifndef RESULT_LIST_H
#define RESULT_LIST_H

#include <QWidget>
#include <QList>

#include "ResultItem.h"
#include "ResultStruct.h"

class ResultList : public QWidget
{
	Q_OBJECT

public:
	ResultList(QWidget* parent = nullptr);

	void setWidth(int w);

	QSize sizeHint() const override;

public slots:
	void slotResultReady(QList<ResultStruct> result);
	void slotListChanged();
	void slotRemoveAllDup();

private:
	void layout(int w);

private:
	QList<ResultItem*> m_items;
};

#endif // RESULT_LIST_H
