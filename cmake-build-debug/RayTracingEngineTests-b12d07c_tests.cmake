add_test( [==[test circle hit book page 620]==] D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe [==[test circle hit book page 620]==]  )
set_tests_properties( [==[test circle hit book page 620]==] PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( [==[test circle hit]==] D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe [==[test circle hit]==]  )
set_tests_properties( [==[test circle hit]==] PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( [==[test circle hit edge]==] D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe [==[test circle hit edge]==]  )
set_tests_properties( [==[test circle hit edge]==] PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( Translation D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe Translation  )
set_tests_properties( Translation PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( Scaling D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe Scaling  )
set_tests_properties( Scaling PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( X-rotation D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe X-rotation  )
set_tests_properties( X-rotation PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( Y-rotation D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe Y-rotation  )
set_tests_properties( Y-rotation PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( Z-rotation D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe Z-rotation  )
set_tests_properties( Z-rotation PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( [==[Z-rotation and inverse]==] D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe [==[Z-rotation and inverse]==]  )
set_tests_properties( [==[Z-rotation and inverse]==] PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
add_test( [==[example book page 220]==] D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug/Debug/RayTracingEngineTests.exe [==[example book page 220]==]  )
set_tests_properties( [==[example book page 220]==] PROPERTIES WORKING_DIRECTORY D:/UA/Semester7/ComputerGraphics/CppCode/RayTracingEngine/cmake-build-debug SKIP_RETURN_CODE 4)
set( RayTracingEngineTests_TESTS [==[test circle hit book page 620]==] [==[test circle hit]==] [==[test circle hit edge]==] Translation Scaling X-rotation Y-rotation Z-rotation [==[Z-rotation and inverse]==] [==[example book page 220]==])
