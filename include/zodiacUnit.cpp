#include "zodiacUnit.h"

int GetNChineseSignOfZodiac( const int Day, const int Month )
{
	if (((Month == 12) && (Day >= 22)) || ((Month == 1) && (Day <= 20))) return 1;
	if (((Month == 1) && (Day >= 21)) || ((Month == 2) && (Day <= 20))) return 2;
	if (((Month == 2) && (Day >= 21)) || ((Month == 3) && (Day <= 20))) return 3;
	if (((Month == 3) && (Day >= 21)) || ((Month == 4) && (Day <= 20))) return 4;
	if (((Month == 4) && (Day >= 21)) || ((Month == 5) && (Day <= 20))) return 5;
	if (((Month == 5) && (Day >= 21)) || ((Month == 6) && (Day <= 21))) return 6;
	if (((Month == 6) && (Day >= 22)) || ((Month == 7) && (Day <= 22))) return 7;
	if (((Month == 7) && (Day >= 23)) || ((Month == 8) && (Day <= 23))) return 8;
	if (((Month == 8) && (Day >= 24)) || ((Month == 9) && (Day <= 23))) return 9;
	if (((Month == 9) && (Day >= 24)) || ((Month == 10) && (Day <= 23))) return 10;
	if (((Month == 10) && (Day >= 24)) || ((Month == 11) && (Day <= 22))) return 11;
	if (((Month == 11) && (Day >= 23)) || ((Month == 12) && (Day <= 21))) return 12;
}

QString GetChineseSignOfZodiac( const int Day, const int Month )
{
	if (((Month == 12) && (Day >= 22)) || ((Month == 1) && (Day <= 20))) return QString::fromUtf8("Козерог");
	if (((Month == 1) && (Day >= 21)) || ((Month == 2) && (Day <= 20))) return QString::fromUtf8("Водолей");
	if (((Month == 2) && (Day >= 21)) || ((Month == 3) && (Day <= 20))) return QString::fromUtf8("Рыбы");
	if (((Month == 3) && (Day >= 21)) || ((Month == 4) && (Day <= 20))) return QString::fromUtf8("Овен");
	if (((Month == 4) && (Day >= 21)) || ((Month == 5) && (Day <= 20))) return QString::fromUtf8("Телец");
	if (((Month == 5) && (Day >= 21)) || ((Month == 6) && (Day <= 21))) return QString::fromUtf8("Близнецы");
	if (((Month == 6) && (Day >= 22)) || ((Month == 7) && (Day <= 22))) return QString::fromUtf8("Рак");
	if (((Month == 7) && (Day >= 23)) || ((Month == 8) && (Day <= 23))) return QString::fromUtf8("Лев");
	if (((Month == 8) && (Day >= 24)) || ((Month == 9) && (Day <= 23))) return QString::fromUtf8("Дева");
	if (((Month == 9) && (Day >= 24)) || ((Month == 10) && (Day <= 23))) return QString::fromUtf8("Весы");
	if (((Month == 10) && (Day >= 24)) || ((Month == 11) && (Day <= 22))) return QString::fromUtf8("Скорпион");
	if (((Month == 11) && (Day >= 23)) || ((Month == 12) && (Day <= 21))) return QString::fromUtf8("Стрелец");
}

