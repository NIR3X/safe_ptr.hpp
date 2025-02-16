# safe_ptr - A C++ utility for safe memory reading

A C++ utility for safely reading memory from a specified process using `ReadProcessMemory`. This module provides a `safe_ptr` class that allows for optional memory protection when accessing addresses.

## Features

- Safe memory reading using `ReadProcessMemory`.
- Supports optional memory protection via `VirtualProtectEx`.
- Works with different data types using `std::optional<T>`.
- Can be used for introspection and debugging purposes.

## Installation

Clone the repository and include `safe_ptr.hpp` in your project:

```bash
git clone https://github.com/NIR3X/safe_ptr.hpp
cd safe_ptr.hpp
```

Include the header file in your C++ project:
```cpp
#include "safe_ptr.hpp"
```

## Usage

### Basic Example

```cpp
#include "safe_ptr.hpp"
#include <iostream>

int main() {
	int someVariable = 42;
	safe_ptr intPtr(&someVariable);
	
	auto value = intPtr._<int>(0);
	if (value.has_value()) {
		std::cout << "Value: " << *value << std::endl;
	} else {
		std::cout << "Failed to read memory" << std::endl;
	}
}
```

### Test Code

A test file (`test.cpp`) is provided to verify the functionality:

```cpp
#include "safe_ptr.hpp"
#include <cassert>
#include <cstdio>

int main() {
	safe_ptr xFFFFPtr((PVOID)0xFFFF);
	assert(!xFFFFPtr._<uint8_t>(0).has_value());

	safe_ptr mainPtr(&main);
	assert(mainPtr._<uint8_t>(0).has_value());

	safe_ptr modulePtr(GetModuleHandleW(NULL));
	assert(modulePtr._<uint16_t>(0) == IMAGE_DOS_SIGNATURE);

	auto imageDosHeaderOpt = modulePtr._<IMAGE_DOS_HEADER>(0);
	assert(imageDosHeaderOpt.has_value());
	
	auto imageNtHeaderOpt = modulePtr._<IMAGE_NT_HEADERS>(imageDosHeaderOpt->e_lfanew);
	assert(imageNtHeaderOpt.has_value());
	assert(imageNtHeaderOpt->Signature == IMAGE_NT_SIGNATURE);

	puts("PASS");
}
```

## Requirements

- C++17 or later
- Windows platform (uses `windows.h` APIs)

## License

[![GNU AGPLv3 Image](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.html)

This program is Free Software: You can use, study share and improve it at your
will. Specifically you can redistribute and/or modify it under the terms of the
[GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html) as
published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
