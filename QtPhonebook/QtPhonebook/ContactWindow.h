#pragma once
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstring.h>
#include <QDebug>
#include <QtGlobal>
#include "MyWidget.h"
#include "TableWindow.h"

class ContactWindow : public QWidget
{

    Q_OBJECT

private:
    QPushButton* button;
    QLabel* label;
    QListWidget* contacts;
    QLineEdit* find;
    ContactManager* cont;
public:
    ContactWindow(QWidget* parent = nullptr)
    {
        button = new QPushButton("Add contact", this);
        label = new QLabel("Label", this);
        contacts = new QListWidget(this);
        find = new QLineEdit(this);
        contacts->setMinimumHeight(100);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(find);
        layout->addWidget(button);
        layout->addWidget(contacts);
        connect(button, &QPushButton::clicked, this, &ContactWindow::OnButtonClick);
        connect(find, &QLineEdit::textChanged, this, &ContactWindow::Finder);
        connect(contacts, &QListWidget::itemDoubleClicked, this, &ContactWindow::DeletePerson);
    }
    ~ContactWindow()
    {

    }

    void SetCont(ContactManager &contacts)
    {
        cont = &contacts;
    }

    void AddContacts(std::map <QString, Contact> &contact_map)
    {

        for (auto it = contact_map.begin(); it != contact_map.end(); it++)
        {
            if (!it->second.GetFavorite())
            {
                continue;
            }
            QString res = "";
            QListWidgetItem* listw = new QListWidgetItem(contacts);
            res += it->first;
            res += ", ";
            res += it->second.GetAll();
            
            TableWindow* con = new TableWindow(res, it->second.GetFavorite(), this);

            con->SetCont(it->second);
            
            contacts->setItemWidget(listw,con);
        }
        for (auto it = contact_map.begin(); it != contact_map.end(); it++)
        {
            if (it->second.GetFavorite())
            {
                continue;
            }
            QString res = "";
            QListWidgetItem* listw = new QListWidgetItem(contacts);
            res += it->first;
            res += ", ";
            res += it->second.GetAll();

            TableWindow* con = new TableWindow(res, it->second.GetFavorite(), this);

            con->SetCont(it->second);

            contacts->setItemWidget(listw, con);
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

        connect(Forman, &MyWidget::CloseWidg, this, &ContactWindow::Refresh);

        Forman->SetCont(*cont);

        Forman->show();
    }

    void Finder(const QString& str)
    {
        std::map <QString, Contact> findnames = cont->FindContactsAtAllFields(str);
        contacts->clear();
        AddContacts(findnames);
    }

    void DeletePerson(QListWidgetItem* item)
    {
        QString name = "";
        QString alltext = item->text();
        for (auto it = alltext.begin(); *it != ','; it++)
        {
            name += *it;
        }
        if (cont->DeleteContact(name))
        {
            Refresh();
        }
    }

};

