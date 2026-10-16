#pragma once
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qevent.h>

#include "Contact.h"


class EditWidget : public QWidget
{
    Q_OBJECT

private:
    QPushButton* editContactButton;
    QLineEdit* name;
    QLineEdit* phone;
    QLineEdit* email;
    QLineEdit* adress;
    Contact* contactForEdit;
public:
    EditWidget(QWidget* parent = nullptr)
    {
        editContactButton = new QPushButton("Edit Contact", this);
        phone = new QLineEdit("phone", this);
        email = new QLineEdit("email", this);
        adress = new QLineEdit("adress", this);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(editContactButton);
        layout->addWidget(phone);
        layout->addWidget(email);
        layout->addWidget(adress);
        connect(editContactButton, &QPushButton::clicked, this, &EditWidget::OnButtonClick);
    }
    ~EditWidget()
    {

    }

    void SetCont(Contact& contacts)
    {
        contactForEdit = &contacts;
        phone->setText(contactForEdit->GetPhone());
        email->setText(contactForEdit->GetEmail());
        adress->setText(contactForEdit->GetAdress());
    }

    void closeEvent(QCloseEvent* event) override
    {
        emit CloseWidg();
        event->accept();
    }

private slots:
    void OnButtonClick()
    {
        contactForEdit->SetAllInfo(phone->text(), email->text(), adress->text());
        emit RefreshBook();
        close();
    }
signals:
    void CloseWidg();

    void RefreshBook();
};

