#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QTextEdit>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QInputDialog>
#include <QIcon>
#include <QTime>
#include <QDateTime>
#include <QPalette>
#include <QShortcut>
#include <QComboBox>
#include <fcntl.h>
#include "SettingsUI.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow()
    {
        setupUI();
        connectButtons();
    }
    ~MainWindow()
    {

    }
    int New;

private:
    SettingsUI settings;
    QLineEdit *NomLineEdit;
    QLineEdit *PrenomLineEdit;
    QLineEdit *ClasseLineEdit;
    QShortcut *shortcutMed;
    QShortcut *shortcutFlemme;
    QComboBox *ComboBox1;
    QTextEdit *TextEdit1;
    QPushButton *QuitButton;
    QPushButton *ApplyButton;
    QPushButton *ToolsButton;
    QScreen *screen;
    QLabel *Spacer;
    QLabel *Title;
    int ToolsWidowStatus;

    void setupUI()
    {
        New = 0;
        screen = QGuiApplication::primaryScreen();
        QWidget *window = new QWidget;
        QIcon progIcon(":/Images/Icon.png");
        NomLineEdit = new QLineEdit(this);
        PrenomLineEdit = new QLineEdit(this);
        ClasseLineEdit = new QLineEdit(this);
        TextEdit1 = new QTextEdit(this);
        QuitButton = new QPushButton("Quitter", this);
        ApplyButton = new QPushButton("Enregistrer", this);
        ToolsButton = new QPushButton("Outils", this);
        shortcutFlemme = new QShortcut(QKeySequence(tr("Ctrl+M, Ctrl+I, Ctrl+C, Ctrl+H")), this);
        ComboBox1 = new QComboBox(this);
        Spacer = new QLabel(this);
        Title = new QLabel(this);
        QPixmap SpacerImage(":/Images/Spacer.png");
        QPixmap TitleImage(":/Images/Title.png");
        Spacer->setPixmap(SpacerImage);
        Title->setPixmap(TitleImage);
        NomLineEdit->setFixedWidth(300);
        PrenomLineEdit->setFixedWidth(300);
        ClasseLineEdit->setFixedWidth(300);
        ComboBox1->setFixedWidth(300);
        QuitButton->setFixedWidth(148);
        ApplyButton->setFixedWidth(148);
        ToolsButton->setFixedWidth(300);
        Spacer->setFixedSize(300, 2);
        Title->setFixedSize(342, 71);
        TextEdit1->setFixedSize(800, 150);

        ToolsWidowStatus = 0;
        ResetFields();
        TextEdit1->setReadOnly(1);
        TextEdit1->setAlignment(Qt::AlignCenter);
        TextEdit1->append("Bienvenue dans PCECDI ! Merci à Mme Noiret pour l'idée de ce projet pour le CDI !\nRentrer votre nom, prénom , classe et enfin une raison afin d\'être enregistré.\n|----------------------------------------------------------------------------------------|\n");
        TextEdit1->setAlignment(Qt::AlignLeft);

        QVBoxLayout *layout = new QVBoxLayout(window);
        QVBoxLayout *Vlayout = new QVBoxLayout;
        QHBoxLayout *Hlayout = new QHBoxLayout;
        QHBoxLayout *Hlayout2 = new QHBoxLayout;
        QHBoxLayout *Hlayout3 = new QHBoxLayout;
        QHBoxLayout *Hlayout4 = new QHBoxLayout;

        Hlayout3->setSpacing(0);
        Hlayout4->setSpacing(0);

        layout->addLayout(Hlayout3);
        layout->addLayout(Hlayout);
        layout->addLayout(Hlayout4);

        Hlayout4->addWidget(TextEdit1);
        Hlayout3->addWidget(Title);

        Hlayout->addLayout(Vlayout);
        Vlayout->addWidget(NomLineEdit);
        Vlayout->addWidget(PrenomLineEdit);
        Vlayout->addWidget(ClasseLineEdit);
        Vlayout->addWidget(ComboBox1);
        Vlayout->addLayout(Hlayout2);
        Hlayout2->addWidget(ApplyButton);
        Hlayout2->addWidget(QuitButton);
        Vlayout->addWidget(Spacer);
        Vlayout->addWidget(ToolsButton);
        setCentralWidget(window);
        setWindowIcon(progIcon);
        setWindowTitle("PCECDI");
        setMinimumSize(820, 450);
        TextEdit1->append("[PCECDI] Le programme s'est lancé avec succès. ");

        QPixmap bkgnd(":/Images/WallPaper.jpg");
        bkgnd = bkgnd.scaled(screen->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }

    void connectButtons()
    {
        QObject::connect(QuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
        QObject::connect(ApplyButton, SIGNAL(clicked()), this, SLOT(Register()));
        QObject::connect(ToolsButton, SIGNAL(clicked()), this, SLOT(LaunchSettingsUI()));
        QObject::connect(shortcutFlemme, SIGNAL(activated()), this, SLOT(Mich()));
    }

    void RebootRegister()
    {
        Register();
    }

    void ResetFields()
    {
        NomLineEdit->setText("");
        PrenomLineEdit->setText("");
        ClasseLineEdit->setText("");
        ComboBox1->clear();
        ComboBox1->setPlaceholderText("Je suis venu(e) au CDI pour...");
        NomLineEdit->setPlaceholderText("Nom :");
        PrenomLineEdit->setPlaceholderText("Prénom :");
        ClasseLineEdit->setPlaceholderText("Classe :");

        ComboBox1->addItem("Travailler sur les postes");
        ComboBox1->addItem("Dessiner");
        ComboBox1->addItem("Apprendre");
        ComboBox1->addItem("Lire");
        ComboBox1->addItem("Faire un exposé");
        ComboBox1->addItem("Voir des exposés");
        ComboBox1->addItem("Jouer au jeux de sociétés");
        ComboBox1->addItem("Jouer de la musique");
        ComboBox1->addItem("Faire ses devoirs");
        ComboBox1->addItem("Se connecter à l'ENT");
        ComboBox1->addItem("Jouer à des escape games");
        ComboBox1->addItem("Faire des recherches");
        ComboBox1->addItem("Aider des élèves");
        ComboBox1->addItem("Venir en tant que délégué CDI");
        ComboBox1->addItem("Faire du théâtre");
        ComboBox1->addItem("Aider Mme Noiret");
        ComboBox1->addItem("Exclusion");
        ComboBox1->addItem("Dormir");
        ComboBox1->addItem("S'informer");
        ComboBox1->addItem("Club");
        ComboBox1->addItem("Retard");
        ComboBox1->addItem("Professeur absent");
        ComboBox1->addItem("Rendez-vous médical");
    }

private slots:
    void Mich()
    {
        NomLineEdit->setText("Durand");
        PrenomLineEdit->setText("Michel");
        ClasseLineEdit->setText("4C");
        ComboBox1->setCurrentIndex(0);
    }

    void LaunchSettingsUI()
    {
        settings.move(screen->geometry().width()/2 - settings.width()/2, screen->geometry().height()/2.5 - settings.height()/2);
        settings.ResetFieldsSettings();
        settings.show();
    }

    void Register()
    {
        bool ok;

        QDateTime *DateWithTime = new QDateTime(QDateTime::currentDateTime());
        QTime ProgTime = DateWithTime->time();
        QDate ProgDate = DateWithTime->date();

        QString CSVFileName = QString("%1 %2.csv").arg(ProgDate.year(), 4, 10, QChar('0')).arg(ProgDate.month(), 2, 10, QChar('0'));
        QString ProgDate2 = QString("%1/%2/%3").arg(ProgDate.day(), 2, 10, QChar('0')).arg(ProgDate.month(), 2, 10, QChar('0')).arg(ProgDate.year(), 4, 10, QChar('0'));
        QString ProgTime2;

        int compsec = ProgTime.second();
        int compheure = ProgTime.hour();
        int compmin = ProgTime.minute();

        switch (compheure)
        {
            case 7:
                ProgTime2 = QString("7:20 - 8:20");
                break;

            case 8:
                if(compmin < 20) ProgTime2 = QString("7:20 - 8:20");
                if(compmin >= 20) ProgTime2 = QString("8:20 - 9:20");
                break;

            case 9:
                if(compmin < 20) ProgTime2 = QString("8:20 - 9:20");
                if(compmin >= 20) ProgTime2 = QString("9:20 - 10:20");
                break;

            case 10:
                if(compmin < 20) ProgTime2 = QString("9:20 - 10:20");
                if(compmin >= 35) ProgTime2 = QString("10:20 - 11:35");
                break;

            case 11:
                if(compmin < 35) ProgTime2 = QString("10:20 - 11:35");
                if(compmin >= 35) ProgTime2 = QString("11:35 - 12:35");
                break;

            case 12:
                if(compmin < 35) ProgTime2 = QString("11:35 - 12:35");
                if(compmin >= 35) ProgTime2 = QString("12:35 - 13:00");
                break;

            default:
                ProgTime2 = QString("%1:00 - %2:00").arg(compheure).arg(compheure+1);
                break;
        }

        QString nom = NomLineEdit->text();
        QString prenom = PrenomLineEdit->text();
        QString classe = ClasseLineEdit->text();
        QString raison = ComboBox1->currentText();

        nom.remove(",");
        prenom.remove(",");
        classe.remove(",");
        nom.remove(";");
        prenom.remove(";");
        classe.remove(";");

        QFile CSVFile(QDir::currentPath() + "/CSVFiles/" + CSVFileName);
        if(!CSVFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            mkdir("CSVFiles");
            creat("CSVFiles/"+CSVFileName.toUtf8(), 0777);
            CSVFile.open(QIODevice::ReadWrite | QIODevice::Text);
            QTextStream hellostream(&CSVFile);
            QString line = "Dates :,Heures :,Noms :,Prénoms :,Classes :, Raisons :\n";
            hellostream<<line;
            CSVFile.close();
            RebootRegister();
        }
        else
        {
            if(nom == "" || prenom == "" || classe == "" || raison == "" || classe.size() != 2)
            {
                if(nom == "")
                {
                    NomLineEdit->setPlaceholderText("Vide...");
                }
                if(prenom == "")
                {
                    PrenomLineEdit->setPlaceholderText("Vide...");
                }
                if(classe == "" || classe.size() != 2)
                {
                    ClasseLineEdit->setText("");
                    ClasseLineEdit->setPlaceholderText("La classe doit être un chiffre puis une lettre.");
                }
                if(raison == "")
                {
                    ComboBox1->setPlaceholderText("Veuillez choisir un option...");
                }
            }
            else
            {
                if(raison == "Travailler sur les postes" || raison == "Se connecter à l'ENT")
                {
                    int numposte = QInputDialog::getInt(this, tr("Numéro de Poste"), tr("Entre ton numéro de poste :"), 1, 1, 9, 1, &ok);
                    if (ok && !numposte == 0)
                    {
                        raison = QString("%1 - poste : %2").arg(raison).arg(numposte);
                    }
                    else
                    {
                        return;
                    }
                }

                CSVFile.close();
                CSVFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
                QString line = ProgDate2 + "," + ProgTime2 + "," + nom + "," + prenom + "," + classe + "," + raison + "\n";
                QString heurelog = QString("%1:%2:%3").arg(compheure, 2, 10, QChar('0')).arg(compmin, 2, 10, QChar('0')).arg(compsec, 2, 10, QChar('0'));
                QTextStream hellostream(&CSVFile);
                hellostream<<line;
                CSVFile.close();
                TextEdit1->append(QString("[PCECDI] [%1] Élève %2 %3 en %4 à %5, le %6. Qui est venu(e) pour %7 enregistré(e) avec succès !").arg(heurelog, nom, prenom, classe, ProgTime2, ProgDate2, raison));
                ResetFields();
            }
        }
    }
};
#endif // MAINWINDOW_H
