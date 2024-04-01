//TP 2022/2023: Zadaća 5, Zadatak 4
#include <iostream> 
#include <iomanip> 
#include <cstring> 
#include <stdexcept> 
#include <new> 
#include <string>
#include <type_traits>
#include <algorithm>
#include <cmath>
#include <functional>  
#include <fstream>
#include <vector>

template <typename TipEl> 
  class Matrica { 
    char ime_matrice; 
    int br_redova, br_kolona; 
    TipEl **elementi;  
    static TipEl **AlocirajMemoriju(int br_redova, int br_kolona); 
    static void DealocirajMemoriju(TipEl **elementi, int br_redova); 
    void KopirajElemente(TipEl **elementi);
    void TestIndexa(int i, int j) const {
        if(i < 1 || i > br_redova || j < 1 || j >br_kolona)
            throw std::range_error("Neispravan indeks");
    }
  public: 
    Matrica(int br_redova, int br_kolona, char ime = 0); 
    Matrica(const Matrica &m);  
    Matrica(Matrica &&m);  
    ~Matrica() { DealocirajMemoriju(elementi, br_redova); }      
    Matrica &operator =(const Matrica &m); 
    Matrica &operator =(Matrica &&m); 
    Matrica &operator += (const Matrica &m2);
    Matrica &operator -= (const Matrica &m2);
    Matrica &operator *= (const Matrica &m2);
    template <typename T>
        Matrica &operator *= (T broj) {
            for(int i=0; i<br_redova; i++) {
                std::transform(elementi[i], elementi[i]+br_kolona, elementi[i],[broj](TipEl& x) {
                    x *= broj;
                    return x;
                });
            }
            //std::transform(elementi, elementi+br_redova, elementi, std::bind(std::multiplies<TipEl>(), broj, std::placeholders::_1)); 
            return *this;
        }
    TipEl *operator[] (int index) {return elementi[index]; }
    TipEl *operator[] (int index) const {return elementi[index]; }
    TipEl &operator() (int i, int j) { TestIndexa(i, j); return elementi[i-1][j-1]; }
    TipEl &operator() (int i, int j) const { TestIndexa(i, j); return elementi[i-1][j-1]; }
    operator std::string() const;

    Matrica(std::string ime_datoteke, bool binarna_dat);
    void SacuvajUTekstualnuDatoteku(std::string ime_datoteke) const;
    void SacuvajUBinarnuDatoteku(std::string ime_datoteke) const;
    void ObnoviIzTekstualneDatoteke(std::string ime_datoteke);
    void ObnoviIzBinarneDatoteke(std::string ime_datoteke);

    template <typename Tip>
        friend std::istream &operator >>(std::istream &tok, Matrica<Tip> &m); 
    template <typename Tip>
        friend std::ostream &operator <<(std::ostream &tok, const Matrica<Tip> &);
    template <typename Tip2> 
      friend Matrica<Tip2> operator +(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
    template <typename Tip>
        friend Matrica<Tip> operator *(const Matrica<Tip> &m1, const Matrica<Tip> &m2);
    template <typename Tip>
        friend Matrica<Tip> operator -(const Matrica<Tip> &m1, const Matrica<Tip> &m2);
    template <typename Tip>
        friend Matrica<Tip> operator -(const Matrica<Tip> &m1);
    template <typename Tip, typename Tip2>
        friend Matrica<Tip> operator *(Matrica<Tip> m, Tip2 broj);
    template <typename Tip, typename Tip2>
        friend Matrica<Tip> operator *(Matrica<Tip> m, Tip2 broj);
};

template <typename Tip>
Matrica<Tip>::operator std::string() const {
    std::string s = "{";
    for(int i=0; i<br_redova; i++) {
        s.push_back('{');
        for(int j=0; j<br_kolona; j++) {
            std::string pomocni = std::to_string(elementi[i][j]);
            s += pomocni.substr(0, pomocni.find('.'));
            if(j != br_kolona-1) s.push_back(',');
        }
        s.push_back('}');
        if(i!=br_redova-1) s.push_back(',');
        else s.push_back('}');
    }
    return s;
}
 
template <typename TipEl> 
  TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {     
    TipEl **elementi = new TipEl*[br_redova]{};   
    try { 
      for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona]{};     
    }  
    catch(...) { 
      DealocirajMemoriju(elementi, br_redova); throw; 
    } 
    return elementi; 
  } 
 
