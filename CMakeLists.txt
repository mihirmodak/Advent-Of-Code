cmake_minimum_required(VERSION 3.15)
project(advent_of_code)

# Add vcpkg toolchain file if not already specified
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure proper compiler detection
enable_language(CXX)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Add compiler-specific flags if needed
if(MSVC)
    # MSVC-specific flags
    add_compile_options(/W4)
else()
    # GCC/Clang flags
    add_compile_options(-Wall -Wextra)
endif()

# Function to get all subdirectories
function(get_subdirectories result current_dir)
    file(GLOB children RELATIVE ${current_dir} ${current_dir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${current_dir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction()

# Get all subdirectories in the project
get_subdirectories(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# For each subdirectory
foreach(subdir ${SUBDIRS})
    # Get all .cpp files in the subdirectory
    file(GLOB CPP_FILES "${subdir}/*.cpp")

    # For each .cpp file in the subdirectory
    foreach(cpp_file ${CPP_FILES})
        # Get the filename without extension
        get_filename_component(filename ${cpp_file} NAME_WE)

        # Create an executable for each cpp file
        add_executable(${subdir}_${filename} ${cpp_file})

        # Set the output directory to be the same as the source directory
        set_target_properties(${subdir}_${filename}
                PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}"
        )

        # Add include directories if needed
        target_include_directories(${subdir}_${filename} PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/common
                ${OPENSSL_INCLUDE_DIR}  # Add OpenSSL include directory
        )

        # Link against OpenSSL libraries
        target_link_libraries(${subdir}_${filename} PRIVATE
                OpenSSL::SSL
                OpenSSL::Crypto
        )
    endforeach()
endforeach()