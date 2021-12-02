#ifndef RESULT_ITEM_H
#define RESULT_ITEM_H

#include <QWidget>
#include <QLabel>
#include <QByteArray>
#include "FileNameWidget.h"

class ResultItem : public QWidget
{
	Q_OBJECT

public:
	ResultItem(QWidget* parent = nullptr);
	
	void setHashValue(QByteArray hashValue);
	QString getHashValue();

	void setFiles(QStringList fileList);
	QStringList getFiles();

	void removeAllDup();

	void setWidth(int w);

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

public slots:
	void slotRemoveFile(FileNameWidget* widget);

signals:
	void signalSizeChanged();

private:
	void layout(int w);

private:
	QLabel* m_hashVlaueLabel;
	QList<FileNameWidget*> m_fileNameWidgetList;
	bool m_hovered;
};

#endif // RESULT_ITEM_H