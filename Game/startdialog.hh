#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <QMessageBox>

#include "player.hh"

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = nullptr);
    virtual ~StartDialog() override;

public slots:
    virtual void accept() override;

signals:
    void sendParameters(std::vector<std::string> playerList,
                        std::vector<PlayerColor> colorList,
                        unsigned map_x,
                        unsigned map_y);

private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_HH
