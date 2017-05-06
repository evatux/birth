// version 0.1

#include <QtGui>

#include "zodiacdialog.h"
#include <QDir>
#include <QMessageBox>

ZodiacDialog::ZodiacDialog(QWidget *parent = 0) : QDialog(parent)
{
	setWindowTitle(QString::fromUtf8("Знак зодиака"));
        setWindowIcon(QIcon(":/zodiak/zodiak.ico"));
	birthdayLabel = new QLabel(QString::fromUtf8("Дата рождения: "), this);

	birthdayEdit = new QDateEdit(QDate::currentDate(), this);
	birthdayEdit->setDisplayFormat("yyyy-MM-dd");
	birthdayLabel->setBuddy(birthdayEdit);

	QString str = GetZodiacText( QDate::currentDate().day(), QDate::currentDate().month() );
        str += QString::fromUtf8("\nГод: ") + GetYearAnimalSign(QDate::currentDate().year()) + "(" + GetYearElementSign(QDate::currentDate().year()) + ")";
	text = new QPlainTextEdit(str);

        str = ":/zodiak/" + QString::number(GetNChineseSignOfZodiac( QDate::currentDate().day(), QDate::currentDate().month() ), 10) + ".bmp";

	resultImage = new QLabel();
	resultImage->setPixmap(QPixmap( str ));

	closeButton = new QPushButton(QString::fromUtf8("Закрыть"), this);

	connect(birthdayEdit, SIGNAL(dateChanged ( const QDate& )), this, SLOT(dateChng( const QDate& )));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout *topLayout1 = new QHBoxLayout;
	topLayout1->addWidget(birthdayLabel);
	topLayout1->addWidget(birthdayEdit);
	QHBoxLayout *topLayout2 = new QHBoxLayout;
	topLayout2->addWidget(text);
	topLayout2->addWidget(resultImage);
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch(1);
	bottomLayout->addWidget(closeButton);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setMargin(11);
	mainLayout->setSpacing(6);
	mainLayout->addLayout(topLayout1);
	mainLayout->addLayout(topLayout2);
	mainLayout->addLayout(bottomLayout);
}

void ZodiacDialog::prepare( const QDate date )
{
	birthdayEdit->setDate(date);
}

void ZodiacDialog::dateChng( const QDate & date )
{
	QString str = GetZodiacText( date.day(), date.month() );
        str += QString::fromUtf8("\nГод: ") + GetYearAnimalSign(date.year()) + "(" + GetYearElementSign(date.year()) + ")";
        text -> setPlainText( str );

        str = ":/zodiak/" + QString::number(GetNChineseSignOfZodiac( date.day(), date.month() ), 10) + ".bmp";

        resultImage->setPixmap(QPixmap(str));
}