template <typename TipEl> 
  void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {     
    for(int i = 0; i < br_redova; i++) delete[] elementi[i]; 
    delete[] elementi; 
  } 
 
template <typename TipEl> 
  Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :  
    br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),  
    elementi(AlocirajMemoriju(br_redova, br_kolona)) {}  
 
template <typename TipEl> 
  void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {     
      for(int i = 0; i < br_redova; i++) 
        for(int j = 0; j < br_kolona; j++) 
            Matrica::elementi[i][j] = elementi[i][j];  
}  
 
template <typename TipEl> 
  Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova), br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),  
    elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {  
      KopirajElemente(m.elementi);  
}  
 
template <typename TipEl> 
  Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),  
    br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice) {        
        m.br_redova = 0; m.elementi = nullptr;  
}  
 
template <typename TipEl> 
  Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) 
{ 
    if(br_redova < m.br_redova || br_kolona < m.br_kolona) {  
      TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);        
      DealocirajMemoriju(elementi, br_redova);  
      elementi = novi_prostor;  
    }  
    else if(br_redova > m.br_redova) 
      for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];     
      br_redova = m.br_redova; br_kolona = m.br_kolona;  
    ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);  
    return *this; 
}  
 
template <typename TipEl> 
  Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) 
{ 
    std::swap(br_redova, m.br_redova); std::swap(br_kolona, m.br_kolona);      
    std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);      
    return *this; 
}

template <typename TipEl> 
  std::istream &operator >>(std::istream &tok, Matrica<TipEl> &mat) { 
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++) 
        { 
            std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";          
            std::cin >> mat.elementi[i][j];  
        }  
    }
    return tok;
}   
 
template <typename TipEl> 
  std::ostream &operator <<(std::ostream &tok, const Matrica<TipEl> &mat) { 
    int sirina = tok.width();
    for(int i = 0; i < mat.br_redova; i++) { 
        for(int j = 0; j < mat.br_kolona; j++) {
            tok << std::setw(sirina) << mat.elementi[i][j];      
        } 
        tok << std::endl; 
    } 
    return tok; 
}   
 
template <typename TipEl> 
  Matrica<TipEl> operator +(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) { 
      if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)         
        throw std::domain_error("Matrice nemaju jednake dimenzije!");       
      Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);  
      for(int i = 0; i < m1.br_redova; i++) 
        for(int j = 0; j < m1.br_kolona; j++) 
          m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];        
    return m3; 
} 

template <typename Tip>
    Matrica<Tip> operator -(const Matrica<Tip> &m2) {
        Matrica<Tip> m1(m2);
        for(int i=0; i<m1.br_redova; i++) {
            for(int j=0; j<m1.br_kolona; j++) {
                m1[i][j] = -m1[i][j];
            }
        }
        return m1;
    }

template <typename Tip>
    Matrica<Tip> operator -(const Matrica<Tip> &m1, const Matrica<Tip> &m2) {
        return m1 + -m2;
    }

template <typename Tip>
    Matrica<Tip> operator *(const Matrica<Tip> &m1, const Matrica<Tip> &m2) {
        if(m2.br_redova != m1.br_kolona) {
            throw std::domain_error("Matrice nisu saglasne za mnozenje");
        }
        Matrica<Tip> m3(m1.br_redova, m2.br_kolona);
        for(int i=0; i<m1.br_redova; i++) {
            for(int j=0; j<m2.br_kolona; j++) {
                for(int k=0; k<m1.br_kolona; k++) {
                    m3.elementi[i][j] += m1.elementi[i][k] * m2.elementi[k][j];
                }
            } 
        }
        return m3;
    }
template <typename Tip>
Matrica<Tip> &Matrica<Tip>::operator +=(const Matrica<Tip> &m2) {
    if(Matrica<Tip>::br_redova != m2.br_redova || Matrica<Tip>::br_kolona != m2.br_kolona)         
        throw std::domain_error("Matrice nemaju jednake dimenzije!");       
      for(int i = 0; i < Matrica<Tip>::br_redova; i++) 
        for(int j = 0; j < Matrica<Tip>::br_kolona; j++) 
          Matrica<Tip>::elementi[i][j] = Matrica<Tip>::elementi[i][j] + m2.elementi[i][j];        
    return *this;
}

