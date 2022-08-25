#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a()
{
    list<Product*> redProd;
    list<Product*>::iterator it;

    //Parcurge lista de produse din server si cauta articole din categoria "espressor" si daca produsul are discount
    //Si le introduce in lista <redProd>
    for(it = (*server).getProductsList().begin(); it != (*server).getProductsList().end(); ++it)
        if((*(*it)).getProductType() == "DiscountedProduct" && (*(*it)).Product::getCategory() == "espressor")
            redProd.push_back(*it);
  
  return redProd;
}

list<User*> QuerySolver::Query_3b()
{
    list<User*> redUser;
    list<User*>::iterator it;
    
    //Parcurge lista de useri si cauta "BasicUser" care au <transportCost> <= 11.5
    //Si ii introduce in <redUser>
    for(it = (*server).getUsersList().begin(); it != (*server).getUsersList().end(); ++it)
        if((*(*it)).getUserType() == "BasicUser" && (*(*it)).getTransportCost() <= 11.5)
            redUser.push_back(*it);

    return redUser;
}

list<Product*> QuerySolver::Query_3c()
{   
    vector<float> aux;
    list<Product*> retProd;
    list<Product*>::iterator it, it2;
    ReturnedProduct* itRet;

    //Parcurge lista de produse pentru a gasit produse resigilate care au motivul "lipsa_accesorii"
    //Si le introduce pretul in vectorul aux
    for(it = (*server).getProductsList().begin(); it != (*server).getProductsList().end(); ++it)
    {
        itRet = dynamic_cast<ResealedProduct*>(*it);

        if(itRet != nullptr)
            if((*itRet).getProductType() == "ResealedProduct" && (*itRet).getReason() == "lipsa_accesorii")
                aux.push_back((*itRet).getPrice());       
    }

    //Sorteaza vectorul cu preturi
    sort(aux.begin(), aux.end());
    vector<float>::iterator poz;

    //Parcurge vectorul sortat de preturi si cauta produsele <ReturnedProduct> cu pretul respectiv 
    for(poz = aux.begin(); poz != aux.end(); ++poz)
    {
        for(it = (*server).getProductsList().begin(); it != (*server).getProductsList().end(); ++it)
        {
            itRet = dynamic_cast<ReturnedProduct*>(*it);
            if(itRet != nullptr)
            {
                if((*itRet).getPrice() == *poz)
                {
                    //Deci, le introduce ordonat dupa pret in lista <redProd>
                    retProd.push_back(itRet);
                }
            }
        }
    }

  return retProd;
}

list<Product*> QuerySolver::Query_3d()
{
    vector<string> numeProd, taraProd;
    vector<float> pretProd;

    list<Product*> prodAl, aux;
    list<Product*>::iterator it;

    FoodProduct* itFood;

    //Cauta articole "FoodProduct" si le introduce in lista aux(care memoreaza doar articole "FoodProduct")
    for(it = (*server).getProductsList().begin(); it != (*server).getProductsList().end(); ++it)
    {
            if((*(*it)).getProductType() == "FoodProduct")
            {
                aux.push_back(*it);
                itFood = dynamic_cast<FoodProduct*>(*it);
                if(itFood != nullptr)
                {
                    //Introduce numele, tara de origine si pretul fiecarui <FoodProduct> gasit in cate un vector dedicat
                    numeProd.push_back((*itFood).getName());       
                    taraProd.push_back((*itFood).getCountryOfOrigin());
                    pretProd.push_back((*itFood).getLeiPerKg());
                }
            }
    }

    //Sorteaza fiecare vector
    sort(numeProd.begin(), numeProd.end());
    sort(taraProd.begin(), taraProd.end());
    sort(pretProd.begin(), pretProd.end());

    //Elimina elementele duplicate din fiecare vector
    unique(numeProd.begin(), numeProd.end());
    unique(taraProd.begin(), taraProd.end());
    unique(pretProd.begin(), pretProd.end());

    vector<string>::iterator itn, itt;
    vector<float>::iterator itp;


    //Parcurge fiecare vector pentru a crea combinatiile de nume, tara si pret in ordine crescatoare
    //Ex: Nume1 = "Ceapa"           Nume1 = "Ceapa"             Nume1 = "Ceapa"     ...
    //    Tara1 = "Polonia"         Tara1 = "Polonia"           Tara2 = "Olanda"    ...
    //    Pret1 = "1.05"            Pret2 = "2.50"              Pret1 = "1.05"      ...

    for(itn = numeProd.begin(); itn != numeProd.end(); ++itn)
    {
        for(itt = taraProd.begin(); itt != taraProd.end(); ++itt)
        {
            for(itp = pretProd.begin(); itp != pretProd.end(); ++itp)
            {
                //Parcurge lista de <FoodProduct> pe care am creat-o pentru a cauta combinatia la care se afla acum
                for(it = aux.begin(); it != aux.end(); ++it)
                {
                    itFood = dynamic_cast<FoodProduct*>(*it);
                    if(itFood != nullptr)
                    {
                        //Daca o gaseste, introduce acel <FoodProduct> in lista <prodAl>, iar la sfarsit acestea vor fi deja ordonate
                        if((*itn) == (*itFood).getName() && (*itt) == (*itFood).getCountryOfOrigin() && (*itp) == (*itFood).getLeiPerKg())
                        {
                            prodAl.push_back(itFood);
                            it = aux.erase(it);
                        }
                    }
                }
            }
        }
    }
//---------------------------------------------------------------------------------------------

//Aceasta metoda ineficienta este motivul pentru durata crescuta de verificare a testului 8

//---------------------------------------------------------------------------------------------

    return prodAl;
}

