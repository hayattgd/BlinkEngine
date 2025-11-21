You can break these rules if things have to be so.
Also, feel free to make new issues and PRs :)

# Commit names
Prefer using commit prefix like `feat:` and `fix:` though it's not necessary.

# Naming
Abbreviations are ok as long as they are well-known, just don't make it UPPERCASE.

e.g.
 - ❌️`int GetCurrentFPS();`
 - ✅️`int GetCurrentFps();`

## UPPERCASE
- Constants
## PascalCase
- Namespace
- Class
- Struct
- Enum
- Enum item
- Function
## camelCase
- Public class data
## snake_case
- Private class data
- Struct data
- File and directory

use `.cc` for C++, `.h` for header.

# Namespace

It's basically path to source,
 - `src/render/mesh.h` -> BlinkEngine::Render
 - `src/foo/bar/code.cc` -> BlinkEngine::Foo::Bar
