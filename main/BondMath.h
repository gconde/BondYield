#ifndef __BONDMATH_H__
#define __BONDMATH_H__

#include <QtCore/QtMath>

/*!
 * A static class for calculating bond price and yield. Validation of input
 * is generally left to the caller which is from Qt line edit input validation
 * in this case. Very large values will cause low accurcy results.
 * 
 */
class BondMath {
public:
    BondMath() = delete;

    BondMath(const BondMath&) = delete;

    static qreal CalcPrice(qreal coupon, qreal years, qreal face, qreal rate);

    static qreal CalcYield(qreal coupon, qreal years, qreal face, qreal price);

    static qreal CalcYieldDeeley(qreal rate, qreal n, qreal V, qreal P);

    /*!
     * Returns the number of iterations used for the last yield calculation.
     * 
     * \return Number of iterations.
     */
    static int GetInterations() { return interations_; }

    /*!
     * Returns the amount of time taken for the last yield calculation.
     * 
     * \return Time in nanoseconds.
     */
    static qint64 GetTimedResult() { return timed_; }

private:
    static int interations_;

    static qint64 timed_;
};

#endif //__BONDMATH_H__
