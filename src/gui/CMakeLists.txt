set(extra_gui_SRCS "")
if(ENABLE_TOUCH)
	set(extra_gui_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/touchscreengui.cpp)
endif()

set(gui_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/guiAnimatedImage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiBackgroundImage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiBox.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiButton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiButtonImage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiButtonItemImage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiChatConsole.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiConfirmRegistration.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiEditBox.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiEditBoxWithScrollbar.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiFormSpecMenu.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiInventoryList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiItemImage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiKeyChangeMenu.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiPathSelectMenu.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiScene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiScrollBar.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiScrollContainer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiSkin.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiTable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiHyperText.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/guiVolumeChange.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/modalMenu.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/profilergraph.cpp
	${extra_gui_SRCS}
	PARENT_SCOPE
)
