#ifndef LIST_ITEM_H
#define LIST_ITEM_H

#include <QWidget>
#include <QSvgWidget>
#include "IconButton.h"

class ListItem : public QWidget
{
	Q_OBJECT

public:
	ListItem(QWidget* parent);

	void setText(QString text);
	QString getText();

protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

signals:
	void signalRemoved(ListItem* item);

public slots:
	void slotRemove();
	void slotSetWidth(int w);

private:
	void layout();

private:
	QString m_text;
	QWidget* m_parent;
	QSvgWidget* m_iconWidget;
	IconButton* m_removeButton;
	bool m_hovered;
};

#endif // LIST_ITEM_H
