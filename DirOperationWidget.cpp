#include "DirOperationWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>

DirOperationWidget::DirOperationWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	m_scrollArea = new QScrollArea;
	m_dirListWidget = new DirListWidget;
	m_inputEdit = new QLineEdit;
	m_browseButton = new QPushButton(tr("Browse"));
	m_addButton = new QPushButton(tr("Add"));
	m_searchButoon = new QPushButton(tr("Search"));

	m_scrollArea->setWidget(m_dirListWidget);
//	m_scrollArea->setWidgetResizable(true);

	QHBoxLayout* hLayout = new QHBoxLayout;
	QVBoxLayout* vLayout = new QVBoxLayout;

	vLayout->addWidget(m_scrollArea);
	hLayout->addWidget(m_inputEdit);
	hLayout->addWidget(m_browseButton);
	hLayout->addWidget(m_addButton);
	vLayout->addLayout(hLayout);
	vLayout->addWidget(m_searchButoon);

	setLayout(vLayout);

	connect(m_browseButton, &QPushButton::clicked, this, &DirOperationWidget::broseDir);
	connect(m_addButton, &QPushButton::clicked, this, &DirOperationWidget::addDir);
	connect(m_searchButoon, &QPushButton::clicked, this, &DirOperationWidget::search);
}

void DirOperationWidget::broseDir(bool checked /*= false*/)
{
	QString dir = QFileDialog::getExistingDirectory(this,
		tr("Open Directory"), "");
	m_inputEdit->setText(dir);
}

void DirOperationWidget::addDir(bool checked /*= false*/)
{
	if (m_inputEdit->text() != "")
		m_dirListWidget->addDir(m_inputEdit->text());
}

void DirOperationWidget::search(bool checked /*= false*/)
{
	QStringList* dirList = m_dirListWidget->getDirList();
	for (size_t i = 0; i < dirList->length(); i++)
	{
		QString s = dirList->at(i);
	}

	m_searchButoon->setEnabled(false);
	m_searchButoon->setText(tr("Searching..."));
	m_searchThread = new SearchThread;
	m_searchThread->setDirList(*dirList);
	m_searchThread->start();
	connect(m_searchThread, &SearchThread::resultReady, this, &DirOperationWidget::result);
}

void DirOperationWidget::result()
{
	m_searchButoon->setEnabled(true);
	m_searchButoon->setText(tr("Search"));
	emit signalResultReady(*m_searchThread->getResult());
	delete m_searchThread;
	m_searchThread = nullptr;
}

void DirOperationWidget::resizeEvent(QResizeEvent* event)
{
	m_dirListWidget->sizeChanged();
}
