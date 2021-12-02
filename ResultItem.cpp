#include "ResultItem.h"

#include <QPainter>
#include <QFile>
#include <QMessageBox>

ResultItem::ResultItem(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	m_hashVlaueLabel = new QLabel(this);
	m_hovered = false;
}

void ResultItem::setHashValue(QByteArray hashValue)
{
	m_hashVlaueLabel->setText("SHA256: " + hashValue.toHex());
}

QString ResultItem::getHashValue()
{
	QString text = m_hashVlaueLabel->text();
	return text.split(":").at(1);
}

void ResultItem::setFiles(QStringList fileList)
{
	for (size_t i = 0; i < fileList.length(); i++)
	{
		FileNameWidget* widget = new FileNameWidget(this);
		widget->setFileName(fileList.at(i));
		widget->show();
		m_fileNameWidgetList << widget;
		connect(widget, &FileNameWidget::signalRemoveFile,
			this, &ResultItem::slotRemoveFile);
	}

	layout(width());
}

QStringList ResultItem::getFiles()
{
	QStringList list;
	for (size_t i = 0; i < m_fileNameWidgetList.length(); i++)
	{
		list << m_fileNameWidgetList.at(i)->getFileName();
	}

	return list;
}

void ResultItem::removeAllDup()
{
	for (size_t i = 0; i < m_fileNameWidgetList.length(); i++)
	{
		FileNameWidget* widget = m_fileNameWidgetList.at(i);
		QFile file(widget->getFileName());
		if (i != 0)
		{
			file.remove();
		}
		delete widget;
	}

	m_fileNameWidgetList.clear();
}

void ResultItem::setWidth(int w)
{
	layout(w);
}

void ResultItem::slotRemoveFile(FileNameWidget* widget)
{
	QFile file(widget->getFileName());
	int ret = QMessageBox::question(this, tr("Remove File"), tr("Remove this file?"),
		QMessageBox::Yes, QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		bool b = file.remove();
		if (!b)
		{
			QMessageBox::warning(this, nullptr, "Cannot Remove this file!", QMessageBox::Ok);
		}
		else
		{
			m_fileNameWidgetList.remove(m_fileNameWidgetList.indexOf(widget));
			delete widget;
			emit signalSizeChanged();
			layout(width());
		}
	}
}

void ResultItem::layout(int w)
{
	int h = 0;
	m_hashVlaueLabel->move(0, 0);
	m_hashVlaueLabel->resize(w, 40);
	h += 40;

	for (size_t i = 0; i < m_fileNameWidgetList.length(); i++)
	{
		m_fileNameWidgetList.at(i)->move(0, h);
		m_fileNameWidgetList.at(i)->resize(w, 40);
		h += 40;
	}

	resize(w, h);
}

void ResultItem::enterEvent(QEnterEvent* event)
{
	m_hovered = true;
	update();
}

void ResultItem::leaveEvent(QEvent* event)
{
	m_hovered = false;
	update();
}

void ResultItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	if (m_hovered)
	{
		painter.fillRect(0, 0, width(), height(), QColor(220, 220, 220));
	}
}
