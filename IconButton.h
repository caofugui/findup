#ifndef ICON_BUTOON_H
#define ICON_BUTOON_H

#include <QSvgWidget>
class IconButton : public QSvgWidget
{
	Q_OBJECT

public:
	IconButton(const QString& file, QWidget* parent);

	QSize sizeHint() const override;

protected:
	void mousePressEvent(QMouseEvent* event) override;

signals:
	void clicked();
};

#endif // ICON_BUTOON_H
