#include "BondMath.h"

#include <QElapsedTimer>

int BondMath::interations_ = 0;

qint64 BondMath::timed_ = 0;

/*!
 * Calculates the present value of the bond.
 * 
 * \param coupon Rate per period.
 * \param years The term to maturity in interest (or rate) periods.
 * \param face The redemption value of the bond.
 * \param rate Annual rate of reinvestment.
 * \return The present value of the bond.
 */
qreal BondMath::CalcPrice(qreal coupon, qreal years, qreal face, qreal rate)
{
    qreal r = 1.f + rate;
    qreal C = coupon * face;
    qreal price = face / qPow(r, years);
    for (int i = 1; i <= years; i++) {
        price += C / qPow(r, i);
    }
    return price;
}

/*!
 * Calculates the bond yield using an iterative approach. Approaches
 * the correct yield by adding/subtracting to the rate based on the difference
 * to the correct price by an amount that gets smaller.
 * 
 * \param coupon Rate per period.
 * \param years The term to maturity in interest (or rate) periods.
 * \param face The redemption value of the bond.
 * \param price The purchase price of the bond.
 * \return The yield.
 */
qreal BondMath::CalcYield(qreal coupon, qreal years, qreal face, qreal price)
{
    QElapsedTimer timer;
    timer.start();
    qreal C = coupon * face;
    qreal r = (C - (price - face) / years) / ((price + face) / 2.f); //initial guess
    qreal increment = .05f;
    qreal calc_price = 0.f;
    qreal delta = 1.f;
    bool sign = true; //false for subtract, true for add
    interations_ = 0;
    while (qFabs(delta) > 1e-010) {
        calc_price = CalcPrice(coupon, years, face, r);
        delta = calc_price - price;
        if (delta < 0.f) {
            //calc was less, guess lower r
            r -= increment;
            if (sign) {
                increment /= 2.f;
                sign = false;
            }
        }
        else {
            //calc was greater, guess higher r
            r += increment;
            if (!sign) {
                increment /= 2.f;
                sign = true;
            }
        }
        ++interations_;
        if (interations_ > 1000000)
        {
            r = -1;
            break;
        }
    }
    timed_ = timer.nsecsElapsed();
    return r;
}

/*!
 * Calculates the bond yield.
 * Uses algorithm described here: https://papers.ssrn.com/sol3/papers.cfm?abstract_id=1253166
 * Basically better than Newton's Method as it converges faster.
 *
 * \param rate Rate per period.
 * \param n The term to maturity in interest (or rate) periods.
 * \param V The redemption value of the bond.
 * \param P The purchase price of the bond.
 * \return The yield.
 */
qreal BondMath::CalcYieldDeeley(qreal rate, qreal n, qreal V, qreal P)
{
    QElapsedTimer timer;
    timer.start();
    qreal calc_price = 0.f;
    qreal delta = 1.f;
    interations_ = 0;
    qreal C = rate * V;
    qreal i = (C - (P - V) / n) / ((P + V) / 2.f); //initial guess
    while (qFabs(delta) > 1e-010) {
        qreal FV = C * ((qPow(1.f + i, n) - 1.f) / i) + V;
        i = qPow(FV / P, 1.f / n) - 1.f;
        calc_price = CalcPrice(rate, n, V, i);
        delta = calc_price - P;
        ++interations_;
        if (interations_ > 1000000)
        {
            i = -1;
            break;
        }
    }
    timed_ = timer.nsecsElapsed();
    return i;
}
