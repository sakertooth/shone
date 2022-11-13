# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindAubio
-------

Finds the Aubio library.

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``Aubio_FOUND``
  True if the system has the Aubio library.
``Aubio_VERSION``
  The version of the Aubio library which was found.
``Aubio_INCLUDE_DIRS``
  Include directories needed to use Aubio.
``Aubio_LIBRARIES``
  Libraries needed to link to Aubio.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``Aubio_INCLUDE_DIR``
  The directory containing ``Aubio.h``.
``Aubio_LIBRARY``
  The path to the Aubio library.

#]=======================================================================]

find_package(PkgConfig)
pkg_check_modules(PC_Aubio QUIET aubio)

find_path(Aubio_INCLUDE_DIR
  NAMES aubio.h
  PATHS ${PC_Aubio_INCLUDE_DIRS}
  PATH_SUFFIXES aubio
)

find_library(Aubio_LIBRARY
  NAMES aubio
  PATHS ${PC_Aubio_LIBRARY_DIRS}
)

set(Aubio_VERSION ${PC_Aubio_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Aubio
  FOUND_VAR Aubio_FOUND
  REQUIRED_VARS
    Aubio_LIBRARY
    Aubio_INCLUDE_DIR
  VERSION_VAR Aubio_VERSION
)

if(Aubio_FOUND)
  set(Aubio_LIBRARIES ${Aubio_LIBRARY})
  set(Aubio_INCLUDE_DIRS ${Aubio_INCLUDE_DIR})
  set(Aubio_DEFINITIONS ${PC_Aubio_CFLAGS_OTHER})
endif()

mark_as_advanced(
  Aubio_INCLUDE_DIR
  Aubio_LIBRARY
)
