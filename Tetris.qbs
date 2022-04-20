import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true

        cpp.cxxLanguageVersion: "c++14"

        files: [
            "Board.cpp",
            "Board.h",
            "Constants.h",
            "Cube.h",
            "Figure.cpp",
            "Figure.h",
            "Menu.cpp",
            "Menu.h",
            "main.cpp",
        ]

        cpp.includePaths: "fltk_win64/include"
        cpp.libraryPaths: "fltk_win64/lib"
        cpp.cxxFlags: "-Wno-unused-parameter"
        cpp.driverLinkerFlags: "-mwindows"
        cpp.staticLibraries: [
            "fltk_images",
            "fltk",
            "fltk_png",
            "z",
            "fltk_jpeg",
            "ole32",
            "uuid",
            "comctl32",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
