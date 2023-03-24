# Credits: 
# https://stackoverflow.com/questions/15639781/how-to-find-the-qt5-cmake-module-on-windows
cmake_minimum_required(VERSION 3.12)

SET(QT_MISSING True)


# Function to extract the version number from a path
function(get_version_number out path)
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" version ${path})
    set(${out} ${version} PARENT_SCOPE)
    # message("Extracted version: "${version})
endfunction()

# msvc only; mingw will need different logic
IF(MSVC AND QT_MISSING)
    MESSAGE("Searching for QT installs...")

    # look for user-registry pointing to qtcreator
    GET_FILENAME_COMPONENT(QT_BIN [HKEY_CURRENT_USER\\Software\\Classes\\Applications\\QtProject.QtCreator.cpp\\shell\\Open\\Command] PATH)
    #message("QT Path: "${QT_BIN})
    # get root path so we can search for 5.3, 5.4, 5.5, etc
    STRING(REPLACE "/Tools" ";" QT_BIN "${QT_BIN}")
    LIST(GET QT_BIN 0 QT_BIN)
    FILE(GLOB QT_VERSIONS "${QT_BIN}/5.*")
    #message("QT Version: "${QT_VERSIONS})
    #message("QT Path: "${QT_BIN})


    ####
    
    # List of paths with version numbers
    #set(paths "C:/Qt/5.14.2" "C:/Qt/5.15.0" "C:/Qt/5.9.2")

    
    
    # Create a list of version numbers
    foreach(path ${QT_VERSIONS})
        get_version_number(version ${path})
        #message("Extracted version: "${version})
        list(APPEND version_numbers ${version})
    endforeach()

    # Sort the list of paths in descending order based on their version number
    list(LENGTH version_numbers num_versions)
    #message("List: "${version_numbers})
    math(EXPR last_index "${num_versions} - 1")
    foreach(i RANGE ${last_index})
        foreach(j RANGE ${last_index})
            list(GET version_numbers ${i} version_i)
            list(GET version_numbers ${j} version_j)

            #message("compare: "${version_i} " to "${version_j})
            if(version_i VERSION_GREATER version_j)
                #message(" is greater than")
                list(GET QT_VERSIONS ${i} path_i)
                list(GET QT_VERSIONS ${j} path_j)
                list(REMOVE_AT QT_VERSIONS ${i})
                list(INSERT QT_VERSIONS ${i} ${path_j})
                list(REMOVE_AT QT_VERSIONS ${j})
                list(INSERT QT_VERSIONS ${j} ${path_i})
                list(REMOVE_AT version_numbers ${i})
                list(INSERT version_numbers ${i} ${version_j})
                list(REMOVE_AT version_numbers ${j})
                list(INSERT version_numbers ${j} ${version_i})
            endif()
        endforeach()
    endforeach()

    # Print the sorted list of paths
    #foreach(path ${QT_VERSIONS})
    #    message(${path})
    #endforeach()

    ####

    #message("QT Version: "${QT_VERSIONS})
    

    
    list(GET QT_VERSIONS 0 QT_VERSION)
    # fix any double slashes which seem to be common
    STRING(REPLACE "//" "/"  QT_VERSION "${QT_VERSION}")

    FILE(GLOB CompilerPath "${QT_VERSION}/msvc*")

    if (EXISTS ${CompilerPath})
        #message("Compiler path: ${CompilerPath}")
        set(QT_PATH ${CompilerPath})
        SET(QT_MISSING False)
    else()
        message("No QT5 installation found")
    endif()


ENDIF()

# use Qt_DIR approach so you can find Qt after cmake has been invoked
IF(NOT QT_MISSING)
    MESSAGE("-- Qt found: ${QT_PATH}")
    
    SET(Qt5_DIR "${QT_PATH}/lib/cmake/Qt5")
    SET(Qt5Widgets_DIR  "${QT_PATH}/lib/cmake/Qt5Widgets")
    SET(Qt5Test_DIR "${QT_PATH}/lib/cmake/Qt5Test")

    
ENDIF()