set(CMAKE_INCLUDE_DIRECTORIES_BEFORE on)

aux_source_directory(thread thread_src_files)
aux_source_directory(utils utils_src_files)

set( ALL_SRC_LIST
    ${thread_src_files}
    ${utils_src_files}
)

ADD_LIBRARY(common STATIC ${ALL_SRC_LIST})
