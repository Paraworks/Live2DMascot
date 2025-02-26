#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtextbrowser.h>
#include <QtCore/qpropertyanimation.h>

class Dialog : public QWidget
{
protected:
	void mouseReleaseEvent(QMouseEvent* e);
public:
	Dialog();
	void pop(const char* text);
	void Release();
	void AttachToCharacter();
	void paintEvent(QPaintEvent* e);
private:
	QPropertyAnimation* animation;
	int _xBorder;
	int _yBorder;
	QString _text;
	QFont _font;
	QFontMetrics* _fontMetrics;
};