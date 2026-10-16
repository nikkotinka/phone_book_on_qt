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

#include "EditWidget.h"

#include "Contact.h"


class OneContactWidget : public QWidget
{
	Q_OBJECT

private:
	QCheckBox* addToFavorite;
	QPushButton* editContactButt;
	QLabel* contact;

	Contact* cont;

public:

	OneContactWidget(QWidget* parent = nullptr) : QWidget(parent)
	{
		contact = new QLabel(this);
		addToFavorite = new QCheckBox("Fav", this);
		editContactButt = new QPushButton("Edit contactact", this);

		QHBoxLayout* layout = new QHBoxLayout(this);

		layout->addWidget(contact);
		layout->addWidget(addToFavorite);
		connect(addToFavorite, &QCheckBox::checkStateChanged, this, &OneContactWidget::CheckFavorite);
	}

	OneContactWidget(QString cont, bool checked, QWidget* parent = nullptr) : QWidget(parent)
	{
		contact = new QLabel(cont, this);
		addToFavorite = new QCheckBox("Fav", this);
		editContactButt = new QPushButton("Edit contactact", this);

		addToFavorite->setChecked(checked);
		QHBoxLayout* layout = new QHBoxLayout(this);

		layout->addWidget(contact);
		layout->addWidget(addToFavorite);
		layout->addWidget(editContactButt);

		connect(addToFavorite, &QCheckBox::checkStateChanged, this, &OneContactWidget::CheckFavorite);
		connect(editContactButt, &QPushButton::clicked, this, &OneContactWidget::EditContact);

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
		
		emit RefreshBookAfterAddToFav();
	}

	void EditContact()
	{
		EditWidget* editContactWidget = new EditWidget(this);
		editContactWidget->SetCont(*cont);

		editContactWidget->show();

		connect(editContactWidget, &EditWidget::CloseWidg, this, &OneContactWidget::RefreshBookAfterEdditContact);
		

	}
	
signals:
	
	void RefreshBookAfterAddToFav();
	void RefreshBookAfterEdditContact();
	
};

