#include <gtest/gtest.h>
#include <sstream>
#include <memory>
namespace {
    std::stringstream ss;
}
class Button {
public:
    virtual void ButtonFoo() = 0;
    virtual ~Button() = default;
};
class Box {
public:
    virtual void BoxFoo() = 0;
    virtual ~Box() = default;
};

class WinButton : public Button {
public:
    void ButtonFoo() override
    {
        ss << "WinButtonFoo";
    }
};
class LinuxButton : public Button {
public:
    void ButtonFoo() override
    {
        ss << "LinuxButtonFoo";
    }
};
class WinBox : public Box {
public:
    void BoxFoo() override
    {
        ss << "WinBoxFoo";
    }
};
class LinuxBox : public Box {
public:
    void BoxFoo() override
    {
        ss << "LinuxBoxFoo";
    }
};

class AbstractFactory {
public:
    virtual std::unique_ptr<Button> CreateButton() = 0;
    virtual std::unique_ptr<Box> CreateBox() = 0;
    virtual ~AbstractFactory() = default;
};

class WinFactory : public AbstractFactory {
public:
    std::unique_ptr<Button> CreateButton() override
    {
        return std::make_unique<WinButton>();
    }
    std::unique_ptr<Box> CreateBox() override
    {
        return std::make_unique<WinBox>();
    }
};
class LinuxFactory : public AbstractFactory {
public:
    std::unique_ptr<Button> CreateButton() override
    {
        return std::make_unique<LinuxButton>();
    }
    std::unique_ptr<Box> CreateBox() override
    {
        return std::make_unique<LinuxBox>();
    }
};
TEST(DesignPatterns, AbstractFactory)
{
    WinFactory win_;
    LinuxFactory linux_;
    auto box = win_.CreateBox();
    auto button = win_.CreateButton();
    std::string s;

    box->BoxFoo();
    ss >> s;
    EXPECT_EQ(s, "WinBoxFoo");
    ss.clear();

    button->ButtonFoo();
    ss >> s;
    EXPECT_EQ(s, "WinButtonFoo");
    ss.clear();

    box = linux_.CreateBox();
    button = linux_.CreateButton();

    box->BoxFoo();
    ss >> s;
    EXPECT_EQ(s, "LinuxBoxFoo");
    ss.clear();

    button->ButtonFoo();
    ss >> s;
    EXPECT_EQ(s, "LinuxButtonFoo");
    ss.clear();
}