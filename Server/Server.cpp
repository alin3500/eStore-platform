#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
    usersCapacity = usr.size();
    list<User*>::iterator it = usr.begin();
    
    //Parcurge toti userii si creeaza cate un shoppingCart nou pentru fiecare, dupa care ii introduce in map
    for(it = usr.begin(); it != usr.end(); ++it)
    {
        ShoppingCart* cartAux = new ShoppingCart();
        __UserID__ProductsCart__.insert(pair<int, ShoppingCart*>((*(*it)).getUserID(), cartAux));
    }
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{
	map<int, ShoppingCart*>::iterator it1 = __UserID__ProductsCart__.find(userID);
    
    list<Product*>::iterator itp;
    list<User*>::iterator itu;
    map<int, int>::iterator itcart;

    //Verifica daca exista userul cu ID-ul <userID> si daca a fost introdusa o cantitate valida
    if(quantity <= 0 || it1 == __UserID__ProductsCart__.end())
        return false;

    //Parcurge lista de produse din server pentru a gasi <productID>
    for(itp = prod.begin(); itp != prod.end(); ++itp)
    {
        if((*(*itp)).getId() == productID)
         {
            if((*(*itp)).checkQuantity(quantity))
            {
                //Daca <productID> a fost gasit iar cantitatea disponibila este >= cu <quantity>
                //verifica daca <ShoppingCart> pentru <userID> este gol, si adauga produs nou
                if((*(*it1).second).getShoppingCart().size() == 0)
                    (*(*it1).second).addProduct(productID, quantity);

                //Daca <ShoppingCart> contine 1 sau mai multe produse, cauta pentru a vedea daca
                //printre ele se afla si <productID>
                else
                {
                    itcart = (*(*it1).second).getShoppingCart().find(productID);

                    //Daca da, mareste cantitatea lui <productID> din cos
                    if(itcart != (*(*it1).second).getShoppingCart().end())
                        (*(*it1).second).raiseQuantity(productID, quantity);
                    
                    //Altfel, adauga drept produs nou in cos
                    else
                        (*(*it1).second).addProduct(productID, quantity);

                }
                
                //Scade cantitatea disponibila in stoc
                (*(*itp)).decreaseQuantity(quantity);
                return true;
            }
        }
    }
    
    return false;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
    list<Product*>::iterator itp;
    map<int, ShoppingCart*>::iterator it1 = __UserID__ProductsCart__.find(userID);
    map<int, int>::iterator itmap = (*(*it1).second).getShoppingCart().find(productID);

    itmap = (*(*it1).second).getShoppingCart().find(productID);

    //Verifica daca exista <userID>, <productID> in <ShoppingCart> si daca <quantity> este un numar valid
    if(itmap == (*(*it1).second).getShoppingCart().end() || it1 == __UserID__ProductsCart__.end() || quantity <= 0)
        return false;

    //Auxiliar pentru a memore cantitatea scazuta cu adevarat din cos
    int realQuantity = 0;

    //Cazul in care cantitatea din cos este mai mare decat cantitatea de scazut <quantity>
    if((*(*it1).second).getQuantity(productID) > quantity)
    {
        //Scade cantitatea din cos
        realQuantity = quantity;
        (*(*it1).second).lowerQuantity(productID, quantity);

        //Cauta produsul in stoc si ii mareste cantitatea disponibila
        for(itp = prod.begin(); itp != prod.end(); ++itp)
            if((*(*itp)).getId() == productID)
                (*(*itp)).increaseQuantity(realQuantity);

        return true;
    }

    //Cazul in care cantitatea din cos este mai mica sau egala cu cantitatea de scazut <quantity>
    else if((*(*it1).second).getQuantity(productID) <= quantity)
    {
        //Sterge produsul din cos si memoreaza in <realQuantity> cantitatea care s-a scazut de fapt
        realQuantity = (*(*it1).second).getQuantity(productID);
        (*(*it1).second).deleteProduct(productID);

        //Mareste cantitatea disponibila in stoc
        for(itp = prod.begin(); itp != prod.end(); ++itp)
            if((*(*itp)).getId() == productID)
                (*(*itp)).increaseQuantity(realQuantity);

        return true;
    }

    

    return false;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}