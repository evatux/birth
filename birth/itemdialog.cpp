// version 0.1

#if QT_VERSION < 0x050000
#include <QtGui>
#else
#include <QtWidgets>
#endif

#include "itemdialog.h"

ItemDialog::ItemDialog(QWidget *parent = 0) : QDialog(parent) 
{
	setWindowTitle(QString::fromUtf8("Добавление/Изменение данных"));
	nameLabel = new QLabel(QString::fromUtf8("Имя: "), this);
	birthdayLabel = new QLabel(QString::fromUtf8("Дата рождения: "), this);

	nameEdit = new QLineEdit(this);
	nameLabel->setBuddy(nameEdit);
	birthdayEdit = new QDateEdit(QDate::currentDate(), this);
	birthdayEdit->setDisplayFormat("yyyy-MM-dd");
	birthdayLabel->setBuddy(birthdayEdit);

	button = new QPushButton(QString::fromUtf8("Сохранить"), this);
	button->setDefault(true);
	button->setEnabled(false);
	closeButton = new QPushButton(QString::fromUtf8("Выход"), this);

	connect(nameEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enablebutton(const QString &)));
	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout *topLayout1 = new QHBoxLayout;
	topLayout1->addWidget(nameLabel);
	topLayout1->addWidget(nameEdit);
	QHBoxLayout *topLayout2 = new QHBoxLayout;
	topLayout2->addWidget(birthdayLabel);
	topLayout2->addWidget(birthdayEdit);
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch(1);
	bottomLayout->addWidget(button);
	bottomLayout->addWidget(closeButton);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setMargin(11);
	mainLayout->setSpacing(6);
	mainLayout->addLayout(topLayout1);
	mainLayout->addLayout(topLayout2);
	mainLayout->addLayout(bottomLayout);
}

void ItemDialog::prepare (QString name, QDate birthday, int _index)
{
    if (isAdd) {
        nameEdit->setText("");
        birthdayEdit->setDate(QDate::currentDate());
        return;
    }

    index = _index;
    nameEdit->setText(name);
    birthdayEdit->setDate(birthday);
}

void ItemDialog::buttonClicked()
{
	QString name = nameEdit->text();
	QDate birthday = birthdayEdit->date();
	if ( isAdd ) emit getaItem(name, birthday);
	else emit geteItem(name, birthday, index);
        this->hide();
}


void ItemDialog::enablebutton(const QString &text)
{
	button->setEnabled(!text.isEmpty());
}

