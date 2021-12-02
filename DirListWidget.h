#ifndef DIR_LIST_WIDGET_H
#define DIR_LIST_WIDGET_H

#include <QWidget.h>

#include "ListItem.h"

class DirListWidget : public QWidget
{
	Q_OBJECT

public:
	DirListWidget(QWidget* parent = nullptr);

	void addDir(QString dir);
	QStringList* getDirList();

	QSize sizeHint() const override;

public slots:
	void sizeChanged();
	void removeDir(ListItem* item);

signals:
	void dirRemoved(QString dir);

private:
	void layout();

private:
	QStringList m_dirList;
	QList<ListItem*> m_dirWidgetItemList;
};

#endif // DIR_LIST_WIDGET_H