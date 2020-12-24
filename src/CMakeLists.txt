cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(TITLE muninn)
project(muninn)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../inc)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2.lib)
set(SDL2_MAIN ${PROJECT_SOURCE_DIR}/../lib/SDL2main.lib)
set(SDLIMG_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_image.lib)
set(SDLMIX_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_mixer.lib)

include_directories(${SDL2_INCLUDE_DIR})

set(SRCDIR ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
${SRCDIR}/CAnimation.cpp
${SRCDIR}/CApp.cpp
${SRCDIR}/CApp_ext.cpp
${SRCDIR}/CApp_OnCleanup.cpp
${SRCDIR}/CApp_OnEvent.cpp
${SRCDIR}/CApp_OnInit.cpp
${SRCDIR}/CApp_OnLoop.cpp
${SRCDIR}/CApp_OnRender.cpp
${SRCDIR}/CAsset.cpp
${SRCDIR}/CAsset_Ext.cpp
${SRCDIR}/CCanvas.cpp
${SRCDIR}/CConfig.cpp
${SRCDIR}/CCreate.cpp
${SRCDIR}/CCreate_ext.cpp
${SRCDIR}/CError.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CInform.cpp
${SRCDIR}/CInterrupt.cpp
${SRCDIR}/CMask.cpp
${SRCDIR}/CMode.cpp
${SRCDIR}/CSound.cpp
${SRCDIR}/CSurface.cpp
${SRCDIR}/CTitle.cpp
${SRCDIR}/CTitle_Event.cpp
${SRCDIR}/CTitle_ext.cpp
${SRCDIR}/CTitle_Loop.cpp
${SRCDIR}/CTitle_Render.cpp
${SRCDIR}/CTransition.cpp
${SRCDIR}/CType.cpp
${SRCDIR}/CType_Def.cpp
${SRCDIR}/CUtil.cpp
${SRCDIR}/CVocab_Event.cpp
${SRCDIR}/CVocab_ext.cpp
${SRCDIR}/CVocab_Render.cpp
${SRCDIR}/CVocab.cpp
${SRCDIR}/CVocabcard.cpp
)

set(HEADER_FILES
${SRCDIR}/CAnimation.h
${SRCDIR}/CApp.h
${SRCDIR}/CAsset.h
${SRCDIR}/CCanvas.h
${SRCDIR}/CConfig.h
${SRCDIR}/CCreate.h
${SRCDIR}/CError.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFPS.h
${SRCDIR}/CInform.h
${SRCDIR}/CInterrupt.h
${SRCDIR}/CMask.h
${SRCDIR}/CMode.h
${SRCDIR}/CSound.h
${SRCDIR}/CSurface.h
${SRCDIR}/CTitle.h
${SRCDIR}/CTransition.h
${SRCDIR}/CType.h
${SRCDIR}/CUtil.h
${SRCDIR}/CVocab.h
${SRCDIR}/CVocabcard.h
${SRCDIR}/Define.h
)

set(GCC_COVERAGE_LINK_FLAGS  "-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(${TITLE} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${TITLE} ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
