#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <memory>
// 组合模式（Composite Pattern） 是一种结构型设计模式，用于将对象组织成树形结构，以表示“部分-整体”的层次关系。客户端可以统一对待单个对象和组合对象，无需区分它们。适用场景
// 需要表示对象的部分-整体层次结构（如文件系统、公司组织架构、图形界面控件树）。
// 希望客户端忽略单个对象与组合对象之间的差异，用同一套接口操作它们。

class Component {
public:
    virtual std::string GetName() const = 0;
    virtual void AddChild(const std::shared_ptr<Component>& c) {
        throw std::logic_error("Cannot add child to a leaf");
    }
    virtual void RemoveChild(const std::shared_ptr<Component>& c) {
        throw std::logic_error("Cannot remove child from a leaf");
    }
    virtual std::string Display() const = 0;
    virtual ~Component() = default;
    Component(const std::string& name) : m_name(name) {}

protected:
    std::string m_name{};
};

class Directory : public Component {
public:
    Directory(const std::string& name) : Component(name) {}
    std::string GetName() const override
    {
        return m_name;
    }

    std::string Display() const override
    {
        if (components.empty())
            return m_name + "[]";
        std::string ret = m_name + "[ ";
        for (const auto& c : components) {
            ret += c->Display() + " ";
        }
        ret += " ]";
        return ret;
    }

    void AddChild(const std::shared_ptr<Component>& c) override
    {
        components.push_back(c);
    }

    void RemoveChild(const std::shared_ptr<Component>& c) override
    {
        components.erase(std::remove(components.begin(), components.end(), c), components.end());
    }

private:
    std::vector<std::shared_ptr<Component>> components{};
};

class MyFile : public Component {
public:
    MyFile(const std::string& name):Component(name){}
    std::string Display() const override
    {
        return m_name;
    }
    std::string GetName() const override
    {
        return  m_name;
    }
};

TEST(DesignPatterns, Composite)
{
    auto school = std::make_shared<Directory>("school");
    auto class1 = std::make_shared<Directory>("class1");
    auto class2 = std::make_shared<Directory>("class2");
    auto student1 = std::make_shared<MyFile>("student1");
    auto student2 = std::make_shared<MyFile>("student2");
    auto student3 = std::make_shared<MyFile>("student3");
    auto student4 = std::make_shared<MyFile>("student4");
    school->AddChild(class1);
    school->AddChild(class2);
    class1->AddChild(student1);
    class1->AddChild(student2);
    class2->AddChild(student3);
    class2->AddChild(student4);
    EXPECT_EQ(school->Display(), "school[ class1[ student1 student2  ] class2[ student3 student4  ]  ]");


}