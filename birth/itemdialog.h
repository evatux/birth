// version 0.1

#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>

#include <QString>
#include <QDate>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QLayout>

class ItemDialog : public QDialog
{
	Q_OBJECT

public:
	ItemDialog(QWidget*);
        void prepare (QString, QDate, int);
	bool isAdd;

signals:
	void getaItem(QString, QDate);
	void geteItem(QString, QDate, int);

private slots:
	void buttonClicked();
	void enablebutton(const QString &text);

private:
	QLabel *nameLabel;
	QLabel *birthdayLabel;
	
	QLineEdit *nameEdit;
	QDateEdit *birthdayEdit;

	QPushButton *button;
	QPushButton *closeButton;

	int index;
};

#endif