template <typename Tip>
Matrica<Tip> &Matrica<Tip>::operator -=(const Matrica<Tip> &m2) {
    if(Matrica<Tip>::br_redova != m2.br_redova || Matrica<Tip>::br_kolona != m2.br_kolona)         
        throw std::domain_error("Matrice nemaju jednake dimenzije!");       
      for(int i = 0; i < Matrica<Tip>::br_redova; i++) 
        for(int j = 0; j < Matrica<Tip>::br_kolona; j++) 
          Matrica<Tip>::elementi[i][j] = Matrica<Tip>::elementi[i][j] - m2.elementi[i][j];        
    return *this;
}

template <typename Tip>
Matrica<Tip> &Matrica<Tip>::operator *= (const Matrica &m2) {
    if(m2.br_redova != Matrica<Tip>::br_kolona) {
            throw std::domain_error("Matrice nisu saglasne za mnozenje");
        }
    Matrica<Tip> m3(Matrica<Tip>::br_redova, m2.br_kolona);
    for(int i=0; i<Matrica<Tip>::br_redova; i++) {
        for(int j=0; j<m2.br_kolona; j++) {
            Tip suma = 0;
            for(int k=0; k<Matrica<Tip>::br_kolona; k++) {
                suma += this->elementi[i][k] * m2.elementi[k][j];
            }
            m3.elementi[i][j] = suma;
        } 
    }
    DealocirajMemoriju(elementi, br_redova);
    elementi = AlocirajMemoriju(m3.br_redova, m3.br_kolona);
    KopirajElemente(m3.elementi);
    return *this;
}

template <typename Tip, typename Tip2>
Matrica<Tip> operator *(Matrica<Tip> m, Tip2 broj) {
    for(int i=0; i<m.br_redova; i++) {
        for(int j=0; j<m.br_kolona; j++) {
            m[i][j] *= broj;
        }
    }
    return m;
}

template <typename Tip, typename Tip2>
Matrica<Tip> operator *(Tip2 broj, Matrica<Tip> m) {
    return m * broj;
}

//----------------------------------------------------------
template <typename Tip>
void Matrica<Tip>::SacuvajUTekstualnuDatoteku(std::string ime_datoteke) const {
    std::ofstream izlazni_tok(ime_datoteke);
    for(int i=0; i<br_redova; i++) {
        for(int j=0; j<br_kolona; j++) {
            int element;
            izlazni_tok << (*this)[i][j];
            if(j != br_kolona - 1) izlazni_tok << ",";
            if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
        }
        izlazni_tok << std::endl;
    }
    izlazni_tok.close();
}