QString GetDruidSignOfZodiac( const int Day, const int Month )
{
	if ((Month == 12) && ((Day == 21) || (Day == 22)) ) return QString::fromUtf8("Бук");
	if (((Month == 12) && (Day >= 23)) || ((Month == 1) && (Day <= 1)) || ((Month == 6) && (Day >= 25)) || ((Month == 7) && (Day <= 4)) ) return QString::fromUtf8("Яблоня");
	if (((Month == 1) && (Day >= 2) && (Day <= 11)) || ((Month == 7) && (Day >= 5) && (Day <= 14)) ) return QString::fromUtf8("Пихта");
	if (((Month == 1) && (Day >= 12) && (Day <= 24)) || ((Month == 7) && (Day >= 15) && (Day <= 25)) ) return QString::fromUtf8("Вяз");
	if (((Month == 1) && (Day >= 25)) || ((Month == 2) && (Day <= 3)) || ((Month == 7) && (Day >= 26)) || ((Month == 8) && (Day <= 4)) ) return QString::fromUtf8("Кипарис");
	if (((Month == 2) && (Day >= 4) && (Day <= 8)) || ((Month == 8) && (Day >= 5) && (Day <= 13)) ) return QString::fromUtf8("Тополь");
	if (((Month == 2) && (Day >= 9) && (Day <= 18)) || ((Month == 8) && (Day >= 14) && (Day <= 23)) ) return QString::fromUtf8("Картас Южный");
	if (((Month == 2) && (Day >= 19) && (Day <= 29)) || ((Month == 8) && (Day >= 24)) || ((Month == 9) && (Day <= 2)) ) return QString::fromUtf8("Сосна");
	if (((Month == 3) && (Day >= 1) && (Day <= 10)) || ((Month == 9) && (Day >= 3) && (Day <= 12)) ) return QString::fromUtf8("Ива");
	if (((Month == 3) && (Day >= 11) && (Day <= 20)) || ((Month == 9) && (Day >= 13) && (Day <= 22)) ) return QString::fromUtf8("Липа");
	if ((Month == 3) && (Day == 21) ) return QString::fromUtf8("Дуб");
	if ((Month == 9) && (Day == 23) ) return QString::fromUtf8("Маслина");
	if (((Month == 3) && (Day >= 22) && (Day <= 31)) || ((Month == 9) && (Day >= 24)) || ((Month == 10) && (Day <= 3)) ) return QString::fromUtf8("Орешник");
	if (((Month == 4) && (Day >= 1) && (Day <= 10)) || ((Month == 10) && (Day >= 4) && (Day <= 13)) ) return QString::fromUtf8("Рябина");
	if (((Month == 4) && (Day >= 11) && (Day <= 20)) || ((Month == 10) && (Day >= 14) && (Day <= 23)) ) return QString::fromUtf8("Клен");
	if (((Month == 4) && (Day >= 21) && (Day <= 30)) || ((Month == 10) && (Day >= 24)) || ((Month == 11) && (Day <= 2)) ) return QString::fromUtf8("Орех");
	if (((Month == 5) && (Day >= 1) && (Day <= 14)) || ((Month == 11) && (Day >= 3) && (Day <= 11)) ) return QString::fromUtf8("Жасмин");
	if (((Month == 5) && (Day >= 15) && (Day <= 24)) || ((Month == 11) && (Day >= 12) && (Day <= 21)) ) return QString::fromUtf8("Каштан");
	if (((Month == 5) && (Day >= 23)) || ((Month == 6) && (Day <= 3)) || ((Month == 11) && (Day >= 22)) || ((Month == 12) && (Day <= 1)) ) return QString::fromUtf8("Ясень");
	if (((Month == 6) && (Day >= 4) && (Day <= 13)) || ((Month == 12) && (Day >= 2) && (Day <= 11)) ) return QString::fromUtf8("Граб");
	if (((Month == 6) && (Day >= 14) && (Day <= 23)) || ((Month == 12) && (Day >= 12) && (Day <= 21)) ) return QString::fromUtf8("Инжир");
	if ((Month == 6) && (Day == 24) ) return QString::fromUtf8("Береза");
}

