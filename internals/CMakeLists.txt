project(Internals)
cmake_minimum_required(VERSION 2.6)

add_subdirectory(Object)
add_subdirectory(Number)
add_subdirectory(Comparation)
add_subdirectory(Logic)
add_subdirectory(CharFactory)
add_subdirectory(NumberFactory)
add_subdirectory(StringFactory)
add_subdirectory(LogicFactory)

add_subdirectory(Allocator)
add_subdirectory(AutoreleasePool)
add_subdirectory(Undestroyable)

add_subdirectory(Method)
add_subdirectory(MethodFactory)

add_subdirectory(File)
add_subdirectory(Console)

add_subdirectory(Char)

add_subdirectory(List)
add_subdirectory(ListNode)
add_subdirectory(ListIterator)
add_subdirectory(ListMap)
add_subdirectory(ListMapNode)
add_subdirectory(ListMapIterator)
add_subdirectory(ListMapIteratorElement)

add_subdirectory(Map)
add_subdirectory(MapIterator)
add_subdirectory(Stack)
add_subdirectory(Queue)
add_subdirectory(MultiSet)
add_subdirectory(UIDGenerator)
add_subdirectory(JSONParser)

#add_subdirectory(Array)

add_subdirectory(Synonim)

add_subdirectory(ProcessorCommandSystem)
add_subdirectory(Processor)
add_subdirectory(MachineScheduler)
add_subdirectory(Machine)
add_subdirectory(Runtime)

add_subdirectory(ExternalMachineManipulator)

add_subdirectory(ExternalObjectManipulator)
add_subdirectory(ExternalConsoleManipulator)
add_subdirectory(ExternalFileManipulator)
add_subdirectory(ExternalNumberManipulator)
add_subdirectory(ExternalListManipulator)

add_subdirectory(ExternalEntitiesFactory)
add_subdirectory(ExternalObjectsFactory)


add_executable(VM main.c)
target_link_libraries(VM Machine Runtime Object OSKernel)
