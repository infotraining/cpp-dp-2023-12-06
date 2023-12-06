#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "rectangle.hpp"
#include "shape_readers_writers/square_reader_writer.hpp"

namespace Drawing
{

    class Square : public Shape
    {
        Rectangle rect_;

    public:
        static constexpr const char* id = "Square";

        Square(int x = 0, int y = 0, int size = 0);

        Point coord() const;

        void set_coord(const Point& pt);

        int size() const;

        void set_size(int size);

        void draw() const override;

        void move(int x, int y) override;

        std::unique_ptr<IO::ShapeReaderWriter> create_reader_writer() override
        {
            return std::make_unique<IO::SquareReaderWriter>();
        }
    };
}

#endif // SQUARE_HPP