QString GetFlowerSignOfZodiac( const int Day, const int Month )
{
	if ((Month == 1) && (Day >= 1) && (Day <= 10) ) return QString::fromUtf8("Горечавка желтая");
	if ((Month == 1) && (Day >= 11) && (Day <= 20) ) return QString::fromUtf8("Чертополох");
	if ((Month == 1) && (Day >= 21) && (Day <= 31) ) return QString::fromUtf8("Бессмертник");
	if ((Month == 2) && (Day >= 1) && (Day <= 10) ) return QString::fromUtf8("Омела");
	if ((Month == 2) && (Day >= 11) && (Day <= 19) ) return QString::fromUtf8("Красавка");
	if ((Month == 2) && (Day >= 20) && (Day <= 29) ) return QString::fromUtf8("Мимоза");
	if ((Month == 3) && (Day >= 1) && (Day <= 10) ) return QString::fromUtf8("Мак");
	if ((Month == 3) && (Day >= 11) && (Day <= 20) ) return QString::fromUtf8("Лилия");
	if ((Month == 3) && (Day >= 21) && (Day <= 31) ) return QString::fromUtf8("Наперстянка");
	if ((Month == 4) && (Day >= 1) && (Day <= 10) ) return QString::fromUtf8("Магнолия");
	if ((Month == 4) && (Day >= 11) && (Day <= 20) ) return QString::fromUtf8("Гортензия");
	if ((Month == 4) && (Day >= 21) && (Day <= 30) ) return QString::fromUtf8("Георгин");
	if ((Month == 5) && (Day >= 1) && (Day <= 10) ) return QString::fromUtf8("Ландыш");
	if ((Month == 5) && (Day >= 11) && (Day <= 21) ) return QString::fromUtf8("Портулак");
	if ((Month == 5) && (Day >= 22) && (Day <= 31) ) return QString::fromUtf8("Ромашка");
	if ((Month == 6) && (Day >= 1) && (Day <= 11) ) return QString::fromUtf8("Колокольчик");
	if ((Month == 6) && (Day >= 12) && (Day <= 21) ) return QString::fromUtf8("Маргаритка");
	if (((Month == 6) && (Day >= 22)) || ((Month == 7) && (Day <= 1)) ) return QString::fromUtf8("Тюльпан");
	if ((Month == 7) && (Day >= 2) && (Day <= 12) ) return QString::fromUtf8("Кувшинка");
	if ((Month == 7) && (Day >= 13) && (Day <= 23) ) return QString::fromUtf8("Фиалка");
	if (((Month == 7) && (Day >= 24)) || ((Month == 8) && (Day <= 2)) ) return QString::fromUtf8("Шиповник");
	if ((Month == 8) && (Day >= 3) && (Day <= 12) ) return QString::fromUtf8("Подсолнух");
	if ((Month == 8) && (Day >= 13) && (Day <= 23) ) return QString::fromUtf8("Роза");
	if (((Month == 8) && (Day >= 24)) || ((Month == 9) && (Day <= 2)) ) return QString::fromUtf8("Дельфиниум");
	if ((Month == 9) && (Day >= 3) && (Day <= 11) ) return QString::fromUtf8("Гвоздика");
	if ((Month == 9) && (Day >= 12) && (Day <= 22) ) return QString::fromUtf8("Астра");
	if (((Month == 9) && (Day >= 23)) || ((Month == 10) && (Day <= 3)) ) return QString::fromUtf8("Вереск");
	if ((Month == 10) && (Day >= 4) && (Day <= 13) ) return QString::fromUtf8("Камелия");
	if ((Month == 10) && (Day >= 14) && (Day <= 23) ) return QString::fromUtf8("Сирень");
	if (((Month == 10) && (Day >= 24)) || ((Month == 11) && (Day <= 2)) ) return QString::fromUtf8("Фрезия");
	if ((Month == 11) && (Day >= 3) && (Day <= 12) ) return QString::fromUtf8("Орхидея");
	if ((Month == 11) && (Day >= 13) && (Day <= 22) ) return QString::fromUtf8("Лион");
	if (((Month == 11) && (Day >= 23)) || ((Month == 12) && (Day <= 2)) ) return QString::fromUtf8("Гладиолус");
	if ((Month == 12) && (Day >= 3) && (Day <= 12) ) return QString::fromUtf8("Одуванчик");
	if ((Month == 12) && (Day >= 13) && (Day <= 22) ) return QString::fromUtf8("Лотос");
	if ((Month == 12) && (Day >= 23) && (Day <= 31) ) return QString::fromUtf8("Эдельвейс");
}

QString GetZodiacText( const int Day, const int Month )
{
	QString str = QString::fromUtf8("По зодиакальному гороскопу - ");
	str += GetChineseSignOfZodiac( Day, Month );
	str += QString::fromUtf8("\nПо гороскопу друидов - ");
	str += GetDruidSignOfZodiac( Day, Month );
	str += QString::fromUtf8("\nПо цветочному гороскопу - ");
	str += GetFlowerSignOfZodiac( Day, Month );

	return str;
}

QString GetYearAnimalSign(const int Year)
{
	switch (Year % 12)
	{
		case 0: return QString::fromUtf8("Обезьяна");
		case 1: return QString::fromUtf8("Петух");
		case 2: return QString::fromUtf8("Собака");
		case 3: return QString::fromUtf8("Свинья");
		case 4: return QString::fromUtf8("Крыса");
		case 5: return QString::fromUtf8("Бык");
		case 6: return QString::fromUtf8("Тигр");
		case 7: return QString::fromUtf8("Кролик");
		case 8: return QString::fromUtf8("Дракон");
		case 9: return QString::fromUtf8("Змея");
		case 10: return QString::fromUtf8("Лошадь");
		case 11: return QString::fromUtf8("Коза");
	}
}

QString GetYearElementSign(const int Year)
{
	switch (Year % 10)
	{
		case 0: return QString::fromUtf8("Металл");
		case 1: return QString::fromUtf8("Металл");
		case 2: return QString::fromUtf8("Вода");
		case 3: return QString::fromUtf8("Вода");
		case 4: return QString::fromUtf8("Дерево");
		case 5: return QString::fromUtf8("Дерево");
		case 6: return QString::fromUtf8("Огонь");
		case 7: return QString::fromUtf8("Огонь");
		case 8: return QString::fromUtf8("Земля");
		case 9: return QString::fromUtf8("Земля");
	}
}
