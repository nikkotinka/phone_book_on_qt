#pragma once
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qevent.h>
#include "ContactManager.h"


class MyWidget : public QWidget
{
    Q_OBJECT

private:
    QPushButton* button;
    QLabel* label;
    QLineEdit* name;
    QLineEdit* phone;
    QLineEdit* email;
    QLineEdit* adress;
    ContactManager* cont;
public:
    MyWidget(QWidget* parent = nullptr)
    {
        button = new QPushButton("Add Contact", this);
        label = new QLabel("Label", this);
        name = new QLineEdit("name", this);
        phone = new QLineEdit("phone", this);
        email = new QLineEdit("email", this);
        adress = new QLineEdit("adress", this);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(button);
        layout->addWidget(name);
        layout->addWidget(phone);
        layout->addWidget(email);
        layout->addWidget(adress);
        connect(button, &QPushButton::clicked, this, &MyWidget::OnButtonClick);
    }
    ~MyWidget()
    {

    }

    void SetCont(ContactManager& contacts)
    {
        cont = &contacts;
    }

    void closeEvent(QCloseEvent* event) override
    {
        emit CloseWidg();
        event->accept();
    }

private slots:
    void OnButtonClick()
    {
        cont->AddContact(name->text(), { phone->text().toStdString() ,email->text().toStdString() ,adress->text().toStdString() });
        close();
    }
signals:
    void CloseWidg();
};

