#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

#ifdef _DEBUG
#define QT_SHAREDPOINTER_TRACK_POINTERS
#endif

#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "BondYieldForm.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        BondYieldForm byf;
        byf.show();
        return a.exec();
    }
    catch (const std::bad_alloc &ba)
    {
        QMessageBox::critical(0, "Out of Memory", QString::fromUtf8(ba.what()), QMessageBox::Ok);
        return 1;
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(0, "General Exception", QString::fromUtf8(e.what()), QMessageBox::Ok);
        return 2;
    }
    return 0;
}
