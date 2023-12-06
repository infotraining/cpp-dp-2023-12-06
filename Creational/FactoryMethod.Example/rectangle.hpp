#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "shape_readers_writers/rectangle_reader_writer.hpp"

namespace Drawing
{

    class Rectangle : public ShapeBase
    {
        int width_, height_;

    public:
        static constexpr const char* id = "Rectangle";

        Rectangle(int x = 0, int y = 0, int w = 0, int h = 0);

        int width() const
        {
            return width_;
        }

        void set_width(int w)
        {
            width_ = w;
        }

        int height() const
        {
            return height_;
        }

        void set_height(int h)
        {
            height_ = h;
        }

        void draw() const override;

        std::unique_ptr<IO::ShapeReaderWriter> create_reader_writer() override
        {
            return std::make_unique<IO::RectangleReaderWriter>();
        }
    };
}
#endif // RECTANGLE_HPP
