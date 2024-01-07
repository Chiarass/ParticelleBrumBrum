# Libraries config file

include_guard(DIRECTORY)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/libraries)

#find package section
find_package(ROOT REQUIRED)

find_package(Boost COMPONENTS REQUIRED)

#link libraries defines
#Define a set of libraries to be linked
#Variables must have this structure: PROGRAM_LIBRARIES_<combination_name>
set(PROGRAM_LIBRARIES_DEFAULT
        ROOT::Core
        ROOT::Gpad
        ROOT::Graf3d
        ROOT::Graf
        ROOT::Hist
        ROOT::Imt
        ROOT::MathCore
        ROOT::Matrix
        ROOT::MultiProc
        ROOT::Net
        ROOT::Physics
        ROOT::Postscript
        ROOT::RIO
        ROOT::ROOTDataFrame
        ROOT::ROOTVecOps
        ROOT::Rint
        ROOT::Thread
        ROOT::TreePlayer
        ROOT::Tree
        ROOT::Gui
        )