# EnvSync - .env Diff & Sync Tool

A powerful command-line tool for comparing and synchronizing `.env` files with **colorful output**, **interactive mode**, and **automatic backups**.

## ✨ Features

- **🔍 Smart Comparison**: Find missing, extra, and different keys between `.env` files
- **🎨 Colorful Output**: Beautiful terminal colors and emojis for better readability
- **🔄 Interactive Mode**: Step-by-step guidance with confirmation prompts
- **💾 Automatic Backups**: Timestamped backups before any file modifications
- **🛡️ Safe Operations**: Backup and restore functionality for peace of mind
- **📊 Detailed Reports**: Summary statistics and clear difference indicators

## 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/xentixar/envsync.git
cd envsync

# Build the project
make

# Install (optional)
sudo cp bin/envsync /usr/local/bin/
```

## 📖 Usage

### Basic Commands

```bash
# Compare two .env files
envsync compare file1.env file2.env

# Sync missing keys from file2 to file1
envsync sync file1.env file2.env

# Show help
envsync help
```

### Interactive Mode

```bash
# Interactive compare with step-by-step guidance
envsync compare-i file1.env file2.env

# Interactive sync with backup confirmation
envsync sync-i file1.env file2.env
```

### Backup Management

```bash
# Create a backup of a file
envsync backup file.env

# Restore a file from backup
envsync restore file.env
```

## 🎯 Examples

### Compare Files
```bash
$ envsync compare .env.local .env.example
[EnvCompare]: Comparing .env.local <-> .env.example

✗ Missing in .env.local: DATABASE_URL
✗ Missing in .env.local: REDIS_URL
⚠ Extra in .env.local: DEBUG_MODE

📊 Summary: 3 difference(s) found
```

### Interactive Sync
```bash
$ envsync sync-i .env.local .env.example
[Interactive Sync]: .env.local <- .env.example

Found 2 missing key(s) in .env.local:
  ✗ DATABASE_URL
  ✗ REDIS_URL

Would you like to sync these missing keys? (y/N): y
Create a backup before syncing? (y/N): y
✓ Backup created: .env.local.backup.20241201_143022
✓ Added DATABASE_URL to .env.local
✓ Added REDIS_URL to .env.local

🎉 Successfully synced 2 key(s)!

Would you like to compare the files now? (y/N): y
```

## 🧪 Testing

Run the test suite to verify functionality:

```bash
# Make test script executable
chmod +x tests/test_envs.sh

# Run tests
cd tests
./test_envs.sh
```

## 🏗️ Building from Source

### Prerequisites
- GCC compiler
- Make build system
- Linux/Unix environment

### Build Steps
```bash
make clean    # Clean previous builds
make          # Build the project
make install  # Install to system (optional)
```

## 📁 Project Structure

```
envsync/
├── include/          # Header files
│   ├── compare.h     # Comparison functions
│   ├── parser.h      # .env file parsing
│   ├── sync.h        # Synchronization functions
│   └── utils.h       # Utility functions (colors, backups)
├── src/              # Source code
│   ├── main.c        # Main program entry point
│   ├── compare.c     # Comparison implementation
│   ├── parser.c      # Parser implementation
│   ├── sync.c        # Sync implementation
│   └── utils.c       # Utility implementation
├── tests/            # Test files
├── bin/              # Compiled binary
├── build/            # Build artifacts
├── Makefile          # Build configuration
└── README.md         # This file
```

## 🎨 Color Scheme

- **🔵 Blue**: Information and help text
- **🟢 Green**: Success messages and confirmations
- **🟡 Yellow**: Warnings and prompts
- **🔴 Red**: Errors and missing items
- **🟣 Magenta**: Summary statistics
- **🟦 Cyan**: Section headers and commands
- **⚪ White**: Default text
- **🟤 Bold**: Emphasis and titles

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Built with modern C programming practices
- Terminal color support for better UX
- Comprehensive backup and restore functionality
- Interactive mode for safer operations
