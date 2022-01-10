SET(SOURCES main.cpp LogonWidget.cpp)
MAKE_PROGRAM(logon)
TARGET_LINK_LIBRARIES(logon libpond libui libduck libapp)