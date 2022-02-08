#include "ziapi/Config.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <unordered_map>

using namespace ziapi::config;

TEST(Config, SimpleInt)
{
    Node node(10);

    ASSERT_EQ(node.AsInt(), 10);
}

TEST(Config, SimpleString)
{
    Node node("Hello world");

    ASSERT_EQ(node.AsString(), "Hello world");
}

TEST(Config, SimpleDouble)
{
    Node node(45.647f);

    ASSERT_EQ(node.AsDouble(), 45.647f);
}

TEST(Config, SimpleBool)
{
    Node node(true);

    ASSERT_EQ(node.AsBool(), true);
}

TEST(Config, SimpleArray)
{
    auto array = Node::MakeArray({10, "Hello world", 14.5f});

    ASSERT_EQ(array.AsArray()[0]->AsInt(), 10);
    ASSERT_EQ(array.AsArray()[1]->AsString(), "Hello world");
    ASSERT_EQ(array.AsArray()[2]->AsDouble(), 14.5f);
}

TEST(Config, SimpleDict)
{
    Node modules_count(10);
    auto dict = Node::MakeDict({{"modules_count", modules_count}});

    ASSERT_EQ(dict.AsDict()["modules_count"]->AsInt(), 10);
}

TEST(Config, NestedAccess)
{
    auto cfg = Node::MakeDict({
        {"modules", Node::MakeDict({{"directoryListing", Node::MakeDict({{"root", "/var/www"}})}})},
    });

    ASSERT_EQ(cfg["modules"]["directoryListing"]["root"].AsString(), "/var/www");
}

TEST(Config, OperatorBool)
{
    Node undefined(Undefined{});
    Node null(nullptr);
    Node string("Hello");

    ASSERT_EQ(undefined.operator bool(), false);
    ASSERT_EQ(null.operator bool(), false);
    ASSERT_EQ(string.operator bool(), true);
}