template <typename Tip>
void Matrica<Tip>::ObnoviIzTekstualneDatoteke(std::string ime_datoteke) {
    std::ifstream ulazni_tok(ime_datoteke);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
    int br_redova{}, br_kolona{};
    bool prvo_citanje = true;
    Tip n;
    while(ulazni_tok >> n) {
        char znak;
        int brojac_kolona = 0;
        brojac_kolona++;
        //std::cout << "\nPrije unutr petlje broj: " << n << "\n";
        while(ulazni_tok.get(znak), znak != '\n') {
            if(ulazni_tok.eof()) break;
            if(znak != ',') {
                //std::cout << znak << " <-znak\tbroj-> " << n <<std::endl << std::endl;
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            ulazni_tok >> n;
            brojac_kolona++;
        }
        //std::cout << "Ovdje je kraj jedne iteracije!, znak: " << znak << " broj: "<< n <<"\n";
        if(prvo_citanje) { br_kolona = brojac_kolona; }
        else if(br_kolona != brojac_kolona || ulazni_tok.bad()) {
            //std::cout << znak << br_kolona << "==" << brojac_kolona << "\n";
            throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
        br_redova++;
        prvo_citanje = false;
    }
    if(!ulazni_tok.eof()) throw std::logic_error("Problemi pri citanju datoteke");
    
    Tip **novo = AlocirajMemoriju(br_redova, br_kolona);
    
    ulazni_tok.clear();
    ulazni_tok.seekg(0);

    for(int i=0; i<br_redova; i++) {
        char znak;
        for(int j=0; j<br_kolona; j++) {
            ulazni_tok >> novo[i][j];
            ulazni_tok.get(znak);
        }
    }
    DealocirajMemoriju(elementi, this->br_redova);
    this->br_redova = br_redova;
    this->br_kolona = br_kolona;
    elementi = novo;
    ulazni_tok.close();
}

template <typename Tip>
void Matrica<Tip>::SacuvajUBinarnuDatoteku(std::string ime_datoteke) const {
    std::ofstream izlazni_tok(ime_datoteke, std::ios::binary);
    izlazni_tok.write(reinterpret_cast<const char*>(&br_redova), sizeof br_redova);
    izlazni_tok.write(reinterpret_cast<const char*>(&br_kolona), sizeof br_kolona);
    for(int i=0; i<br_redova; i++) {
        izlazni_tok.write(reinterpret_cast<char*>(elementi[i]), sizeof(Tip) * br_kolona);
        if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
    }
    izlazni_tok.close();
}

template <typename Tip>
void Matrica<Tip>::ObnoviIzBinarneDatoteke(std::string ime_datoteke) {
    std::ifstream ulazni_tok(ime_datoteke, std::ios::binary);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
    int broj_kolona{}, broj_redova{};
    ulazni_tok.read(reinterpret_cast<char*>(&broj_redova), sizeof broj_redova);
    ulazni_tok.read(reinterpret_cast<char*>(&broj_kolona), sizeof broj_kolona);
    if(!ulazni_tok) throw std::logic_error("Problemi pri citanju datoteke");
    
    Tip **novi = AlocirajMemoriju(broj_redova, broj_kolona);
    DealocirajMemoriju(elementi, br_redova);
    
    elementi = novi;
    br_redova = broj_redova;
    br_kolona = broj_kolona;
    for(int i=0; i<broj_redova; i++) {
        for(int j=0; j<broj_kolona; j++) {
            ulazni_tok.read(reinterpret_cast<char*>(&elementi[i][j]), sizeof elementi[i][j]);
            if(!ulazni_tok) throw std::logic_error("Problemi pri citanju datoteke");
        }
    }
    ulazni_tok.close();
}

template <typename Tip>
Matrica<Tip>::Matrica(std::string ime_datoteke, bool binarna_dat) : br_kolona(0), br_redova(0), 
elementi(AlocirajMemoriju(0, 0)) {
    try {
        if(binarna_dat == true) {
            ObnoviIzBinarneDatoteke(ime_datoteke);
        }
        else {
            ObnoviIzTekstualneDatoteke(ime_datoteke);
        }
    } catch(...) {
        delete[] elementi;
        throw;
    }
}
//----------------------------------------------------------

int main() {
   try {
        Matrica<int> a(2, 2, 'a');
        a(1,1) = 2; a(1,2) = 2; 
        a(2,1) = 4; a(2,2) = 5; 
        Matrica<int> b(2, 2, 'b');
        b(1,1) = 1; b(1,2) = 1;
        b(2,1) = 4; b(2,2) = 6;
        a=a*b;
        std::cout << "MATRICA B: \n";
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++)
                std::cout << b(i+1,j+1) << " ";
                std::cout << std::endl;
            }
        std::cout << "---------------" << std::endl;
        a=a*5;
        std::cout << "Matrica A: \n";
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++)
                std::cout << a(i+1,j+1) << " ";
                std::cout << std::endl;
        }
        std::cout << "---------------" << std::endl;
        a.SacuvajUTekstualnuDatoteku("mat.txt");
        b.ObnoviIzTekstualneDatoteke("mat.txt");
        std::cout << "MATRICA B obnovljena: \n";
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++)
                std::cout << b(i+1,j+1) << " ";
                std::cout << std::endl;
            }
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
    }
        catch(std::domain_error e) {
        std::cout << e.what();
    }
        catch(std::range_error e) {
        std::cout << e.what();
    }
    return 0;
}