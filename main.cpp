#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <time.h>
#include <cstdlib>

std::mutex dostepDoPasa;
std::condition_variable ladowanieCV;
std::condition_variable wylatywanieCV;

const std::size_t  maxSamolotowN {10};
const std::size_t liczbaZmianyPriorytetuK {5};
const std::size_t maxLWatkow {500};
std::vector<int> samolotyNaLotniskowcu {};
std::size_t lWatkow {0};

void ladowanie(int id){

        std::unique_lock<std::mutex> zajeciePasa(dostepDoPasa);
        ladowanieCV.wait(zajeciePasa, []{return samolotyNaLotniskowcu.size() < maxSamolotowN;});

        std::cout << "Samolot " << id << " wyladowal na lotniskowcu." << std::endl;
        samolotyNaLotniskowcu.push_back(id);

        zajeciePasa.unlock();
        wylatywanieCV.notify_one();
        ladowanieCV.notify_one();

}

void wylatywanie(size_t index){

        std::unique_lock<std::mutex> zajeciePasa(dostepDoPasa);
        wylatywanieCV.wait(zajeciePasa, [index]{return (samolotyNaLotniskowcu.size() > index && samolotyNaLotniskowcu.size() >= liczbaZmianyPriorytetuK);});

        std::cout << "Samolot " << samolotyNaLotniskowcu.at(index) << " wylecial." << std::endl;
        samolotyNaLotniskowcu.erase(samolotyNaLotniskowcu.begin() + index);

        zajeciePasa.unlock();
        wylatywanieCV.notify_one();
        ladowanieCV.notify_one();
}

int main(){

        std::vector<std::thread> wszystkieSamolotyWatki {};
        int lastID {};
        std::srand(std::time(0));

        while(true){

                if(std::rand() % 2 == 0){

                        wszystkieSamolotyWatki.push_back(std::thread(ladowanie, lastID++));
			
                }else if (samolotyNaLotniskowcu.size() != 0){

                        wszystkieSamolotyWatki.push_back(std::thread(wylatywanie, std::rand() % samolotyNaLotniskowcu.size()));
                
		}
		lWatkow ++;
		if(lWatkow>= maxLWatkow){
			
        		for(std::thread& watekSamolotu : wszystkieSamolotyWatki) {
				if(watekSamolotu.joinable()){
                		watekSamolotu.detach();
				lWatkow --;
			}
		}
        }


        }


        return 0;
}
