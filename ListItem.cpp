#include "ListItem.h"

#include <QPainter>
#include <QMessageBox>

ListItem::ListItem(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	m_parent = parent;
	m_hovered = false;
	m_iconWidget = new QSvgWidget(":/icons/folder.svg", this);
	m_iconWidget->resize(20, 20);
	m_removeButton = new IconButton(":/icons/minus.svg", this);
	m_removeButton->resize(20, 20);
	m_removeButton->setToolTip(tr("Remove from list"));
	resize(parent->width(), 40);
	connect(m_removeButton, &IconButton::clicked, this, &ListItem::slotRemove);

	layout();
}

void ListItem::setText(QString text)
{
	m_text = text;
}

QString ListItem::getText()
{
	return m_text;
}

void ListItem::slotRemove()
{
	//	QMessageBox::information(nullptr, nullptr, "");
	emit signalRemoved(this);
}

void ListItem::slotSetWidth(int w)
{
	resize(w, height());
	layout();
}

void ListItem::layout()
{
	m_iconWidget->move(10, 10);
	m_removeButton->move(width() - 40, 10);
}

void ListItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	if (m_hovered)
	{
		painter.fillRect(0, 0, width(), height(), QColor(220, 220, 220));
	}
	painter.drawText(QRect(40, 0, width() - 40, 40),
		Qt::AlignLeft | Qt::AlignVCenter, m_text);
}

void ListItem::enterEvent(QEnterEvent* event)
{
	m_hovered = true;
	update();
}

void ListItem::leaveEvent(QEvent* event)
{
	m_hovered = false;
	update();
}

void ListItem::resizeEvent(QResizeEvent* event)
{
	layout();
}
