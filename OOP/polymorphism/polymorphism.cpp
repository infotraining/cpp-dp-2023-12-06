#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <variant>

using namespace std::literals;

namespace DynamicPolymorphism
{
    class Pickup
    {
    public:
        virtual std::string convert_signal(const std::string& string_vibrations) const = 0;
        virtual ~Pickup() = default;
    };

    class SingleCoil : public Pickup
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const override
        {
            return "humming "s + string_vibrations;
        }
    };

    class Humbucker : public Pickup
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const override
        {
            return "strong, noiseless "s + string_vibrations;
        }
    };

    class Guitar
    {
        std::unique_ptr<Pickup> pickup_;

    public:
        Guitar(std::unique_ptr<Pickup> pickup)
            : pickup_{std::move(pickup)}
        {
            assert(pickup_ != nullptr);
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing " << pickup_->convert_signal(sound) << std::endl;
        }
    };
}

namespace StaticPolymorphism
{
    class SingleCoil
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const
        {
            return "humming "s + string_vibrations;
        }
    };

    class Humbucker
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const
        {
            return "strong, noiseless "s + string_vibrations;
        }
    };

    template <typename TPickup_>
    class Guitar
    {
        TPickup_ pickup_;

    public:
        Guitar() = default;

        Guitar(TPickup_ pickup)
            : pickup_{std::move(pickup)}
        {
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing " << pickup_.convert_signal(sound) << std::endl;
        }
    };
}

namespace DuckTyping
{
    using Pickup = std::function<std::string(const std::string&)>;

    class SingleCoil
    {
    public:
        std::string operator()(const std::string& string_vibrations) const
        {
            return "humming "s + string_vibrations;
        }
    };

    struct Guitar
    {
        Pickup pickup;

        Guitar(Pickup pickup)
            : pickup{std::move(pickup)}
        {
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing " << pickup(sound) << std::endl;
        }
    };
}

namespace DynamicPolymorphism
{
    struct Point
    {
        int x, y;
    };

    class Shape
    {
    public:
        virtual ~Shape() = default;

        virtual void move(int dx, int dy) = 0;
        virtual void draw() const = 0;
    };

    struct ShapeBase : public Shape
    {
        Point coord;

        ShapeBase(int x, int y)
            : coord{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord.x += dx;
            coord.y += dy;
        }
    };

    struct Rectangle : public ShapeBase
    {
        int width, height;

        Rectangle(int x, int y, int w, int h)
            : ShapeBase{x, y}
            , width{w}
            , height{h}
        {
        }

        void draw() const override
        {
            std::cout << "Drawing Rectangle at (" << coord.x << ", " << coord.y << "); w: " << width << "; h: " << height << "\n";
        }
    };

    struct Circle : public ShapeBase
    {
        int radius;

        Circle(int x, int y, int r)
            : ShapeBase{x, y}
            , radius{r}
        {
        }

        void draw() const override
        {
            std::cout << "Drawing Circle at (" << coord.x << ", " << coord.y << "); r: " << radius << "\n";
        }
    };
}

namespace StaticPolymorphism
{
    struct Point
    {
        int x, y;
    };

    struct ShapeBase
    {
        Point coord;

        ShapeBase(int x, int y)
            : coord{x, y}
        {
        }

        void move(int dx, int dy)
        {
            coord.x += dx;
            coord.y += dy;
        }
    };

    struct Rectangle : public ShapeBase
    {
        int width, height;

        Rectangle(int x, int y, int w, int h)
            : ShapeBase{x, y}
            , width{w}
            , height{h}
        {
        }

        void draw() const
        {
            std::cout << "Drawing Rectangle at (" << coord.x << ", " << coord.y << "); w: " << width << "; h: " << height << "\n";
        }
    };

    struct Circle : public ShapeBase
    {
        int radius;

        Circle(int x, int y, int r)
            : ShapeBase{x, y}
            , radius{r}
        {
        }

        void draw() const
        {
            std::cout << "Drawing Circle at (" << coord.x << ", " << coord.y << "); r: " << radius << "\n";
        }
    };

    using ShapeVariant = std::variant<Circle, Rectangle>;

    class Shape
    {
        ShapeVariant shp;
    public:
        template <typename T>
        Shape(T shape) : shp(shape)
        {}

        void move(int dx, int dy)
        {
            std::visit([=](auto& s) { s.move(dx, dy); }, shp);
        }

        void draw() const
        {
            std::visit([](auto& s) { s.draw(); }, shp);
        }
    };
}

void shapes()
{
    {
        using namespace DynamicPolymorphism;

        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::make_unique<Circle>(10, 20, 40));
        shapes.push_back(std::make_unique<Rectangle>(10, 20, 40, 400));

        for (const auto& shp : shapes)
            shp->draw();
    }

    {
        using namespace StaticPolymorphism;
        Shape shp = Rectangle(10, 20, 300, 400);
        shp.draw();
        shp = Circle(100, 200, 400);
        shp.draw();

        std::vector<Shape> shapes;
        shapes.push_back(shp);
        shapes.push_back(Rectangle(0, 0, 100, 200));

        for (const auto& shp : shapes)
            shp.draw();
    }
}

int main()
{
    // {
    //     using namespace DynamicPolymorphism;

    //     Guitar strat{std::make_unique<SingleCoil>()};
    //     strat.play("D-power-cord");

    //     Guitar les_paul{std::make_unique<Humbucker>()};
    //     les_paul.play("D-power-cord");
    // }

    // {
    //     using namespace StaticPolymorphism;

    //     Guitar strat{SingleCoil{}}; /// CTAD
    //     strat.play("D-power-cord");

    //     Guitar<Humbucker> les_paul;
    //     les_paul.play("D-power-cord");
    // }

    // {
    //     using namespace DuckTyping;

    //     SingleCoil sc;

    //     Guitar g{std::move(sc)};

    //     g.play("D-power-cord");

    //     g.pickup = [](const std::string& string_vibrations)
    //     {
    //         return "strong, noiseless "s + string_vibrations;
    //     };

    //     g.play("A-power-cord");
    // }

    shapes();
}