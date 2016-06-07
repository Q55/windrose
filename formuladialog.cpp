#include "formuladialog.h"
#include "ui_formuladialog.h"

FormulaDialog::FormulaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormulaDialog)
{
    ui->setupUi(this);

}

FormulaDialog::~FormulaDialog()
{
    delete ui;
}
