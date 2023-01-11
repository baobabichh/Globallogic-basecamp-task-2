### File Indexer Application
Implement File indexer application. Language/libraries: C/C++, STL, usage of additional libraries
or 3rd party code is prohibited. For threading should be used platform-dependent API (unless
specified otherwise by mentor). For UI might be used winAPI, Qt etc. The application should be
written with using OOP.

### Application should:
- Index all files on all local disks – find all files and store their name/date/size/path to local
storage (XML file).
- Non-blocking UI – it should not freeze while indexing files.
- UI should show directory it currently index.
- GUI controls for start/pause/stop indexing, for searching file.
- Find file in index:
    1. By name
    2. By extension
    3. By date
    4. By size
- If file is not in index, search in file system.
- Compile for Linux and Windows.
- Documentation: requirements specification, software design documentation (application
modules description, UML diagrams).

### How to use
-   Make with QT, so you need QT creator to open.
-   Open .pro file.
-   Compile for your platform.

### Guide
-   Open program.
-   Use "select file path" button to select file where you want to index files.
-   Use "start indexing" to index files.
-   Stop or wait until all files indexed.
-   Check criterias you want to search.
-   Use "start search" to search for files.
-   Stop searcher.
