#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QApplication>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QSize>
#include <QPixmap>
#include <QTextEdit>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QScreen>
#include <QHBoxLayout>
#include <QDir>
#include <fcntl.h>

class SettingsUI : public QWidget
{
    Q_OBJECT

public:
    SettingsUI(QWidget *parent = nullptr)
    {
        setupUI();
        connectButtons();
    }
    ~SettingsUI()
    {

    }

    void ResetFieldsSettings()
    {
        TextEdit2->setText(QDir::currentPath() + "/CSVFiles");
    }

private:
    QWidget *GeneralTab;
    QWidget *AboutTab;
    QTabWidget *tabWidget;
    QLabel *CreditsShort;
    QLabel *CSVPath;
    QLabel *TitleandIcon;
    QLabel *Credits;
    QPushButton *OKButton;
    QPushButton *AboutQt;
    QTextEdit *TextEdit2;
    QPushButton *OpenDirCSVButton;
    QPushButton *OpenDirExeButton;

    void setupUI()
    {
        QVBoxLayout *settingsLayout = new QVBoxLayout;
        QVBoxLayout *settingsGeneralLayout = new QVBoxLayout;
        QVBoxLayout *settingsAboutLayout = new QVBoxLayout;
        QHBoxLayout *settingsLayoutH = new QHBoxLayout;
        QHBoxLayout *settingsGeneralLayoutH = new QHBoxLayout;
        TextEdit2 = new QTextEdit(this);
        CSVPath = new QLabel("Chemin du dossier\ndes fichiers CSV :", this);
        OpenDirCSVButton = new QPushButton("Ouvrir le dossier des fichiers CSV", this);
        OpenDirExeButton = new QPushButton("Ouvrir le dossier de l'éxecutable", this);
        AboutQt = new QPushButton("À Propos de Qt", this);
        TitleandIcon = new QLabel(this);
        Credits = new QLabel("Ce programme a été créé pour le CDI par Michel Durand.\nMerci à Mme Noiret pour l'idée de ce projet.\nL'image de fond d'écran a été\nprise sur : URL.\nCe programme a été créé avec Qt. Pour plus d'info :\n", this);
        TitleandIcon->setPixmap(QPixmap(":/Images/TitleWithIcon.png"));
        TitleandIcon->setFixedSize(326, 42);
        TextEdit2->setFixedSize(250, 100);
        AboutTab = new QWidget;
        GeneralTab = new QWidget;
        OKButton = new QPushButton("OK", this);
        OKButton->setFixedWidth(75);
        CreditsShort = new QLabel("Par Michel Durand", this);
        tabWidget = new QTabWidget(this);
        tabWidget->addTab(GeneralTab, "General");
        tabWidget->addTab(AboutTab, "About");
        setLayout(settingsLayout);
        settingsLayout->addWidget(tabWidget);
        settingsLayout->addLayout(settingsLayoutH);
        settingsLayoutH->addWidget(CreditsShort);
        settingsLayoutH->addWidget(OKButton);

        GeneralTab->setLayout(settingsGeneralLayout);
        AboutTab->setLayout(settingsAboutLayout);
        settingsAboutLayout->addWidget(TitleandIcon);
        settingsAboutLayout->addWidget(Credits);
        settingsAboutLayout->addWidget(AboutQt);
        settingsGeneralLayout->addLayout(settingsGeneralLayoutH);
        settingsGeneralLayout->addWidget(OpenDirCSVButton);
        settingsGeneralLayout->addWidget(OpenDirExeButton);
        settingsGeneralLayoutH->addWidget(CSVPath);
        settingsGeneralLayoutH->addWidget(TextEdit2);

        ResetFieldsSettings();
        setWindowTitle("Dev Mode");
        setWindowIcon(QIcon(":/Images/Icon.png"));
        setFixedSize(400, 300);
    }

    void connectButtons()
    {
        QObject::connect(OKButton, SIGNAL(clicked()), this, SLOT(quit()));
        QObject::connect(OpenDirCSVButton, SIGNAL(clicked()), this, SLOT(OpenCSVFile()));
        QObject::connect(OpenDirExeButton, SIGNAL(clicked()), this, SLOT(OpenExeFile()));
        QObject::connect(AboutQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    }

private slots:
    void quit()
    {
        hide();
    }

    void OpenExeFile()
    {
        QDesktopServices::openUrl(QUrl(QDir::currentPath()));
    }

    void OpenCSVFile()
    {
        QString CSVPath = QString("%1/CSVFiles").arg(QDir::currentPath());
        if(!QDesktopServices::openUrl(QUrl(CSVPath)))
        {
            mkdir("CSVFiles");
            QDesktopServices::openUrl(QUrl(CSVPath));
        }
    }
};
#endif // MAINSETTINGS_H
