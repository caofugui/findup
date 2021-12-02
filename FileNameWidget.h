#ifndef FILE_NAME_WIDGET
#define FILE_NAME_WIDGET

#include <QWidget>
#include <QLabel>
#include "IconButton.h"

class FileNameWidget : public QWidget
{
	Q_OBJECT

public:
	FileNameWidget(QWidget* parent = nullptr);

	void setFileName(QString file);
	QString getFileName();

signals:
	void signalRemoveFile(FileNameWidget* widget);

private slots:
	void slotRemove();

private:
	QLabel* m_fileNameLabel;
	IconButton* m_removeButton;

protected:
	void resizeEvent(QResizeEvent* event) override;
};

#endif // FILE_NAME_WIDGET
