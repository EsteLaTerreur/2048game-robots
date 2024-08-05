#include "case.h"
#include <iostream>
using namespace std;

const QVector<QString> Case::Originale = {"#d875ff", "#7c32aa", "#B14068","#C43E3E", "#F8841F", "#F8B82E","#FFDA75", "#F5E96B", "#A5CE4D", "#68E758", "#51E792", "#3FEFC9", "#60ADEC", "#4E6AB3", "#2A1B49", "#160823","#edc0ff"};

const QVector<QString> Case::Classique = {"#D0D4E5","#B96C31","#CAC6C7","#C49F89","#CA8069","#B55842","#B33617","#C0B98A","#BAB47A","#BCB15E","#C8B95A","#AC9D32","#C8252C","#B61413","#9B090E","#A40E11","#979D9E"};

const QVector<QString> Case::Oceane = {"#F7CC66","#251E73","#2C3480","#334A8C","#4075A5","#4EA0BE","#5BCBD7","#A5E0E9","#EFF5FA","#C7E7E2","#9ED8CA","#4CBB9A","#3E987D","#2F745F","#205142","#112D24","#F6D898"};

const QVector<QString> Case::Fleurie = {"#397D28","#FFFFFF","#EFD31C","#E01C1C","#E3304A","#E54378","#E63EA1","#E639CA","#9A27A7","#741E96","#4E1484","#3F3899","#305BAD","#11A2D6","#4DBAE1","#88D1EB","#6CDA54"};

const QVector<QString> Case::Noel = {"#18430F","#FF0000","#C00000","#800000","#AF240B","#DE4816","#C26938","#E1B49C","#C8B49B","#AFB39A","#5F6635","#3C5522","#18430F","#12330C","#0C2208","#000000","#DBDBDB"};

const QVector<QString> Case::Flammes = {"#1D1C1C","#FFE500","#FB6500","#FF0000","#FF2700","#FF3A00","#FF4D00","#FF7300","#FF8600","#FF9900","#FFBF00","#FFD200","#FFE500","#FFEC40","#FFF280","#FFF9C0","#3E3D3D"};

const QVector<QString> Case::Arc_en_ciel = {"#BFE3FF","#9D00FF","#0800FF","#4FCEF1","#1DAA18","#FFE100","#ED6300","#ED0000","#E800CD","#B85EEF","#5C57E7","#8DDAEF","#54B151","#FFEF76","#E38B4C","#E06060","#FFFFFF"};

const QVector<QString> Case::Neon = {"#080850","#DE007A","#F1ED7D","#54E8A0","#25C4F8","#2667FC","#270AFF","#5816E1","#B4119E","#DE007A","#DC1350","#D92525","#DF573B","#E58951","#EBBB67","#F1ED7D","#1A64DB"};

Case::Case(int id, int val, bool fusion, QObject *parent)
    : QObject{parent}, caseID(id), valeur(val)
{}

Case::Case() : valeur(10), listeCouleursPossibles(Originale) {

}

void Case::set_val(int val) {
    if(valeur!=val){
        valeur = val;
        readValeur();
        if(val!=1){
            emit animation();
        }
    }
}

void Case::set_id(int id) {
    caseID = id;
}

void Case::autre_palette(){
    listeCouleursPossibles = Classique;
}

void Case::set_couleur() {
    couleur = listeCouleursPossibles[log2(valeur)];
    readCouleur();
}

QString Case::get_couleur(){
    return couleur;
}

int Case::get_val(){
    return valeur;
}

Case& Case::operator=(const Case& case1)
{
    if (this != &case1)
    {
        this->caseID = case1.caseID;
        this->valeur = case1.valeur;
        this->couleur = case1.couleur;
        this->fusion = case1.fusion;
    }
    return *this;
}


void Case::aleatoire(){
    int i = rand()%9;
    if (i==0){ // une chance sur 10
    this->set_val(pow(2,2));
    }
    else{
        this->set_val(pow(2,1));
    }
    this->set_couleur();
}

QString Case::readCouleur() {
    emit couleurChanged();
    return QString(couleur);
}
QString Case::readValeur() {
    emit valeurChanged();
    return QString::number(valeur);
}
