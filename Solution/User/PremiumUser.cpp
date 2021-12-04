#include "PremiumUser.h"

using namespace std;

PremiumUser::PremiumUser()
{
    premiumSubscriptionCost = 0;
}

PremiumUser::PremiumUser(const string &judetf, const string &localitatef, const string &stradaf, int nr_stradaf, const string &blocf, int apartamentf,
						 const string &judetl, const string &localitatel, const string &stradal, int nr_stradal, const string &blocl, int apartamentl,
						 int id, const string &nume, const string &prenume, const string &email, int premiumSubscriptionCost, const map<int, int> &discounts)
	: User(judetf, localitatef, stradaf, nr_stradaf, blocf, apartamentf, judetl, localitatel, stradal, nr_stradal, blocl, apartamentl, id, nume, prenume, email)
{
    (*this).discounts = discounts;
    premiumSubscriptionCost = premiumSubscriptionCost;
}

PremiumUser::PremiumUser(const PremiumUser &up) : User(up)
{
    (*this).discounts = up.discounts;
    (*this).premiumSubscriptionCost = up.premiumSubscriptionCost;
}

const PremiumUser &PremiumUser::operator=(const PremiumUser &up)
{
    (*this).discounts = up.discounts;
    (*this).premiumSubscriptionCost = up.premiumSubscriptionCost;
    User::operator=(up);
    
    return *this;
}

void PremiumUser::displayUser()
{
	throw("undefined");
}

string PremiumUser::getUserType()
{
	return "PremiumUser";
}

float PremiumUser::getTransportCost()
{
    return 0.0;    
}

map<int, int> &PremiumUser::getDiscounts()
{
    return discounts;  
}

void PremiumUser::setDiscounts(map<int, int> red)
{
    discounts = red;
}

void PremiumUser::setPremiumSubscriptionCost(int cap)
{
    premiumSubscriptionCost = cap;
}

int PremiumUser::getPremiumSubscriptionCost()
{
    return premiumSubscriptionCost;
}

json PremiumUser::toJSON()
{
	return json(*this);
}