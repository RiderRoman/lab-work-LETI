# Shunting yard fuzzing report

- Generated: 2026-10-17 19:29:05
- Platform: `win32` (executable suffix `.exe`)
- **MD5 of all C++ files: `f6c30c963ed92d49536c41664ad0d825`** (7 files)
- Executable: `main.exe`
- Executable MD5: `193c1240e5d8126d825fc86f7cf66094` (1659392 bytes)
- Compiled with: `"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\bin\HostX64\x64\cl.EXE" /nologo /std:c++14 /Zi C:\Users\Admin\Desktop\test17.10\main.cpp /Fe:C:\Users\Admin\Desktop\test17.10\main.exe /Fo:C:\Users\Admin\Desktop\test17.10\main.obj`
- Toolchain: cl.exe is not on PATH; using the Visual Studio environment
- Toolchain: Visual Studio environment: C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat amd64
- Toolchain:   VSCMD_VER=18.10.3
- Toolchain:   VSCMD_ARG_TGT_ARCH=x64
- Toolchain: flag translation: -std=c++11 -> /std:c++14 (MSVC has no C++11 mode; C++14 is the closest)
- Toolchain: flag translation: -g -> /Zi
- Reference: Python oracle implementing the same algorithm (tokens `+ - * / ^ sin cos ( ) 0-9`, space separated)
- Random seed: `20261012` (re-run with `--seed 20261012` to reproduce)
- Fuzz runs requested: 1000 (max nesting depth 3, parentheses: mixed)
- Every generated expression is well-formed: the generator parses its own output back with the reference grammar and refuses to continue when the parentheses do not match the tree
- Per-run timeout: 5s
- Duration: 6.80s

## Verdict

**PASS**

| Metric | Value |
| --- | --- |
| Total executions | 1013 |
| 10 default bound examples | 10 |
| Rejection (error handling) tests | 3 |
| Random fuzz runs | 1000 |
| - minimal parentheses | 462 |
| - fully parenthesised | 538 |
| Errors found | **0** |
| Fuzz-stage errors | 0 |
| Pass rate | 100.00% |

## C++ files hashed (MD5)

Aggregate MD5 of all C++ files: **`f6c30c963ed92d49536c41664ad0d825`**

| File | Size (bytes) | MD5 |
| --- | --- | --- |
| `DoublyLinkedList.cpp` | 1258 | `61b835b836d1099abfb517c6d406e76c` |
| `DoublyLinkedList.h` | 350 | `f250ef3513a1d704f8effdb32eb18564` |
| `DynamicArr.h` | 623 | `294b8402e22eb3fa770e890793a8fedc` |
| `DynamicArr.hpp` | 2523 | `e7baa70c3c4acb9c53203a368af7f145` |
| `Stack.h` | 331 | `f3928af5f5d7801e99e1d555c6463b5f` |
| `Stack.hpp` | 561 | `3afb1afb1ea35021ba3f8e9196ee06a1` |
| `main.cpp` | 4720 | `4f254a1e9cc612c7eb4f43fab0492c2f` |

| Artifact | Size (bytes) | MD5 |
| --- | --- | --- |
| `main.exe` (executable) | 1659392 | `193c1240e5d8126d825fc86f7cf66094` |

## Default bound test examples

| # | Input | Expected RPN | Target | Result |
| --- | --- | --- | --- | --- |
| 1 | `5` | `5` | `5` | PASS |
| 2 | `0 + 0` | `0 0 +` | `0 0 +` | PASS |
| 3 | `123 + 456 * 789` | `123 456 789 * +` | `123 456 789 * +` | PASS |
| 4 | `1 + 3 - 4` | `1 3 + 4 -` | `1 3 + 4 -` | PASS |
| 5 | `2 ^ 3 ^ 2` | `2 3 2 ^ ^` | `2 3 2 ^ ^` | PASS |
| 6 | `1 + 2 * 3 ^ 4 - 5 / 6` | `1 2 3 4 ^ * + 5 6 / -` | `1 2 3 4 ^ * + 5 6 / -` | PASS |
| 7 | `( 1 + 2 ) * 3` | `1 2 + 3 *` | `1 2 + 3 *` | PASS |
| 8 | `( ( 1 + 2 ) * ( 3 - 4 ) ) ^ 2` | `1 2 + 3 4 - * 2 ^` | `1 2 + 3 4 - * 2 ^` | PASS |
| 9 | `sin ( 0 ) + cos ( 9 )` | `0 sin 9 cos +` | `0 sin 9 cos +` | PASS |
| 10 | `2 + sin ( 5 + 3 ) * 8 + ( 9 * 7 )` | `2 5 3 + sin 8 * + 9 7 * +` | `2 5 3 + sin 8 * + 9 7 * +` | PASS |

## Error handling tests

| Input | Expected | Result |
| --- | --- | --- |
| `( 1 + 2` | reject: mismatched parentheses | PASS (exit non-zero) |
| `1 + 2 )` | reject: mismatched parentheses | PASS (exit non-zero) |
| `1 # 2` | reject: unknown token: # | PASS (exit non-zero) |

## Error breakdown

No errors: every execution matched the reference implementation.

## Notes

- The MD5 hashes cover every C++ file of the project: the listed sources, all `.cpp`/`.hpp`/`.h` files next to them, and any `--hash-file`.
  The aggregate hash is computed from the sorted `<path>:<md5>` lines, so it changes whenever any file changes, is added, removed or renamed,
  and it does not depend on the order the files were listed in or on the absolute path of the project.
- The executable MD5 identifies the exact binary that was tested, but it may differ between builds of identical sources because some
  linkers (e.g. Mach-O on macOS) embed a random UUID. The aggregate C++ MD5 is the stable identity of the sources.
- The oracle mirrors `main.cpp`: precedence `+ -` < `* /` < `^` < `sin cos`, `^` right-associative, everything else left-associative,
  parentheses group subexpressions, a function directly before `(` is emitted after the group.
- Every fuzz input is a *correct* arithmetic expression over the required operations `+ - * / ^ sin cos ( )` and `0-9`:
  the generator builds an expression tree, renders it, parses the text back with the reference grammar and re-renders it in minimal
  form. Text and tree have to agree, otherwise the generator aborts instead of feeding a wrong corpus to the target.
- Parentheses are emitted only where precedence and associativity require them (`--parens min`), around every subexpression
  (`--parens full`), or either one per expression (`--parens mixed`, the default). Both styles are checked against the same oracle.
- Malformed input is *not* generated: the only rejection cases are the fixed `## Error handling tests` above, which still verify that the
  target reports unknown tokens and mismatched parentheses on stderr and exits non-zero.
- A passing run means the compiled target agrees with the reference on every bound and fuzz case, with no crash, timeout or stray stderr output.
