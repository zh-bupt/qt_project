#include "cancelfocusdialog.h"
#include "ui_cancelfocusdialog.h"

CancelFocusDialog::CancelFocusDialog(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::CancelFocusDialog)
{
    ui->setupUi(this);
    ui->label->setText("取消对" + name + "的关注?");
}

CancelFocusDialog::~CancelFocusDialog()
{
    delete ui;
}

void CancelFocusDialog::on_btn_cancel_clicked()
{
    close();
}

void CancelFocusDialog::on_btn_confirm_clicked()
{
    accept();
}
