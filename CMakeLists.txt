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

file(GLOB SRC_FILES ${SRC_DIR}/*/*/*/*.c ${SRC_DIR}/*/*/*.c ${SRC_DIR}/*/*.c ${SRC_DIR}/*.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME
	${PROJECT_NAME}.elf)

add_custom_target(strip ALL avr-strip ${PROJECT_NAME}.elf DEPENDS
	${PROJECT_NAME})

add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PROJECT_NAME}.elf
	${PROJECT_NAME}.hex DEPENDS strip)

# clean additional files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"${PROJECT_NAME}.hex;${PROJECT_NAME}.eeprom;${PROJECT_NAME}.lst")
