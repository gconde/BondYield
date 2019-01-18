#ifndef __DOUBLEVALIDATOR_H__
#define __DOUBLEVALIDATOR_H__

#include <QDoubleValidator>

/*!
 * This class is needed since the base class returns QValidator::Intermediate
 * when we really want invalid.
 * 
 */
class DoubleValidator : public QDoubleValidator
{
public:
    DoubleValidator(double bottom, double top, int decimals, QObject * parent = Q_NULLPTR) :
        QDoubleValidator(bottom, top, decimals, parent)
    {
    }

    QValidator::State validate(QString &s, int &i) const
    {
        if (s.isEmpty()) {
            return QValidator::Intermediate;
        }

        bool ok;
        double d = s.toDouble(&ok);

        if (ok && d >= bottom() && d <= top()) {
            return QValidator::Acceptable;
        }
        else {
            return QValidator::Invalid;
        }
    }
};

#endif //__DOUBLEVALIDATOR_H__
