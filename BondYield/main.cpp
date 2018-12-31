#include "BondYieldForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BondYieldForm w;
	w.show();
	return a.exec();
}
