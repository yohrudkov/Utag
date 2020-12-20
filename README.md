<h1 align="center"> Utag </h1> <br>

<p align="center">
    <a href="https://github.com/yohrudkov/Utag">
        <img alt="Utag"
        title="Utag"
        src="https://github.com/yohrudkov/Utag/blob/main/app/resources/logo.svg?raw=true"
        width="250">
    </a>
</p>

<p align="center"> Tag editor is always with you. Build with Cmake. </p>

<p align="center">
    <a href="https://github.com/yohrudkov">
        <img alt="yohrudkov GitHub main page"
        title="Main page"
        src="https://github.githubassets.com/images/modules/logos_page/GitHub-Logo.png"
        width="140">
    </a>
</p>

## Table of Contents

- [Introduction](#Introduction)
- [Features](#Features)
- [Build Process](#Build Process)
    - [Dependencies](#Dependencies)
    - [Preparation](#Preparation)
    - [Compilation](#Compilation)
    - [Initiation](#Initiation)
- [Authors](#Authors)
- [License](#License)
- [Acknowledgments](#Acknowledgments)

## Introduction

Desktop application for reading and editing metadata of several popular audio formats.\
Utag uses a graphical interface to make it easy to modify tags and is completely free to use.

## Features

A few of the things you can do with Utag:

* Supports several popular audio file formats
* Allows to edit more tags of audio files (year, track number, etc.)
* Supports the display and edit of the lyrics
* Opens the directory with the files through the GUI
* Edits an album image for an audio file and displays it via the GUI
* Allows browsing the opened directory and all subdirectories recursively
* Sort audio files in the directory
* Accept a directory as a command-line argument

## Build Process

### Dependencies

- [CMake](https://cmake.org) - *an open-source, cross-platform family of tools designed to build, test and package software.*
- [Qt](https://www.qt.io) - *a free and open-source widget toolkit for creating graphical user interfaces as well as cross-platform applications that run on various software and hardware platforms.*
- [TagLib](https://taglib.org) - *a library for reading and editing the meta-data of several popular audio formats.*

### Preparation

For find_package to be successful, CMake must find the Qt installation in one of the following ways:

- Set your CMAKE_PREFIX_PATH environment variable to the Qt 5 installation prefix:
    - uncomment and change CMAKE_PREFIX_PATH path in *`Utag/CMakeLists.txt`* file;
    - or just run *`export CMAKE_PREFIX_PATH=/path_to_qt_directory`* commend in shell.
- Set the Qt5_DIR in the CMake cache to the location of the Qt5Config.cmake file.

### Compilation

To build Utag project, run the following *`./build.sh`* script.

### Initiation

To begin to use Utag project, run the following *`./utag`* exe file.

## Authors

- Yaroslav Ohrudkov - *Application development* - [yohrudkov](https://github.com/yohrudkov)

## License

Collision is an open-sourced software licensed under the [MIT license](https://en.wikipedia.org/wiki/MIT_License).
012345678901234567890123456789

## Acknowledgments

Thanks [Ucode IT academy](https://ucode.world/ru/) for the training program provided.
