# Miscellaneous

This folder keeps the course reference material and extra framework files together for a later review of duplicates and supporting code. The original directories and filenames are retained within it.

## Contents

- [Course.wiki](Course.wiki/): the full unzipped course wiki, including the syllabus, setup instructions, assignment pages, helper-library notes, and handshake reference.
- [Course.wiki.zip](Course.wiki.zip): the original uploaded wiki archive.
- [shimate-main](shimate-main/): the original course framework with its SCons build scripts, setup files, driver, interface declarations, helper library, test utilities, and editor settings.

## Relation to the Projects

The seven numbered implementations and their tests are grouped under [projects](../projects/). Each project also has an assignment description beside the code. The Project 1 tests and RUDP packet header are copied from the framework into the relevant project folders, while their original copies remain here.

The original framework's SCons commands refer to its `src/` and `.setup/` layout. Its files are kept together so that the build context and supporting code can be reviewed alongside the numbered assignments. The course framework retains its [original license](shimate-main/LICENSE).
