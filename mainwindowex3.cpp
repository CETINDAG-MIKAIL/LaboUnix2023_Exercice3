#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
    fprintf(stderr, "Clic sur le bouton Lancer Recherche\n");

    pid_t idFils[3], id;
    int retour, status;
    int fd;
    
    fd = open("Trace.log", O_RDWR | O_CREAT | O_APPEND, 0666);
    if (fd == -1) {
        perror("Erreur de open()");
        exit(1);
    }

    if (dup2(fd, STDERR_FILENO) == -1) {
        perror("Erreur de dup2()");
        exit(1);
    }

    if (recherche1Selectionnee() == true)
    {
      if ((id = fork()) == -1) 
      {
        perror("Erreur de fork");
      } 
      idFils[0] = id;
      if (idFils[0] == 0)
      {
            if (execlp("Lecture", "Lecture", getGroupe1(), NULL) == -1) 
            {
                perror("Erreur execlp");
            }
      }
    }
    if (recherche2Selectionnee() == true)
    {
      if ((id = fork()) == -1) 
      {
        perror("Erreur de fork");
      } 
      idFils[1] = id;
      if (idFils[1] == 0)
      {
            if (execlp("Lecture", "Lecture", getGroupe2(), NULL) == -1) 
            {
                perror("Erreur execlp");
            }
      }
    }
    if (recherche3Selectionnee() == true)
    {
      if ((id = fork()) == -1) 
      {
        perror("Erreur de fork");
      } 
      idFils[2] = id;
      if (idFils[2] == 0)
      {
            if (execlp("Lecture", "Lecture", getGroupe3(), NULL) == -1) 
            {
                perror("Erreur execlp");
            }
      }
    }

    while ((retour = wait(&status)) != -1) {
        if (!WIFEXITED(status)) {
            printf("Fils non terminé par exit\n");
        }

        int retour_status = WEXITSTATUS(status);

        if (retour == idFils[0]) {
            setResultat1(retour_status);
        } else if (retour == idFils[1]) {
            setResultat2(retour_status);
        } else if (retour == idFils[2]) {
            setResultat3(retour_status);
        }
    }
}


void MainWindowEx3::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton vider\n");
  // TO DO
ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();

}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  // TO DO
  exit(0);
}
