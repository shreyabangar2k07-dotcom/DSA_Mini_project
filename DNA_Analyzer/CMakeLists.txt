cmake_minimum_required(VERSION 3.10)
project(DNA_Analyzer)

set(CMAKE_CXX_STANDARD 17)

add_executable(DNA_Analyzer
    main.cpp
    FastaReader.cpp
    SequenceAnalyzer.cpp
    ReportManager.cpp
    UIManager.cpp
)
