#include "startdialog.hh"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::accept()
{
    std::vector<std::string> playerList = {};
    std::vector<PlayerColor> colorList = {};
    unsigned map_x = static_cast<unsigned>(ui->mapSizeX->value());
    unsigned map_y = static_cast<unsigned>(ui->mapSizeY->value());

    struct logicPair {
        QCheckBox* checkbox;
        QLineEdit* name;
        PlayerColor color;
    };

    std::vector<logicPair> nameSelection = {
        {ui->checkboxP1, ui->nameP1, PlayerColor::RED},
        {ui->checkboxP2, ui->nameP2, PlayerColor::BLUE},
        {ui->checkboxP3, ui->nameP3, PlayerColor::GREEN},
        {ui->checkboxP4, ui->nameP4, PlayerColor::ORANGE},
        {ui->checkboxP5, ui->nameP5, PlayerColor::PURPLE},
        {ui->checkboxP6, ui->nameP6, PlayerColor::CYAN}
    };

    for (unsigned i = 0; i < nameSelection.size(); ++i) {
        logicPair pair = nameSelection[i];
        if (pair.checkbox->isChecked()) {
            QString QName = pair.name->text();
            std::string name = QName.toStdString();

            if (name == "") {
                QMessageBox warning;
                warning.setText("Player name can't be empty.");
                warning.exec();
                return;
            }

            playerList.push_back(name);
            colorList.push_back(pair.color);
        }
    }

    if (playerList.size() < 2) {
        QMessageBox warning;
        warning.setText("Needs atleast 2 players to start!");
        warning.exec();
        return;
    }

    emit sendParameters(playerList, colorList, map_x, map_y);
    done(QDialog::Accepted);
}
