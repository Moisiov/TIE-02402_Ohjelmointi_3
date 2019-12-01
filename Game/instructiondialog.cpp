#include "instructiondialog.h"
#include "ui_instructiondialog.h"

InstructionDialog::InstructionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionDialog)
{
    ui->setupUi(this);
    setWindowTitle("How to play");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

InstructionDialog::~InstructionDialog()
{
    delete ui;
}
