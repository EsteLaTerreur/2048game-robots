#ifndef LISTECASES_H
#define LISTECASES_H
#include <QObject>
#include <string>
#include <iostream>
#include <vector>
#include "case.h"
using namespace std;

class ListeCases :public QObject
{ Q_OBJECT
public:
    explicit ListeCases(int size=16, QObject *parent = nullptr);
    ~ListeCases();
    Case *TAB;
    int score;
    int bestscore;
    int meilleure_tuile;
    bool partie_terminee;
    QString meilleure_couleur;
    bool peutJouer();
    // recopie
    ListeCases(const ListeCases& other);
    ListeCases& operator=(const ListeCases& other);
    // logique du jeu
    Q_INVOKABLE void lirePartie(vector<int> donneePartie);
    Q_INVOKABLE void lireFichier(QString adresse);
    Q_INVOKABLE void ecrireFichier();
    Q_INVOKABLE void updateScore();
    Q_INVOKABLE void trouveMeilleuretuile();
    Q_INVOKABLE void aleatoire();
    Q_INVOKABLE void tour(int indice);
    Q_INVOKABLE void nouveaujeu(bool a_clique=true);
    Q_INVOKABLE void nouvellepalette();
    Q_INVOKABLE void update4cases(ListeCases& liste4cases);
    Q_INVOKABLE void essayeDeDeplacer(Case& C1, Case& C2);
    Q_INVOKABLE void essayeDeFusionner(Case& C1, Case& C2);
    // partie robot
    Q_INVOKABLE void lanceRobot0();
    Q_INVOKABLE void lanceRobot1();
    Q_INVOKABLE void lanceRobot2();
    Q_INVOKABLE void lanceRobot3();
    Q_INVOKABLE void pauseRobot();
    Q_INVOKABLE int tourRobot(int indice);
    Q_INVOKABLE int update4casesRobot(ListeCases& liste4cases);
    Q_INVOKABLE void essayeDeDeplacerRobot(Case& C1, Case& C2);
    Q_INVOKABLE int essayeDeFusionnerRobot(Case& C1, Case& C2);
    Q_INVOKABLE int compteCasesVides();

    Q_PROPERTY(QString score READ readScore NOTIFY scoreChanged)
    Q_PROPERTY(QString bestscore READ readbestScore NOTIFY bestscoreChanged)
    Q_PROPERTY(QString meilleure_tuile READ readmeilleuretuile NOTIFY meilleuretuileChanged)
    Q_PROPERTY(QString meilleure_couleur READ readmeilleuretuileCouleur NOTIFY meilleuretuileCouleurChanged)
    Q_PROPERTY(bool partie_terminee READ readpartieTerminee NOTIFY partieTermineeChanged)
    Q_PROPERTY(NOTIFY popup)

private:
    int taille;
    bool robotPause;
    bool unRobotLance;
    QString readScore();
    QString readbestScore();
    QString readmeilleuretuile();
    QString readmeilleuretuileCouleur();
    bool readpartieTerminee();
signals:
    void scoreChanged();
    void bestscoreChanged();
    void meilleuretuileChanged();
    void meilleuretuileCouleurChanged();
    void partieTermineeChanged();
    void popup();
};

#endif // LISTECASES_H
