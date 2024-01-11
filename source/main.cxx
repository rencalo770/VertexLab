
#include "../header/ApplicationCommonWindow.h"

#include <OSD_Environment.hxx>

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QLocale>
#include <QSettings>
#include <QStringList>
#include <QTranslator>
#include <Standard_WarningsRestore.hxx>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication aQApp(argc, argv);


   //Q_INIT_RESOURCE(VertexLab);


    QSettings settings(":/icons/VertexLab.conf", QSettings::IniFormat);
    settings.beginGroup("ApplicationSetting");
    ApplicationType aCategory = static_cast<ApplicationType>(settings.value("ApplicationType", "").toInt()); 
    settings.endGroup();
    
    ApplicationCommonWindow* aWindow = new ApplicationCommonWindow(aCategory);
    QString aResName(":/icons/lamp.png");
    aWindow->setWindowIcon(QPixmap(aResName));

    settings.beginGroup("WindowPosition");
    int x = settings.value("x", -1).toInt();
    int y = settings.value("y", -1).toInt();
    int width = settings.value("width", -1).toInt();
    int height = settings.value("height", -1).toInt();
    settings.endGroup();

    if (x > 0 && y > 0 && width > 0 && height > 0)
    {
       
        aWindow->setGeometry(x, y, width, height);
    }
    aWindow->SetApplicationType(aCategory);

    aWindow->show();
    int aResult = aQApp.exec();

    settings.beginGroup("WindowPosition");
    settings.setValue("x", aWindow->x());
    settings.setValue("y", aWindow->y());
    settings.setValue("width", aWindow->width());
    settings.setValue("height", aWindow->height());
    settings.endGroup();

    settings.beginGroup("ApplicationSetting");
    settings.setValue("ApplicationType", aWindow->GetApplicationType());
    settings.endGroup();

    return aResult;
}
