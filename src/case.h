#ifndef CASE_H
#define CASE_H

#include <QObject>
#include <string>
#include <vector>
class Case : public QObject
{
    Q_OBJECT
public:
    explicit Case(int id,int val=10, bool fusion = false,QObject *parent = nullptr);
    Case(); // constructeur par défaut
    bool fusion;
    void set_val(int val);
    void set_id(int id);
    int get_val();
    void set_couleur();
    Case& operator=(const Case& case0); // opérateur égal
    QString get_couleur();
    Q_INVOKABLE void aleatoire();
    Q_INVOKABLE void autre_palette();
    QVector<QString> listeCouleursPossibles;

    Q_PROPERTY(QString caseCouleur READ readCouleur NOTIFY couleurChanged)
    Q_PROPERTY(QString caseValeur READ readValeur NOTIFY valeurChanged)
    Q_PROPERTY(NOTIFY animation)
    static const QVector<QString> Originale;
    static const QVector<QString> Classique;
    static const QVector<QString> Oceane;
    static const QVector<QString> Fleurie;
    static const QVector<QString> Noel;
    static const QVector<QString> Flammes;
    static const QVector<QString> Arc_en_ciel;
    static const QVector<QString> Neon;
private:
    int caseID;
    int valeur;
    QString couleur = "#d875ff";
    QString readCouleur();
    QString readValeur();
    int readScale();
signals:
    void valeurChanged();
    void couleurChanged();
    void animation();
};

#endif // Case_H
