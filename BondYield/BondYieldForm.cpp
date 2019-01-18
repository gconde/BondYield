#include "BondYieldForm.h"

#include <QIntValidator>
#include "DoubleValidator.hpp"
#include "BondMath.h"

BondYieldForm::BondYieldForm(QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint)
{
    setWindowTitle(tr("Bond/Yield Calculator"));
    QVBoxLayout *main_layout_ = new QVBoxLayout();
    setLayout(main_layout_);
    setMinimumSize(350, 430);
    setMaximumSize(450, 430);
    // layout for bond properties groupbox
    gbBondProps_ = new QGroupBox(tr("Bond Properties"));
    bond_layout_ = new QFormLayout();
    leFaceValue_ = new QLineEdit();
    leTime_ = new QLineEdit();
    leCoupon_ = new QLineEdit();
    lePrice_ = new QLineEdit();
    leRate_ = new QLineEdit();
    bond_layout_->addRow(tr("Face Value $"), leFaceValue_);
    bond_layout_->addRow(tr("Time (Years)"), leTime_);
    bond_layout_->addRow(tr("Coupon Payment %"), leCoupon_);
    bond_layout_->addRow(tr("Price $"), lePrice_);
    bond_layout_->addRow(tr("Rate %"), leRate_);
    bond_layout_->setLabelAlignment(Qt::AlignRight);
    gbBondProps_->setLayout(bond_layout_);
    DoubleValidator* face_validator = new DoubleValidator(0.0f, qPow(10.f, 9.f), 10);
    QIntValidator* time_validator = new QIntValidator(0, 200);
    DoubleValidator* payment_validator = new DoubleValidator(0.0f, 100.f, 10);
    DoubleValidator* price_validator = new DoubleValidator(0.0f, qPow(10.f, 9.f), 10);
    DoubleValidator* rate_validator = new DoubleValidator(0.0f, 100.f, 10);
    leFaceValue_->setValidator(face_validator);
    leTime_->setValidator(time_validator);
    leCoupon_->setValidator(payment_validator);
    lePrice_->setValidator(price_validator);
    leRate_->setValidator(rate_validator);
    // layout for mode group box
    gbMode_ = new QGroupBox(tr("Mode"));
    mode_layout_ = new QHBoxLayout();
    gbMode_->setLayout(mode_layout_);
    radPrice_ = new QRadioButton(tr("Calculate Price"));
    radPrice_->setChecked(true);
    mode_layout_->addStretch(1);
    mode_layout_->addWidget(radPrice_);
    radYield_ = new QRadioButton(tr("Calculate Yield"));
    mode_layout_->addStretch(1);
    mode_layout_->addWidget(radYield_);
    mode_layout_->addStretch(1);
    // layout for yield calculation group box
    gbYieldMethod_ = new QGroupBox(tr("Yield Calculation Method"));
    calc_layout_ = new QHBoxLayout();
    gbYieldMethod_->setLayout(calc_layout_);
    radIterative_ = new QRadioButton(tr("Iterative"));
    radIterative_->setChecked(true);
    calc_layout_->addStretch(1);
    calc_layout_->addWidget(radIterative_);
    radDeeley_ = new QRadioButton(tr("Deeley"));
    calc_layout_->addStretch(1);
    calc_layout_->addWidget(radDeeley_);
    calc_layout_->addStretch(1);
    // layout for stats
    gbStats_ = new QGroupBox(tr("Yield Calculation Stats"));
    lblStats_ = new QLabel("Interations: 0\nLatency: 0 ms");
    QHBoxLayout* stats_layout_ = new QHBoxLayout();
    stats_layout_->addWidget(lblStats_);
    gbStats_->setLayout(stats_layout_);
    // button layout
    btnCalculate_ = new QPushButton(tr("Calculate"));
    btnQuit_ = new QPushButton(tr("Quit"));
    button_layout_ = new QHBoxLayout();
    button_layout_->addStretch();
    button_layout_->addWidget(btnCalculate_);
    button_layout_->addWidget(btnQuit_);
    // add layouts to main form layout
    main_layout_->addWidget(gbBondProps_);
    main_layout_->addWidget(gbMode_);
    main_layout_->addWidget(gbYieldMethod_);
    main_layout_->addWidget(gbStats_);
    main_layout_->addLayout(button_layout_);
    lePrice_->setEnabled(false);
    leRate_->setEnabled(true);
    // setup slots/signals for GUI
    SetupSlotsSignals();
}

