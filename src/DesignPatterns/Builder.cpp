#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
namespace {
    std::stringstream ss;
}
// Builder 的核心价值是把“复杂、可选、多步骤”的创建过程封装起来，让客户端代码变干净、让对象始终处于合法状态。
// 如果对象创建本身就简单，就不要强行用；一旦开始出现“参数太多、重载太多、调用看不懂、容易造出残缺对象”的症状，就该上 Builder 了。
enum class DeviceType {
    PHONE,
    TABLET,
    PC
};

class Computer {
    friend class ComputerBuilder;

public:
    const std::string& GetCPU() const
    { return CPU; }
    const std::string& GetGPU() const
    { return GPU; }
    const std::string& GetRAM() const
    { return RAM; }
    DeviceType GetType() const
    { return Type; }

private:
    Computer() = default;
    std::string CPU{};
    std::string GPU{};
    std::string RAM{};
    DeviceType Type{};
};

class ComputerBuilder {
public:
    ComputerBuilder& SetCPU(std::string cpu)
    {
        c.CPU = cpu;
        return *this;
    }
    ComputerBuilder& SetGPU(std::string gpu)
    {
        c.GPU = gpu;
        return *this;
    }
    ComputerBuilder& SetRAM(std::string ram)
    {
        c.RAM = ram;
        return *this;
    }
    ComputerBuilder& SetType(DeviceType type)
    {
        c.Type = type;
        return *this;
    }
    Computer Build()
    {
        if (c.CPU == "") {
            c = Computer{};
            throw std::invalid_argument("CPU is required!");
        }
        auto ret = std::move(c);
        c = Computer{};
        return ret;
    }

private:
    Computer c;
};

TEST(DesignPatterns, Builder)
{
    ComputerBuilder b;
    auto c = b.SetCPU("i7").SetGPU("gtx3060").SetRAM("8g").SetType(DeviceType::PC).Build();
    EXPECT_EQ(c.GetCPU(), "i7");
    EXPECT_EQ(c.GetGPU(), "gtx3060");
    EXPECT_EQ(c.GetRAM(), "8g");
    EXPECT_EQ(c.GetType(), DeviceType::PC);
}
