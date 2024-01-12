//Autor: Husić Muhamed
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>

std::vector<std::vector<int>> KreirajSpiralnuMatricu(int M, int N, int pocetni_broj, bool desna_spirala) {
    std::vector<std::vector<int>> spiralna_matrica(M, std::vector<int>(N));
    if(M <= 0 || N <= 0) {
        spiralna_matrica.resize(0, std::vector<int>(0));
        return spiralna_matrica;
    }

    int krajnji_broj = pocetni_broj + M * N - 1;
    int gore{0}, dolje{M}; // gornji/donji red
    int lijevo{0}, desno{N}; // lijeva/desna kolona
    if(desna_spirala) {
        /* KADA SE RADI O DESNOJ SPIRALNOJ MATRICI */
        while(pocetni_broj <= krajnji_broj) {
            // Gornji red
            for(int i=lijevo; i<desno; i++) {
                spiralna_matrica.at(gore).at(i) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;
            gore++;
            desno--;
            
            // Desna kolona
            for(int i=gore; i<dolje; i++) {
                spiralna_matrica.at(i).at(desno) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;
            dolje--;

            // Donji red
            for(int i=desno-1; i>=lijevo; i--) {
                spiralna_matrica.at(dolje).at(i) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;

            // Lijeva kolona
            for(int i=dolje-1; i>=gore; i--) { 
                spiralna_matrica.at(i).at(lijevo) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;
            lijevo++;
        }
    } else {
        /* KADA SE RADI O LIJEVOJ SPIRALNOJ MATRICI */
        while(pocetni_broj <= krajnji_broj) {
            // Lijeva kolona
            for(int i=gore; i<dolje; i++) {
                spiralna_matrica.at(i).at(lijevo) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;
            lijevo++;
            dolje--;
            
            // Donji red
            for(int i=lijevo; i<desno; i++) {
                spiralna_matrica.at(dolje).at(i) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;
            desno--;

            // Desna kolona
            for(int i=dolje-1; i>=gore; i--) {
                spiralna_matrica.at(i).at(desno) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;

            // Gornji red
            for(int i=desno-1; i>=lijevo; i--) { 
                spiralna_matrica.at(gore).at(i) = (pocetni_broj++);
            }
            if(pocetni_broj > krajnji_broj) break;
            gore++;
        }
    }

    return spiralna_matrica;
}

int BrojElemenata(const std::vector<std::vector<int>> &matrica) {
    int broj{0};
    for(std::vector<int> red : matrica) {
        for(int x : red) {
            broj++;
        }
    }
    return broj;
}

bool DaLiJeSpiralnaMatrica(const std::vector<std::vector<int>> &matrica) {
    // ako je matrica formata 0x0 ne izvrsi se petlja
    if(0 == matrica.size()) return false; 
    for(int i=0; i<matrica.size(); i++) {
        if(matrica.at(i).size() == 0) return false;
    }
    int poc = matrica.at(0).at(0);
    int zadnji = poc + matrica.size()*matrica.at(0).size()-1;
    if(poc > zadnji) return false;
    bool desna{false};
    if(matrica.at(0).size() > 1 && matrica.at(0).at(0) == matrica.at(0).at(1) - 1) {
        desna = true;
    }
    if(matrica.at(0).size() == 1 && matrica.at(1).size() > 1 && (matrica.at(0).at(0) == matrica.at(1).at(1) - 1)) {
        desna = true;
    }
    std::vector<std::vector<int>> spirala = KreirajSpiralnuMatricu(matrica.size(), matrica.at(0).size(), poc, desna);
    int visina = matrica.size();
    int sirina = matrica.at(0).size(); 
    for(int i=0; i<visina; i++) {
        if(sirina != matrica.at(i).size()) return false;
        for(int j=0; j<sirina; j++) {
            if(matrica.at(i).at(j) != spirala.at(i).at(j)) {
                return false;
            }
        }
    }
    return true;
}

// dodatna funkcija za testiranje da li je grbava matrica spiralna
bool DaLiJeSpiralnaGrbavaMatrica(const std::vector<std::vector<int>> &matrica) {
    // ako je matrica formata 0x0 ne izvrsi se petlja
    for(int i=0; i<matrica.size(); i++) {
        if(matrica.at(i).size() == 0) return false;
    }
    if(0 == matrica.size()) return 0;
    bool desna{false};
    if(matrica.at(0).size() > 1 && matrica.at(0).at(0) == matrica.at(0).at(1) - 1) {
        desna = true;
    }
    if(matrica.at(0).size() == 1 && matrica.at(1).size() > 1 && (matrica.at(0).at(0) == matrica.at(1).at(1) - 1)) {
        desna = true;
    }
    int gore{0}, dolje = matrica.size(); // gornji/donji red
    int lijevo{0}, pomakUdesno{0}; // lijeva/desna kolona
    int pocetni_gore{0};
    int brojac{0}, broj_elemenata=BrojElemenata(matrica);
    // broji od kojeg gornjeg clana trebamo poceti porediti, u prva dva reda krece se od 0, treci od 1...
    // Desna SPIRALNA MATRICA
    while(desna) {
        // Gornji red
        if(gore >= 2) pocetni_gore++;
        for(int i=pocetni_gore; i<(matrica.at(gore).size()-1-pomakUdesno); i++) {
            if(matrica.at(gore).at(i) != matrica.at(gore).at(i+1) - 1) {
                return false;
            }
            brojac++;
        }
        if(brojac >= broj_elemenata-1) break;
        gore++;
        pomakUdesno++;

        // Desna kolona
        for(int i=gore-1; i<dolje-1; i++) {
            int trenutni = matrica.at(i).size()-pomakUdesno;
            int trenutni2 = matrica.at(i+1).size()-pomakUdesno;
            if(matrica.at(i).at(trenutni) !=  matrica.at(i+1).at(trenutni2) - 1) {
                return false;
            }
            brojac++;            
        }
        if(brojac >= broj_elemenata-1) break;
        dolje--;

        // Donji red
        for(int i=matrica.at(dolje).size()-pomakUdesno; i>lijevo; i--) {
            if(matrica.at(dolje).at(i) != matrica.at(dolje).at(i-1)-1) {
                return false;
            }
            brojac++;
       }
        if(brojac >= broj_elemenata-1) break;

        // Lijeva kolona
        for(int i=dolje; i>gore; i--) {
            if(matrica.at(i).at(lijevo) != matrica.at(i-1).at(lijevo) - 1) {
                return false;
            }
            brojac++;
        }
        if(brojac >= broj_elemenata-1) break;
        lijevo++;
    }
    // LIJEVA SPIRALNA MATRICA
    bool poc_gore{true};
    int *gornji_element;
    gornji_element = &pocetni_gore;
    if(matrica.at(0).size() == 1) {
        gornji_element = &pomakUdesno;
        poc_gore = false;
    }
    while(!desna && dolje > gore) {
        // Lijeva kolona
        if(poc_gore && gore >= 2) pocetni_gore++;
        for(int i=*gornji_element; i<dolje-1; i++) {
            if(brojac >= broj_elemenata-1) {
                desna = true;
                break;
            }
            if(matrica.at(i).at(lijevo) != matrica.at(i+1).at(lijevo) - 1) {
                return false;
            }
            brojac++;
        }
        lijevo++;
        dolje--;
        
        // Donji red
        for(int i=lijevo-1; i<(matrica.at(dolje).size()-1-pomakUdesno); i++) {
            if(brojac >= broj_elemenata-1) {
                desna = true;
                break;
            }
            if(matrica.at(dolje).at(i) != matrica.at(dolje).at(i+1) - 1) {
                return false;
            }
            brojac++;
        }
        pomakUdesno++;

        // Desna kolona
        for(int i=dolje; i>gore+*gornji_element; i--) {
            if(brojac >= broj_elemenata-1) {
                desna = true;
                break;
            }
            
            if(matrica.at(i).at(matrica.at(i).size() - pomakUdesno) != matrica.at(i-1).at(matrica.at(i-1).size() - pomakUdesno) - 1) {
                return false;
            }
            brojac++;
        }

        // Gornji red
        for(int i=(matrica.at(gore).size()-pomakUdesno); i>lijevo; i--) {
            if(brojac >= broj_elemenata-1) {
                desna = true;
                break;
            }
            if(matrica.at(gore).at(i) != matrica.at(gore).at(i-1) - 1) {
                return false;
            }
            brojac++;
        }
        gore++;
    }

    return true;
}

int Sirina(std::vector<std::vector<int>> &matrica, int M, int N) {
    // najvise znakova ce imati ili prvi(zbog minusa), ili zadnji br
    int prvi = log10(std::fabs(matrica.at(0).at(0))) + 1;
    int zadnji_broj = matrica.at(0).at(0) + M * N - 1;
    int zadnji = log10(std::fabs(zadnji_broj)) + 1;
    if(matrica.at(0).at(0) < 0) prvi++;
    if(zadnji_broj < 0) zadnji++;
    return (prvi > zadnji ? prvi : zadnji);
}

int main () {
    std::cout  << "Unesite broj redova i kolona matrice: ";
    int br_redova, br_kolona;
    std::cin >> br_redova >> br_kolona;
    std::cout << "Unesite pocetnu vrijednost: ";
    int pocetni_broj;
    std::cin >> pocetni_broj;
    // da isprazni spremnik ako korisnik eventualno napise i pocetnu vrijednost i L/D
    std::cin.ignore(1000, '\n');

    std::cout << "Unesite L za lijevu, a D za desnu spiralnu matricu: ";
    char desna_lijeva = std::cin.get();
    
    // da izbjegnemo if-else klauzu ako je lijevo => desna_lijeva = 0 tj false
    if(desna_lijeva == 'L') desna_lijeva = 0;
    std::cout << std::endl << "Kreirana spiralna matrica: " << std::endl;
    std::vector<std::vector<int>> matrica = KreirajSpiralnuMatricu(br_redova, br_kolona, pocetni_broj, desna_lijeva);
    int sirina{0};
    if(matrica.size() != 0 && matrica.at(0).size() != 0) sirina = Sirina(matrica, br_redova, br_kolona) + 1;
    for(std::vector<int> &red : matrica) {
        for(int x : red) {
            std::cout << std::setw(sirina) << x;
        }
        std::cout << "\n";
    }

    // std::vector<std::vector<int>> matrica{ {1,2,3,4}, {11,12,5}, {10,14,13,6},{9,8,7} };
    // std::vector<std::vector<int>> matrica2{ {1,2,3}, {8,9,4}, {7,6,5} };
    // std::vector<std::vector<int>> matrica3{ {1,2,3,4,5,6,7,8,9}, {23,24,25,26,27,28,10}, {22,37,38,39,29,11}, {21,36,43,42,41,40,30,12},{20,35,34,33,32,31,13}, {19,18,17,16,15,14} };
    // std::vector<std::vector<int>> matrica4{ {1}, {9, 2}, {8, 11, 10, 3}, {7,6,5,4} };
    // std::vector<std::vector<int>> matrica7{ {2,21,27,15}, {3,22,28,29,30,31,26,14}, {4,23,24,25,13},{5,6,7,8,9,10,11,12} };
     //std::vector<std::vector<int>> mat{{1,2,3},{},{7,6,5}};

    // std::vector<std::vector<int>> matLIJEVO{{1}, {2,9}, {3,10,8}, {4,5,6,7}};
    // std::vector<std::vector<int>> matrica5{ {1,12,11,10}, {2,13,9}, {3,8}, {4,5,6,7} };
    // std::vector<std::vector<int>> matrica6{ {1,10,9,8}, {2,11,11,7}, {3,4,5,6} };//false
    // std::vector<std::vector<int>> matrica66{ {1,10,9,8}, {2,11,12,7}, {3,4,5,6} };//true
    // std::vector<std::vector<int>> matrica8{ {1,8}, {2,7}, {3,6}, {4,5} };
    // std::cout << std::endl << std::boolalpha <<DaLiJeSpiralnaGrbavaMatrica(matrica3);

	return 0;
}