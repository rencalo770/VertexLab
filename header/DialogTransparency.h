
#include <Standard_WarningsDisable.hxx>
#include <QDialog>
#include <QSlider>
#include <QWidget>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>

class QSlider;

//! Qt dialog with slider for change shapes transparency
class DialogTransparency : public QDialog
{
    Q_OBJECT
public:
    DialogTransparency(QWidget* parent = 0);
    ~DialogTransparency() { }

    int value() const
    {
        return mySlider->value();
    }

    void setValue(int theVal) const
    {
        mySlider->setValue(theVal);
    }

signals:
    void sendTransparencyChanged(int value);

private:
    QSlider* mySlider;
};
