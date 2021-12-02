#include "ResultWidget.h"
#include <QVBoxLayout>
#include <QMessageBox>

ResultWidget::ResultWidget(QWidget* parent)
	:QWidget(parent)
{
	m_scrolArea = new QScrollArea;
	m_resulListWidget = new ResultList;
	m_singlizeButton = new QPushButton(tr("Remove All Duplicated Files"));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(m_scrolArea);
	layout->addWidget(m_singlizeButton);

	m_scrolArea->setWidget(m_resulListWidget);
	
	setLayout(layout);

	connect(this, &ResultWidget::signalResultReady,
		m_resulListWidget, &ResultList::slotResultReady);
	connect(m_singlizeButton, &QPushButton::clicked,
		this, &ResultWidget::slotSinglize);
	connect(this, &ResultWidget::signalRemoveAllDup,
		m_resulListWidget, &ResultList::slotRemoveAllDup);
}

void ResultWidget::slotSinglize()
{
	emit signalRemoveAllDup();
}

void ResultWidget::resizeEvent(QResizeEvent* event)
{
	m_resulListWidget->setWidth(width());
}
