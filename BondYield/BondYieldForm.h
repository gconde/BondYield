#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BondYieldForm.h"

class BondYieldForm : public QMainWindow
{
	Q_OBJECT

public:
	BondYieldForm(QWidget *parent = Q_NULLPTR);

private:
	Ui::BondYieldFormClass ui;
};
