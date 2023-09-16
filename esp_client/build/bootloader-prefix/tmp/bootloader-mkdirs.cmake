# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/allan/esp/esp-idf/components/bootloader/subproject"
  "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader"
  "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix"
  "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix/tmp"
  "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix/src/bootloader-stamp"
  "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix/src"
  "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/coding_pirates/hacking/esp-projekter/esp_client/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
