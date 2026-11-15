#include <gtest/gtest.h>
#include <memory>

class Target {
public:
    virtual std::string Request(const std::string& code) const = 0;
    virtual ~Target() = default;
};

class Adaptee {
public:
    virtual std::string OldRequest(int num, const std::string& code) const
    {
        return std::to_string(num) + code;
    }
    virtual ~Adaptee() = default;
};

class Adapter: public Target{
public:
    std::string Request(const std::string &code) const override
    {
        auto [num, newCode] = Parse(code);
        return  m_old->OldRequest(num, newCode);
        
    }
private:
    auto Parse(const std::string & code) const -> std::pair<int,  std::string>
    {
        int num = std::stoi(code.substr(0,1));
        auto newCode = code.substr(1);
        return {num, newCode};
    }
    std::unique_ptr<Adaptee> m_old{std::make_unique<Adaptee>()};
};

TEST(DesignPatterns, Adapter)
{
    std::string str{"10image"};
    EXPECT_EQ(Adapter().Request(str), Adaptee().OldRequest(1, "0image"));
}