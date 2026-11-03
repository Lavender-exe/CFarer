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

## Tracks

| Track | Directory | Notes |
|-------|-----------|-------|
| c23 | `exercises_c23/` | Core C (44 exercises, main track) |
| linux | `exercises_linux/` | Linux system programming |
| maldev | `exercises_maldev/` | Malware development - Windows only, authorized lab use (md01-md18, links `ws2_32` + `wininet`) |
| redteam | `exercises_redteam/` | Red team tooling - Windows only, authorized lab use (rt01-rt10, plus rt06a COM bridge; links `ws2_32`/`dbghelp`/`bcrypt`/COM libs) |
| winternals | `exercises_winternals/` | Windows internals |

The `maldev` and `winternals` tracks are Windows-only and require cross-compilation
(e.g. `x86_64-w64-mingw32-gcc`) or MSVC. CFarer links `ws2_32` and `wininet`
automatically for the maldev track.

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
|---|------|-------|------------|
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
| 11 | ex11_arrays | Arrays, sizeof | Intermediate |
| 12 | ex12_strings | char arrays / strings | Intermediate |
| 13 | ex13_string_functions | <string.h> | Intermediate |
| 14 | ex14_pointer_intro | Pointers: &, * (first contact) | Intermediate |
| 15 | ex15_pointers | Pointers + functions (swap) | Intermediate |
| 16 | ex16_out_params | Output parameters | Intermediate |
| 17 | ex17_pointer_array | Arrays decay to pointers | Intermediate |
| 18 | ex18_pointer_arithmetic | Pointer arithmetic | Intermediate |
| 19 | ex19_structs | struct + member access | Intermediate |
| 20 | ex20_typedef_struct | typedef + struct | Intermediate |
| 21 | ex21_struct_pointers | Pointers to structs (->) | Intermediate |
| 22 | ex22_dynamic_memory | malloc, free, NULL check | Intermediate |
| 23 | ex23_pointer_to_pointer | Pointers to pointers | Intermediate |
| 24 | ex24_callback_intro | Function pointers | Intermediate |
| 25 | ex25_map_inplace | Callbacks: transform in place | Advanced |
| 26 | ex26_function_pointers | Callbacks: map to a new heap array | Advanced |
| 27 | ex27_enums | enum, named constants | Intermediate |
| 28 | ex28_preprocessor | #define, macros | Intermediate |
| 29 | ex29_file_io | fopen/fprintf/fscanf | Advanced |
| 30 | ex30_c23_bool | C23 bool,true,false | Intermediate |
| 31 | ex31_c23_nullptr | C23 nullptr | Intermediate |
| 32 | ex32_c23_typeof | C23 typeof | Intermediate |
| 33 | ex33_c23_constexpr | C23 constexpr | Intermediate |
| 34 | ex34_c23_bitint | C23 _BitInt | Intermediate |
| 35 | ex35_linked_list | Linked list (capstone) | Advanced |
| 36 | ex36_sorting | qsort + comparators | Advanced |
| 37 | ex37_variadic | va_list variadic functions | Advanced |
| 38 | ex38_generic_selection | _Generic | Advanced |
| 39 | ex39_generic_math | tgmath | Advanced |
| 40 | ex40_secure_strings | Safe string handling | Advanced |
| 41 | ex41_integer_overflow | Overflow + limits | Advanced |
| 42 | ex42_error_handling | errno, return codes | Advanced |
| 43 | ex43_input_validation | Untrusted input | Advanced |
| 44 | ex44_secure_memory | Secure alloc/clearing | Advanced |

---

## Windows Internals Track (`exercises_winternals/`)

| # | File | Topic | Difficulty |
|---|------|-------|------------|
| 01 | wi01_process_list | Toolhelp process enumeration | Beginner |
| 02 | wi02_thread_list | Toolhelp thread enumeration | Beginner |
| 03 | wi03_virtual_memory | VirtualQuery, region states, RWX | Intermediate |
| 04 | wi04_registry | Registry read/write/enumerate | Intermediate |
| 05 | wi05_named_pipes | Named pipe IPC | Intermediate |
| 06 | wi06_token_privileges | Access tokens, SeDebugPrivilege | Advanced |
| 07 | wi07_object_handles | Handles, flags, DuplicateHandle | Intermediate |
| 08 | wi08_ntdll_syscall | ntdll Nt* direct calls | Advanced |
| 09 | wi09_memory_mapped_files | CreateFileMapping / MapViewOfFile | Intermediate |
| 10 | wi10_shared_memory | Pagefile-backed shared memory IPC | Intermediate |
| 11 | wi11_seh | Structured Exception Handling | Intermediate |
| 12 | wi12_heap_api | Private heaps, HeapWalk | Intermediate |
| 13 | wi13_srw_locks | SRW locks + condition variables | Intermediate |
| 14 | wi14_job_objects | Job objects, process limits | Advanced |
| 15 | wi15_tls | Thread Local Storage | Intermediate |
| 16 | wi16_iocp | I/O Completion Ports | Advanced |
| 17 | wi17_fibers | Fiber scheduler | Advanced |
| 18 | wi18_veh | Vectored Exception Handling | Advanced |
| 19 | wi19_device_io | DeviceIoControl, IOCTL codes | Advanced |

Notes: wi11 SEH compiles with MinGW GCC (excpt.h `__try1`/`__except1` emulation)
and MSVC/Clang (`__try`/`__except`); only safe_divide is SEH-guarded on MinGW
(one guarded scope per translation unit). wi19 needs no elevation for the C:
volume query used by the starter gate.

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
