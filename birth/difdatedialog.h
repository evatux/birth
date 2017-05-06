// version 0.1

#ifndef DIFDATEDIALOG_H
#define DIFDATEDIALOG_H

#include <QDialog>
#include <QDate>
#include <QString>

QT_BEGIN_NAMESPACE
class QLabel;
class QDateEdit;
class QSpinBox;
class QCheckBox;
QT_END_NAMESPACE

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
