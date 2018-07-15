#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    enum {NO_STATE,NOT_SAVE,SAVE,CANCEL} state;
    explicit SaveDialog(QWidget *parent = 0);
    ~SaveDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SaveDialog *ui;

};

#endif // SAVEDIALOG_H
