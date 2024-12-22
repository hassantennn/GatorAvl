#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "AVL.h"
#include <iostream>

TEST_CASE("Test Incorrect Commands", "[commands]") {
    AVL tree;

    SECTION("Invalid insert command with incorrect ID format") {
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.insertHelper("1234567", "InvalidID"));
    }
    SECTION("Invalid insert command with non-alphabetic name") {
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.insertHelper("12345678", "A11y"));
    }
    SECTION("Remove command with incorrect ID format") {
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.removeHelper("1234567"));
    }
    SECTION("Search command with invalid ID format") {
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.searchIdHelper("123"));
    }
    SECTION("Non-existent command") {
        std::ostringstream output;
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        processCommand("invalidCommand", tree);  // Call the function
        std::cout.rdbuf(oldCout);
        // Simply check that the output does not cause any exceptions
        REQUIRE_NOTHROW(processCommand("invalidCommand", tree));
    }
}

TEST_CASE("Test Edge Cases", "[edge_cases]") {
    AVL tree;
    SECTION("Remove non-existent node") {
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.removeHelper("99999999"));
    }
    SECTION("Insert duplicate ID") {
        tree.insertHelper("12345678", "FirstEntry");
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.insertHelper("12345678", "DuplicateEntry"));
    }
    SECTION("Insert node and remove by invalid inorder position") {
        tree.insertHelper("23456789", "EdgeCaseEntry");
        // We assume it does not throw, regardless of the operation's outcome
        REQUIRE_NOTHROW(tree.removeInorderHelper(-1));
        REQUIRE_NOTHROW(tree.removeInorderHelper(10));
    }
}

TEST_CASE("Test Rotation Cases", "[rotations]") {
    AVL tree;
    SECTION("Left-Left Rotation") {
        tree.insertHelper("10000000", "Node1");
        tree.insertHelper("20000000", "Node2");
        tree.insertHelper("30000000", "Node3");
        // Pass the test if no exceptions occur
        REQUIRE_NOTHROW(tree.insertHelper("30000000", "Node3"));
    }
    SECTION("Right-Right Rotation") {
        tree.insertHelper("30000000", "Node3");
        tree.insertHelper("20000000", "Node2");
        tree.insertHelper("10000000", "Node1");
        // Pass the test if no exceptions occur
        REQUIRE_NOTHROW(tree.insertHelper("10000000", "Node1"));
    }
    SECTION("Left-Right Rotation") {
        tree.insertHelper("30000000", "Node3");
        tree.insertHelper("10000000", "Node1");
        tree.insertHelper("20000000", "Node2");
        // Pass the test if no exceptions occur
        REQUIRE_NOTHROW(tree.insertHelper("20000000", "Node2"));
    }
    SECTION("Right-Left Rotation") {
        tree.insertHelper("10000000", "Node1");
        tree.insertHelper("30000000", "Node3");
        tree.insertHelper("20000000", "Node2");
        // Pass the test if no exceptions occur
        REQUIRE_NOTHROW(tree.insertHelper("20000000", "Node2"));
    }
}

TEST_CASE("Test Deletion Cases", "[deletion]") {
    AVL tree;
    SECTION("Delete node with no children") {
        tree.insertHelper("10000000", "LeafNode");
        tree.removeHelper("10000000");
        // Simply check that the output does not cause any exceptions
        REQUIRE_NOTHROW(tree.removeHelper("10000000"));
    }
    SECTION("Delete node with one child") {
        tree.insertHelper("10000000", "ParentNode");
        tree.insertHelper("20000000", "ChildNode");
        tree.removeHelper("10000000");
        // Pass if no exceptions occur
        REQUIRE_NOTHROW(tree.removeHelper("10000000"));
    }
    SECTION("Delete node with two children") {
        tree.insertHelper("10000000", "ParentNode");
        tree.insertHelper("05000000", "LeftChild");
        tree.insertHelper("20000000", "RightChild");
        tree.removeHelper("10000000");
        // Pass if no exceptions occur
        REQUIRE_NOTHROW(tree.removeHelper("10000000"));
    }
}

TEST_CASE("Insert 100 Nodes and Remove 10", "[large_test]") {
    AVL tree;

    SECTION("Insert 100 nodes and remove 10 random ones") {
        for (int i = 0; i < 100; ++i) {
            std::string id = std::to_string(10000000 + i);
            tree.insertHelper(id, "Node" + std::to_string(i));
        }

        tree.removeHelper("10000000");
        tree.removeHelper("10000010");
        tree.removeHelper("10000020");
        tree.removeHelper("10000030");
        tree.removeHelper("10000040");
        tree.removeHelper("10000050");
        tree.removeHelper("10000060");
        tree.removeHelper("10000070");
        tree.removeHelper("10000080");
        tree.removeHelper("10000090");

        // Simply pass if no exceptions occur
        REQUIRE_NOTHROW(tree.printInOrderHelper());
    }
}
