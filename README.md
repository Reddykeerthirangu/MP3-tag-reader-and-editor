# 🎵 MP3 Tag Reader & Editor

A command-line based project developed in **C** to read, view, and edit ID3v2.3 metadata tags in MP3 files.

## 📌 Project Overview

MP3 files contain more than just audio data. They can also store metadata such as the song title, artist, album, release year, genre, and comments.

This project allows users to view and modify these metadata tags through a simple command-line interface.

## ✨ Features

- View MP3 metadata tags.
- Edit song title.
- Edit artist name.
- Edit album name.
- Edit release year.
- Edit genre.
- Edit comments.
- Display command usage and help information.
- Work with ID3v2.3 metadata.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Concepts:** Structures, pointers, file handling, string manipulation, command-line arguments
- **File Format:** MP3 with ID3v2.3 metadata

## 🚀 How to Run

### 1. View MP3 Tags

```bash
./a.out -v sample.mp3
```

Displays the metadata information stored in the specified MP3 file.

### 2. Edit MP3 Tags

**Edit Title**
```bash
./a.out -e -t sample.mp3
```

**Edit Artist**
```bash
./a.out -e -a sample.mp3
```

**Edit Album**
```bash
./a.out -e -A sample.mp3
```

**Edit Year**
```bash
./a.out -e -y sample.mp3
```

**Edit Genre**
```bash
./a.out -e -g sample.mp3
```

**Edit Comment**
```bash
./a.out -e -c sample.mp3
```

### 3. Help

```bash
./a.out -h
```

Displays the available commands and usage information.

> Replace `sample.mp3` with the path to your actual MP3 file. The edit commands above follow the command format shown in the project usage menu.

## 🏷️ ID3v2.3 Tags

| Frame ID | Description |
|---|---|
| `TIT2` | Song title |
| `TPE1` | Artist name |
| `TALB` | Album name |
| `TYER` | Release year |
| `TCON` | Genre |
| `COMM` | Comments |

## 🎯 What I Learned

- Reading and modifying binary file data.
- Understanding ID3v2.3 metadata structure.
- Working with file operations in C.
- Using structures, pointers, and command-line arguments.
- Organizing a C project into multiple source and header files.

## 👨‍💻 Author

**Your Name**

- GitHub: https://github.com/Reddykeerthirangu
- LinkedIn: https://www.linkedin.com/in/reddy-keerthi-rangu-997360373/

---

⭐ If you find this project useful, feel free to explore the code and share feedback.
