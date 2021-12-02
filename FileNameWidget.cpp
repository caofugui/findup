#include "FileNameWidget.h"

FileNameWidget::FileNameWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	m_fileNameLabel = new QLabel(this);
	m_removeButton = new IconButton(":/icons/x.svg", this);
	m_removeButton->setToolTip(tr("Remove"));
	connect(m_removeButton, &IconButton::clicked, this, &FileNameWidget::slotRemove);
}

void FileNameWidget::setFileName(QString file)
{
	m_fileNameLabel->setText(file);
}

QString FileNameWidget::getFileName()
{
	return m_fileNameLabel->text();
}

void FileNameWidget::slotRemove()
{
	emit signalRemoveFile(this);
}

void FileNameWidget::resizeEvent(QResizeEvent* event)
{
	m_fileNameLabel->move(0, 0);
	m_removeButton->move(width() - 40, 10);
	m_removeButton->resize(20, 20);
}
