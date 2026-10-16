#include <QtCore/QCoreApplication>
#include <qapplication.h>
#include "ContactWindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    ContactManager contacts;
    
    contacts.AddContact("AAAAAaa", { "BBB","CCCC","DDDD" });

    ContactWindow wid;
    wid.SetCont(contacts);
    wid.AddContacts(contacts.GetMap());
    wid.show();



    return app.exec();
}
