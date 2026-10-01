# Contributing to Pecha

Thank you for your interest in contributing to **Pecha**! Whether it's bug reports, feature requests, documentation improvements, or code contributions, all contributions are greatly appreciated.

Please follow these guidelines to help make the contribution process smooth and effective.

---

## Getting Started

To get a local copy up and running, follow these steps:

1. **Fork** the repository on GitHub.
2. **Clone** your fork locally:
   ```bash
   git clone https://github.com/your-username/pecha.git
   cd pecha
   ```
3. Create a Branch for your feature or bug fix:
   ```bash
   git checkout -b feature/your-feature-name
   ```
## How To Contribute
### Reporting Bugs

- Check existing issues to avoid duplicates.
- Open a new issue with a clear description, steps to reproduce, and your environment details.

### Suggesting Enhancements

- Open an issue describing the feature, why it is needed, and how it could be implemented.

### Pull Requests

- Ensure your code builds cleanly without errors or warnings.
- Keep pull requests focused on a single change, fix, or feature.

## Development Guidelines
### Code Style

 - **Avoid External Dependencies:** Try to minimize or avoid adding new third-party libraries or external dependencies. Rely on standard C libraries whenever possible.
 - **Variable Naming:** Use clear, meaningful names for all variables and functions using the `snake_case` format (e.g., `user_id`, `max_limit`, `calculate_total`).
 - **Macros:** Define all macros and constants in full capital letters (e.g., `#define MAX_BUFFER_SIZE 1024`, `#define DEBUG_MODE 1`).
 - **Formatting:** This project uses a `.clang-format` configuration to maintain consistent styling. Format your code before committing:
    ```bash
    clang-format -i src/*.c include/*.h
    ```
 - **Simplicity:** Write clean, minimal, and highly optimized C code.

### Building & Testing

  - Compile the project using the Makefile:
    ```bash
    make
    ```
  - Clean compiled binaries before a fresh build:
    ```bash
    make clean
    ```
    
### Commit Message Guidelines

Use clear, descriptive commit messages, preferably following conventional commits (e.g., feat:, fix:, docs:, refactor:):
```bash
git commit -m "feat: add memory tracking utility"
```
