# will be implictly used for any compilation unit if not overrided by SYSTEM_INCLUDE_FOLDERS parameter
# these directories go as -isystem <dir> to avoid warnings from code of third-party libraries

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bvsio.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bvsio.bios/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bvsio.msig/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bvsio.msig/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bvsio.system/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bvsio.system/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bvsio.token/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bvsio.token/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bvsio.wrap/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bvsio.wrap/)
