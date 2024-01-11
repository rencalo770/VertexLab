
#include "../header/TranslateDialog.h"

#include <Standard_WarningsDisable.hxx>
#include <QGridLayout>
#include <Standard_WarningsRestore.hxx>

TranslateDialog::TranslateDialog(QWidget* parent, Qt::WindowFlags flags, bool modal)
    : QFileDialog(parent, flags)
{
    setOption(QFileDialog::DontUseNativeDialog);
    setModal(modal);

    QGridLayout* grid = ::qobject_cast<QGridLayout*>(layout());

    if (grid)
    {
        QVBoxLayout* vbox = new QVBoxLayout;

        QWidget* paramGroup = new QWidget(this);
        paramGroup->setLayout(vbox);

        myBox = new QComboBox(paramGroup);
        vbox->addWidget(myBox);

        int row = grid->rowCount();
        grid->addWidget(paramGroup, row, 1, 1, 3); // make combobox occupy 1 row and 3 columns starting from 1
    }
}

TranslateDialog::~TranslateDialog()
{
}

int TranslateDialog::getMode() const
{
    if (myBox->currentIndex() < 0 || myBox->currentIndex() > (int)myList.count() - 1)
    {
        return -1;
    }
    else
    {
        return myList.at(myBox->currentIndex());
    }
}

void TranslateDialog::setMode(const int mode)
{
    int idx = myList.indexOf(mode);
    if (idx >= 0)
    {
        myBox->setCurrentIndex(idx);
    }
}

void TranslateDialog::addMode(const int mode, const QString& name)
{
    myBox->show();
    myBox->addItem(name);
    myList.append(mode);
    myBox->updateGeometry();
    updateGeometry();
}

void TranslateDialog::clear()
{
    myList.clear();
    myBox->clear();
    myBox->hide();
    myBox->updateGeometry();
    updateGeometry();
}

QListView* TranslateDialog::findListView(const QObjectList& childList)
{
    QListView* listView = 0;
    for (int i = 0, n = childList.count(); i < n && !listView; i++)
    {
        listView = qobject_cast<QListView*>(childList.at(i));
        if (!listView && childList.at(i))
        {
            listView = findListView(childList.at(i)->children());
        }
    }
    return listView;
}

void TranslateDialog::showEvent(QShowEvent* event)
{
    QFileDialog::showEvent(event);
    QListView* aListView = findListView(children());
    aListView->setViewMode(QListView::ListMode);
}
