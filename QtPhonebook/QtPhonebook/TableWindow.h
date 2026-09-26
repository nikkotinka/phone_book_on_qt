#pragma once
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qcheckbox.h>
#include <qevent.h>
#include <QDebug>

#include "Contact.h"


class TableWindow : public QWidget
{
	Q_OBJECT

private:
	QCheckBox* addToFavorite;
	QLabel* contact;

	Contact* cont;

public:

	TableWindow(QWidget* parent = nullptr) : QWidget(parent)
	{
		contact = new QLabel(this);
		addToFavorite = new QCheckBox("Fav", this);
		QHBoxLayout* layout = new QHBoxLayout(this);

		layout->addWidget(contact);
		layout->addWidget(addToFavorite);
		connect(addToFavorite, &QCheckBox::checkStateChanged, this, &TableWindow::CheckFavorite);
	}

	TableWindow(QString cont, bool checked, QWidget* parent = nullptr) : QWidget(parent)
	{
		contact = new QLabel(cont, this);
		addToFavorite = new QCheckBox("Fav", this);
		addToFavorite->setChecked(checked);
		QHBoxLayout* layout = new QHBoxLayout(this);

		layout->addWidget(contact);
		layout->addWidget(addToFavorite);
		connect(addToFavorite, &QCheckBox::checkStateChanged, this, &TableWindow::CheckFavorite);

	}

	void SetCont(Contact& oneCont)
	{
		cont = &oneCont;
	}

	QString GetText()
	{
		return contact->text();
	}

private slots:

	void CheckFavorite(Qt::CheckState chek)
	{
		if (chek == Qt::CheckState::Unchecked)
		{
			cont->SetFavorite(false);

		}
		else
		{
			cont->SetFavorite(true);
		}
		
		emit AddToFav();
	}

	
signals:
	
	void AddToFav();
};

