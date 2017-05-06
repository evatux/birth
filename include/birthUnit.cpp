#include "birthUnit.h"

birthItem& birthItem::operator= (const birthItem& eq)
{
	if ( this != &eq )
	{
		this->name = eq.name;
		this->birthday = eq.birthday;
	}

	return *this;
};

int birthItem::operator < (const birthItem& b) const {
    return ( ( birthday.month()  < b.birthday.month() ) ||
             ( birthday.month() == b.birthday.month() && birthday.day()  < b.birthday.day() ) ||
             ( birthday.month() == b.birthday.month() && birthday.day() == b.birthday.day() && birthday.year() < b.birthday.year() )
           );
}

QDataStream& operator<< (QDataStream& out, const birthItem& item)
{
	out << item.name << item.birthday;
	return out;
}

QDataStream& operator>> (QDataStream& in, birthItem& item)
{
	in >> item.name >> item.birthday;
	return in;
}

void loadDataFromFile( QList<birthItem>& birthList )
{
	birthItem tmpItem;

	birthList.clear();

	QFile file( QDir::homePath() + "/.birth.dat");
	if ( !file.exists() )
	{
		ioError(file, "File %1 doesn't exist");
		file.open(QIODevice::WriteOnly);
		QDataStream out(&file);
		out.setVersion(7);	
		out << MagicNumber;	
		file.close();
		return;
	}
	if ( !file.open(QIODevice::ReadOnly) ) { ioError(file, "Cannot open file %1 for reading"); return; };

	QDataStream in(&file);
	in.setVersion(7);

	quint32 magic;
	in >> magic;
	if (magic != MagicNumber)
	{
		ioError(file, "File %1 is not a Birth Data Base file");
		return;
	}


	while ( !in.atEnd() )
	{
		in >> tmpItem;
		birthList.push_back(tmpItem);
	}

	file.close();
}

void ioError(const QFile& file, const QString& message)
{
	error(file, message + ": " + file.errorString());
}

void error(const QFile& file, const QString& message)
{
	QMessageBox::warning(0, "Birth", message.arg( file.fileName() ) );
}
/*
void birthItem::writeToStream(QDataStream& out)
{
  list<Drawing>::const_iterator it = drawings.begin();
  while (it != drawings.end()) {
    out << *it;
    ++it;
  }
}*/
