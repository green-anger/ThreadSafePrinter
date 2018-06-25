set( lib thread_safe_printer )

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( HEADERS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" )

set( HDRS
    ${HEADERS_ROOT}/ThreadSafePrinter.hpp
)

add_library( ${lib} INTERFACE )

target_include_directories( ${lib} INTERFACE
    ${HEADERS_ROOT}
)
