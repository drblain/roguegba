# Function to convert one or more .bin files into .o objects
function(bin2o)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs BIN_FILES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ARG_BIN_FILES)
        message(FATAL_ERROR "bin2o requires at least one BIN_FILE")
    endif()

    foreach(BIN_FILE IN LISTS ARG_BIN_FILES)
        # Get the filename (with extension) and generate output paths
        get_filename_component(BASENAME ${BIN_FILE} NAME)
        set(OBJ_FILE "${CMAKE_CURRENT_BINARY_DIR}/${BASENAME}.o")
        string(REPLACE "." "_" HEADER_NAME ${BASENAME})
        set(HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/${HEADER_NAME}.h")
        set(TMP_ASM "${CMAKE_CURRENT_BINARY_DIR}/${BASENAME}.s")

        # Add a custom command for this .bin to .o
        add_custom_command(
            OUTPUT ${OBJ_FILE} ${HEADER_FILE}
            COMMAND bin2s -a 4 -H ${HEADER_FILE} ${BIN_FILE} > ${TMP_ASM}
            COMMAND ${CMAKE_C_COMPILER} -x assembler-with-cpp
                    ${CMAKE_C_FLAGS} ${CMAKE_ASM_FLAGS} -c ${TMP_ASM} -o ${OBJ_FILE}
            COMMAND ${CMAKE_COMMAND} -E rm -f ${TMP_ASM}
            DEPENDS ${BIN_FILE}
            COMMENT "Converting binary ${BIN_FILE} to object ${OBJ_FILE}"
            VERBATIM
        )

        # Collect generated objects to return to caller
        list(APPEND GENERATED_OBJS ${OBJ_FILE})
    endforeach()

    # Return list of generated objects
    set(BIN2O_OBJS ${GENERATED_OBJS} PARENT_SCOPE)
endfunction()
