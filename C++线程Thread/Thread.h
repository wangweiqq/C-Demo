#pragma once

#include <QtWidgets/QDialog>
#include "ui_Thread.h"

class Thread : public QDialog
{
	Q_OBJECT

public:
	Thread(QWidget *parent = Q_NULLPTR);

private:
	Ui::ThreadClass ui;
};
