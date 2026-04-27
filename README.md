# CFarer - Learn C (C23) through small exercises

Inspired by [rustlings](https://github.com/rust-lang/rustlings).

---

## Prerequisites

| Platform | Compiler |
|----------|----------|
| Linux / macOS | `gcc` or `clang` (any recent version) |
| Windows | [MSYS2/MinGW gcc](https://www.msys2.org/), [LLVM clang](https://releases.llvm.org/), or MSVC (`cl`) |

For full C23 support (exercises 23–27) use **GCC 13+** or **Clang 14+**.

CFarer auto-detects your compiler - no configuration needed.

---

## Quick Start

```bash
# Clone / download the repo, then:
python cfarer.py
```

CFarer starts in **watch mode**:
- Edit the current exercise file in `exercises/`
- Save - CFarer recompiles automatically
- Fix errors until it compiles and runs
- Remove `// I AM NOT DONE` from the file to advance to the next exercise

---

## Commands

### While in watch mode (type + Enter)

| Command | Action |
|---------|--------|
| `hint` | Show hints for the current exercise |
| `list` | List all exercises with progress |
| `next` | Skip to the next exercise |
| `goto N` | Jump to exercise number N |
| `quit` | Exit CFarer |

### Standalone

```bash
python cfarer.py watch    # start watch mode (default)
python cfarer.py list     # show exercise list
python cfarer.py hint     # print hint for current exercise
python cfarer.py run      # compile/run current exercise once
python cfarer.py goto 5   # jump to exercise 5
python cfarer.py reset    # instructions to restore original file
```

---

## Exercise List

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 01 | ex01_hello_world | printf | Beginner |
| 02 | ex02_variables | Data types | Beginner |
| 03 | ex03_printf_format | Format specifiers | Beginner |
| 04 | ex04_arithmetic | Operators | Beginner |
| 05 | ex05_if_else | Conditionals | Beginner |
| 06 | ex06_switch | switch/case | Beginner |
| 07 | ex07_while_loop | while loop | Beginner |
| 08 | ex08_for_loop | for loop | Beginner |
| 09 | ex09_functions | Functions | Beginner |
| 10 | ex10_recursion | Recursion | Intermediate |
| 11 | ex11_arrays | Arrays | Intermediate |
| 12 | ex12_strings | char arrays / strings | Intermediate |
| 13 | ex13_string_functions | `<string.h>` | Intermediate |
| 14 | ex14_pointers | Pointers (`&`, `*`) | Intermediate |
| 15 | ex15_pointer_arithmetic | Pointer arithmetic | Intermediate |
| 16 | ex16_structs | struct + member access | Intermediate |
| 17 | ex17_typedef_struct | typedef + struct | Intermediate |
| 18 | ex18_dynamic_memory | malloc / free | Intermediate |
| 19 | ex19_function_pointers | Function pointers | Advanced |
| 20 | ex20_enums | enum | Intermediate |
| 21 | ex21_preprocessor | #define macros | Intermediate |
| 22 | ex22_file_io | fopen / fprintf / fscanf | Advanced |
| 23 | ex23_c23_bool | **C23** `bool`/`true`/`false` | Intermediate |
| 24 | ex24_c23_nullptr | **C23** `nullptr` | Intermediate |
| 25 | ex25_c23_typeof | **C23** `typeof` | Advanced |
| 26 | ex26_c23_constexpr | **C23** `constexpr` | Advanced |
| 27 | ex27_c23_bitint | **C23** `_BitInt(N)` | Advanced |
| 28 | ex28_linked_list | Linked list | Advanced |
| 29 | ex29_sorting | `qsort` + comparators | Advanced |
| 30 | ex30_variadic | Variadic functions | Advanced |

---

## How exercises work

Each exercise file has:

1. A comment header explaining the concept and task
2. Broken or incomplete C code that you must fix
3. `assert()` calls that verify your solution is correct
4. `// I AM NOT DONE` at the bottom - remove it once you're satisfied

CFarer compiles with `-std=c2x -Wall -Wextra -Wpedantic`.
Runtime crashes (assertion failures, segfaults) are shown as failures.

---

## Resetting an exercise

```bash
git checkout exercises/ex05_if_else.c
```

---

## Adding your own exercises

Create `exercises/exNN_name.c` and optionally `exercises/exNN_name.hint`.
CFarer picks them up automatically by sorted filename order.
