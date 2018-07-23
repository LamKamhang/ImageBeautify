#include "clickableqlabel.h"

ClickableQLabel::ClickableQLabel( const QString & text, QWidget * parent )
:QLabel(parent)
{
    this->setText(text);
    this->setAlignment(Qt::AlignCenter);
//    connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

void ClickableQLabel::slotClicked()
{
}

void ClickableQLabel::mousePressEvent ( QMouseEvent * event )
{
    emit clicked();
}
