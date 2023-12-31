#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "shape.hpp"
#include "shape_group.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

class GraphicsDoc
{
    ShapeGroup shapes_;
    ShapeFactory& shape_factory_;
    ShapeRWFactory& shape_rw_factory_;

public:
    GraphicsDoc(ShapeFactory& shape_factory, ShapeRWFactory& shape_rw_factory)
        : shape_factory_{shape_factory}, shape_rw_factory_{shape_rw_factory}
    {
    }

    void add(unique_ptr<Shape> shp)
    {
        shapes_.add(std::move(shp));
    }

    void render()
    {
        shapes_.draw();
    }

    void load(const string& filename)
    {
        ifstream file_in{filename};

        if (!file_in)
        {
            cout << "File not found!" << endl;
            exit(1);
        }

        string shape_id;
        file_in >> shape_id;
        assert(shape_id == ShapeGroup::id);

        auto shape_group_rw = shape_rw_factory_.create(make_type_index<ShapeGroup>());
        shape_group_rw->read(shapes_, file_in);
    }

    void save(const string& filename)
    {
        ofstream file_out{filename};

        for (const auto& shp : shapes_)
        {
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shp));
            shape_rw->write(*shp, file_out);
        }
    }
};

int main()
{
    cout << "Start..." << endl;

    GraphicsDoc doc(SingletonShapeFactory::instance(), SingletonShapeRWFactory::instance());

    doc.load("drawing_composite.txt");

    cout << "\n";

    doc.render();

    doc.save("new_drawing_composite.txt");
}
