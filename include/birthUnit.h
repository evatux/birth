// version 0.3

#ifndef BIRTHUNIT_H
#define BIRTHUNIT_H

#include <QString>
#include <QDate>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QtGlobal>

class birthItem
{
	QString name;
	QDate	birthday;
public:
        birthItem() {}
        birthItem(QString _name, QDate _birthday) { name = _name; birthday = _birthday; }
        ~birthItem() {}

        void setname(QString _name) { name = _name; }
        void setbirthday(QDate _birthday) { birthday = _birthday; }

        QString getname()	{ return name; }
        QDate	getbirthday()	{ return birthday; }
        int	getday()	{ return birthday.day(); }
        int	getmonth()	{ return birthday.month(); }
        int	getyear()	{ return birthday.year(); }

	birthItem& operator = (const birthItem&);

        int     operator < (const birthItem&) const;

	friend Q_CORE_EXPORT QDataStream& operator << (QDataStream&, const birthItem&);
	friend Q_CORE_EXPORT QDataStream& operator >> (QDataStream&, birthItem&);
};

const QString birth_version = "0.3.5 alpha";
const quint32 MagicNumber = 0xbd3c8ffe;
//const QString appPath= "/root/c/qt/birth/birth_" + birth_version + "/editor/";

void loadDataFromFile( QList<birthItem>& );

void error(const QFile&, const QString&);
void ioError(const QFile&, const QString&);

#endif
