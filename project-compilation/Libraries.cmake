# Libraries config file

include_guard(DIRECTORY)

list(APPEND CMAKE_PREFIX_PATH "/home/chiara/root")
list(APPEND CMAKE_LIBRARY_PATH "/home/chiara/root//lib")

#find package section
list(APPEND CMAKE_MODULE_PATH "/home/chiara/root/6.26.06/lib/cmake/root")
find_package(ROOT REQUIRED)

#find_package(Boost COMPONENTS REQUIRED)

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