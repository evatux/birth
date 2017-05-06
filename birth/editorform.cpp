// version 0.3.4

#include <QtGui>

#include "editorform.h"
#include "../include/birthUnit.h"
#include "birth.h"
#include <QProcess>
#include <QColor>
#include <QSettings>

EditorForm::EditorForm() //: settings(QApplication::organizationName(), QApplication::applicationName())
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	idialog = 0;
	zdialog = 0;
	vdialog = 0;
        ddialog = 0;

	calendarWidget = new QCalendarWidget;
        //calendarWidget->setFixedSize(350, 208);
        //calendarWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        calendarWidget->setFirstDayOfWeek(Qt::Monday);
	lastYear = calendarWidget->yearShown();
	seenYears.push_back(lastYear);
        connect(calendarWidget, SIGNAL(currentPageChanged(int, int)), SLOT(reformatCalendarPage(int, int)));
        connect(calendarWidget, SIGNAL(selectionChanged()), SLOT(fillViewGroupBox()));
        //connect(calendarWidget, SIGNAL(currentPageChanged(int, int)), this, SLOT(fillViewGroupBox())); // ??remove??

	itemList = new QListWidget;

        connect(itemList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(showOnCalendar(QListWidgetItem*)));

	createViewGroupBox();

        connect(anotherListWidget, SIGNAL(itemSelectionChanged()), SLOT(anotherListWidgetSelectionChanged()));

        findEdit = new QLineEdit;

        connect(findEdit, SIGNAL(textChanged(QString)), SLOT(searchItems(QString)));

	createActions();
	createMenus();
	createContextMenu();	

	QHBoxLayout *topLayout = new QHBoxLayout;
        topLayout->addWidget(calendarWidget, 1);
        //topLayout->addStretch(1);
        topLayout->addWidget(viewGroupBox, 2);

        QHBoxLayout *bottomLayout = new QHBoxLayout;
        bottomLayout->addStretch(1); //addSpacerItem(QSpacerItem());
        bottomLayout->addWidget(findEdit);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setMargin(8);
	mainLayout->setSpacing(8);
        mainLayout->addLayout(topLayout, 1);
        mainLayout->addWidget(itemList, 2);
        mainLayout->addLayout(bottomLayout);

	widget->setLayout(mainLayout);

	setWindowTitle(QString::fromUtf8("Настройки"));
        setMinimumSize(800, 600);
        resize(800, 600);

	loadData();
	fillCalendar(0,0);

	fillViewGroupBox();

        /*for (int i = 0; i < itemList->count(); i++) {
            itemList->item(i)->setBackgroundColor(QColor(QRgb("#323232")));
        }*/
}

void EditorForm::addItem()
{
	if (!idialog)
	{
		idialog = new ItemDialog(this);
                connect(idialog, SIGNAL(getaItem(QString, QDate)), SLOT(add(QString, QDate)));
                connect(idialog, SIGNAL(geteItem(QString, QDate, int)), SLOT(edit(QString, QDate, int)));
	}

	idialog -> isAdd = true;

	idialog->show();
	idialog->raise();
	idialog->activateWindow();
}

void EditorForm::add(QString name, QDate birthday)
{
	birthList.push_back(birthItem(name, birthday));
	itemList->addItem( birthday.toString("yyyy-MM-dd") + "        " + name );
	fillCalendar(birthday.month(), birthday.day());
	saveData();

}

void EditorForm::editItem()
{
	if ( itemList->currentRow() == -1 )
	{
		QMessageBox::critical(this, QString("Error"), QString::fromUtf8("Не выделена запись для изменения"), QMessageBox::Ok,QMessageBox::Ok);
		return;
	}

	if (!idialog)
	{
		idialog = new ItemDialog(this);
		connect(idialog, SIGNAL(getaItem(QString, QDate)), this, SLOT(add(QString, QDate)));
		connect(idialog, SIGNAL(geteItem(QString, QDate, int)), this, SLOT(edit(QString, QDate, int)));
	}

	idialog -> isAdd = false;

	int i = itemList->currentRow();
        idialog->prepare(birthList[i].getname(), birthList[i].getbirthday(), i);

	idialog->show();
	idialog->raise();
	idialog->activateWindow();
}

void EditorForm::edit(QString name, QDate birthday, int index)
{
	int _month = birthList[index].getmonth();
	int _day   = birthList[index].getday();

	birthList[index] = birthItem(name, birthday);
	itemList->item(index)->setText(birthday.toString("yyyy-MM-dd") + "        " + name);
	fillCalendar(birthday.month(), birthday.day());

	if (findByBirthday(_month, _day, 0) == -1) clearCalendar(_month, _day);

	saveData();
}

