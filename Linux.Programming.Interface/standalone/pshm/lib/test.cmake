
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ename.c.inc
    COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/Build_ename.sh 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating ename.c.inc"
)
