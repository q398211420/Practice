#include <gtest/gtest.h>
#include <sstream>
#include <memory>
namespace {
    std::stringstream ss;
}
class AbstractProduct {
public:
    virtual void foo() = 0;
    virtual ~AbstractProduct() = default;

private:
};

class ProductA : public AbstractProduct {
public:
    virtual void foo() override
    {
        ss << "ConcreteA";
    }

private:
};

class ProductB : public AbstractProduct {
public:
    virtual void foo() override
    {
        ss << "ConcreteB";
    }

private:
};

class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProduct> CreateProduct() = 0;
    virtual ~AbstractFactory() = default;

private:
};

class AFactory : public AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProduct> CreateProduct() override
    {
        return std::make_unique<ProductA>();
    }
    virtual ~AFactory() = default;

private:
};

class BFactory : public AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProduct> CreateProduct() override
    {
        return std::make_unique<ProductB>();
    }
    virtual ~BFactory() = default;

private:
};

TEST(DesignPatterns, FactoryMethod)
{
    AFactory A;
    BFactory B;
    auto a = A.CreateProduct();
    auto b = B.CreateProduct();

    std::string s;

    a->foo();
    ss >> s;
    EXPECT_EQ(s, "ConcreteA");
    ss.clear();
    b->foo();
    ss >> s;
    EXPECT_EQ(s, "ConcreteB");
}
