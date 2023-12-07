#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#define MOTIF

enum class IconType
{
    none,
    ok,
    cancel,
    warning,
    error
};

class Widget
{
public:
    virtual void draw() = 0;
    virtual ~Widget() = default;
};

class Button : public Widget
{
    std::string caption_;
    IconType icon_type_;

public:
    Button(const std::string& caption, IconType icon_type)
        : caption_{caption}
        , icon_type_{icon_type}
    {
    }

    std::string caption() const
    {
        return caption_;
    }

    void set_caption(const std::string& caption)
    {
        caption_ = caption;
    }

    IconType icon() const
    {
        return icon_type_;
    }
};

class Menu : public Widget
{
    std::string text_;

public:
    Menu(const std::string& text)
        : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }

    void set_text(const std::string& text)
    {
        text_ = text;
    }
};

///////////////////////////////////////////////////////////////////
// Motif Widgets

class MotifButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "MotifButton [ " << caption() << " ]\n";
    }
};

class MotifMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "MotifMenu { " << text() << " }\n";
    }
};

///////////////////////////////////////////////////////////////////
// Windows Widgets

class WindowsButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "WindowsButton [ " << caption() << " ]\n";
    }
};

class WindowsMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "WindowsMenu { " << text() << " }\n";
    }
};

///========

class WidgetFactory
{
public:
    virtual std::unique_ptr<Button> CreateButton(const std::string& caption, IconType icon_type) = 0;
    virtual std::unique_ptr<Menu> CreateMenu(const std::string& text) = 0;
    virtual ~WidgetFactory() = default;
};

class MotifFactory : public WidgetFactory
{
public:
    std::unique_ptr<Button> CreateButton(const std::string& caption, IconType icon_type) override
    {
        return std::make_unique<MotifButton>(caption, icon_type);
    }

    std::unique_ptr<Menu> CreateMenu(const std::string& text) override
    {
        return std::make_unique<MotifMenu>(text);
    }
};

class WindowsFactory : public WidgetFactory
{
public:
    std::unique_ptr<Button> CreateButton(const std::string& caption, IconType icon_type) override
    {
        return std::make_unique<WindowsButton>(caption, icon_type);
    }

    std::unique_ptr<Menu> CreateMenu(const std::string& text) override
    {
        return std::make_unique<WindowsMenu>(text);
    }
};

class Window
{
    std::vector<std::unique_ptr<Widget>> widgets;

public:
    void display() const
    {
        std::cout << "######################\n";
        for (const auto& w : widgets)
            w->draw();
        std::cout << "######################\n\n";
    }

    void add_widget(std::unique_ptr<Widget> widget)
    {
        widgets.push_back(std::move(widget));
    }
};

class WindowOne : public Window
{
public:
    WindowOne(WidgetFactory& factory)
    {
        auto ok_button = factory.CreateButton("OK", IconType::ok);
        ok_button->set_caption("OK!!!");
        add_widget(std::move(ok_button));
        add_widget(factory.CreateMenu("File"));
    }
};

class WindowTwo : public Window
{
public:
    WindowTwo(WidgetFactory& factory)
    {
        add_widget(factory.CreateMenu("Edit"));
        add_widget(factory.CreateButton("OK", IconType::ok));
        add_widget(factory.CreateButton("Cancel", IconType::cancel));
    }
};

int main(void)
{
#ifdef MOTIF
    MotifFactory factory;
#else // WINDOWS
    WindowsFactory factory;
#endif

    WindowOne w1(factory);
    w1.display();

    WindowTwo w2(factory);
    w2.display();
}
