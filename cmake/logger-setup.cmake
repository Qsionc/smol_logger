set(LOGGER_LIB_INSTALL_REL_PATH_DIR lib/smogger)
set(LOGGER_ARCHIVE_INSTALL_REL_PATH_DIR lib/smogger)
set(LOGGER_INCLUDE_INSTALL_REL_PATH_DIR include/smogger)
set(LOGGER_CMAKE_CONFIG_INSTALL_REL_PATH_DIR ${LOGGER_LIB_INSTALL_REL_PATH_DIR}/cmake)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

add_library(smogger STATIC
        ${SOURCE_DIR}/core/jthread.cpp
        ${SOURCE_DIR}/core/logger_queue.cpp
        ${SOURCE_DIR}/core/logger_reader.cpp
        ${SOURCE_DIR}/core/basic_sink.cpp
        ${SOURCE_DIR}/core/logger.cpp)
target_include_directories(smogger PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIR}>)
target_link_libraries(smogger PUBLIC
        Threads::Threads
        singleton::singleton
        smormat::smormat)

install(TARGETS smogger
        EXPORT smoggerTargets
        ARCHIVE DESTINATION
        ${LOGGER_ARCHIVE_INSTALL_REL_PATH_DIR}
        INCLUDES DESTINATION ${LOGGER_INCLUDE_INSTALL_REL_PATH_DIR})
install(EXPORT smoggerTargets
        FILE smoggerTargets.cmake
        NAMESPACE smogger::
        DESTINATION ${LOGGER_CMAKE_CONFIG_INSTALL_REL_PATH_DIR})
install(FILES
        ${CMAKE_SOURCE_DIR}/cmake/smogger-config.cmake
        ${CMAKE_SOURCE_DIR}/cmake/packages-setup.cmake
        DESTINATION ${LOGGER_CMAKE_CONFIG_INSTALL_REL_PATH_DIR})
install(FILES
        ${INCLUDE_DIR}/smogger.h
        DESTINATION ${LOGGER_INCLUDE_INSTALL_REL_PATH_DIR})
install(FILES
        ${INCLUDE_DIR}/core/basic_sink.h
        ${INCLUDE_DIR}/core/jthread.h
        ${INCLUDE_DIR}/core/logger.h
        ${INCLUDE_DIR}/core/logger_queue.h
        ${INCLUDE_DIR}/core/logger_reader.h
        DESTINATION ${LOGGER_INCLUDE_INSTALL_REL_PATH_DIR}/core)
install(FILES
        ${INCLUDE_DIR}/settings/logger_settings.h
        DESTINATION ${LOGGER_INCLUDE_INSTALL_REL_PATH_DIR}/settings)