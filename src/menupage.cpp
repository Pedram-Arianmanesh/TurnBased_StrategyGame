#include "menupage.h"
#include "playerdialog.h"
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
    // نمونه ساده برای ادامه‌ی پروژه
   // PlayerDialog *dialog = new PlayerDialog(this);
    //dialog->exec();  // یا show()، بسته به طراحی
}

