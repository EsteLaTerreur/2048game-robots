#include "listecases.h"
#include "case.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <cerrno>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>
#include <QTime>
#include <QCoreApplication>

using namespace std;
// Constructeur
ListeCases::ListeCases(int size,QObject *parent) {

    if(size>0){
        taille = size;
    }else taille = 16;
    TAB = new Case[taille];

    for (int i = 0; i < this->taille; ++i) {
        TAB[i].set_id(i);
        TAB[i].set_val(pow(2,0)); // case d'indice i, initialisée à 2^0
        TAB[i].set_couleur();
    }
    if(taille==16){ // pour ne pas modifier la liste de 4 cases utilisée dans la méthode coup
        bool a_clique = false;
        this->nouveaujeu(a_clique);
        this->robotPause = false;
    }
}

ListeCases::~ListeCases() {
    delete[] TAB;
}

ListeCases::ListeCases(const ListeCases& other) {
    this->taille = other.taille;
    this->score = other.score;
    this->bestscore = other.bestscore;
    this->meilleure_tuile = other.meilleure_tuile;
    this->partie_terminee = other.partie_terminee;
    this->meilleure_couleur = other.meilleure_couleur;
    this->TAB = new Case[this->taille];
    for (int i = 0; i < this->taille; ++i) {
        this->TAB[i] = other.TAB[i];
    }
}
ListeCases& ListeCases::operator=(const ListeCases& other) {
    if (this != &other) {
        // Perform a deep copy of member variables
        this->taille = other.taille;
        this->score = other.score;
        this->bestscore = other.bestscore;
        this->meilleure_tuile = other.meilleure_tuile;
        this->partie_terminee = other.partie_terminee;
        this->meilleure_couleur = other.meilleure_couleur;
        delete[] this->TAB;
        this->TAB = new Case[this->taille];
        for (int i = 0; i < this->taille; ++i) {
            this->TAB[i] = other.TAB[i];
        }
    }
    return *this;
}

// Logique de l'application

void ListeCases::updateScore(){
    score = 0;
    for (int i=0;i<16;i++){
        score = score + TAB[i].get_val();
    }
    emit scoreChanged();
}

void ListeCases::trouveMeilleuretuile(){
    int maxi = 0;
    QString couleur;
    for (int i=0;i<16;i++){
        if (TAB[i].get_val()>maxi){
            maxi = TAB[i].get_val();
            couleur = TAB[i].get_couleur();
        }
    }
    meilleure_couleur = couleur;
    meilleure_tuile = maxi;
    emit meilleuretuileChanged();
    emit meilleuretuileCouleurChanged();
}

void ListeCases::aleatoire(){
    // on récupère les indices des cases vides :
    vector<int> listeIndice;
    for(int ind=0;ind<16;ind++){
        if(TAB[ind].get_val()==1){// case vide
            listeIndice.push_back(ind);
        }
    }
    // puis on tire un indice aléatoire parmi cette liste
    if(listeIndice.size()>=2){ // le jeu se déroule normalement
        srand(static_cast<unsigned int>(time(nullptr)));
        int indice = rand()%listeIndice.size();
        int indiceRandom = listeIndice[indice];
        TAB[indiceRandom].aleatoire(); // on initialise cette case vide
    } else if(listeIndice.size()==1){ // la dernière case vide est initialisée avc une valeur
        TAB[listeIndice[0]].aleatoire();
        if(this->peutJouer()){ // il existe un coup pour que le joueur puisse bouger
            // rien ne se passe, le joueur doit trouver le coup
        } else { // fin de la partie, le joueur ne peut plus jouer
            partie_terminee = true;
            // écriture du fichier meilleur score si besoin
            if (score >= bestscore) {
                bestscore = score;
                ofstream fichier("../Jeu2048/src/parties/best_score.txt", ofstream::out);
                if (fichier.is_open()) {
                    fichier << this->bestscore ;
                    fichier.close();
                } else {
                    cerr << "Erreur lors de l'ouverture du fichier best en écriture." << endl;
                }
            }
            emit partieTermineeChanged();
        }
    }
}