void BondYieldForm::SetupSlotsSignals()
{
    QObject::connect(radPrice_,     SIGNAL(toggled(bool)), this, SLOT(slot_mode_change(bool)));
    QObject::connect(radYield_,     SIGNAL(toggled(bool)), this, SLOT(slot_mode_change(bool)));
    QObject::connect(btnCalculate_, SIGNAL(clicked()),     this, SLOT(slot_calculate()));
    QObject::connect(btnQuit_,      SIGNAL(clicked()),     this, SLOT(slot_quit()));
}

QString BondYieldForm::ValidateFields() const
{
    QString msg;
    QStringList bad_fields;
    if (!validate_int(leFaceValue_))
    {
        bad_fields.push_back("face");
    }
    if (!validate_int(leTime_))
    {
        bad_fields.push_back("time");
    }
    if (!validate_int(leCoupon_))
    {
        bad_fields.push_back("coupon");
    }
    if (radYield_->isChecked() && !validate_double(lePrice_))
    {
        bad_fields.push_back("price");
    }
    if (radPrice_->isChecked() && !validate_int(leRate_))
    {
        bad_fields.push_back("rate");
    }
    if (!bad_fields.empty())
        msg = "The following fields are invalid: " + bad_fields.join(", ");
    return msg;
}

bool BondYieldForm::validate_int(QLineEdit* le)
{
    bool ok;
    int num = le->text().toInt(&ok);
    return ok;
}

bool BondYieldForm::validate_double(QLineEdit* le)
{
    bool ok;
    double num = le->text().toDouble(&ok);
    return ok;
}

int BondYieldForm::get_int(QLineEdit* le)
{
    int num = le->text().toInt();
    return num;
}

double BondYieldForm::get_double(QLineEdit* le)
{
    double num = le->text().toDouble();
    return num;
}

void BondYieldForm::slot_mode_change(bool checked)
{
    if (checked)
    {
        QString tmp = leRate_->text();
        bond_layout_->removeRow(bond_layout_->rowCount() - 1);
        leRate_ = new QLineEdit();
        leRate_->setValidator(new QDoubleValidator(0.0f, 100.f, 10));
        leRate_->setMaxLength(20);
        leRate_->setText(tmp);
        if (radPrice_->isChecked())
        {
            bond_layout_->addRow(tr("Rate %"), leRate_);
            lePrice_->setEnabled(false);
            leRate_->setEnabled(true);
        }
        else
        {
            bond_layout_->addRow(tr("Yield %"), leRate_);
            lePrice_->setEnabled(true);
            leRate_->setEnabled(false);
        }
    }
}

void BondYieldForm::slot_calculate()
{
    QString msg = ValidateFields();
    if (!msg.isEmpty())
    {
        QMessageBox::warning(this, tr("Invalid Input"), msg, QMessageBox::Ok);
        return;
    }
    qreal f, p, r, c, result;
    f = get_double(leFaceValue_);
    c = get_double(leCoupon_) / 100.f;
    int n = get_int(leTime_);
    if (radPrice_->isChecked())
    {
        r = get_double(leRate_) / 100.f;
        result = BondMath::CalcPrice(c, n, f, r);
        lePrice_->setText(QString::number(result, 'g', 10));
    }
    else
    {
        p = get_double(lePrice_);
        if (radIterative_->isChecked())
            result = BondMath::CalcYield(c, n, f, p) * 100.f;
        else
            result = BondMath::CalcYieldDeeley(c, n, f, p) * 100.f;
        if (result >= 0.f)
        {
            leRate_->setText(QString::number(result, 'g', 10));
            QString stats = QString("Interations: %1\nLatency: %2 ms")
                .arg(QString::number(BondMath::GetInterations()), QString::number(BondMath::GetTimedResult() / 1000.f));
            lblStats_->setText(stats);
        }
        else
            lblStats_->setText(tr("Failed to converge."));
    }
}

void BondYieldForm::slot_quit()
{
    close();
}
