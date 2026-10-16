#pragma once
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qevent.h>
#include "ContactManager.h"


class NewContactWidget : public QWidget
{
    Q_OBJECT

private:
    QPushButton* addContactButton;
    QLabel* label;
    QLineEdit* name;
    QLineEdit* phone;
    QLineEdit* email;
    QLineEdit* adress;
    ContactManager* newContact;
public:
    NewContactWidget(QWidget* parent = nullptr)
    {
        addContactButton = new QPushButton("Add Contact", this);
        label = new QLabel("Label", this);
        name = new QLineEdit("name", this);
        phone = new QLineEdit("phone", this);
        email = new QLineEdit("email", this);
        adress = new QLineEdit("adress", this);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(addContactButton);
        layout->addWidget(name);
        layout->addWidget(phone);
        layout->addWidget(email);
        layout->addWidget(adress);
        connect(addContactButton, &QPushButton::clicked, this, &NewContactWidget::OnButtonClick);
    }
    ~NewContactWidget()
    {

    }

    void SetCont(ContactManager& allContacts)
    {
        newContact = &allContacts;
    }

    void closeEvent(QCloseEvent* event) override
    {
        emit CloseWidg();
        event->accept();
    }

private slots:
    void OnButtonClick()
    {
        newContact->AddContact(name->text(), { phone->text() ,email->text() ,adress->text() });
        close();
    }
signals:
    void CloseWidg();
};

