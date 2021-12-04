#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity)
{
    (*this).capacity = capacity;
    size = 0;

}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
    int gasit, aux;
    vector<int>::reverse_iterator itR;
    vector<int> cacheAux;
    vector<int>::iterator it, it2;

    //Parcurge vectorul <requestsNo> si verifica daca
    for(it = requestsNo.begin(); it != requestsNo.end(); it++)
    {
        //In <cacheAux> exista vreun request, daca nu, creeaza unul, cu valoarea primului element din <requestsNo>
        if(cacheAux.size() == 0)
            cacheAux.push_back(*it);
        
        //In <cacheAux> exista deja cel putin un request
        else
        {
            //Variabila pentru a memora daca valoarea din <requestsNo> este deja prezenta in <cacheAux>
            gasit = 0;

            for(it2 = cacheAux.begin(); it2 != cacheAux.end(); ++it2)
            {
                //Daca e gasit, sterge valoarea respectiva din <cacheAux> si o adauga la sfarsit
                if(*it == *it2)
                {
                    gasit = 1;
                    aux = *it2;
                    cacheAux.erase(it2);
                    cacheAux.push_back(aux);
                }
            }

            if(gasit == 0)
            {
                //Daca nu se regaseste in <cacheAux> si <cacheAux> nu si-a atins capacitatea maxima, este introdusa noua valoare la sfarsitul listei
                if(cacheAux.size() < capacity)
                    cacheAux.push_back(*it);
               //Daca <cacheAux> este la capacitatea maxima, sterge primul element din lista si adauga noua valoare la sfarsit(primul element fiind acum al doilea de dinainte de a se sterge)
               else
                {
                    cacheAux.erase(cacheAux.begin());
                    cacheAux.push_back(*it);
                    
                }
                
            }
        }
    }

    //Parcurge <cacheAux> in ordine inversa si introduce fiecare element in lista <lru>
    for(itR = cacheAux.rbegin(); itR != cacheAux.rend(); ++itR)
        lru.push_back(*itR);

    size = lru.size();

    return lru;
}

int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	return capacity;
}

void LRUCache::setCapacity(int capacity)
{
	(*this).capacity = capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	(*this).lru = aux;
}
