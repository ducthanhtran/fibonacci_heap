#include "catch.hpp"

#include "fibonacci_heap.hpp"

TEST_CASE("Insert integer keys", "[insert]")
{
    FibonacciHeap<int32_t> fHeap;
    REQUIRE(fHeap.numNodes() == 0);
    REQUIRE(fHeap.min_node() == nullptr);
    const auto result = fHeap.min();
    REQUIRE(!result.has_value());

    fHeap.insert(5);
    fHeap.insert(3);
    fHeap.insert(55);
    fHeap.insert(2);

    const auto result2 = fHeap.min();
    REQUIRE(result2.has_value());
    REQUIRE(result2.value() == 2);
    REQUIRE(fHeap.numNodes() == 4);

    const auto minNode = fHeap.min_node();
    REQUIRE(minNode != nullptr);
    REQUIRE(minNode->key == 2);

    fHeap.insert(1);

    const auto result3 = fHeap.min();
    REQUIRE(result3.has_value());
    REQUIRE(result3.value() == 1);
    REQUIRE(fHeap.numNodes() == 5);

    auto minNode2 = fHeap.min_node();
    REQUIRE(minNode2 != nullptr);
    REQUIRE(minNode2->key == 1);
    minNode2 = nullptr;
    REQUIRE(minNode2 == nullptr);
}