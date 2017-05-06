// version 0.1

#ifndef ZODIACDIALOG_H
#define ZODIACDIALOG_H

#include <QString>
#include <QDate>

#include "../include/zodiacUnit.h"
#include "../include/birthUnit.h"

class QDialog;
class QLabel;
class QDateEdit;
class QPushButton;
class QPlainTextEdit;
class QImage;
class QPixmap;

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