list<User*> QuerySolver::Query_3e()
{

    multimap<int, string> judete;
    multimap<int, string>::iterator itmap;
    list<User*> usrAux, resUsr;
    list<User*>::iterator it;
    vector<int> usrIDs;
    vector<int>::iterator itID;
    string judMax, value;
    int key, gasit;

    //Parcurge lista de useri din <server> si creeaza element nou, respectiv creste numarul de locuitori pentru
    //judetul user-ului actual, in multimap-ul <judete>

//---------------------------------------------------------------------------------------------

//Am utilizat <multimap> pentru abilitatea acestui template de a se sorta singur in functie de key(nr. de locuitori)

//---------------------------------------------------------------------------------------------
    for(it = (*server).getUsersList().begin(); it != (*server).getUsersList().end(); ++it)
    {
        if(judete.size() == 0)
        {
            judete.insert(pair<int, string>(1, (*(*it)).getBillingData().getCounty()));
        }
        else
        {
            gasit = 0;

            for(itmap = judete.begin(); itmap != judete.end(); ++itmap)
                if((*itmap).second == (*(*it)).getBillingData().getCounty())
                {   
                    //Daca judetul actual se afla deja in map, pentru a-i mari numarul de locuitori(a modifica key-ul)
                    //este nevoie ca acesta sa fie sters din map si introdus la loc, cu key-ul modificat
                    key = (*itmap).first;
                    value = (*itmap).second;
                    judete.erase(itmap);
                    key++;
                    judete.insert(pair<int, string>(key, value));

                    gasit = 1;
                    break;
                }

            //Daca judetul actual nu se afla in map, creeaza un element nou cu key(nr. de locuitori = 1 si numele judetului)
            if(gasit == 0)
            {
                judete.insert(pair<int, string>(1, (*(*it)).getBillingData().getCounty()));
            }
        }
    }

    //Este salvat numele judetului cu cel mai mare numar de useri
    judMax = (*judete.rbegin()).second;
    
    //Parcurge lista de useri si ii cauta pe cei cu adresa in <judMax>, creeaza o lista cu toti userii din <judMax>
    //si memoreaza ID-urile lor in <usrIDs> 
    for(it = (*server).getUsersList().begin(); it != (*server).getUsersList().end(); ++it)
    {
        if((*(*it)).getBillingData().getCounty() == judMax && (*(*it)).getBillingData().getBlock() == "-" && (*(*it)).getDeliveryData().getBlock() == "-" && (*(*it)).getBillingData().getApartment() == 0 && (*(*it)).getDeliveryData().getApartment() == 0)
        {
            usrAux.push_back(*it);
            usrIDs.push_back((*(*it)).getUserID());
        }
    }

    //Sorteaza crescator ID-urile userilor
    sort(usrIDs.begin(), usrIDs.end());

    //Cauta, in ordine crescatoare a ID-urilor, userii din usrAux, si ii memoreaza(ordonat) in resUsr
    for(itID = usrIDs.begin(); itID != usrIDs.end(); ++itID)
        for(it = usrAux.begin(); it != usrAux.end(); ++it)
            if(*itID == (*(*it)).getUserID())
                resUsr.push_back(*it);
    

    return resUsr;
}

list<User*> QuerySolver::Query_3f()
{
    list<User*> premUsers, resUsr;
    list<User*>::iterator it;
    list<Product*> tlf_impr;
    list<Product*>::iterator itProd, itTI;
    vector<int> id_tlf_impr;
    vector<int>::iterator itvec;
    map<int, int>::iterator itmap;
    PremiumUser* itPrem;

    //Creeaza o lista cu toti <PremiumUser> 
    for(it = (*server).getUsersList().begin(); it != (*server).getUsersList().end(); ++it)
        if((*(*it)).getUserType() == "PremiumUser")
            premUsers.push_back(*it);

    //Creeaza o lista cu toate <Product> care sunt "telefon" sau "imprimanta"
    for(itProd = (*server).getProductsList().begin(); itProd != (*server).getProductsList().end(); ++itProd)
        if((*(*itProd)).getCategory() == "telefon" || (*(*itProd)).getCategory() == "imprimanta")
            tlf_impr.push_back(*itProd);

    //Parcurge lista <premUsers> si verifica daca vreunul din codurile lor de discount se potriveste cu produsele din <tlf_impr>
    int k =0;
    for(it = premUsers.begin(); it != premUsers.end(); ++it)
    {
        itPrem = dynamic_cast<PremiumUser*>(*it);

        for(itmap = (*itPrem).getDiscounts().begin(); itmap != (*itPrem).getDiscounts().end(); ++itmap)
        {
            for(itTI = tlf_impr.begin(); itTI != tlf_impr.end(); ++itTI)
            {
                if((*itmap).first == (*(*itTI)).getId())
                {
                    //Daca da, introduce <PremiumUser> respectiv in lista <resUsr> si modifica iteratorii <itmap> si <itTI>
                    //pentru a incheia al doilea si al treilea for
                    k++;
                    resUsr.push_back(itPrem);

                    itmap = (*itPrem).getDiscounts().end();
                    itmap--;
                    itTI = tlf_impr.end();
                    itTI--;
                }
            }
        }
    }

    return resUsr;
}
