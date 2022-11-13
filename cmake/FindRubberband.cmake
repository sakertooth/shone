# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindRubberband
-------

Finds the Rubberband library.

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``Rubberband_FOUND``
  True if the system has the Rubberband library.
``Rubberband_VERSION``
  The version of the Rubberband library which was found.
``Rubberband_INCLUDE_DIRS``
  Include directories needed to use Rubberband.
``Rubberband_LIBRARIES``
  Libraries needed to link to Rubberband.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``Rubberband_INCLUDE_DIR``
  The directory containing ``Rubberband.h``.
``Rubberband_LIBRARY``
  The path to the Rubberband library.

#]=======================================================================]

find_package(PkgConfig)
pkg_check_modules(PC_Rubberband QUIET rubberband)

find_path(Rubberband_INCLUDE_DIR
  NAMES RubberBandStretcher.h
  PATHS ${PC_Rubberband_INCLUDE_DIRS}
  PATH_SUFFIXES rubberband
)

find_library(Rubberband_LIBRARY
  NAMES rubberband
  PATHS ${PC_Rubberband_LIBRARY_DIRS}
)

set(Rubberband_VERSION ${PC_Rubberband_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Rubberband
  FOUND_VAR Rubberband_FOUND
  REQUIRED_VARS
    Rubberband_LIBRARY
    Rubberband_INCLUDE_DIR
  VERSION_VAR Rubberband_VERSION
)

if(Rubberband_FOUND)
  set(Rubberband_LIBRARIES ${Rubberband_LIBRARY})
  set(Rubberband_INCLUDE_DIRS ${Rubberband_INCLUDE_DIR})
  set(Rubberband_DEFINITIONS ${PC_Rubberband_CFLAGS_OTHER})
endif()

mark_as_advanced(
  Rubberband_INCLUDE_DIR
  Rubberband_LIBRARY
)
