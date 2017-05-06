// version 0.1

#ifndef ZODIACUNIT_H
#define ZODIACUNIT_H

#include <QString>
#include <QDate>

int GetNChineseSignOfZodiac( const int, const int );
QString GetChineseSignOfZodiac( const int, const int );
QString GetDruidSignOfZodiac( const int, const int );
QString GetFlowerSignOfZodiac( const int, const int );
QString GetZodiacText( const int, const int );

QString GetYearAnimalSign(const int);
QString GetYearElementSign(const int);

#endif
