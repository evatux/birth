// version 0.3.4

#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QCalendarWidget;
class QListWidget;
class QListWidgetItem;
class QLabel;
class QLCDNumber;
class QGroupBox;
class QLineEdit;
QT_END_NAMESPACE

#include "../include/birthUnit.h"
#include "../include/zodiacUnit.h"
#include "itemdialog.h"
#include "zodiacdialog.h"
#include "viewmonthdialog.h"
#include "difdatedialog.h"

class EditorForm : public QMainWindow
{
	Q_OBJECT
public:
	EditorForm();

        void loadSettings();

protected:
//	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void addItem();
	void editItem();
	void deleteItem();

        void showOnCalendar(QListWidgetItem*);

	void add(QString, QDate);
	void edit(QString, QDate, int);

	void runBirthday();

        void searchItems(QString);

	void signofZodiak();
	void viewtoMonth();
        void difDate();

        void sortItems();
        void saveSettings();

	void fillViewGroupBox();

	void reformatCalendarPage(int, int);
	void fillCalendar(int, int);
	void clearCalendar(int, int);

	void anotherListWidgetSelectionChanged();

	void about();

private:
        enum {s_non, s_name, s_date, s_age};

	void createActions();
	void createMenus();
	void createContextMenu();

        void createViewGroupBox();

	void loadData();
	void saveData();
	void fillList();

	void anotherListWidgetSelectionChanged(int);

	int findByBirthday(int, int, int);

	QList<birthItem> birthList;

	QMenu		*fileMenu;
	QMenu		*toolsMenu;
        QMenu           *settingsMenu;
	QMenu		*helpMenu;

        // File Menu
	QAction		*addItemAct;
	QAction		*editItemAct;
	QAction		*deleteItemAct;
	QAction		*runBirthdayAct;
	QAction		*exitAct;

        // Tools Menu
	QAction		*signofZodiakAct;
	QAction		*viewtoMonthAct;
        QAction         *difDateAct;

        // Settings Submenu
        QAction         *sortNonAct;
        QAction         *sortByNameAct;
        QAction         *sortByDateAct;
        QAction         *sortByAgeAct;
        QAction         *saveSettingsAct;

        // Help Menu
	QAction		*aboutAct;
	QAction		*aboutQtAct;

	ItemDialog	*idialog;
	ZodiacDialog	*zdialog;
	ViewMonthDialog *vdialog;
        DifDateDialog   *ddialog;

	QCalendarWidget	*calendarWidget;

	QGroupBox	*viewGroupBox;
	QLabel		*nameLabel;
	QLabel		*birthdayLabel;
	QLabel		*yearsLabel;
	QLabel		*moreinfLabel;
	QListWidget	*anotherListWidget;
	QLCDNumber	*lcdNumber;

	QListWidget	*itemList;
        QLineEdit       *findEdit;

	QList<int>	anotherNList;
	QList<int>	seenYears;
	int 		lastYear;

        QSettings       settings;

        int             s_type;
};

#endif
