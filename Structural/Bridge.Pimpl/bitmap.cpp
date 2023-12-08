#include "bitmap.hpp"
#include <algorithm>
#include <array>
#include <list>

using namespace std;

struct Bitmap::BitmapImpl
{
    std::vector<char> image_;

    BitmapImpl(size_t size, char fill_char) : image_(size, fill_char)
    {}

    void render()
    {
        for(const auto& pixel :image_)
            cout << pixel;
        cout << endl;
    }
};

Bitmap::Bitmap(size_t size, char fill_char) : pimpl_{std::make_unique<BitmapImpl>(size, fill_char)}
{
}

Bitmap::~Bitmap() = default;

void Bitmap::draw()
{
    cout << "Image: ";

    pimpl_->render();

    cout << endl;
}
