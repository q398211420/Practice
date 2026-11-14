#include <gtest/gtest.h>
#include <atomic>
#include <memory>

// 原型模式（Prototype Pattern） 是一种创建型设计模式。它的核心思想是：通过复制（克隆）一个已有对象来创建新对象，而不是每次都从零开始 new。
// 什么时候用原型模式？

// 对象的创建成本很高（初始化复杂、需要大量数据、需要查询数据库/文件等）。
// 想要避免为每种配置都写一个子类,配置存在对象状态里，靠克隆复用,配置差异用「对象的数据」来表达，而不是用「新的类型」来表达
// 需要在运行时动态决定要创建哪种对象。
// 对象之间有大量相似的状态，只想修改少量差异。

// 典型场景：游戏中的怪物克隆、文档/图形编辑器中的对象复制、配置模板等。
class Monster {
public:
    Monster(const std::string& name) : m_name(name) {}
    virtual std::string attack() const = 0;
    virtual std::unique_ptr<Monster> Clone() const = 0;
    virtual ~Monster() = default;

protected:
    std::string m_name;
    static uint32_t GenerateId()
    {
        static std::atomic<uint32_t> id{1000};
        return ++id;
    }
};

class Goblin : public Monster {
public:
    Goblin(const std::string& name) : Monster(name), m_id(GenerateId()) {}
    Goblin(const std::string& name, int hp, int power, const std::string& weapon) : Monster(name), m_hp(hp), m_power(power), m_weapon(weapon), m_id(GenerateId())
    {
    }
    std::string attack() const override
    {
        std::string ret(m_name + " " + std::to_string(m_id) + " " + std::to_string(m_hp) + " " + std::to_string(m_power) + " " + m_weapon);
        return ret;
    }
    std::unique_ptr<Monster> Clone() const override
    {
        auto newGoblin = std::make_unique<Goblin>(*this);
        newGoblin->m_id = GenerateId();
        return newGoblin;
    }

private:
    uint32_t m_id;
    int m_hp{};
    int m_power{};
    std::string m_weapon{};
};

class Mage : public Monster {
public:
    Mage(const std::string& name) : Monster(name), m_id(GenerateId()) {}
    Mage(const std::string& name, int hp, int mana, const std::string& weapon) : Monster(name), m_hp(hp), m_mana(mana), m_weapon(weapon), m_id(GenerateId())
    {
    }
    std::string attack() const override
    {
        std::string ret(m_name + " " + std::to_string(m_id) + " " + std::to_string(m_hp) + " " + std::to_string(m_mana) + " " + m_weapon);
        return ret;
    }
    std::unique_ptr<Monster> Clone() const override
    {
        auto mage = std::make_unique<Mage>(*this);
        mage->m_id = GenerateId();
        return mage;
    }

private:
    uint32_t m_id;
    int m_hp{};
    int m_mana{};
    std::string m_weapon{};
};

class Registry {
public:
    static Registry& GetInstance()
    {
        static Registry instance;
        return instance;
    }
    std::unique_ptr<Monster> Create(const std::string& name)
    {
        if (!m_reg.contains(name))
            return nullptr;
        return m_reg[name]->Clone();
    }
    void Register(const std::string& name, std::unique_ptr<Monster> monster)
    {
        m_reg[name] = std::move(monster);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Monster>> m_reg{};
    Registry() = default;
};

TEST(DesignPatterns, Prototype)
{
    auto redGoblin = std::make_unique<Goblin>("redGoblin", 40, 40, "axe");
    auto whiteGoblin = std::make_unique<Goblin>("whiteGoblin", 20, 20, "gun");

    auto redMage = std::make_unique<Mage>("redMage", 100, 100, "book");
    auto whiteMage = std::make_unique<Mage>("whiteMage", 200, 200, "glass");

    Registry::GetInstance().Register("redGoblin", std::move(redGoblin));
    Registry::GetInstance().Register("whiteGoblin", std::move(whiteGoblin));
    Registry::GetInstance().Register("redMage", std::move(redMage));
    Registry::GetInstance().Register("whiteMage", std::move(whiteMage));

    auto m1 = Registry::GetInstance().Create("redGoblin");
    auto m2 = Registry::GetInstance().Create("whiteGoblin");
    auto m3 = Registry::GetInstance().Create("redMage");
    auto m4 = Registry::GetInstance().Create("whiteMage");

    auto a1 = m1->attack();
    auto a2 = m2->attack();
    auto a3 = m3->attack();
    auto a4 = m4->attack();

    EXPECT_EQ(a1, "redGoblin 1005 40 40 axe");
    EXPECT_EQ(a2, "whiteGoblin 1006 20 20 gun");
    EXPECT_EQ(a3, "redMage 1007 100 100 book");
    EXPECT_EQ(a4, "whiteMage 1008 200 200 glass");
}