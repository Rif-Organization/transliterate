# transliterate

A C library for transliterating Latin-based text to Tifinagh script.

## Features

- Transliterates Latin characters to Tifinagh (Amazigh/Berber) script
- Supports spirants, labialized consonants, affricates, and emphatic consonants
- Handles multi-byte UTF-8 characters correctly
- Preserves unmapped characters as-is

## Building

To build the main application:

```bash
make all
```

## Running

To transliterate text:

```bash
./bin/main "your text here"
```

Example:
```bash
./bin/main "azul"
# Output: ⴰⵣⵓⵍ
```

## Testing

The project includes a comprehensive test suite with 56+ tests covering:
- Basic alphabet transliteration
- Multi-byte UTF-8 characters (spirants, emphatics, etc.)
- Labialized consonants
- Edge cases (NULL input, empty strings, etc.)
- Memory safety

To run the tests:

```bash
make test
```

To clean build artifacts:

```bash
make clean
```

## Continuous Integration

The project uses GitHub Actions for automated testing. Tests run automatically on:
- Push to main branches
- Pull requests
- Manual workflow dispatch

The CI pipeline includes:
- Building the project
- Running the full test suite
- Code quality checks with strict compiler warnings

## Character Mapping

The library supports the following character mappings:

### Base Alphabet
| Latin | Tifinagh |
|-------|----------|
| a     | ⴰ        |
| b     | ⴱ        |
| c     | ⵛ        |
| d     | ⴷ        |
| e     | ⴻ        |
| ... and more

### Special Characters
- **Spirants**: ṯ, ḏ, ḵ, ḇ, g̱
- **Labialized**: g°, k°
- **Affricates**: č, ğ, ɣ, ε
- **Emphatic**: ḍ, ṭ, ṣ, ẓ, ṛ, ḥ

## Development

### Project Structure
```
.
├── include/
│   └── transliterate.h          # Header file
├── src/
│   ├── transliterate.c          # Core transliteration logic
│   ├── main.c                   # CLI application
│   └── test_transliterate.c     # Test suite
├── makefile                     # Build configuration
└── .github/
    └── workflows/
        └── ci.yml               # CI/CD configuration
```

### Performance Optimizations

The implementation includes several optimizations:
- **Cached string lengths**: Source and destination string lengths are pre-calculated and stored in the mapping table, eliminating redundant `strlen()` calls in the transliteration loop
- **Efficient memory allocation**: Output buffer is allocated once with appropriate size
- **Early termination**: Loop breaks immediately when a match is found

## License

[Add your license here]

