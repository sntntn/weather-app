#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{

}


void SettingsDialog::onSaveClicked()
{
    accept();
}
