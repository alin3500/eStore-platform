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

    //Iterates through <requestsNo> and verifies if
    for(it = requestsNo.begin(); it != requestsNo.end(); it++)
    {
        //There is any request in <cacheAux>, if not, it creates one with the value of the first element of <requestsNo>
        if(cacheAux.size() == 0)
            cacheAux.push_back(*it);
        
        //There is at least one request in <cacheAux>
        else
        {
            //Variable used to verify if the value in <requestsNo> already exists in <cacheAux>
            gasit = 0;

            for(it2 = cacheAux.begin(); it2 != cacheAux.end(); ++it2)
            {
                //If found, it deletes that value from <cacheAux> and adds it to the end
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
                //If not found in <cacheAux> and <cacheAux> didn't reach its maximum capacity, the new value is added at the end of the list
                if(cacheAux.size() < capacity)
                    cacheAux.push_back(*it);
               //If <cacheAux> is at its maximum capacity, deletes the first element and adds the new element at the end(shifting the entire list so the old 2nd element is now the 1st)
               else
                {
                    cacheAux.erase(cacheAux.begin());
                    cacheAux.push_back(*it);
                    
                }
                
            }
        }
    }

    //Iterates through <cacheAux> backwards and adds each element to the <lru> list
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
