cmake_minimum_required(VERSION 3.10)

project(traffic LANGUAGES C VERSION 1.0 )

set(MCU atmega32)
set(F_CPU 1000000UL)
set(BAUD 9600)

add_definitions(-DR_CPU=${F_CPU} -DBUAD=${BAUD})
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})
add_compile_options(-mmcu=${MCU} -Os)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB SRC_FILES ${SRC_DIR}/*/*/*/*.c ${SRC_DIR}/*/*/*.c ${SRC_DIR}/*/*.c
	${SRC_DIR}/*.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME
	${PROJECT_NAME}.elf)

add_custom_target(strip ALL avr-strip ${PROJECT_NAME}.elf DEPENDS
	${PROJECT_NAME})

add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PROJECT_NAME}.elf
	${PROJECT_NAME}.hex DEPENDS strip)

# clean additional files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"${PROJECT_NAME}.hex;")

###################################################
# testing 
###################################################

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test)
configure_file(${CMAKE_CURRENT_LIST_DIR}/test/test.simu ${CMAKE_BINARY_DIR}/test/test_circuit.simu COPYONLY)

# dio
file(GLOB DIO_TEST_FILES ${CMAKE_CURRENT_LIST_DIR}/test/dio_test.c
	${CMAKE_CURRENT_LIST_DIR}/src/MCAL/*/*.c)
add_executable(dio_test ${DIO_TEST_FILES} )
set_target_properties(dio_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}/test/)
add_custom_target(strip_dio ALL avr-strip test/dio_test DEPENDS
	dio_test)
add_custom_target(hex_dio ALL avr-objcopy -R .eeprom -O ihex test/dio_test
	test/dio_test.hex DEPENDS strip_dio)
# clean additional files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"test/dio_test.hex;")

# led
file(GLOB LED_TEST_FILES ${CMAKE_CURRENT_LIST_DIR}/test/led_test.c
	${CMAKE_CURRENT_LIST_DIR}/src/MCAL/*/*.c
	${CMAKE_CURRENT_LIST_DIR}/src/ECUAL/led/*.c)
add_executable(led_test ${LED_TEST_FILES} )
set_target_properties(led_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}/test/)
add_custom_target(strip_led ALL avr-strip test/led_test DEPENDS
	led_test)
add_custom_target(hex_led ALL avr-objcopy -R .eeprom -O ihex test/led_test
	test/led_test.hex DEPENDS strip_led)
# clean additional files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"test/led_test.hex;")

# button
file(GLOB BUTTON_TEST_FILES ${CMAKE_CURRENT_LIST_DIR}/test/button_test.c
	${CMAKE_CURRENT_LIST_DIR}/src/MCAL/*/*.c
	${CMAKE_CURRENT_LIST_DIR}/src/ECUAL/*/*.c)
add_executable(button_test ${BUTTON_TEST_FILES} )
set_target_properties(button_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}/test/)
add_custom_target(strip_button ALL avr-strip test/button_test DEPENDS
	button_test)
add_custom_target(hex_button ALL avr-objcopy -R .eeprom -O ihex test/button_test
	test/button_test.hex DEPENDS strip_button)
# clean additional files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"test/button_test.hex;")

