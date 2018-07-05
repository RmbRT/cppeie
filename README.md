# EIE - Enum Interface Extension

C++ does not have any reflection for enums, which makes it harder to maintain code.

EIE provides an interface for keeping track of an `enum class`'s constant count and easy validity checks.
Please note that EIE only works as intended for enums that have continuous values, starting at `0`.
EIE works at compile time and is ultra lightweight, so no overhead is created when using EIE.
However, this also means that no string tables for string conversion are created, so the feature set is kept very simple.

## Cloning

```sh
git clone https://github.com/RmbRT/cppeie
```

## License

EIE is released under the GNU Affero Genereral Public License, version 3 or newer.
A copy of the license file can be found in `LICENSE`.

## Usage

In an `enum class`, simply wrap `EIE()` around the last value in the enum.
This will register the enum's size and enable more sophisticated enum access.

Example:

```cpp
enum class Hobbies
{
	Programming,
    EIE(Eating)
};
```

### Enum constant count

By calling `eie::count<Enum>()`, the number of `Enum`'s constants is retrieved.

```cpp
int table[eie::count<Hobbies>()];
```

### Enum value check

By calling `eie::valid()`, it can be determined whether an enum value is valid.

```cpp
Hobbies hobby = unreliable_value();
assert(eie::valid(hobby));
```
### Enum value loops

The `eie::Range<Enum>` type can be used to easily loop through all of an enum's values.

```cpp
for(Hobbies hobby: eie::Range<Hobbies>())
	sophisticated(hobby);
```