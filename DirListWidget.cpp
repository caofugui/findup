#include "DirListWidget.h"

#include <QPainter>
#include <QMessageBox>

DirListWidget::DirListWidget(QWidget* parent)
	:QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void DirListWidget::addDir(QString dir)
{
	QStringList* list = getDirList();
	if (list->contains(dir))
	{
		QMessageBox::information(this, nullptr, tr("dir exist in the list"));
		return;
	}

	ListItem* widget = new ListItem(this);
	widget->setText(dir);
	widget->show();
	m_dirWidgetItemList.append(widget);
	connect(widget, &ListItem::signalRemoved, this, &DirListWidget::removeDir);
	int y = 0;
	for (size_t i = 0; i < m_dirWidgetItemList.length(); i++)
	{
		y += m_dirWidgetItemList.at(i)->height();
	}

	resize(qobject_cast<QWidget*>(parent())->width() - 10, y);
	layout();
}

QStringList* DirListWidget::getDirList()
{
	m_dirList.clear();
	for (ListItem* widget : m_dirWidgetItemList)
	{
		m_dirList.append(widget->getText());
	}
	return &m_dirList;
}

QSize DirListWidget::sizeHint() const
{
	return QSize(600, 400);
}

void DirListWidget::sizeChanged()
{
	resize(qobject_cast<QWidget*>(parent())->width() - 10, height());
	layout();
}

void DirListWidget::removeDir(ListItem* item)
{
	m_dirWidgetItemList.remove(m_dirWidgetItemList.indexOf(item));
	delete item;
	sizeChanged();
}

void DirListWidget::layout()
{
	int y = 0;
	size_t i = 0;
	for (; i < m_dirWidgetItemList.length(); i++)
	{
		ListItem* item = m_dirWidgetItemList.at(i);
		item->resize(width(), item->height());
		item->move(0, y);
		y += item->height();
	}
}
