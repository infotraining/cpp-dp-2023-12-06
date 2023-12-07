#include "text_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../text.hpp"

using namespace std;
using namespace Drawing;
using namespace IO;

// TODO - register creator for a TextReaderWriter class
namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
                             .register_creator(make_type_index<Text>(), [] { return make_unique<TextReaderWriter>(); });
}

void TextReaderWriter::read(Shape& shp, istream& in)
{
    Text& text = static_cast<Text&>(shp);

    Point pt;
    std::string _text;

    in >> pt >> _text;

    text.set_coord(pt);
    text.set_text(_text);

}

void TextReaderWriter::write(const Shape& shp, ostream& out)
{
    const Text& text = static_cast<const Text&>(shp);

    out << Text::id << " " << text.get_text() << std::endl;
}
