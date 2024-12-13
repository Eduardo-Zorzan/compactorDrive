# Install script for directory: C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/src/1.11.1-9b7bdec657.clean/cpr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/pkgs/cpr_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/lib/cpr.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr" TYPE FILE FILES
    "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/cpr/cprConfig.cmake"
    "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/cpr/cprConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr/cprTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr/cprTargets.cmake"
         "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/cpr/CMakeFiles/Export/9cbb545e1300ea60881e0aa5742b2a45/cprTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr/cprTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr/cprTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr" TYPE FILE FILES "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/cpr/CMakeFiles/Export/9cbb545e1300ea60881e0aa5742b2a45/cprTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cpr" TYPE FILE FILES "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/cpr/CMakeFiles/Export/9cbb545e1300ea60881e0aa5742b2a45/cprTargets-debug.cmake")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Duduz/OneDrive/Documents/programacao/projetos/compacterDrive/app/vcpkg_installed/vcpkg/blds/cpr/x64-windows-dbg/cpr/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
