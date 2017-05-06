// Birthday [ver. 0.2]

#include "birth.h"

#include <QString>
#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include <QtAlgorithms>

#include "../include/birthUnit.h"

void message( const QString name, int ndays, int years = 0 )
{
	QString str = QString::fromUtf8("До дня рождения объекта ") + name;

	if ( !ndays ) 
	{
		str = QString::fromUtf8("Сегодня объекту ") + name + QString::fromUtf8(" исполнилось ") + QString::number(years, 10) + QString::fromUtf8("!!!\nНе забудьте поздравить!");

		QMessageBox mb( "Birth [ver. 0.3]", str , QMessageBox::Information, QMessageBox::Ok | QMessageBox::Default, 0, 0 );
		mb.exec();
		return;
	}

	switch (ndays)
	{
		case 1: str += QString::fromUtf8(" остался один день!"); break;
		case 2: str += QString::fromUtf8(" осталось два дня!"); break;
		case 3: str += QString::fromUtf8(" осталось три дня!"); break;
		case 4: str += QString::fromUtf8(" осталось четыре дня!"); break;
		case 5: str += QString::fromUtf8(" осталось пять дней!"); break;
		case 6: str += QString::fromUtf8(" осталось шесть дней!"); break;
		case 7: str += QString::fromUtf8(" осталась неделя!"); break;
	}

	if ( ndays )
	{
		QMessageBox mb( "Birth [ver. 0.3]", str, QMessageBox::Information, QMessageBox::Ok | QMessageBox::Default, 0, 0 );
		mb.exec();
	}
}

int run_check()
{
	QList<birthItem> birthList;
	loadDataFromFile( birthList );

	QDate today = QDate::currentDate();
	QDate tmp;

        qSort(birthList.begin(), birthList.end());

	QList<birthItem>::iterator i;
	for (i = birthList.begin(); i != birthList.end(); ++i)
	{
		tmp.setDate( today.year(), (i->getbirthday()).month(), (i->getbirthday()).day() );
		if ( today == tmp )
		{
			message( i->getname(), 0, (today.year() - (i->getbirthday()).year()) );
			continue;
		}

		if ( (today.daysTo(tmp) <= 7 ) && (today.daysTo(tmp) >= 0) ) message( i->getname(), today.daysTo(tmp));
	}

	return 0;
}

int run_help() {
    qDebug() << "usage: birth [options]";
    qDebug() << "  -c  --check\t\tcheck for the nearest birthdays and exit";
    qDebug() << "  -h  --help\t\tprint this usage and exit";
    qDebug() << "  -v  --version\t\tprint version information and exit";
    return 0;
}

int run_version() {
    qDebug() << "Birth" << birth_version;
    qDebug() << "Qt version:" << qVersion();
    return 0;
}
