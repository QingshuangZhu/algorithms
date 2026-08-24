#include "../../tree/binaryTree.h"
#include "../../tree/balanceBinarySortTree.h"

#include <cstddef>

int main() {
    biTNode binaryNode = {'A', NULL, NULL};
    bBSTNode balancedNode = {1, 0, NULL, NULL};
    return binaryNode.data == 'A' && balancedNode.data == 1 ? 0 : 1;
}
