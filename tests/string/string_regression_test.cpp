#include "../../string/patternMatching.h"

#include <cassert>
#include <cstddef>
#include <string>

extern "C" void *__real_malloc(std::size_t size);
extern "C" void *__wrap_malloc(std::size_t size);

static bool failNextMalloc = false;

extern "C" void *__wrap_malloc(std::size_t size) {
    if (failNextMalloc) {
        failNextMalloc = false;
        return NULL;
    }
    return __real_malloc(size);
}

typedef int (*MatchFunction)(const char *, int, const char *, int);

static void verifyCommonContract(MatchFunction match) {
    assert(match("", 0, "abc", 3) == 0);
    assert(match(NULL, 0, NULL, 0) == 0);
    assert(match("ab", 2, "zabz", 4) == 1);
    assert(match("aa", 2, "baaa", 4) == 1);
    assert(match("abcd", 4, "abc", 3) == -1);
    assert(match("x", 1, "abc", 3) == -1);
    assert(match("a", -1, "abc", 3) == -1);
    assert(match("a", 1, NULL, 1) == -1);
    assert(match("", 0, NULL, 1) == -1);
    assert(match(NULL, 0, NULL, 1) == -1);
}

static void testAllMatchersUseTheSameFirstMatchContract() {
    verifyCommonContract(bruteForce1);
    verifyCommonContract(bruteForce2);
    verifyCommonContract(KMP);
}

static void testKmpHandlesPrefixTableAllocationFailure() {
    failNextMalloc = true;
    assert(KMP("ab", 2, "zabz", 4) == -1);
}

static void appendBinaryStrings(std::string prefix, int remaining,
                                std::string output[], int *count) {
    if(0 == remaining){
        output[(*count)++] = prefix;
        return;
    }
    appendBinaryStrings(prefix + 'a', remaining - 1, output, count);
    appendBinaryStrings(prefix + 'b', remaining - 1, output, count);
}

static void testAllMatchersAgainstStandardOracle() {
    std::string texts[127];
    std::string patterns[31];
    int textCount = 0;
    int patternCount = 0;
    for(int length = 0; length <= 6; length++){
        appendBinaryStrings("", length, texts, &textCount);
    }
    for(int length = 0; length <= 4; length++){
        appendBinaryStrings("", length, patterns, &patternCount);
    }

    MatchFunction matchers[] = {bruteForce1, bruteForce2, KMP};
    for(int matcher = 0; matcher < 3; matcher++){
        for(int textIndex = 0; textIndex < textCount; textIndex++){
            for(int patternIndex = 0; patternIndex < patternCount; patternIndex++){
                std::size_t found = texts[textIndex].find(patterns[patternIndex]);
                int expected = found == std::string::npos ? -1 : (int)found;
                int actual = matchers[matcher](
                    patterns[patternIndex].data(), (int)patterns[patternIndex].size(),
                    texts[textIndex].data(), (int)texts[textIndex].size());
                assert(actual == expected);
            }
        }
    }
}

int main() {
    testAllMatchersUseTheSameFirstMatchContract();
    testKmpHandlesPrefixTableAllocationFailure();
    testAllMatchersAgainstStandardOracle();
    return 0;
}
