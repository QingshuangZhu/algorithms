#include "../../tree/balanceBinarySortTree.h"

#include <cstdlib>

#define CHECK(condition) do { if (!(condition)) return __LINE__; } while (0)

int main(int argc, char **argv) {
    if (argc != 2) {
        return 64;
    }

    const int scenario = std::atoi(argv[1]);
    if (scenario == 0) {
        rRotate(NULL);
        lRotate(NULL);
        return 0;
    }
    if (scenario == 1) {
        bBSTNodeTree root = NULL;
        rRotate(&root);
        lRotate(&root);
        CHECK(root == NULL);
        return 0;
    }
    if (scenario == 2) {
        bBSTNode node = {10, 0, NULL, NULL};
        bBSTNodeTree root = &node;
        rRotate(&root);
        CHECK(root == &node);
        lRotate(&root);
        CHECK(root == &node);
        return 0;
    }
    if (scenario == 3) {
        bBSTNode rootNode = {30, 2, NULL, NULL};
        bBSTNode leftNode = {20, 1, NULL, NULL};
        bBSTNode middleNode = {25, 0, NULL, NULL};
        rootNode.lChild = &leftNode;
        leftNode.rChild = &middleNode;
        bBSTNodeTree root = &rootNode;

        rRotate(&root);
        CHECK(root == &leftNode);
        CHECK(leftNode.rChild == &rootNode);
        CHECK(rootNode.lChild == &middleNode);
        CHECK(rootNode.bf == 2);
        CHECK(leftNode.bf == 1);
        CHECK(middleNode.bf == 0);
        return 0;
    }
    if (scenario == 4) {
        bBSTNode rootNode = {10, -2, NULL, NULL};
        bBSTNode rightNode = {20, -1, NULL, NULL};
        bBSTNode middleNode = {15, 0, NULL, NULL};
        rootNode.rChild = &rightNode;
        rightNode.lChild = &middleNode;
        bBSTNodeTree root = &rootNode;

        lRotate(&root);
        CHECK(root == &rightNode);
        CHECK(rightNode.lChild == &rootNode);
        CHECK(rootNode.rChild == &middleNode);
        CHECK(rootNode.bf == -2);
        CHECK(rightNode.bf == -1);
        CHECK(middleNode.bf == 0);
        return 0;
    }
    return 65;
}
