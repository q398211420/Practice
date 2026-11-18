#include <gtest/gtest.h>
#include <memory>
#include <format>
#include <string>
// 桥接模式（Bridge Pattern） 核心意图是将抽象部分与实现部分分离，使它们可以独立变化。
// 核心思想
// 传统继承容易把抽象和实现绑死，导致类爆炸（例如：圆形×OpenGL、圆形×DirectX、矩形×OpenGL……）。桥接模式用组合替代继承，把两个变化维度拆成两套独立的类层次，再通过“桥”（持有实现对象的引用）连接起来。
class Shape {
public:
    virtual std::string Draw() const = 0;
    virtual ~Shape() = 0;

protected:
    Shape() = default;
    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) = delete;
};

inline Shape::~Shape() = default;

class BackendAPI {
public:
    virtual std::string DrawCircle(int x, int y, float radius) const = 0;
    virtual std::string DrawRectangle(int x, int y, int width, int height) const = 0;
    virtual ~BackendAPI() = 0;

protected:
    BackendAPI() = default;
    BackendAPI(const BackendAPI&) = delete;
    BackendAPI& operator=(const BackendAPI&) = delete;
};

inline BackendAPI::~BackendAPI() = default;

class Skia : public BackendAPI {
public:
    std::string DrawCircle(int x, int y, float radius) const override
    {
        return std::format("Skia Circle {} {} {}", x, y, radius);
    }
    std::string DrawRectangle(int x, int y, int width, int height) const override
    {
        return std::format("Skia Rectangle {} {} {} {}", x, y, width, height);
    }
};

class DDGR : public BackendAPI {
public:
    std::string DrawCircle(int x, int y, float radius) const override
    {
        return std::format("DDGR Circle {} {} {}", x, y, radius);
    }
    std::string DrawRectangle(int x, int y, int width, int height) const override
    {
        return std::format("DDGR Rectangle {} {} {} {}", x, y, width, height);
    }
};

class Circle : public Shape {
public:
    Circle(int x, int y, float radius, std::shared_ptr<BackendAPI> api) : m_x(x), m_y(y), m_radius(radius), m_api(api) {}
    std::string Draw() const override
    {
        return "Draw Circle " + m_api->DrawCircle(m_x, m_y, m_radius);
    }

private:
    int m_x{};
    int m_y{};
    float m_radius{};
    std::shared_ptr<BackendAPI> m_api{};
};

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height, std::shared_ptr<BackendAPI> api) : m_x(x), m_y(y), m_width(width), m_height(height), m_api(api) {}
    std::string Draw() const override
    {
        return "Draw Rectangle " + m_api->DrawRectangle(m_x, m_y, m_width, m_height);
    }

private:
    int m_x{};
    int m_y{};
    int m_width{};
    int m_height{};
    std::shared_ptr<BackendAPI> m_api{};
};

TEST(DesignPatterns, Bridge)
{
    auto ddgr = std::make_shared<DDGR>();
    auto skia = std::make_shared<Skia>();
    auto c1 = Circle(1,2,3.1,skia);
    auto c2 = Circle(1,2,3.2,ddgr);
    auto r1 = Rectangle(1,2,3,4,skia);
    auto r2 = Rectangle(2,2,3,4,ddgr);
    EXPECT_EQ(c1.Draw(), "Draw Circle Skia Circle 1 2 3.1");    
    EXPECT_EQ(c2.Draw(), "Draw Circle DDGR Circle 1 2 3.2");    
    EXPECT_EQ(r1.Draw(), "Draw Rectangle Skia Rectangle 1 2 3 4");   
    EXPECT_EQ(r2.Draw(), "Draw Rectangle DDGR Rectangle 2 2 3 4");
}