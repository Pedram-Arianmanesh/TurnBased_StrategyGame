#include "playerdialog.h"
#include <QMessageBox>

PlayerDialog::PlayerDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);

    connect(ui->StartButtonFinal, &QPushButton::clicked, this, &PlayerDialog::onStartClicked);
}

QString PlayerDialog::player1Name() const {
    return ui->Player1LineEdit->text();
}

QString PlayerDialog::player2Name() const {
    return ui->Player2LineEdit->text();
}

void PlayerDialog::onStartClicked()
{
    if (player1Name().isEmpty() || player2Name().isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Enter both player's names!");
        return;
    }

    this->accept();
}
