#ifndef RESULT_WIDGET_H
#define RESULT_WIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include "ResultList.h"
#include "ResultStruct.h"

class ResultWidget : public QWidget
{
	Q_OBJECT

public:
	ResultWidget(QWidget* parent = nullptr);

public slots:
	void slotSinglize();

signals:
	void signalResultReady(QList<ResultStruct> result);
	void signalRemoveAllDup();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QScrollArea* m_scrolArea;
	ResultList* m_resulListWidget;
	QPushButton* m_singlizeButton;
};


#endif // RESULT_WIDGET_H
