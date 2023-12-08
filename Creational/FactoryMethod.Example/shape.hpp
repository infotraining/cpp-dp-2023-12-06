#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

namespace Drawing
{
    namespace IO
    {
        class ShapeReaderWriter;
    }

    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        
        virtual std::unique_ptr<IO::ShapeReaderWriter> create_reader_writer() = 0;
    };


    class ShapeBase : public Shape
    {
        Point coord_; // composition
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
}

#endif // SHAPE_HPP
