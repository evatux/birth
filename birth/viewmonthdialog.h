// version 0.1

#ifndef VIEWMONTHDIALOG_H
#define VIEWMONTHDIALOG_H

#include <QDialog>

#include <QString>
#include "../include/birthUnit.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QPushButton;
QT_END_NAMESPACE

class ViewMonthDialog : public QDialog
{
	Q_OBJECT

public:
	ViewMonthDialog(QWidget*);

	void fillList(QList<birthItem>);

	//void prepare( const QDate );

//private slots:
	//void dateChng( const QDate & date );

private:
	QListWidget *itemList;
	QPushButton *closeButton;
};

#endif
