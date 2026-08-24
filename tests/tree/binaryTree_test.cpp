#include "../../tree/binaryTree.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#define CHECK(condition) do { if (!(condition)) return __LINE__; } while (0)

static bool trackAllocations = false;
static int failAllocation = -1;
static int allocationAttempts = 0;
static int successfulAllocations = 0;
static int trackedFrees = 0;

extern "C" void *__real_malloc(size_t size);
extern "C" void __real_free(void *memory);
extern "C" void *__wrap_malloc(size_t size);
extern "C" void __wrap_free(void *memory);

extern "C" void *__wrap_malloc(size_t size) {
    if (!trackAllocations) {
        return __real_malloc(size);
    }

    const int attempt = allocationAttempts++;
    if (attempt == failAllocation) {
        return NULL;
    }

    void *memory = __real_malloc(size);
    if (memory != NULL) {
        ++successfulAllocations;
    }
    return memory;
}

extern "C" void __wrap_free(void *memory) {
    if (trackAllocations && memory != NULL) {
        ++trackedFrees;
    }
    __real_free(memory);
}

static void destroyForTest(linkedBiTree tree) {
    if (tree == NULL) {
        return;
    }
    destroyForTest(tree->lChild);
    destroyForTest(tree->rChild);
    std::free(tree);
}

typedef void (*TraversalFunction)(linkedBiTree);

static int captureTraversal(TraversalFunction traversal, linkedBiTree tree,
                            char output[], size_t capacity) {
    if (capacity == 0) {
        return 0;
    }
    FILE *temporaryOutput = std::tmpfile();
    if (temporaryOutput == NULL) {
        return 0;
    }
    std::fflush(stdout);
    const int savedOutput = dup(STDOUT_FILENO);
    if (savedOutput < 0 || dup2(fileno(temporaryOutput), STDOUT_FILENO) < 0) {
        if (savedOutput >= 0) {
            close(savedOutput);
        }
        std::fclose(temporaryOutput);
        return 0;
    }

    traversal(tree);
    std::fflush(stdout);
    std::rewind(temporaryOutput);
    const size_t bytes = std::fread(output, 1, capacity - 1, temporaryOutput);
    output[bytes] = '\0';

    const int restoreResult = dup2(savedOutput, STDOUT_FILENO);
    close(savedOutput);
    std::fclose(temporaryOutput);
    return restoreResult >= 0;
}

