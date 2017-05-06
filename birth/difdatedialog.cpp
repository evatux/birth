// version 0.1

#include <QtGui>

#include "difdatedialog.h"

DifDateDialog::DifDateDialog(QWidget *parent = 0) : QDialog(parent)
{
        setWindowTitle(QString::fromUtf8("Разница между датами"));

        startDateLabel = new QLabel(QString::fromUtf8("Начальная дата: "), this);
        startDateEdit = new QDateEdit(this);
        startDateEdit->setDate(QDate::currentDate());
        startDateEdit->setCalendarPopup(true);
        startDateEdit->setDisplayFormat("yyyy-MM-dd");
        startDateLabel->setBuddy(startDateEdit);
        connect(startDateEdit, SIGNAL(dateChanged(QDate)), SLOT(dateChng(QDate)));

        finishDateLabel = new QLabel(QString::fromUtf8("Конечная дата: "), this);
        finishDateEdit = new QDateEdit(this);
        finishDateEdit->setDate(QDate::currentDate());
        finishDateEdit->setCalendarPopup(true);
        finishDateEdit->setDisplayFormat("yyyy-MM-dd");
        finishDateLabel->setBuddy(finishDateEdit);
        connect(finishDateEdit, SIGNAL(dateChanged(QDate)), SLOT(dateChng(QDate)));

        difDateLabel = new QLabel(QString::fromUtf8("Разница: "), this);
        difDateSpinBox = new QSpinBox(this);
        difDateSpinBox->setValue(0);
        difDateSpinBox->setMaximum(4000000);
        difDateSpinBox->setMinimum(-4000000);
        difDateLabel->setBuddy(difDateSpinBox);
        connect(difDateSpinBox, SIGNAL(valueChanged(int)), SLOT(spinChng(int)));

        fixFinishDateCheckBox = new QCheckBox(QString::fromUtf8("Зафиксировать конечную дату"), this);
        fixFinishDateCheckBox->setChecked(false);

        closeButton = new QPushButton(QString::fromUtf8("Закрыть"), this);
        connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

        QHBoxLayout *startLayout = new QHBoxLayout;
        startLayout->addWidget(startDateLabel);
        startLayout->addWidget(startDateEdit);

        QHBoxLayout *finishLayout = new QHBoxLayout;
        finishLayout->addWidget(finishDateLabel);
        finishLayout->addWidget(finishDateEdit);

        QHBoxLayout *difLayout = new QHBoxLayout;
        difLayout->addWidget(difDateLabel);
        difLayout->addWidget(difDateSpinBox);

        QHBoxLayout *bottomLayout = new QHBoxLayout;
        bottomLayout->addStretch(1);
        bottomLayout->addWidget(closeButton);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        //mainLayout->setMargin(11);
        //mainLayout->setSpacing(6);
        mainLayout->addLayout(startLayout);
        mainLayout->addLayout(finishLayout);
        mainLayout->addLayout(difLayout);
        mainLayout->addWidget(fixFinishDateCheckBox);
        mainLayout->addLayout(bottomLayout);
}

void DifDateDialog::dateChng(QDate date ) {
//    if (!fixFinishDateCheckBox->isChecked()) {
        difDateSpinBox->setValue(startDateEdit->date().daysTo(finishDateEdit->date()));
//    } else {
//        QDate date = finishDateEdit->date();
//        date.addDays(-difDateSpinBox->value());
//        startDateEdit->setDate(date);
//    }
}

void DifDateDialog::spinChng(int val) {
    if (!fixFinishDateCheckBox->isChecked()) {
        finishDateEdit->setDate(startDateEdit->date().addDays(val));
        //difDateSpinBox->setValue(startDateEdit->date().daysTo(finishDateEdit->date()));
    } else {
        startDateEdit->setDate(finishDateEdit->date().addDays(-val));
    }
}
