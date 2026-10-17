# 🎵 MP3 Tag Reader & Editor

A command-line based project developed in **C** to read, view, and edit ID3v2.3 metadata tags in MP3 files.

## 📌 Project Overview

MP3 files contain more than just audio data. They can also store metadata such as the song title, artist, album, release year, genre, and comments.

This project allows users to view and modify these metadata tags through a simple command-line interface.

## Introduction

MP3 is a widely used digital audio format for storing and playing music. Along with audio data, an MP3 file can contain metadata that provides information about the song, such as its title, artist, album, release year, genre, and comments.

The **MP3 Tag Reader & Editor** is a C programming project designed to read and modify this metadata. It helps users view the information stored in an MP3 file and edit supported tags through command-line options.

## What Are MP3 Tags?

MP3 tags are metadata fields embedded in an MP3 file. They help music players and media libraries display useful information about an audio track.

Common MP3 tags include:

- **Title:** Name of the song.
- **Artist:** Name of the singer or artist.
- **Album:** Album containing the song.
- **Year:** Release year.
- **Genre:** Category or style of music.
- **Comment:** Additional information about the track.

## How Does the Project Work?

The project uses C file handling and binary file operations to access MP3 metadata. Based on the selected command-line option, the program identifies the requested operation and processes the corresponding tag.

In view mode, the program reads and displays the available tag information. In edit mode, it updates the selected metadata field according to the user's input.

## Project Objectives

- Understand file handling and binary file operations in C.
- Learn how metadata is stored in MP3 files.
- Practice pointers, structures, strings, and command-line arguments.
- Implement tag viewing and editing operations.
- Improve understanding of data reading, modification, and file management.

## Applications

This project can be useful for organizing music collections, checking song information, and correcting metadata such as song titles, artist names, and album details.

It also provides practical experience with low-level file processing and demonstrates how C can be used to build command-line utilities that work with real-world file formats.

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

## Technical Concepts Used

- **ID3 Metadata:** Stores descriptive information associated with MP3 audio files.
- **File Handling:** Opens, reads, modifies, and closes files using C file operations.
- **Binary File Processing:** Works with file data at the byte level.
- **Structures:** Groups related metadata and file information.
- **Command-Line Arguments:** Allows users to choose view, edit, or help operations when running the program.

## Learning Outcomes

By developing this project, I gained practical experience in C programming, file handling, binary data processing, string manipulation, and command-line application development. It also helped me understand how metadata can be accessed and updated within a file format.
## 👨‍💻 Author

**Your Name**

- GitHub: https://github.com/Reddykeerthirangu
- LinkedIn: https://www.linkedin.com/in/reddy-keerthi-rangu-997360373/

---

