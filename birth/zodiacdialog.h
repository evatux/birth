// version 0.1

#ifndef ZODIACDIALOG_H
#define ZODIACDIALOG_H

#include <QDialog>

#include <QString>
#include <QDate>
#include "../include/zodiacUnit.h"
#include "../include/birthUnit.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QDateEdit;
class QPlainTextEdit;
class QImage;
class QPixmap;
class QPushButton;
QT_END_NAMESPACE

class ZodiacDialog : public QDialog
{
	Q_OBJECT

public:
	ZodiacDialog(QWidget*);

	void prepare( const QDate );

private slots:
	void dateChng( const QDate & date );

private:
	QLabel *birthdayLabel;	
	QDateEdit *birthdayEdit;

	QPlainTextEdit *text;
	QLabel *resultImage;
	QPushButton *closeButton;
};

#endif
