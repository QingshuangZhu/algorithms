# Repository Guidelines

## Project Purpose & Repository Map

This is a C/C++ study/interview repository. Favor correctness, clarity, and reasoning. Preserve meaningful recursive/iterative, sequential/linked, and strategy variants; never remove them merely to modernize. Do not replace the subject with `std::sort`, STL heap algorithms, or a ready-made target container. STL is allowed as a test oracle or documented auxiliary.

`sort/`, `heap/`, and `tree/` pair code with notes; `list/`, `queue/`, and `stack/` contain implementations and headers; `string/` has code and notes. `graph/` has notes and declarations but no implementation; `hashTable/` and `dynamicProgramming/` are notes-only. `README.md` is the entry point.

## Build & Local Verification

No unified build, test runner, CI, formatter, or coverage target exists. Run at root; write artifacts to `/tmp`:

- `g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror=return-type -c sort/quickSort.cpp -o /tmp/quickSort.o` compiles one translation unit.
- `g++ -std=c++11 -Wall -Wextra -Wpedantic -fsyntax-only sort/*.cpp` performs a quick topic check.
- `git diff --check HEAD` detects whitespace errors in tracked changes.

Compile/link only the implementation under test and its explicit dependencies. Do not aggregate all sources until collisions and missing definitions are resolved. Report baseline failures separately.

## Implementation & Interface Conventions

Use four spaces and same-line braces; use lower camel case for functions/types/files and uppercase snake case for macros/guards. Include the module header first and preserve `extern "C"`. Public declarations belong in self-contained headers and must be implemented/tested or marked interface-only. Prefix new public symbols and give helpers internal linkage. Legacy renames require a compatibility plan.

Document length/index ranges, empty inputs, buffer sizes, returns, and ownership. Validate inputs or state preconditions. Pair allocation/release, use a temporary pointer for `realloc`, and clean partial construction. Avoid broad rewrites and unrelated formatting.

## Testing & Learning Documentation

New deterministic tests belong in `tests/<topic>/<algorithm>_test.cpp`; variants sharing a contract run the same suite. As applicable, cover empty/singleton, duplicate, sorted/reversed, zero/negative/extreme, invalid-index, capacity, and ownership cases. Use AddressSanitizer and UndefinedBehaviorSanitizer for pointer-heavy code; STL may compute expected values in tests only. Bug fixes require regression tests.

Add or update topic Markdown with applicable invariants, variant differences, preconditions, stability/in-place behavior, and best/average/worst time and space complexity. Prefer relative links and label content implemented, interface-only, or notes-only.

## Commits & Pull Requests

History uses short action-first subjects such as `implement KMP algorithm` and `update tree.md`. Continue `<verb> <target>` without terminal punctuation. Pull requests must state the problem, approach, affected APIs, teaching trade-offs, verification results, and related issue when applicable.
