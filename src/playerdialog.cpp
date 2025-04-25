#include "playerdialog.h"
#include "gamepage.h"

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
    // اگر فیلدها خالی باشن می‌تونه پیام خطا بده ولی فعلاً فقط بریم به بازی
    GamePage *game = new GamePage(nullptr, player1Name(), player2Name());
    game->show();
    this->accept();
}
