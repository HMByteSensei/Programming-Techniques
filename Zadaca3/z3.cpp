#include <iostream> 
#include <iomanip> 
#include <stdexcept> 
#include <new> 
#include <cmath>
  
template <typename TipElemenata> 
struct Matrica { 
    char ime_matrice;             // Koristi se samo u funkciji "UnesiMatricu"     
    int br_redova, br_kolona; 
    TipElemenata **elementi =  nullptr;  // VEOMA BITNA INICIJALIZACIJA!!! 
};  
 
template <typename TipElemenata> 
void UnistiMatricu(Matrica<TipElemenata> &mat) { 
    if(!mat.elementi) return; 
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i]; 
    delete[] mat.elementi;  
    mat.elementi = nullptr; 
}  
 
template <typename TipElemenata> 
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0) {     
    Matrica<TipElemenata> mat;  
    mat.br_redova = br_redova; mat.br_kolona = br_kolona; mat.ime_matrice = ime;      
    mat.elementi = new TipElemenata*[br_redova]{}; 
    try { 
      for(int i = 0; i < br_redova; i++)  
        mat.elementi[i] = new TipElemenata[br_kolona]{};   
    }  
    catch(...) { 
      UnistiMatricu(mat);  
      throw; 
    } 
    return mat; 
}  
 
template <typename TipElemenata> 
void UnesiMatricu(Matrica<TipElemenata> &mat) { 
    for(int i = 0; i < mat.br_redova; i++) 
      for(int j = 0; j < mat.br_kolona; j++) { 
        std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";  
        std::cin >> mat.elementi[i][j];  
    }  
}  
 
template <typename TipElemenata> 
void IspisiMatricu(Matrica<TipElemenata> mat, int sirina_ispisa, int preciznost = 6, bool treba_brisati = false) 
{ 
    for(int i = 0; i < mat.br_redova; i++) { 
      for(int j = 0; j < mat.br_kolona; j++) 
        //std::cout << std::setw(sirina_ispisa) << std::round(mat.elementi[i][j] * static_cast<double>(std::pow(10, preciznost))) / std::pow(10, preciznost);  
        std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];        
      std::cout << std::endl;  
    }
    if(treba_brisati == true) {
        UnistiMatricu(mat);
    }
}  
 
template <typename TipElemenata> 
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) { 
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)         
        throw std::domain_error("Matrice nemaju jednake dimenzije!");       
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);       
    for(int i = 0; i < m1.br_redova; i++) 
        for(int j = 0; j < m1.br_kolona; j++) 
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];       
    return m3; 
}    

// predpostavka da ne mogu biti zadane grbave matrice
template <typename Tip>
bool DaLiJeKvadratna(Matrica<Tip> A) {
    if(A.br_redova == 0) return false;
    return (A.br_redova == A.br_kolona);
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &A, const Matrica<TipElemenata> &B) {
    if(B.br_redova != A.br_kolona) {
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
    auto C = StvoriMatricu<TipElemenata>(A.br_redova, B.br_kolona);
    for(int i=0; i<A.br_redova; i++) {
        // kvadratna je matrica
        for(int j=0; j<B.br_kolona; j++) {
            for(int k=0; k<B.br_redova; k++) {
                C.elementi[i][j] += A.elementi[i][k] * B.elementi[k][j];
            }
        }
    }
    return C;
}

template<typename TIP>
Matrica<TIP> KopirajMatricu(const Matrica<TIP> &A) {
    Matrica<TIP> rez = StvoriMatricu<TIP>(A.br_redova, A.br_kolona);
    for(int i=0; i<A.br_redova; i++) {
        for(int j=0; j<A.br_kolona; j++) {
            rez.elementi[i][j] = A.elementi[i][j];
        }
    }
    return rez;
}

template <typename TIP>
Matrica<TIP> MatricniHarmonijskiPolinom(const Matrica<TIP> &A, int n) {
    if(!DaLiJeKvadratna(A)) {
        throw std::domain_error("Matrica nije kvadratna");
    }
    if(n < 0) {
        throw std::domain_error("Pogresan parametar n");
    }
    Matrica<TIP> produkt = KopirajMatricu(A); // da ne dode do plitkog kopiranja, upotrijebio sam ovu f-iju
    Matrica<TIP> produkt2 = KopirajMatricu(A);
    Matrica<TIP> rezultat = StvoriMatricu<TIP>(A.br_redova, A.br_kolona);   
    for(int i=1; i<=n; i++) {
        if(i > 1) {
            if(i % 2 == 0) {
                UnistiMatricu(produkt);
                produkt = ProduktMatrica(produkt2, A);
            }
            else {
                UnistiMatricu(produkt2);
                produkt2 = ProduktMatrica(produkt, A);
            }
        }
        //std::cout << "\nMatrica produkt: \n";
        //IspisiMatricu(produkt, 20);
        
        // mnozenje s skalarom
        for(int j=0; j<produkt.br_redova; j++) {
            for(int k=0; k<produkt.br_kolona; k++) {
                if(i%2==0) rezultat.elementi[j][k] += produkt.elementi[j][k] * (i>1 ? (1./i) : 1); 
                else rezultat.elementi[j][k] += produkt2.elementi[j][k] * (i>1 ? (1./i) : 1);
            }
        }
        //std::cout << "\nPomnozena s skalarom: \n";
        //IspisiMatricu(produkt, 20);
        //std::cout << "\nREZULTAT: \n";
        //IspisiMatricu(rezultat, 20);
        // std::cout << "\nIzgled matrice produkt nakon " << i << " prolaza: \n";
        // IspisiMatricu(produkt, 10, 6);
        // std::cout << "\nIzgled matrice rezultat nakon " << i << " prolaza: \n";
        // IspisiMatricu(rezultat, 10, 6);
        // std::cout << "------------------------------------\n";
    }
    UnistiMatricu(produkt);
    UnistiMatricu(produkt2);
    return rezultat;
}

int main() { 
    Matrica<double> a, c;    // AUTOMATSKA INICIJALIZACIJA!!!   
    int m, n; 
    std::cout << "Unesite dimenziju kvadratne matrice: ";  
    std::cin >> m;  
    try { 
        a = StvoriMatricu<double>(m, m, 'A');  
        std::cout << "Unesite elemente matrice A:\n";  
        UnesiMatricu(a);  
        std::cout << "Unesite red polinoma: ";
        std::cin >> n; 
        std::cout << "Matricni harmonijski polinom:\n";  
        IspisiMatricu(c = MatricniHarmonijskiPolinom(a,n), 10);  
    }  
    catch(std::bad_alloc) { 
        std::cout << "Nema dovoljno memorije!\n";  
    }
    catch(std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    UnistiMatricu(a); 
    UnistiMatricu(c); 
 
    return 0; 
}

// int main() {
//     Matrica<int> m1(StvoriMatricu<int>(3,3)), m2;
//     m1.elementi[0][0] = 2;
//     m1.elementi[0][1] = 4;
//     m1.elementi[0][2] = 3;
//     m1.elementi[1][0] = 1;
//     m1.elementi[1][1] = 7;
//     m1.elementi[1][2] = -3;
//     m1.elementi[2][0] = 9;
//     m1.elementi[2][1] = 14;
//     m1.elementi[2][2] = -13;
//     m2 = ProduktMatrica(m1, m1);
//     IspisiMatricu(m2, 4);
//     UnistiMatricu(m1); UnistiMatricu(m2);

//     return 0;
// }