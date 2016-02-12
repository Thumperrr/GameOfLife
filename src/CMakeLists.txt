add_subdirectory(config)
add_subdirectory(core)
add_subdirectory(log)
add_subdirectory(logic)
add_subdirectory(util)

set(SRCROOT "${PROJECT_SOURCE_DIR}/src")
set(SOURCES
${SRCROOT}/main.cpp
${SRCROOT}/AppStateGame.hpp
${SRCROOT}/AppStateGame.cpp
${SRCROOT}/Application.hpp
${SRCROOT}/Application.cpp
${SOURCES}
PARENT_SCOPE)
