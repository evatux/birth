// version 0.1

#if QT_VERSION < 0x050000
#include <QtGui>
#else
#include <QtWidgets>
#endif
#include <QDate>

#include <QDialog>
#include <QPushButton>
#include <QListWidget>
#include <QLayout>

#include "viewmonthdialog.h"

bool caseBirthItemLessThan(birthItem&, birthItem&);

ViewMonthDialog::ViewMonthDialog(QWidget *parent = 0) : QDialog(parent)
{
	setWindowTitle(QString::fromUtf8("Просмотр событий на месяц вперед"));

	itemList = new QListWidget;
	closeButton = new QPushButton(QString::fromUtf8("Закрыть"), this);

	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch(1);
	bottomLayout->addWidget(closeButton);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	//mainLayout->setMargin(11);
	//mainLayout->setSpacing(6);
	mainLayout->addWidget(itemList);
	mainLayout->addLayout(bottomLayout);
}

void ViewMonthDialog::fillList( QList<birthItem> birthList )
{
	QList<birthItem> tmpList;

	itemList->clear();

	for (QList<birthItem>::iterator i = birthList.begin(); i != birthList.end(); ++i)
	{
		QDate today = QDate::currentDate();
		QDate tmp( today.year(), (i->getbirthday()).month(), (i->getbirthday()).day());
		
		if ( (today.daysTo(tmp) >= 0) && (today.daysTo(tmp) <= 30))
			tmpList.push_back(*i);
	}

        // qSort(tmpList.begin(), tmpList.end(), caseBirthItemLessThan);
        qSort(tmpList.begin(), tmpList.end());

	for (QList<birthItem>::iterator i = tmpList.begin(); i != tmpList.end(); ++i)
		itemList->addItem( (i->getbirthday()).toString("yyyy-MM-dd") + "        " + (i->getname()) );
}

bool caseBirthItemLessThan(birthItem &b1, birthItem &b2)
{
	QDate d1 = b1.getbirthday();
	QDate d2( d1.year(), (b2.getbirthday()).month(), (b2.getbirthday()).day());
	return d1 < d2;
}
