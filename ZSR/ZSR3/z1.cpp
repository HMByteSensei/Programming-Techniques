#include <iostream>
#include <iomanip>

int ulazniTok() {
    int x;
    while(!(std::cin >> x))
    {
        std::cout << "Potrebno je samo unijeti broj sati pa potom minuta, pa potom sekundi" << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n'); //zar ovo nije viska kada ce svakako ulazni tok biti "ociscen" buduci da
        //ce cin.cear ignorirati/preskociti sve od trenutka pojave prvog znaka ili bilo cega sto nije br
    }
    return x;
}

int PretvoriUSekunde(int h, int min, int sek) {
    return (h*3600 + min*60 + sek);
}

int main() {
    std::cout << "Unesi prvo vrijeme (h min s): ";
    int prvo_sat{ulazniTok()}, prvo_min{ulazniTok()}, prvo_sek{ulazniTok()}; //jednoobrazna inicijalizacija
    int prvo = PretvoriUSekunde(prvo_sat, prvo_min, prvo_sek);

    std::cout << "Unesi drugo vrijeme (h min s): ";
    int drugo_sat{ulazniTok()}, drugo_min{ulazniTok()}, drugo_sek{ulazniTok()};
    int drugo = PretvoriUSekunde(drugo_sat, drugo_min, drugo_sek);

    int rezultat = std::abs(drugo - prvo);
    std::cout << "Izmedu ova dva trenutka proteklo je " << rezultat/3600 << "h, " << 
    (rezultat - (rezultat/3600)*3600) / 60 << "min, " << (rezultat - ((rezultat/3600)*3600) - 
    ((rezultat - (rezultat/3600)*3600) / 60) * 60) << "s." << std::endl;
    
    //sati od sekundi:   sati = sekunde/3600;
    //minute od sekundi: minute = (sekunde - sati * 3600)/60; 
    //sekunde:           sekune = sekunde - sati*3600 - minute*60;

    std::cout << "Prvo vrijeme je h/min/s   " << prvo_sat << "  /  " << prvo_min << "  /  " << prvo_sek 
    << std::endl;
    
    
    std::cout << "drugo vrijeme je h/min/s   " << drugo_sat << "  /  " << drugo_min << "  /  " << drugo_sek 
    << std::endl;
    
    return 0;
}