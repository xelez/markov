#
# This is root build script for Markov generator
#

cmake_minimum_required (VERSION 2.6)
project (MARKOV)

set (MARKOV_VERSION "1.0")
option(USE_PROFILING "Compile in profiling output" Off)

file(GLOB markov_SOURCES src/*.c)
add_executable(markov ${markov_SOURCES})

install(TARGETS markov DESTINATION bin)

# Packaging
# All in one for now
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/")

set(CPACK_PACKAGE_VENDOR "Alex Ankudinov")
set(CPACK_PACKAGE_CONTACT "Alex Ankudinov <xelez0@gmail.com>")

set(CPACK_PACKAGE_NAME "markov")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Markov Chains for random sequence generation")
set(CPACK_PACKAGE_VERSION "${MARKOV_VERSION}")

#set(CPACK_BINARY_DEB "on")
#set(CPACK_SOURCE_DEB "on")
set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_DEBIAN_PACKAGE_SECTION "text")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.8)")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Markov Chains for random sequence generation
 Little program for generating text based on other text.
 .
 Homepage: http://github.com/xelez/markov/")

 set(CPACK_PACKAGE_DESCRIPTION_FILE "${MARKOV_SOURCE_DIR}/README.md")
 set(CPACK_RESOURCE_FILE_LICENSE "${MARKOV_SOURCE_DIR}/LICENSE")

set (CPACK_SOURCE_IGNORE_FILES "\\/_;/build/;/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp$;\\.#;/#" CACHE STRING "CPACK will ignore this files" )
include(CPack)
