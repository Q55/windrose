#include "postcolrenamedialog.h"
#include "ui_postcolrenamedialog.h"

PostColRenameDialog::PostColRenameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostColRenameDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("列重命名");
}

PostColRenameDialog::PostColRenameDialog(QString orig_col_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostColRenameDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("列重命名");

    ui->lineEdit_orig_col_name->setText(orig_col_name);
    ui->lineEdit_orig_col_name->setEnabled(false);

    ui->lineEdit_new_col_name->setFocus();

    // QT has prepare the connect, so we don't need to do it. by shiqiang, 2016.07.05
    //connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

void PostColRenameDialog::accept() {

    emit postRenameNewColName(ui->lineEdit_orig_col_name->text(), ui->lineEdit_new_col_name->text());
    QDialog::accept();
}

PostColRenameDialog::~PostColRenameDialog()
{
    delete ui;
}
