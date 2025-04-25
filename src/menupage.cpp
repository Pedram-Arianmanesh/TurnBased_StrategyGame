#include "menupage.h"
#include "playerdialog.h"
#include "gamepage.h"
#include <QMessageBox>


MenuPage::MenuPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::MenuPage)
{
    ui->setupUi(this);

    connect(ui->GalleryButton, &QPushButton::clicked, this, &MenuPage::onGalleryClicked);
    connect(ui->StartPvPButton, &QPushButton::clicked, this, &MenuPage::onStartPvPClicked);
}

void MenuPage::onGalleryClicked()
{
    // فعلاً یه پیام ساده؛ بعداً می‌تونه یه صفحه‌ی گالری اختصاصی باشه
    QMessageBox::information(this, "گالری", "گالری Agentها به‌زودی اضافه می‌شود!");
}

void MenuPage::onStartPvPClicked()
{
    PlayerDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        GamePage *game = new GamePage(nullptr,
                                      dialog.player1Name(),
                                      dialog.player2Name());
        game->show();
        this->close();
    }
}


