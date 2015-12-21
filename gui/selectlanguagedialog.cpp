/*
 * Copyright (C) Dag Henning Liodden Sørbø <daghenning@lioddensorbo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "selectlanguagedialog.h"
#include "ui_selectlanguagedialog.h"
#include "settingshandler.h"
#include "i18n.h"
#include <QDesktopWidget>
#include <QCommandLinkButton>

class SelectLanguageButton : public QCommandLinkButton {
    Q_OBJECT

public:
    SelectLanguageButton(QString lang, QString code, QString description)
        : QCommandLinkButton(lang, description),
          _langCode(code)
    {
    }

    QString langCode () {return _langCode;}

private:
    QString _langCode;
};

// Necessary in order to define Q_OBJECT subclass SelectLanguageButton in source file
#include "selectlanguagedialog.moc"


SelectLanguageDialog::SelectLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectLanguageDialog)
{
    ui->setupUi(this);

    for (int i = 0; i < NUM_LANGUAGES; ++i) {
        const char** language = LANGUAGES[i];
        SelectLanguageButton* btn = new SelectLanguageButton(language[0], language[1], language[2]);
        connect(btn, SIGNAL(clicked()), SLOT(selectLanguageClicked()));
        ui->languagesLayout->addWidget(btn);
    }

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    adjustSize();
}

SelectLanguageDialog::~SelectLanguageDialog()
{
    delete ui;
}

void SelectLanguageDialog::selectLanguageClicked()
{
    SelectLanguageButton *button = qobject_cast<SelectLanguageButton*>(sender());
    if (!button) {
        return;
    }

    SettingsHandler::setLanguage(button->langCode());
    accept();
}