static int createWithInput(const char *input, linkedBiTree *tree, int failAt) {
    FILE *temporaryInput = std::tmpfile();
    if (temporaryInput == NULL) {
        return -100;
    }
    const size_t inputLength = std::strlen(input);
    if (std::fwrite(input, 1, inputLength, temporaryInput) != inputLength) {
        std::fclose(temporaryInput);
        return -101;
    }
    std::rewind(temporaryInput);

    const int savedInput = dup(STDIN_FILENO);
    if (savedInput < 0 || dup2(fileno(temporaryInput), STDIN_FILENO) < 0) {
        if (savedInput >= 0) {
            close(savedInput);
        }
        std::fclose(temporaryInput);
        return -102;
    }
    clearerr(stdin);

    failAllocation = failAt;
    allocationAttempts = 0;
    successfulAllocations = 0;
    trackedFrees = 0;
    trackAllocations = true;
    const int result = createBiTree(tree);
    trackAllocations = false;

    const int restoreResult = dup2(savedInput, STDIN_FILENO);
    close(savedInput);
    std::fclose(temporaryInput);
    clearerr(stdin);
    return restoreResult < 0 ? -103 : result;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 64;
    }
    setvbuf(stdin, NULL, _IONBF, 0);

    const int scenario = std::atoi(argv[1]);
    if (scenario == 0) {
        biTreeReverse2(NULL);
        return 0;
    }
    if (scenario == 1) {
        postOrderTraverse2(NULL);
        return 0;
    }
    if (scenario == 2) {
        CHECK(createWithInput("#", NULL, -1) == 0);
        return 0;
    }
    if (scenario == 3) {
        linkedBiTree tree = reinterpret_cast<linkedBiTree>(1);
        CHECK(createWithInput("", &tree, -1) == 0);
        CHECK(tree == NULL);
        return 0;
    }
    if (scenario == 4) {
        linkedBiTree tree = reinterpret_cast<linkedBiTree>(1);
        CHECK(createWithInput("#", &tree, -1) == 1);
        CHECK(tree == NULL);
        return 0;
    }
    if (scenario == 5) {
        linkedBiTree tree = NULL;
        CHECK(createWithInput("AB##C##", &tree, -1) == 1);
        CHECK(tree != NULL && tree->data == 'A');
        CHECK(tree->lChild != NULL && tree->lChild->data == 'B');
        CHECK(tree->rChild != NULL && tree->rChild->data == 'C');
        CHECK(successfulAllocations == 3);
        CHECK(trackedFrees == 0);
        destroyForTest(tree);
        return 0;
    }
    if (scenario == 6) {
        linkedBiTree tree = reinterpret_cast<linkedBiTree>(1);
        CHECK(createWithInput("A##", &tree, 0) == 0);
        CHECK(tree == NULL);
        CHECK(successfulAllocations == 0);
        CHECK(trackedFrees == 0);
        return 0;
    }
    if (scenario == 7) {
        linkedBiTree tree = reinterpret_cast<linkedBiTree>(1);
        CHECK(createWithInput("AB##C##", &tree, 1) == 0);
        CHECK(tree == NULL);
        CHECK(successfulAllocations == 1);
        CHECK(trackedFrees == 1);
        return 0;
    }
    if (scenario == 8) {
        linkedBiTree tree = reinterpret_cast<linkedBiTree>(1);
        CHECK(createWithInput("AB##C##", &tree, 2) == 0);
        CHECK(tree == NULL);
        CHECK(successfulAllocations == 2);
        CHECK(trackedFrees == 2);
        return 0;
    }
    if (scenario == 9) {
        linkedBiTree tree = reinterpret_cast<linkedBiTree>(1);
        CHECK(createWithInput("A#", &tree, -1) == 0);
        CHECK(tree == NULL);
        CHECK(successfulAllocations == 1);
        CHECK(trackedFrees == 1);
        return 0;
    }
    if (scenario == 10) {
        biTNode fourth = {'D', NULL, NULL};
        biTNode second = {'B', &fourth, NULL};
        biTNode third = {'C', NULL, NULL};
        biTNode root = {'A', &second, &third};
        CHECK(biTreeDepth(&root) == 3);
        CHECK(biTreeLeaf(&root) == 2);
        biTreeReverse(&root);
        CHECK(root.lChild == &third && root.rChild == &second);
        CHECK(second.lChild == NULL && second.rChild == &fourth);
        biTreeReverse2(&root);
        CHECK(root.lChild == &second && root.rChild == &third);
        CHECK(second.lChild == &fourth && second.rChild == NULL);
        return 0;
    }
    if (scenario == 11) {
        biTNode fourth = {'D', NULL, NULL};
        biTNode second = {'B', &fourth, NULL};
        biTNode third = {'C', NULL, NULL};
        biTNode root = {'A', &second, &third};
        struct TraversalCase {
            TraversalFunction function;
            const char *expected;
        } cases[] = {
            {preOrderTraverse, "A\nB\nD\nC\n"},
            {preOrderTraverse2, "A\nB\nD\nC\n"},
            {inOrderTraverse, "D\nB\nA\nC\n"},
            {inOrderTraverse2, "D\nB\nA\nC\n"},
            {postOrderTraverse, "D\nB\nC\nA\n"},
            {postOrderTraverse2, "D\nB\nC\nA\n"},
            {levelOrderTraverse, "A\nB\nC\nD\n"}
        };
        for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
            char output[64];
            CHECK(captureTraversal(cases[i].function, &root,
                                   output, sizeof(output)) == 1);
            CHECK(std::strcmp(output, cases[i].expected) == 0);
        }
        return 0;
    }
    return 65;
}
