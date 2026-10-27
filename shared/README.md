# Shared Course Support

The projects were originally stages of one SANS application, the Scholastic Applied Network Sandbox. These common files are stored once rather than copied into every project.

## Contents

- `include/sans.h`: the application and transport function declarations, including `IPPROTO_RUDP`.
- `include/rudp.h`: the packet flags and packet structure from the original Project 5 setup file.
- `src/sans.c`: the original HTTP, SMTP, and proxy command-line driver.
- `testing/testing.h`, `testing/wrappers.c`, and `testing/testutils.c`: the matching course test framework from `shimate-main`.
- `testing/complete.h`: the saved course project-selection header, originally set to Project 1.
- `lib/templates.a`: the supplied compiled helper library used by the earlier stages.
- `legacy-build/SConstruct` and `legacy-build/.conscript`: the original SCons scripts, kept as historical build references.
- [helper-library.md](helper-library.md) and [rudp-handshake.md](rudp-handshake.md): short reference notes based on the uploaded course wiki.
- [LICENSE](LICENSE): the license supplied with the original framework.

## Building and Testing

The saved build scripts expect a single `src/` directory, a `.setup` directory, and project selection through `scons checkout project=N`. They are retained for reference and do not build this reorganized layout directly. The commands in the original assignment pages describe that earlier environment.

The source uses POSIX sockets, GNU linker wrapping, Linux test utilities, and, in Project 7, pthreads. A Linux environment or WSL is appropriate. The supplied `templates.a` contains a compiled x86-64 object and may not work on other platforms.

To restore the original environment, stage the selected project files alongside this driver's `src/sans.c`, put shared declarations under `src/include`, and place the matching test files and framework under `src/testing`. Earlier application source and tests are cumulative. In particular, the Project 2 and Project 3 tests use globals from Project 1, and `s__testdir` is defined in the Project 2 tests. The original setup templates and later driver updates are not all available, so this is not a complete reproduction recipe.

Do not compile every `sans_socket.c` or `sans_transport.c` together: each project represents a replacement for the previous stage. Project 1 alternatives also define the same entry point and must be selected individually.

## Organization Notes

Project 4 uses the TCP-only `Home/sans_socket_old1.c`. The `_5` and `_6` files belong to the handshake and Stop-and-Wait stages. The unnumbered socket and transport files, together with `sans_backend.c`, belong to Go-Back-N. Implementation and test source files were moved without changing their contents.

The broken `Course.wiki` Git reference was replaced by local requirements pages for Projects 1 through 7. The Project 8 page was absent from the uploaded wiki. Class schedules, meeting links, grading details, and the raw syllabus were left out of this code-focused layout.

Removed items include local editor settings, the exact `tempCodeRunnerFile.c` copy of the Project 1 tests, unused scratch notes, superseded test stubs for Projects 2 through 7, older wrapper/header copies, incomplete earlier SMTP code, the near-duplicate HTTP server setup copy, and empty setup implementations already replaced by project source. The removed files remain in Git history.

## Attribution

The requirements and protocol notes come from the Indiana University Computer Networks course wiki for Fall 2024. Tests, the driver, helper declarations, and build scaffolding were supplied with the course repository. They are distinguished from the project implementation files and retain the original license.
