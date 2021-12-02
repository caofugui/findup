#include "IconButton.h"
#include <QMouseEvent>

IconButton::IconButton(const QString& file, QWidget* parent)
	:QSvgWidget(file, parent)
{
	setCursor(Qt::PointingHandCursor);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QSize IconButton::sizeHint() const
{
	return QSize(40, 40);
}

void IconButton::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
		emit clicked();
	event->accept();
}
