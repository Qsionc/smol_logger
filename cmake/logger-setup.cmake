set(LOGGER_LIB_INSTALL_REL_PATH_DIR lib/smogger)
set(LOGGER_ARCHIVE_INSTALL_REL_PATH_DIR lib/smogger)
set(LOGGER_INCLUDE_INSTALL_REL_PATH_DIR include/smogger)
set(LOGGER_CMAKE_CONFIG_INSTALL_REL_PATH_DIR ${LOGGER_LIB_INSTALL_REL_PATH_DIR}/cmake)

add_library(smogger STATIC
        ${SOURCE_DIR}/implementation/jthread.cpp
        ${SOURCE_DIR}/implementation/logger_queue.cpp
        ${SOURCE_DIR}/implementation/logger_reader.cpp
        ${SOURCE_DIR}/implementation/basic_sink.cpp)
target_include_directories(smogger PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)
target_link_libraries(smogger PUBLIC
        Threads::Threads
        singleton::singleton
        smormat::smormat)