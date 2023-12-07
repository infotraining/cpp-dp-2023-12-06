#ifndef COFFEEHELL_HPP_
#define COFFEEHELL_HPP_

#include <iostream>
#include <memory>
#include <string>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual float get_total_price() const = 0;
    virtual std::string get_description() const = 0;
    virtual void prepare() = 0;
};

class CoffeeBase : public Coffee
{
    float price_;
    std::string description_;

public:
    CoffeeBase(float price, const std::string& description)
        : price_{price}
        , description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_;
    }

    std::string get_description() const override
    {
        return description_;
    }
};

class Espresso : public CoffeeBase
{
public:
    Espresso(float price = 4.0, const std::string& description = "Espresso")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect espresso: 7 g, 15 bar and 24 sec.\n";
    }
};

class Cappuccino : public CoffeeBase
{
public:
    Cappuccino(float price = 6.0, const std::string& description = "Cappuccino")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect cappuccino.\n";
    }
};

class Latte : public CoffeeBase
{
public:
    Latte(float price = 8.0, const std::string& description = "Latte")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect latte.\n";
    }
};

// TO DO: Condiments: Whipped: 2.5$, Whisky: 6.0$, ExtraEspresso: 4.0$

class CoffeeDecorator : public Coffee
{
    std::unique_ptr<Coffee> coffee_;

public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee)
        : coffee_{std::move(coffee)}
    {
    }

    void prepare() override
    {
        coffee_->prepare();
    }
protected:
    Coffee& get_decorated_coffee() const
    {
        return *coffee_;
    }
};

class CoffeeBaseDecorator : public CoffeeDecorator
{
    float price_;
    std::string description_;

public:
    CoffeeBaseDecorator(std::unique_ptr<Coffee> coffee, std::string description, float price)
        : CoffeeDecorator{std::move(coffee)}
        , price_{price}
        , description_{std::move(description)}
    {
    }

    float get_total_price() const override
    {
        return get_decorated_coffee().get_total_price() + price_;
    }

    std::string get_description() const override
    {
        return get_decorated_coffee().get_description() + " + " + description_;
    }
};

class WhippedCream : public CoffeeBaseDecorator
{
public:
    WhippedCream(std::unique_ptr<Coffee> coffee) : CoffeeBaseDecorator{std::move(coffee), "Whipped Cream", 6.0}
    {}

    void prepare() override
    {
        CoffeeBaseDecorator::prepare();
        std::cout << "Adding whipped cream...\n";
    }
};

class Whisky : public CoffeeBaseDecorator
{
public:
    Whisky(std::unique_ptr<Coffee> coffee) : CoffeeBaseDecorator{std::move(coffee), "Whisky", 2.5}
    {}

    void prepare() override
    {
        CoffeeBaseDecorator::prepare();
        std::cout << "Adding whisky...\n";
    }
};

class ExtraEspresso : public CoffeeBaseDecorator
{
public:
    ExtraEspresso(std::unique_ptr<Coffee> coffee) : CoffeeBaseDecorator{std::move(coffee), "Extra espresso", 4.0}
    {}

    void prepare() override
    {
        CoffeeBaseDecorator::prepare();
        Espresso espresso;
        espresso.prepare();
    }
};

// TO DO: Add CoffeeDecorator and concrete decorators for condiments

#endif /*COFFEEHELL_HPP_*/
