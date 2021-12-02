#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QSplitter>

#include "DirOperationWidget.h"
#include "ResultWidget.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QSplitter* m_splitter;
	DirOperationWidget* m_dirOperationWidget;
	ResultWidget* m_resultWidget;
};

#endif // MAIN_WINDOW_H
