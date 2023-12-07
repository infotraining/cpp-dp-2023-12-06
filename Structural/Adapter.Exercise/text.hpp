#ifndef TEXT_HPP
#define TEXT_HPP

#include "paragraph.hpp"
#include "shape.hpp"

#include <string>

namespace Drawing
{
    // TODO - adapt Paragraph class to Shape interface
    class Text : public ShapeBase, private LegacyCode::Paragraph
    {
    public:
        static constexpr const char* id = "Text";

        void draw() const override
        {
            render_at(coord().x, coord().y);
        }

        std::string get_text() const
        {
            return get_paragraph();
        }

        void set_text(const std::string& text)
        {
            return set_paragraph(text.c_str());
        }
    };
}

#endif