void EditorForm::deleteItem()
{
	int index;
	if ( (index = itemList->currentRow()) == -1 )
	{
		QMessageBox::critical(this, QString("Error"), QString::fromUtf8("Не выделена запись для удаления"), QMessageBox::Ok,QMessageBox::Ok);
		return;
	}

	QString text = QString::fromUtf8("Вы уверены, что хотите удалить запись: \n'");
	text += birthList[index].getname();
	text += QString::fromUtf8("' ?");

	int ret = QMessageBox::warning(this, QString::fromUtf8("Удаление записи"),  text, QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

	if ( ret == QMessageBox::No) return;

	int _month = birthList[index].getmonth();
	int _day   = birthList[index].getday();

	birthList.removeAt(index);

	if (findByBirthday(_month, _day, 0) == -1) clearCalendar(_month, _day);

	fillList();
	saveData();	
}

void EditorForm::showOnCalendar(QListWidgetItem* plwi) {
    QDate date = QDate(QDate::currentDate().year(), birthList[(itemList->row(plwi))].getmonth(),
                       birthList[(itemList->row(plwi))].getday());
    if (date < QDate::currentDate()) date = date.addYears(1);
    calendarWidget->setSelectedDate(date);
}

void EditorForm::runBirthday()
{
        run_check();
}

void EditorForm::searchItems(QString str) {
    if (!str.length()) {
        for (int i = 0; i < itemList->count(); i++) {
            itemList->item(i)->setBackgroundColor(QColor("white"));
        }
        QPalette pal;
        findEdit->setPalette(pal);
        return;
    }
    int c = 1;
    for (int i = 0; i < itemList->count(); i++) {
        if (itemList->item(i)->text().contains(str, Qt::CaseInsensitive)) {
            itemList->item(i)->setBackgroundColor(QColor("#323232"));
            if (c) {
                itemList->scrollToItem(itemList->item(i));
                c--;
                QPalette pal;
                findEdit->setPalette(pal);
            }
        }
        else
            itemList->item(i)->setBackgroundColor(QColor("white"));
    }
    if (c) {
        QPalette pal;
        pal.setColor(QPalette::Base, QColor("red"));
        findEdit->setPalette(pal);
    }
}

void EditorForm::signofZodiak()
{
	if (!zdialog)
		zdialog = new ZodiacDialog(this);

	if ( itemList->currentRow() != -1 ) zdialog->prepare( birthList[itemList->currentRow()].getbirthday() );

	zdialog->show();
	zdialog->raise();
	zdialog->activateWindow();
}

void EditorForm::viewtoMonth()
{
	if (!vdialog)
		vdialog = new ViewMonthDialog(this);

	if ( itemList->count() != -1 ) vdialog->fillList( birthList );

	vdialog->show();
	vdialog->raise();
	vdialog->activateWindow();
}

void EditorForm::difDate() {
    if (!ddialog)
        ddialog = new DifDateDialog(this);

    ddialog->show();
    ddialog->raise();
    ddialog->activateWindow();
}

void EditorForm::sortItems() {
    if (sortNonAct->isChecked()) s_type = s_non;
    if (sortByNameAct->isChecked()) s_type = s_name;
    if (sortByDateAct->isChecked()) s_type = s_date;
    if (sortByAgeAct->isChecked()) s_type = s_age;
    //
    //
    //
    //
    //
    //
}

void EditorForm::saveSettings() {
    settings.beginGroup("/Settings");

    settings.setValue("/width", width());
    settings.setValue("/height", height());
    settings.setValue("/pos_x", x());
    settings.setValue("/pos_y", y());

    settings.setValue("/sortType", s_type);

    settings.endGroup();
}

void EditorForm::fillViewGroupBox()
{
	anotherListWidget->clear();
	anotherNList.clear();
	QDate curDate(calendarWidget->selectedDate());
	int i = findByBirthday(curDate.month(), curDate.day(), 0);
	if ( i == -1)
	{
		nameLabel->setText(QString::fromUtf8("Объект: ~~~"));
		birthdayLabel->setText(QString::fromUtf8("Дата рождения: ~~~"));
		yearsLabel->setText(QString::fromUtf8("Исполнилось лет: ~~~"));
		moreinfLabel->setText(QString::fromUtf8("Доп. информация: ~~~"));
		lcdNumber->display(0);
	}
	else
	{
		do
		{
			anotherNList.push_back(i);
			anotherListWidget->addItem(birthList[i].getname());
			i = findByBirthday(curDate.month(), curDate.day(), i+1);
		}
		while ( i != -1 );

		anotherListWidgetSelectionChanged(anotherNList[0]);

		//nameLabel->setText(QString::fromUtf8("Объект: ") + birthList[i].getname());
		//i = findByBirthday(curDate.month(), curDate.day(), i+1);
	}
}

void EditorForm::reformatCalendarPage(int year, int month)
{
	if (year != lastYear) {
		if (!seenYears.contains(year)) {
			fillCalendar(0, 0);
			lastYear = year;
			seenYears.push_back(lastYear);
		}
	}
}

void EditorForm::fillCalendar(int month = 0, int day = 0)
{
	QTextCharFormat birthFormat;
	birthFormat.setForeground(Qt::green);
	if (!(month && day))
	{
		for (QList<birthItem>::iterator i = birthList.begin();  i != birthList.end(); ++i)
			calendarWidget->setDateTextFormat(QDate(calendarWidget->yearShown(), i->getmonth(), i->getday()), birthFormat);
	} else
	{
		for (int i = 0; i < seenYears.count(); i++)
		{
			QDate __date(seenYears[i], month, day);
			calendarWidget->setDateTextFormat(__date, birthFormat);
		}
	}
}

void EditorForm::clearCalendar(int month = 0, int day = 0)
{
	if (month && day)
	{
		QTextCharFormat birthFormat;
		for (int i = 0; i < seenYears.count(); i++)
		{
			QDate __date(seenYears[i], month, day);
			if ( (__date.dayOfWeek() == Qt::Saturday) || (__date.dayOfWeek() == Qt::Sunday) ) birthFormat.setForeground(Qt::red);
				else birthFormat.setForeground(Qt::black);
			calendarWidget->setDateTextFormat(__date, birthFormat);
		}
	}
}

void EditorForm::anotherListWidgetSelectionChanged()
{
	if (anotherListWidget->currentRow () >= 0)
		anotherListWidgetSelectionChanged(anotherNList[anotherListWidget->currentRow ()]);
}

void EditorForm::about()
{
	QMessageBox::about(this, QString::fromUtf8("О Birth"),
                QString::fromUtf8("<b>Birth [ver. ") + birth_version + QString::fromUtf8("]</b> - ") +
                        QString::fromUtf8("Программа-напоминалка о днях рождения друзей и не только...  ^_^"));
}

void EditorForm::createActions()
{
//	File
	addItemAct = new QAction(QString::fromUtf8("&Добавить"), this);
	addItemAct->setShortcut(QString::fromUtf8("Ctrl+A"));
	addItemAct->setStatusTip(QString::fromUtf8("Добавить новую запись о дне рождения"));
	connect(addItemAct, SIGNAL(triggered()), this, SLOT(addItem()));

	editItemAct = new QAction(QString::fromUtf8("&Изменить"), this);
	editItemAct->setShortcut(QString::fromUtf8("Ctrl+E"));
	editItemAct->setStatusTip(QString::fromUtf8("Изменить выделенную запись"));
	connect(editItemAct, SIGNAL(triggered()), this, SLOT(editItem()));

	deleteItemAct = new QAction(QString::fromUtf8("&Удалить"), this);
	deleteItemAct->setShortcut(QString::fromUtf8("Ctrl+D"));
	deleteItemAct->setStatusTip(QString::fromUtf8("Удалить выделенную запись"));
	connect(deleteItemAct, SIGNAL(triggered()), this, SLOT(deleteItem()));

	runBirthdayAct = new QAction(QString::fromUtf8("&Проверить"), this);
	runBirthdayAct->setShortcut(QString::fromUtf8("Ctrl+R"));
	runBirthdayAct->setStatusTip(QString::fromUtf8("Собственно запуск центральной программы"));
	connect(runBirthdayAct, SIGNAL(triggered()), this, SLOT(runBirthday()));
	
	QFont boldFont = runBirthdayAct->font();
	boldFont.setBold(true);
	runBirthdayAct->setFont(boldFont);

	exitAct = new QAction(QString::fromUtf8("&Выход"), this);
	exitAct->setShortcut(QString::fromUtf8("Ctrl+Q"));
	exitAct->setStatusTip(QString::fromUtf8("Выйти из программы"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

//	Tools
	signofZodiakAct = new QAction(QString::fromUtf8("Знак зодиака"), this);
	signofZodiakAct->setShortcut(QString::fromUtf8("Ctrl+S"));
	signofZodiakAct->setStatusTip(QString::fromUtf8("Определение знака зодиака по дате рождения"));
	connect(signofZodiakAct, SIGNAL(triggered()), this, SLOT(signofZodiak()));

	viewtoMonthAct = new QAction(QString::fromUtf8("На месяц вперед"), this);
	viewtoMonthAct->setShortcut(QString::fromUtf8("Ctrl+M"));
	viewtoMonthAct->setStatusTip(QString::fromUtf8("Просмотр ближайших событий (на 30 дней вперед)"));
	connect(viewtoMonthAct, SIGNAL(triggered()), this, SLOT(viewtoMonth()));

        difDateAct = new QAction(QString::fromUtf8("Разница между датами"), this);
        difDateAct->setShortcut(QString::fromUtf8("Ctrl+I"));
        difDateAct->setStatusTip(QString::fromUtf8("Калькулятор для вычисления количества дней между датами"));
        connect(difDateAct, SIGNAL(triggered()), this, SLOT(difDate()));

//      Tools -> settings
        sortNonAct = new QAction(QString::fromUtf8("Без сортировки"), this);
        sortNonAct->setStatusTip(QString::fromUtf8("Элементы в порядке их добавления"));
        sortNonAct->setCheckable(true);
        connect(sortNonAct, SIGNAL(triggered()), SLOT(sortItems()));

        sortByNameAct = new QAction(QString::fromUtf8("Сортировка по имени"), this);
        sortByNameAct->setStatusTip(QString::fromUtf8("Элементы в порядке ФИО"));
        sortByNameAct->setCheckable(true);
        connect(sortByNameAct, SIGNAL(triggered()), SLOT(sortItems()));

        sortByDateAct = new QAction(QString::fromUtf8("Сортировка по дате"), this);
        sortByDateAct->setStatusTip(QString::fromUtf8("Элементы в порядке даты рождения (без учета года)"));
        sortByDateAct->setCheckable(true);
        connect(sortByDateAct, SIGNAL(triggered()), SLOT(sortItems()));

        sortByAgeAct = new QAction(QString::fromUtf8("Сортировка по возрасту"), this);
        sortByAgeAct->setStatusTip(QString::fromUtf8("Элементы в порядке даты рождения (с учетом года)"));
        sortByAgeAct->setCheckable(true);
        connect(sortByAgeAct, SIGNAL(triggered()), SLOT(sortItems()));

        saveSettingsAct = new QAction(QString::fromUtf8("Сохранить настройки"), this);
        saveSettingsAct->setStatusTip(QString::fromUtf8("Сохранить способ сортировки, положение и размеры окна"));
        connect(saveSettingsAct, SIGNAL(triggered()), SLOT(saveSettings()));

//	About
	aboutAct = new QAction(QString::fromUtf8("&О программе..."), this);
	aboutAct->setStatusTip(QString::fromUtf8("О программе..."));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(QString::fromUtf8("О &Qt"), this);
	aboutQtAct->setStatusTip(QString::fromUtf8("Показать окно 'О Qt'"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void EditorForm::createMenus()
{
	fileMenu = menuBar()->addMenu(QString::fromUtf8("&Файл"));
	fileMenu->addAction(addItemAct);
	fileMenu->addAction(editItemAct);
	fileMenu->addAction(deleteItemAct);
	fileMenu->addSeparator();
	fileMenu->addAction(runBirthdayAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);
	
        toolsMenu = menuBar()->addMenu(QString::fromUtf8("&Инструменты"));
	toolsMenu->addAction(signofZodiakAct);
	toolsMenu->addAction(viewtoMonthAct);
        toolsMenu->addAction(difDateAct);
        toolsMenu->addSeparator();
        settingsMenu = toolsMenu->addMenu(QString::fromUtf8("&Настройки"));

        QActionGroup* sortGroup = new QActionGroup(this);
        sortGroup->addAction(sortNonAct);
        sortGroup->addAction(sortByNameAct);
        sortGroup->addAction(sortByDateAct);
        sortGroup->addAction(sortByAgeAct);
        sortGroup->setExclusive(true);

        settingsMenu->addAction(sortNonAct);
        settingsMenu->addAction(sortByNameAct);
        settingsMenu->addAction(sortByDateAct);
        settingsMenu->addAction(sortByAgeAct);
        settingsMenu->addSeparator();
        settingsMenu->addAction(saveSettingsAct);
	
	helpMenu = menuBar()->addMenu(QString::fromUtf8("&Помощь"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

void EditorForm::createContextMenu()
{
	itemList->setContextMenuPolicy(Qt::ActionsContextMenu);
	itemList->addAction(addItemAct);
	itemList->addAction(editItemAct);
	itemList->addAction(deleteItemAct);
}

void EditorForm::createViewGroupBox()
{
	viewGroupBox = new QGroupBox(QString::fromUtf8("В этот день..."));
        viewGroupBox->setMaximumHeight(calendarWidget->height());
	nameLabel = new QLabel(QString::fromUtf8("Объект: ~~~"), this);
	birthdayLabel = new QLabel(QString::fromUtf8("Дата рождения: ~~~"), this);
	yearsLabel = new QLabel(QString::fromUtf8("Исполнилось лет: ~~~"), this);
	moreinfLabel = new QLabel(QString::fromUtf8("Доп. информация: ~~~"), this);
	anotherListWidget = new QListWidget;
	lcdNumber = new QLCDNumber;
	lcdNumber->setMaximumWidth(96);
	lcdNumber->setMinimumWidth(96);
	lcdNumber->setSegmentStyle(QLCDNumber::Flat);
	lcdNumber->setNumDigits(3);

	QGridLayout *layout = new QGridLayout;
	layout->setMargin(5);
	layout->setSpacing(5);

	layout->addWidget(nameLabel, 0, 0);
	layout->addWidget(birthdayLabel, 1, 0);
	layout->addWidget(yearsLabel, 2, 0);
	layout->addWidget(moreinfLabel, 3, 0);
	layout->addWidget(anotherListWidget, 4, 0, 1, 2);
	layout->addWidget(lcdNumber, 0, 1, 3, 1);

	viewGroupBox->setLayout(layout);
}

void EditorForm::loadSettings() {
    settings.beginGroup("/Settings");

    int w = settings.value("/width", width()).toInt();
    int h = settings.value("/height", height()).toInt();
    int _x = settings.value("/pos_x", x()).toInt();
    int _y = settings.value("/pos_y", y()).toInt();

    s_type = settings.value("/sortType", s_non).toInt();

    settings.endGroup();

    setGeometry(_x, _y, w, h);

    switch (s_type) {
        case s_non:  sortNonAct->setChecked(true); break;
        case s_name: sortByNameAct->setChecked(true); break;
        case s_date: sortByDateAct->setChecked(true); break;
        case s_age: sortByAgeAct->setChecked(true); break;
    }
}

void EditorForm::loadData()
{
	loadDataFromFile(birthList);
	fillList();
}

void EditorForm::saveData()
{
	QFile file( QDir::homePath() + "/.birth.dat");

	if ( !file.open(QIODevice::WriteOnly) ) { ioError(file, "Cannot open file %1 for writing"); return; };

	QDataStream out(&file);
	out.setVersion(7);

	out << MagicNumber;

	for (QList<birthItem>::iterator i = birthList.begin();  i != birthList.end(); ++i)
		out << (*i);

	file.close();
}

void EditorForm::fillList()
{
	itemList->clear();
	QList<birthItem>::iterator i;
	for (i = birthList.begin(); i != birthList.end(); ++i)
        	itemList->addItem( (i->getbirthday()).toString("yyyy-MM-dd") + "        " + (i->getname()) );
}

void EditorForm::anotherListWidgetSelectionChanged(int index)
{
	QDate tmp = birthList[index].getbirthday();
	QDate curDate(calendarWidget->selectedDate());

	nameLabel->setText(QString::fromUtf8("Объект: ") + birthList[index].getname());
	birthdayLabel->setText(QString::fromUtf8("Дата рождения: ") + tmp.toString("yyyy-MM-dd"));


	int yearsOld = curDate.year() - tmp.year();

	yearsLabel->setText(QString::fromUtf8("Исполнилось лет: ") + QString::number(yearsOld));
	moreinfLabel->setText(QString::fromUtf8("Доп. информация: ") + 
				GetChineseSignOfZodiac(tmp.day(), tmp.month()) + ", " +
				GetYearAnimalSign(tmp.year()) + " (" +
				GetYearElementSign(tmp.year()) + ")");
	lcdNumber->display(yearsOld);
}


int EditorForm::findByBirthday(int _month, int _day, int min = 0)
{
	int i;
	for (i = min; i < birthList.count(); i++)
        	if ((birthList[i].getmonth() == _month) && (birthList[i].getday() == _day)) return i;
	return -1;
}