bool ListeCases::peutJouer(){
    bool peut_jouer = false;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(TAB[4*i+j].get_val()==TAB[4*i+j+1].get_val() || TAB[4*i+j].get_val()==TAB[4*i+j+4].get_val()){
                peut_jouer = true;
            }
        }
    }
    return peut_jouer;
}

void ListeCases::tour(int indice){
    this->ecrireFichier(); // on commence par sauvegarder la position avant de la modifier, pour le undo
    if(indice==0){ // flèche du haut
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[12+i];
            liste4cases->TAB[1] = this->TAB[8+i];
            liste4cases->TAB[2] = this->TAB[4+i];
            liste4cases->TAB[3] = this->TAB[0+i];
            this->update4cases(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[12+i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[8+i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[4+i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[0+i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[12+i].set_couleur();
            this->TAB[8+i].set_couleur();
            this->TAB[4+i].set_couleur();
            this->TAB[0+i].set_couleur();
        }
    }
    if(indice==1){ // flèche de droite
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[0+4*i];
            liste4cases->TAB[1] = this->TAB[1+4*i];
            liste4cases->TAB[2] = this->TAB[2+4*i];
            liste4cases->TAB[3] = this->TAB[3+4*i];
            this->update4cases(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[0+4*i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[1+4*i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[2+4*i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[3+4*i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[0+4*i].set_couleur();
            this->TAB[1+4*i].set_couleur();
            this->TAB[2+4*i].set_couleur();
            this->TAB[3+4*i].set_couleur();
        }
    }
    if(indice==2){ // flèche du bas
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[0+i];
            liste4cases->TAB[1] = this->TAB[4+i];
            liste4cases->TAB[2] = this->TAB[8+i];
            liste4cases->TAB[3] = this->TAB[12+i];
            this->update4cases(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[0+i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[4+i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[8+i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[12+i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[0+i].set_couleur();
            this->TAB[4+i].set_couleur();
            this->TAB[8+i].set_couleur();
            this->TAB[12+i].set_couleur();
        }
    }
    if(indice==3){ // flèche de gauche
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[3+4*i];
            liste4cases->TAB[1] = this->TAB[2+4*i];
            liste4cases->TAB[2] = this->TAB[1+4*i];
            liste4cases->TAB[3] = this->TAB[0+4*i];
            this->update4cases(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[3+4*i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[2+4*i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[1+4*i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[0+4*i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[3+4*i].set_couleur();
            this->TAB[2+4*i].set_couleur();
            this->TAB[1+4*i].set_couleur();
            this->TAB[0+4*i].set_couleur();
        }
    }
    this->aleatoire();
    this->trouveMeilleuretuile();//update de la meilleure tuile
}

void ListeCases::update4cases(ListeCases& liste4cases){
    // on commence par déplacer toutes les cases vers la droite
    for(int i=3;i>0;i--){
        this->essayeDeDeplacer(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // encore une fois
    for(int i=3;i>0;i--){
        this->essayeDeDeplacer(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // et une 3ème
        for(int i=3;i>0;i--){
        this->essayeDeDeplacer(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // puis on fusionne les cases adjacentes de la même valeur (une case ne peut fusionner qu'une fois)
    for(int i=3;i>0;i--){
        this->essayeDeFusionner(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // on redéplace éventuellement les cases vers la droite encore une fois
    for(int i=3;i>0;i--){
        this->essayeDeDeplacer(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // et une dernière fois
    for(int i=3;i>0;i--){
        this->essayeDeDeplacer(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
}

void ListeCases::essayeDeDeplacer(Case& C1, Case& C2){
    if(C2.get_val()==1){ // case de droite vide
        if(C1.get_val()!=1){ // case de gauche non vide
            C2.set_val(C1.get_val());
            C1.set_val(pow(2,0));
        }
    }
}

void ListeCases::essayeDeFusionner(Case& C1, Case& C2){
    if(C1.get_val()==C2.get_val() && C1.get_val()!=1){ // même valeur et case non nulle
        C2.set_val(C2.get_val()*2);
        C1.set_val(pow(2,0));
        C2.set_couleur();
        score = score + C2.get_val();
        if (score > bestscore){
            bestscore = score;
            emit bestscoreChanged();
        }
        emit scoreChanged();
    }
}

void ListeCases::nouveaujeu(bool a_clique){
    for(int i=0;i<16;i++){
        if(TAB[i].get_val()!=1){
            TAB[i].set_val(pow(2,0));
            TAB[i].set_couleur();
        }
    }
    // lecture du meilleur score
    ifstream fichier("../Jeu2048/src/parties/best_score.txt");
    if (fichier){
        string L1;
        while(getline(fichier, L1)){
            bestscore = atoi(L1.c_str());
        }
    } else {
        cerr << "Erreur de lecture du fichier meilleur score." << endl;
    }

    if(a_clique){ // si la nouvelle partie a été demandé par le client via le bouton
        // écriture meilleur score si besoin
        if (score >= bestscore) {
            bestscore = score;
            ofstream fichier("../Jeu2048/src/parties/best_score.txt", ofstream::out);
            if (fichier.is_open()) {
                fichier << this->bestscore ;
                fichier.close();
            } else {
                cerr << "Erreur lors de l'ouverture du fichier best en écriture." << endl;
            }
        }
    }

    // initialisation nouvelle partie
    score = 0;
    partie_terminee = false;
    this->aleatoire();
    this->aleatoire();
    this->trouveMeilleuretuile();
    emit scoreChanged();
    emit bestscoreChanged(); 
}

void ListeCases::nouvellepalette(){
    for (int i=0;i<16;i++){
        TAB[i].autre_palette();
        TAB[i].set_couleur();
    }
}
// Emit au qml

QString ListeCases::readScore() {
    emit scoreChanged();
    return QString::number(score);
}

QString ListeCases::readbestScore() {
    emit bestscoreChanged();
    return QString::number(bestscore);
}

QString ListeCases::readmeilleuretuile() {
    emit meilleuretuileChanged();
    return QString::number(meilleure_tuile);
}
QString ListeCases::readmeilleuretuileCouleur() {
    emit meilleuretuileCouleurChanged();
    return QString(meilleure_couleur);
}
bool ListeCases::readpartieTerminee() {
    emit partieTermineeChanged();
    return partie_terminee;
}


 // Lecture / écriture de fichiers
void ListeCases::lirePartie(vector<int> donneePartie){
    for(int i=0;i<17;i++){
        if(i<16){
            TAB[i].set_val((pow(2,donneePartie[i])));
            TAB[i].set_couleur();
        } else {
            score = donneePartie[i];
            emit scoreChanged();
        }
    }
    partie_terminee = false;
    emit partieTermineeChanged();
}

void ListeCases::lireFichier(QString adresse){

    ifstream fichier(adresse.toStdString());
    if (fichier) {
        vector<int> donneesPartie;
        string ligne;
        while (getline(fichier, ligne)) {
            int chiffre = atoi(ligne.c_str());
            donneesPartie.push_back(chiffre);
        }
        this->lirePartie(donneesPartie);
    } else {
        cerr << "Erreur lors de l'ouverture du fichier : " << strerror(errno) << endl;
    }
}

void ListeCases::ecrireFichier(){
    const char* nomFichier = "../Jeu2048/src/parties/coup_precedent_pour_undo.txt";
    ofstream fichier(nomFichier, ofstream::trunc); // va troncer le fichier pour écraser l'ancienne position
                                                    // et en écrire une nouvelle
    if (fichier.is_open()) {
        for (int i=0;i<16;i++) {
            fichier << log2(this->TAB[i].get_val()) << endl; // on ajoute les valeurs des cases
        }
        fichier << this->score << endl; // puis le score
        fichier.close();
    } else {
        cerr << "Erreur lors de l'ouverture du fichier en écriture." << endl;
    }
}


// partie robot
void ListeCases::lanceRobot0(){ // POUR LE FAIRE JOUER AU HASARD
    if (!unRobotLance){
        if(robotPause){
            robotPause = false;
        }
        cout << "Robot 0 demarre." << endl;
        int compteur = 0;
        int nb_ite_max = 1000;
        while(compteur<nb_ite_max && not(partie_terminee) && not(robotPause)){
            unRobotLance = true;
            // on joue un coup au hasard
            srand(static_cast<unsigned int>(time(nullptr)));
            this->tour(rand()%4);

            // et on attends
            QTime dieTime= QTime::currentTime().addMSecs(100);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            compteur+=1;
        }
        unRobotLance = false;
        if(partie_terminee){
            emit popup();
        }
    } else {
        cout << "Un robot est déjà lancé."<<endl;
    }
}

void ListeCases::lanceRobot1(){ // POUR JOUER LE COUP QUI FAIT LE MEILLEUR SCORE PARMI LES 4
    if (!unRobotLance){
        if(robotPause){
            robotPause = false;
        }
        cout << "Robot 0 demarre." << endl;
        int compteur = 0;
        int nb_ite_max = 1000;
        while(compteur<nb_ite_max && not(partie_terminee) && not(robotPause)){
            unRobotLance = true;
            ListeCases listeCopie0(*this);
            ListeCases listeCopie1(*this);
            ListeCases listeCopie2(*this);
            ListeCases listeCopie3(*this);
            listeCopie0.tour(0);
            listeCopie1.tour(1);
            listeCopie2.tour(2);
            listeCopie3.tour(3);
            vector<int> listeScores;
            listeScores.push_back(listeCopie0.score);
            listeScores.push_back(listeCopie1.score);
            listeScores.push_back(listeCopie2.score);
            listeScores.push_back(listeCopie3.score);
            // recherche du meilleur score
            int maxIndice = 0;
            int maxValeur = listeScores[0];
            for (int i=1;i<listeScores.size();++i) {
                if (listeScores[i] > maxValeur) {
                    maxValeur = listeScores[i];
                    maxIndice = i;
                }
            }
            // on joue le coup qui maximise le prochain score
            this->tour(maxIndice);
            // et on attends
            QTime dieTime= QTime::currentTime().addMSecs(100);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            compteur+=1;
        }
        unRobotLance = false;
        if(partie_terminee){
            emit popup();
        }
    } else {
        cout << "Un robot est déjà lancé."<<endl;
    }
}


void ListeCases::lanceRobot2(){ // POUR JOUER UN COUP QUI FUSIONNE LE PLUS POSSIBLE
    if (!unRobotLance){
        if(robotPause){
            robotPause = false;
        }
        cout << "Robot 0 demarre." << endl;
        int compteur = 0;
        int nb_ite_max = 1000;
        while(compteur<nb_ite_max && not(partie_terminee) && not(robotPause)){
            unRobotLance = true;
            ListeCases listeCopie0(*this);
            ListeCases listeCopie1(*this);
            ListeCases listeCopie2(*this);
            ListeCases listeCopie3(*this);
            listeCopie0.score = 0;
            listeCopie1.score = 0;
            listeCopie2.score = 0;
            listeCopie3.score = 0;
            int nb_fusion0 = listeCopie0.tourRobot(0);
            int nb_fusion1 = listeCopie1.tourRobot(1);
            int nb_fusion2 = listeCopie2.tourRobot(2);
            int nb_fusion3 = listeCopie3.tourRobot(3);
            vector<int> listeScores;
            vector<int> listeFusions;
            listeScores.push_back(listeCopie0.score);
            listeScores.push_back(listeCopie1.score);
            listeScores.push_back(listeCopie2.score);
            listeScores.push_back(listeCopie3.score);
            listeFusions.push_back(nb_fusion0);
            listeFusions.push_back(nb_fusion1);
            listeFusions.push_back(nb_fusion2);
            listeFusions.push_back(nb_fusion3);
            cout << "liste nb fusions : "<<endl;
            for(int i=0;i<4;i++){
                cout << listeFusions[i] << endl;
            }
            // recherche du meilleur score
            int maxIndice = 0;
            int maxValeur = listeScores[0]*listeFusions[0];
            for (int i=1;i<listeScores.size();++i) {
                cout << "coup testé : " << i<<endl;
                cout << "nb fusions : " << listeFusions[i]<<endl;
                if (listeScores[i]*listeFusions[i] > maxValeur) {
                    maxValeur = listeScores[i]*listeFusions[i]; // on va prendre le produit score x nb_fusion occasionnés par le coup
                    maxIndice = i;
                }
            }

            // on joue le coup qui maximise le nombre de fusions et le score
            this->tour(maxIndice);
            // et on attends
            QTime dieTime= QTime::currentTime().addMSecs(100);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            compteur+=1;
        }
        unRobotLance = false;
        if(partie_terminee){
            emit popup();
        }
    } else {
        cout << "Un robot est déjà lancé."<<endl;
    }
}

void ListeCases::lanceRobot3(){  // POUR JOUER LE COUP QUI FAIT LE MEILLEUR SCORE
                                 // EN REGARDANT 3 COUPS EN PROFONDEUR
    if (!unRobotLance){
        if(robotPause){
            robotPause = false;
        }
        cout << "Robot 0 demarre." << endl;
        int compteur = 0;
        int nb_ite_max = 1000;
        while(compteur<nb_ite_max && not(partie_terminee) && not(robotPause)){
            unRobotLance = true;
            ListeCases listeCopie0(*this);
            ListeCases listeCopie1(*this);
            ListeCases listeCopie2(*this);
            ListeCases listeCopie3(*this);
            vector<int> listeScores(4,0);

            vector<ListeCases> listeProfondeur1;
            listeProfondeur1.push_back(listeCopie0);
            listeProfondeur1.push_back(listeCopie1);
            listeProfondeur1.push_back(listeCopie2);
            listeProfondeur1.push_back(listeCopie3);

            for(int i=0; i<4;i++){
                listeProfondeur1[i].score=0;
                listeProfondeur1[i].tour(i);
                listeScores[i]+=listeProfondeur1[i].score;
            }
            vector<ListeCases> listeProfondeur2; // 16 grilles
            for(int i=0; i<4;i++){
                for(int j=0;j<4;j++){
                    ListeCases listeCopieSuivante(listeProfondeur1[i]);
                    listeCopieSuivante.score = 0;
                    listeCopieSuivante.tour(j);
                    listeScores[i]+=listeCopieSuivante.score;
                    listeProfondeur2.push_back(listeCopieSuivante);
                }
            }
            for(int i=0; i<4;i++){
                for(int j=0;j<4;j++){
                    for(int k=0;k<4;k++){
                        ListeCases listeCopieSuivanteSuivante(listeProfondeur2[j+4*i]);
                        listeCopieSuivanteSuivante.score = 0;
                        listeCopieSuivanteSuivante.tour(k);
                        listeScores[i]+=listeCopieSuivanteSuivante.score;
                    }
                }
            }

            // on pondère les scores par le nombres de cases vides qu'il reste sur la grille
            for (int i=1;i<4;++i) {
                listeScores[i] = listeScores[i]*exp(listeProfondeur1[i].compteCasesVides());
            }

            // recherche du meilleur score
            int maxIndice = 0;
            int maxValeur = listeScores[0];
            for (int i=1;i<4;++i) {
                if (listeScores[i] > maxValeur) {
                    maxValeur = listeScores[i];
                    maxIndice = i;
                }
            }
            // on joue le coup qui maximise le prochain score
            this->tour(maxIndice);

            // et on attends
            QTime dieTime= QTime::currentTime().addMSecs(100);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            compteur+=1;
        }
        unRobotLance = false;
        if(partie_terminee){
            emit popup();
        }
    } else {
        cout << "Un robot est déjà lancé."<<endl;
    }
}

void ListeCases::pauseRobot(){
    if(not(robotPause)){
        robotPause = true;
    }
    cout << "Robot en pause." << endl;
}

int ListeCases::tourRobot(int indice){
    int nb_fusions=0;
    if(indice==0){ // flèche du haut
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[12+i];
            liste4cases->TAB[1] = this->TAB[8+i];
            liste4cases->TAB[2] = this->TAB[4+i];
            liste4cases->TAB[3] = this->TAB[0+i];
            nb_fusions = this->update4casesRobot(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[12+i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[8+i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[4+i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[0+i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[12+i].set_couleur();
            this->TAB[8+i].set_couleur();
            this->TAB[4+i].set_couleur();
            this->TAB[0+i].set_couleur();
        }
    }
    if(indice==1){ // flèche de droite
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[0+4*i];
            liste4cases->TAB[1] = this->TAB[1+4*i];
            liste4cases->TAB[2] = this->TAB[2+4*i];
            liste4cases->TAB[3] = this->TAB[3+4*i];
            nb_fusions = this->update4casesRobot(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[0+4*i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[1+4*i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[2+4*i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[3+4*i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[0+4*i].set_couleur();
            this->TAB[1+4*i].set_couleur();
            this->TAB[2+4*i].set_couleur();
            this->TAB[3+4*i].set_couleur();
        }
    }
    if(indice==2){ // flèche du bas
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[0+i];
            liste4cases->TAB[1] = this->TAB[4+i];
            liste4cases->TAB[2] = this->TAB[8+i];
            liste4cases->TAB[3] = this->TAB[12+i];
            nb_fusions = this->update4casesRobot(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[0+i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[4+i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[8+i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[12+i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[0+i].set_couleur();
            this->TAB[4+i].set_couleur();
            this->TAB[8+i].set_couleur();
            this->TAB[12+i].set_couleur();
        }
    }
    if(indice==3){ // flèche de gauche
        for(int i=0;i<4;i++){
            ListeCases* liste4cases = new ListeCases(4);
            liste4cases->TAB[0] = this->TAB[3+4*i];
            liste4cases->TAB[1] = this->TAB[2+4*i];
            liste4cases->TAB[2] = this->TAB[1+4*i];
            liste4cases->TAB[3] = this->TAB[0+4*i];
            nb_fusions = this->update4casesRobot(*liste4cases); // update pour chaque colonne, de bas en haut
            // on récupère les valeurs
            this->TAB[3+4*i].set_val(liste4cases->TAB[0].get_val());
            this->TAB[2+4*i].set_val(liste4cases->TAB[1].get_val());
            this->TAB[1+4*i].set_val(liste4cases->TAB[2].get_val());
            this->TAB[0+4*i].set_val(liste4cases->TAB[3].get_val());
            delete liste4cases;
            // et on actualise les couleurs
            this->TAB[3+4*i].set_couleur();
            this->TAB[2+4*i].set_couleur();
            this->TAB[1+4*i].set_couleur();
            this->TAB[0+4*i].set_couleur();
        }
    }
    this->aleatoire();
    return nb_fusions;
}

int ListeCases::update4casesRobot(ListeCases& liste4cases){
    int compteur_fusion = 0;
    // on commence par déplacer toutes les cases vers la droite
    for(int i=3;i>0;i--){
        this->essayeDeDeplacerRobot(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // encore une fois
    for(int i=3;i>0;i--){
        this->essayeDeDeplacerRobot(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // et une 3ème
    for(int i=3;i>0;i--){
        this->essayeDeDeplacerRobot(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // puis on fusionne les cases adjacentes de la même valeur (une case ne peut fusionner qu'une fois)
    for(int i=3;i>0;i--){
        compteur_fusion += this->essayeDeFusionnerRobot(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // on redéplace éventuellement les cases vers la droite encore une fois
    for(int i=3;i>0;i--){
        this->essayeDeDeplacerRobot(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    // et une dernière fois
    for(int i=3;i>0;i--){
        this->essayeDeDeplacerRobot(liste4cases.TAB[i-1],liste4cases.TAB[i]);
    }
    return compteur_fusion;
}

void ListeCases::essayeDeDeplacerRobot(Case& C1, Case& C2){
    if(C2.get_val()==1){ // case de droite vide
        if(C1.get_val()!=1){ // case de gauche non vide
            C2.set_val(C1.get_val());
            C1.set_val(pow(2,0));
        }
    }
}

int ListeCases::essayeDeFusionnerRobot(Case& C1, Case& C2){
    if(C1.get_val()==C2.get_val() && C1.get_val()!=1){ // même valeur et case non nulle
        C2.set_val(C2.get_val()*2);
        C1.set_val(pow(2,0));
        C2.set_couleur();
        score = score + C2.get_val();
        if (score > bestscore){
            bestscore = score;
            emit bestscoreChanged();
        }
        emit scoreChanged();
        return 1;
    } else {
        return 0;
    }
}

int ListeCases::compteCasesVides(){
    // on récupère les indices des cases vides :
    int compteur = 0;
    for(int ind=0;ind<16;ind++){
        if(TAB[ind].get_val()==1){// case vide
            compteur+=1;
        }
    }
    return compteur;
}
