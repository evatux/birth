// version 0.1

#ifndef DIFDATEDIALOG_H
#define DIFDATEDIALOG_H

#include <QDialog>
#include <QDate>
#include <QString>

class QLabel;
class QDateEdit;
class QSpinBox;
class QCheckBox;
class QPushButton;

class DifDateDialog : public QDialog
{
        Q_OBJECT

public:
        DifDateDialog(QWidget*);

private slots:
       void dateChng(QDate);
       void spinChng(int);

private:
        QLabel      *startDateLabel;
        QDateEdit   *startDateEdit;
        QLabel      *finishDateLabel;
        QDateEdit   *finishDateEdit;
        QLabel      *difDateLabel;
        QSpinBox    *difDateSpinBox;
        QCheckBox   *fixFinishDateCheckBox;
        QPushButton *closeButton;
};

#endif // DIFDATEDIALOG_H
