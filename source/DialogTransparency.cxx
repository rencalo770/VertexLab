
#include "../header/DialogTransparency.h"

#include <Standard_WarningsDisable.hxx>
#include <QHBoxLayout>
#include <QLabel>
#include <Standard_WarningsRestore.hxx>

DialogTransparency::DialogTransparency(QWidget* parent)
	: QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	setWindowTitle(tr("Transparency"));
	QHBoxLayout* base = new QHBoxLayout(this);

	base->addWidget(new QLabel("0", this));

	mySlider = new QSlider(Qt::Horizontal, this);
	mySlider->setRange(0, 10);
	mySlider->setTickPosition(QSlider::TicksBelow);
	mySlider->setTickInterval(1);
	mySlider->setPageStep(2);
	base->addWidget(mySlider);
	connect(mySlider, SIGNAL(valueChanged(int)), this, SIGNAL(sendTransparencyChanged(int)));

	base->addWidget(new QLabel("10", this));
}
