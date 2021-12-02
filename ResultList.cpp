#include "ResultList.h"

#include <QDebug>
#include <QPainter>
#include <QMessageBox>

ResultList::ResultList(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ResultList::setWidth(int w)
{
	layout(w - 20);
}

QSize ResultList::sizeHint() const
{
	return QSize(600, 400);
}

void ResultList::slotResultReady(QList<ResultStruct> result)
{
	for (size_t i = 0; i < m_items.length(); i++)
	{
		delete m_items.at(i);
	}

	m_items.clear();

	for (size_t i = 0; i < result.length(); i++)
	{
		ResultItem* item = new ResultItem(this);
		item->show();
		item->setHashValue(result.at(i).fileShaValue);
		item->setFiles(result.at(i).fileList);
		m_items << item;

		connect(item, &ResultItem::signalSizeChanged,
			this, &ResultList::slotListChanged);
	}
	
	layout(width());
}

void ResultList::slotListChanged()
{
	layout(width());
}

void ResultList::slotRemoveAllDup()
{
	int ret = QMessageBox::question(this, tr("Remove File"), tr("Remove All Dup Files?"),
		QMessageBox::Yes, QMessageBox::No);

	if (ret == QMessageBox::Yes)
	{
		for (size_t i = 0; i < m_items.length(); i++)
		{
			ResultItem* item = m_items.at(i);
			item->removeAllDup();
			delete item;
		}
	}

	m_items.clear();
}

void ResultList::layout(int w)
{
	int h = 0;
	for (size_t i = 0; i < m_items.length(); i++)
	{
		ResultItem* item = m_items.at(i);
		item->setWidth(w);
		item->move(0, h);
		h += item->height();
	}

	resize(w, h);
}
