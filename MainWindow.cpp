#include "MainWindow.h"

#include <QTextEdit>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
	m_splitter = new QSplitter(this);
	m_dirOperationWidget = new DirOperationWidget;
	m_resultWidget = new ResultWidget;
	m_splitter->addWidget(m_dirOperationWidget);
	m_splitter->addWidget(m_resultWidget);
	resize(1280, 800);

	connect(m_dirOperationWidget, &DirOperationWidget::signalResultReady,
		m_resultWidget, &ResultWidget::signalResultReady);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	m_splitter->resize(width(), height());
}

