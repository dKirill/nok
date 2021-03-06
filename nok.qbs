import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    cpp.compilerName: "g++"
    cpp.cxxFlags: "-Weverything", "-Werror"
    cpp.cxxLanguageVersion: "c++11"
    cpp.cxxStandardLibrary: "libstdc++"
    cpp.defines: [/*"DEBUG", "MEASURE"*/]
    cpp.dynamicLibraries: "pthread"
    //cpp.includePaths: [""]
    files: [
        "README",
        "src/Computer.cpp",
        "src/Computer.h",
        "src/Global.h",
        "src/Guarded.h",
        "src/Queue.cpp",
        "src/Queue.h",
        "src/Thread.cpp",
        "src/Thread.h",
        "src/ThreadPool.cpp",
        "src/ThreadPool.h",
        "src/main.cpp",
        "task.txt",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

