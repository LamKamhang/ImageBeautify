#include "Include/savedialog.h"
#include "ui_savedialog.h"

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    state = NO_STATE;
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::on_pushButton_clicked()
{
    state = NOT_SAVE;
    accept();
}

void SaveDialog::on_pushButton_2_clicked()
{
    state = SAVE;
    accept();
}

void SaveDialog::on_pushButton_3_clicked()
{
    state = CANCEL;
    accept();
}
