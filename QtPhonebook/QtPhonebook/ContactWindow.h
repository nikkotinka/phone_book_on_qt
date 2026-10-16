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
#include "NewContactWidget.h"
#include "OneContactWidget.h"

class ContactWindow : public QWidget
{

    Q_OBJECT

private:
    QPushButton* addContactButton;
    QLabel* label;
    QListWidget* allContacts;
    QLineEdit* find;
    ContactManager* contactsData;
public:
    ContactWindow(QWidget* parent = nullptr)
    {
        addContactButton = new QPushButton("Add contact", this);
        label = new QLabel("Label", this);
        allContacts = new QListWidget(this);
        find = new QLineEdit(this);
        allContacts->setMinimumHeight(100);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(find);
        layout->addWidget(addContactButton);
        layout->addWidget(allContacts);
        connect(addContactButton, &QPushButton::clicked, this, &ContactWindow::OnButtonClick);
        connect(find, &QLineEdit::textChanged, this, &ContactWindow::Finder);
        connect(allContacts, &QListWidget::itemDoubleClicked, this, &ContactWindow::DeletePerson);
    }
    ~ContactWindow()
    {

    }

    void SetCont(ContactManager &contacts)
    {
        contactsData = &contacts;
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
            QListWidgetItem* listw = new QListWidgetItem(allContacts);
            res += it->first;
            res += ", ";
            res += it->second.GetAll();
            
            OneContactWidget* newOneContact = new OneContactWidget(res, it->second.GetFavorite(), this);

            newOneContact->SetCont(*contactsData->FindContact(it->first));

            connect(newOneContact, &OneContactWidget::RefreshBookAfterAddToFav, this, &ContactWindow::Refresh);
            connect(newOneContact, &OneContactWidget::RefreshBookAfterEdditContact, this, &ContactWindow::Refresh);

            
            allContacts->setItemWidget(listw, newOneContact);
        }
        for (auto it = contact_map.begin(); it != contact_map.end(); it++)
        {
            if (it->second.GetFavorite())
            {
                continue;
            }
            QString res = "";
            QListWidgetItem* listw = new QListWidgetItem(allContacts);
            res += it->first;
            res += ", ";
            res += it->second.GetAll();

            OneContactWidget* newOneContact = new OneContactWidget(res, it->second.GetFavorite(), this);

            newOneContact->SetCont(*contactsData->FindContact(it->first));

            connect(newOneContact, &OneContactWidget::RefreshBookAfterAddToFav, this, &ContactWindow::Refresh);
            connect(newOneContact, &OneContactWidget::RefreshBookAfterEdditContact, this, &ContactWindow::Refresh);

            allContacts->setItemWidget(listw, newOneContact);
        }
    }

    void Refresh()
    {
        //contacts->clear();
        //AddContacts(cont->GetMap());
        Finder();
    }

private slots:
    void OnButtonClick()
    {
        NewContactWidget* Forman;
        Forman = new NewContactWidget(this);

        connect(Forman, &NewContactWidget::CloseWidg, this, &ContactWindow::Refresh);

        Forman->SetCont(*contactsData);

        Forman->show();
    }

    void Finder()
    {
        std::map <QString, Contact> findnames = contactsData->FindContactsAtAllFields(find->text());
        allContacts->clear();
        AddContacts(findnames);
    }

    void DeletePerson(QListWidgetItem* item)
    {
        QWidget* widget = allContacts->itemWidget(item);

        OneContactWidget* thisContact = qobject_cast <OneContactWidget*> (widget);

        QString name = "";
        QString alltext = thisContact->GetText();

        for (auto it = alltext.begin(); *it != ','; it++)
        {
            name += *it;
        }
        if (contactsData->DeleteContact(name))
        {
            Refresh();
        }
    }

};

