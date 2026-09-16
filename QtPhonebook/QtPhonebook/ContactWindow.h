#pragma once
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstring.h>
#include "MyWidget.h"
class ContactWindow : public QWidget
{

    Q_OBJECT

private:
    QPushButton* button;
    QPushButton* refreshbutton;
    QLabel* label;
    QListWidget* contacts;
    ContactManager* cont;
public:
    ContactWindow(QWidget* parent = nullptr)
    {
        button = new QPushButton("Add contact", this);
        refreshbutton = new QPushButton("Refresh", this);
        label = new QLabel("Label", this);
        contacts = new QListWidget(this);
        contacts->addItem("Strings First");
        contacts->addItem("Strings Second");
        contacts->setMinimumHeight(100);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(button);
        layout->addWidget(refreshbutton);
        layout->addWidget(contacts);
        connect(button, &QPushButton::clicked, this, &ContactWindow::OnButtonClick);
        connect(refreshbutton, &QPushButton::clicked, this, &ContactWindow::OnRefreshButtonClicked);
    }
    ~ContactWindow()
    {

    }

    void SetCont(ContactManager &contacts)
    {
        cont = &contacts;
    }

    void AddContacts(std::map <std::string, Contact> contact_map)
    {
        for (auto it = contact_map.begin(); it != contact_map.end(); it++)
        {
            QString res = "";
            res += it->first;
            res += ", ";
            res += it->second.GetAll();
            contacts->addItem(res);
        }
    }

    void Refresh()
    {
        contacts->clear();
        AddContacts(cont->GetMap());
    }

private slots:
    void OnButtonClick()
    {
        MyWidget* Forman;
        Forman = new MyWidget(this);
        Forman->SetCont(*cont);
        Forman->show();
    }

    void OnRefreshButtonClicked()
    {
        Refresh();
    }
};

