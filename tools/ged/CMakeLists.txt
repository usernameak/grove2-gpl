cmake_minimum_required(VERSION 3.17)

add_executable(
        ged WIN32

        ged/Main.h
        ged/Main.cpp

        ged/Action/Action.h
        ged/Action/UndoStack.cpp
        ged/Action/UndoStack.h
        ged/Action/ActionModifyProperty.cpp
        ged/Action/ActionModifyProperty.h
        ged/Action/Action.cpp
        ged/Action/ActionExecutor.h

        ged/Document/Document.h
        ged/Document/Document.cpp

        ged/Editor/Editor.cpp
        ged/Editor/Editor.h

        ged/Editor/Common/Base3DEditorView.h
        ged/Editor/Common/Base3DEditorView.cpp

        ged/Editor/Material/MaterialEditor.h
        ged/Editor/Material/MaterialEditor.cpp
        ged/Editor/Material/MaterialEditorView.h
        ged/Editor/Material/MaterialEditorView.cpp
        ged/Editor/Material/MaterialEditorPane.h
        ged/Editor/Material/MaterialEditorPane.cpp

        ged/Editor/Scene/SceneEditor.h
        ged/Editor/Scene/SceneEditor.cpp
        ged/Editor/Scene/Outliner.h
        ged/Editor/Scene/Outliner.cpp
        ged/Editor/Scene/SceneEditorView.h
        ged/Editor/Scene/SceneEditorView.cpp
        ged/Editor/Scene/SceneEditorPane.h
        ged/Editor/Scene/SceneEditorPane.cpp

        ged/Editor/Image/ImageEditor.cpp
        ged/Editor/Image/ImageEditor.h
        ged/Editor/Image/ImageEditorPane.cpp
        ged/Editor/Image/ImageEditorPane.h
        ged/Editor/Image/ImageEditorView.cpp
        ged/Editor/Image/ImageEditorView.h

        ged/ObjEditor/ObjEditor.cpp
        ged/ObjEditor/ObjEditor.h

        ged/ProjectExplorer/ProjectExplorerPane.h
        ged/ProjectExplorer/ProjectExplorerPane.cpp

        ged/Property/EditableProperty.h

        ged/Tools/ImportGLTF/nxftGltfImporter.cpp
        ged/Tools/ImportGLTF/nxftGltfImporter.h

        ged/UI/Drag/ActorClassDragObject.h

        ged/UI/Panes/MainPane.h
        ged/UI/Panes/MainPane.cpp
        ged/UI/Panes/TabbedPane.cpp
        ged/UI/Panes/TabbedPane.h

        ged/UI/Widget/TreeList.h
        ged/UI/Widget/TreeList.cpp
        ged/UI/Widget/ListWidget.h
        ged/UI/Widget/ListWidget.cpp
        ged/UI/Widget/MenuBar.h
        ged/UI/Widget/MenuBar.cpp
        ged/UI/Widget/ColorPicker.h
        ged/UI/Widget/ColorPicker.cpp
        ged/UI/Widget/ETF/NumericTextField.h
        ged/UI/Widget/ETF/NumericTextField.cpp
        ged/UI/Widget/ETF/StringTextField.h
        ged/UI/Widget/ETF/StringTextField.cpp
        ged/UI/Widget/ETF/VectorEditField.h
        ged/UI/Widget/ETF/VectorEditField.cpp
        ged/UI/Widget/ETF/TransformEditField.cpp
        ged/UI/Widget/ETF/TransformEditField.h

        ged/UI/Widget/PropEntries/PropEntryRID.cpp
        ged/UI/Widget/PropEntries/PropEntryRID.h
        ged/UI/Widget/Toolbar/ToolbarSwitch.h
        ged/UI/Widget/Toolbar/ToolbarSwitch.cpp

        ged/UI/Window/DataFilesPane.cpp
        ged/UI/Window/DataFilesPane.h
        ged/UI/Window/ErrorWindow.h
        ged/UI/Window/ErrorWindow.cpp
        ged/UI/Window/WindowNameObject.h
        ged/UI/Window/WindowNameObject.cpp
        ged/UI/Window/EngineAboutWindow.cpp
        ged/UI/Window/EngineAboutWindow.h
        ged/UI/Window/FSBrowser/FSBrowser.h
        ged/UI/Window/FSBrowser/FSBrowser.cpp

        thirdparty/tiny_gltf.cpp
        thirdparty/tiny_gltf.h
        thirdparty/tiny_gltf.inc.h

        app.manifest
)

target_link_libraries(ged grApplication grScene grUi grUiNative grRenderView grGitRevision)

target_include_directories(ged PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET ged POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:ged> $<TARGET_FILE_DIR:ged>
        COMMAND_EXPAND_LISTS
)
