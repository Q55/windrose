#include "postexprdialog.h"
#include "ui_postexprdialog.h"

PostExprDialog::PostExprDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostExprDialog)
{
    ui->setupUi(this);

}

PostExprDialog::PostExprDialog(QStringList sel_col, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostExprDialog)
{
    ui->setupUi(this);

    if (sel_col.size() == 1) {
        ui->groupBox_vector_expr->setCheckable(false);
        ui->groupBox_scalar_expr->setChecked(true);
        ui->comboBox_scalar_data->setItemText(0, sel_col[0]);
        ui->lineEdit_scalar_operand->setText("0");
        ui->lineEdit_new_col_name->setText(sel_col[0]);

        // disable vector input
        ui->comboBox_vector_data_1->setEnabled(false);
        ui->comboBox_vector_data_2->setEnabled(false);
        ui->comboBox_vector_operator->setEnabled(false);
    } else if (sel_col.size() == 2) {
        ui->groupBox_scalar_expr->setCheckable(false);
        ui->groupBox_vector_expr->setChecked(true);
        ui->comboBox_vector_data_1->setItemText(0, sel_col[0]);
        ui->comboBox_vector_data_1->setItemText(1, sel_col[1]);
        ui->comboBox_vector_data_2->setItemText(0, sel_col[1]);
        ui->comboBox_vector_data_2->setItemText(1, sel_col[0]);
        ui->lineEdit_new_col_name->setText(sel_col[0] + "#" + sel_col[1]);

        // disable scalar input
        ui->comboBox_scalar_data->setEnabled(false);
        ui->comboBox_scarlar_operator->setEnabled(false);
        ui->lineEdit_scalar_operand->setEnabled(false);
    }

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

void PostExprDialog::accept() {
    if (ui->comboBox_scarlar_operator->currentIndex() == 3 &&
            ui->lineEdit_scalar_operand->text().toDouble() == 0.0) { // "/0"
        QMessageBox msgBox;
        msgBox.setText("除数不能为0.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    } else {
        emit postExprParas(ui->groupBox_scalar_expr->isChecked(),
                       ui->comboBox_scalar_data->currentText(),
                       ui->comboBox_scarlar_operator->currentIndex(),
                       ui->lineEdit_scalar_operand->text().toInt(),
                       ui->groupBox_vector_expr->isChecked(),
                       ui->comboBox_vector_data_1->currentText(),
                       ui->comboBox_vector_operator->currentIndex(),
                       ui->comboBox_vector_data_2->currentText(),
                       ui->lineEdit_new_col_name->text());
        QDialog::accept();
    }
}

PostExprDialog::~PostExprDialog()
{
    delete ui;
}
