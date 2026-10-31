# TODO

Findings from a project review (2026-10-31). The project builds cleanly with no warnings on macOS, and both examples run correctly; nothing below is broken, just worth tidying.

## CMakeLists.txt

- [ ] Replace `set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")` with per-target `target_compile_options(${program} PRIVATE -Wall -Wextra -pedantic)`. The current line overwrites any flags passed in from outside (`-DCMAKE_CXX_FLAGS=...`, `CXXFLAGS`). Use `/W4` on MSVC instead of no warnings.
- [ ] Remove `${CORELIBS}`; it's never defined and expands to nothing.
- [ ] Drop `find_package(Threads REQUIRED)` (no example uses threads yet). When needed, link `Threads::Threads` instead of `${CMAKE_THREAD_LIBS_INIT}`.
- [ ] Add `set(CMAKE_CXX_STANDARD_REQUIRED ON)` so CMake can't silently fall back to an older standard, and `set(CMAKE_CXX_EXTENSIONS OFF)` for `-std=c++17` rather than `-std=gnu++17`.
- [ ] Bump `cmake_minimum_required(VERSION 3.10)` to a range such as `3.16...3.30`. CMake 3.27+ warns about compatibility below 3.10, and CMake 4.x drops support below 3.5.

## CI (`.github/workflows/cmake.yml`)

- [ ] The Test step does nothing: no tests are registered, so `ctest` finds none. Either drop it, or add `enable_testing()` plus `add_test(NAME ${program} COMMAND ${program})` so CI checks that each example runs and exits with 0.
- [ ] CI only runs on `ubuntu-latest`, but the README says the examples were tested on macOS, Linux and Windows. Add a matrix of `[ubuntu-latest, macos-latest, windows-latest]` (this also exercises the MSVC branch).
- [ ] Bump `actions/checkout@v3` (Node 16, retired) to `@v4` or later.
- [ ] Optional: trim the template comments.

## Source

- [ ] `cond.cc`: `x` is hard-coded to `0`, so only the `zero` branch runs. Unless the book does it this way, read the value or loop over `{-1, 0, 1}` to show all three branches.
- [ ] `cond.cc`: `negative..` has two dots where the other messages have three.
- [ ] Pick one style for `return 0;` in `main`: `hello.cc` has it, `cond.cc` doesn't. Leaving it out is legal.
- [ ] Add a `.clang-format` so future examples stay consistent with the "Reformat code." commit.

## Repo hygiene

- [ ] Add a trailing newline to `README.md`.
- [ ] `.gitignore`: remove the Fortran, `.lai` and similar entries from GitHub's generic template; consider adding `compile_commands.json` and `.vscode/`.

## Suggested CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16...3.30)
project(ccc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

set(PROGRAMS hello cond)

foreach (program ${PROGRAMS})
    add_executable(${program} ${program}.cc)
    if (MSVC)
        target_compile_options(${program} PRIVATE /W4)
    else ()
        target_compile_options(${program} PRIVATE -Wall -Wextra -pedantic)
    endif ()
    add_test(NAME ${program} COMMAND ${program})
endforeach ()
```
