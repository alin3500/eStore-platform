#include "Product.h"
using namespace std;

Product::~Product() {}

bool Product::checkQuantity(int requestedQuantity)
{
    if(quantity >= requestedQuantity)
        return true;
    else
        return false;
}

Product::Product(const string &category, int id, const string &name, int quantity)
{
    (*this).category = category;
    (*this).id = id;
    (*this).name = name;
    (*this).quantity = quantity;
}

Product::Product(const Product &p)
{
    name = p.name;
    quantity = p.quantity;
    category = p.category;
    id = p.id;
}

Product::Product()
{
    name = " ";
    quantity = 0;
    category = " ";
    id = 0;
}

void Product::decreaseQuantity(int requestedQuantity)
{
    quantity -= requestedQuantity;
}

void Product::increaseQuantity(int requestedQuantity)
{
    quantity += requestedQuantity;
}

void Product::setCategory(const string &category)
{
    (*this).category = category;
}

void Product::setId(int id)
{
    (*this).id = id;
}

void Product::setQuantity(int quantity)
{
    (*this).quantity = quantity;
}

void Product::setName(const string &name)
{
    (*this).name = name;
}

string &Product::getCategory()
{
    return category;
}

int Product::getQuantity()
{
    return quantity;
}

int Product::getId()
{
    return id;
}

string &Product::getName()
{
    return name;
}

const Product &Product::operator=(const Product &a)
{
    (*this).name = a.name;
    (*this).quantity = a.quantity;
    (*this).category = a.category;
    (*this).id = a.id;

    return (*this);
}

json Product::toJSON()
{
	return json(*this);
}
