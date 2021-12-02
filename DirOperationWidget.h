#ifndef DIR_OPERATION_H
#define DIR_OPERATION_H

#include "DirListWidget.h"

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include "SearchThread.h"

class DirOperationWidget : public QWidget
{
	Q_OBJECT

public:
	DirOperationWidget(QWidget* parent = nullptr);

private slots:
	void broseDir(bool checked = false);
	void addDir(bool checked = false);
	void search(bool checked = false);
	void result();

signals:
	void signalResultReady(QList<ResultStruct> result);

private:
	DirListWidget* m_dirListWidget;
	QScrollArea* m_scrollArea;
	QLineEdit* m_inputEdit;
	QPushButton* m_browseButton;
	QPushButton* m_addButton;
	QPushButton* m_searchButoon;
	SearchThread* m_searchThread;

protected:
	void resizeEvent(QResizeEvent* event) override;

};

#endif // DIR_OPERATION_H
