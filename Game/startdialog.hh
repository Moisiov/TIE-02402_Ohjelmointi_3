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
    /**
     * @brief accept intercepts Dialog ending and does a sanity check on start-up parameters
     * before sending parameters back to MapWindow and closing. Input fields have certain built-in
     * limits to disable too small / large map generation or too long names.
     * @pre Must have selected at least 2 players, and none of the names can be empty.
     */
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
