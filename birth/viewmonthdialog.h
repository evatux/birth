// version 0.1

#ifndef VIEWMONTHDIALOG_H
#define VIEWMONTHDIALOG_H

#include <QString>

class QDialog;
class QPushButton;
class QListWidget;
class QLayout;

#include "../include/birthUnit.h"

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
