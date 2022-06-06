#ifndef __BONDYIELDFORM_H__
#define __BONDYIELDFORM_H__

#include <QtCore/QObject>
#include <QtWidgets/QtWidgets>
#include <QtCore/QString>

/*!
 * Class for all the Qt GUI elements. It performs validation and imposed limits on numerical
 * input which greatly simplifies validation. No destructor is explicitly defined since all
 * GUI controls become a child of the main display widget which deletes all its children upon
 * exit.
 * 
 */
class BondYieldForm : public QDialog
{
    Q_OBJECT

public:
    BondYieldForm(QWidget *parent = Q_NULLPTR);

    QString ValidateFields() const;
    
private slots:
    void slot_mode_change(bool);
    void slot_calculate();
    void slot_quit();

private:
    void SetupSlotsSignals();

    static bool validate_int(QLineEdit* le);

    static bool validate_double(QLineEdit* le);

    static int get_int(QLineEdit* le);

    static double get_double(QLineEdit* le);

    QVBoxLayout* main_layout_;
    QFormLayout* bond_layout_;
    QHBoxLayout* mode_layout_;
    QHBoxLayout* calc_layout_;
    QHBoxLayout* button_layout_;
    QGroupBox* gbBondProps_;
    QLineEdit* leFaceValue_;
    QLineEdit* leTime_;
    QLineEdit* leCoupon_;
    QLineEdit* lePrice_;
    QLineEdit* leRate_;
    QGroupBox* gbMode_;
    QRadioButton* radPrice_;
    QRadioButton* radYield_;
    QGroupBox* gbYieldMethod_;
    QRadioButton* radIterative_;
    QRadioButton* radDeeley_;
    QGroupBox* gbStats_;
    QLabel* lblStats_;
    QHBoxLayout* stats_layout_;
    QPushButton* btnCalculate_;
    QPushButton* btnQuit_;
};

#endif //__BONDYIELDFORM_H__
