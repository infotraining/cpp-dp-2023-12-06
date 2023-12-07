#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <iostream>
#include <string>

class Observer
{
public:
    virtual void update(/*...*/) = 0;
    virtual ~Observer()
    {
    }
};

// Subject
class Stock
{
private:
    std::string symbol_;
    double price_;
    // TODO - container that stores registered observers
public:
    Stock(const std::string& symbol, double price) : symbol_(symbol), price_(price)
    {
    }

    std::string get_symbol() const
    {
        return symbol_;
    }

    double get_price() const
    {
        return price_;
    }

    // TODO: register the observer

    // TODO: unregister the observer

    void set_price(double price)
    {
        price_ = price;

        // TODO: sending notification to observers
    }
};

class Investor : public Observer
{
    std::string name_;

public:
    Investor(const std::string& name) : name_(name)
    {
    }

    void update(/*...*/)
    {
        // TODO: implementacja
    }
};

#endif /*STOCK_HPP_*/
