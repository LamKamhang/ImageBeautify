#ifndef CLICKABLEQLABEL_H
#define CLICKABLEQLABEL_H
#include <QDialog>
#include <QLabel>
#include <QDebug>
#include <QWidget>

class ClickableQLabel:public QLabel{
    Q_OBJECT
public:
    ClickableQLabel( const QString & text, QWidget * parent = 0 );
    ~ClickableQLabel(){}

signals:
    void clicked();

public slots:
    void slotClicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;
};

#endif // CLICKABLEQLABEL_H
