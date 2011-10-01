FinalStage := Object clone do(
	
	Directory copyToPath := method(_path,
		destDir := Directory clone with(_path) createIfAbsent
		items foreach(item,
			if(item name beginsWithSeq(".") not,
				dstPath := _path .. "/" .. (item name)
				if(item type == "File", 
					File clone with(dstPath) remove
				)
				item copyToPath(dstPath)
			)
		)
	)
	
	copyCFiles := method(path,
		if(path isNil, path = "")
		dir := Directory clone with("../../internals_sources_c") 
		dir items selectInPlace(item, item name beginsWithSeq(".") not) foreach(item,
			dstPath := "../../internals" .. path .. "/" .. (item name)
			if(item type == "File", 
				File clone with(dstPath) remove
			)
			item copyToPath(dstPath)
		)
	)
	
	writeInitializers := method(
		initializers := File clone openForAppending("../../internals/initializers.h")
		initializers truncateToSize(0)
		initializers write("void __initAllClasses()\n{\n")
		
		Directory with("../../internals") directories foreach(dir,
			if(dir name beginsWithSeq("."), continue)
			initializers write("\t#{dir name}_InitializeClass();\n" interpolate)
		)
		
		initializers write("}")
		initializers close
	)
	
	writeCMakeLists := method(
		cmakeLists := File clone openForAppending("../../internals/CMakeLists.txt")
		cmakeLists truncateToSize(0)
		cmakeLists write("project(Internals)\n")
		cmakeLists write("cmake_minimum_required(VERSION 2.6)\n\n")
		Directory with("../../internals") directories foreach(dir,
			if(dir name beginsWithSeq("."), continue)
			cmakeLists write("add_subdirectory(#{dir name})\n" interpolate)
		)
		
		cmakeLists write("add_executable(VM main.c)\n")
		cmakeLists write("set_property(TARGET VM PROPERTY LINK_FLAGS \"-T${CMAKE_CURRENT_SOURCE_DIR}/script.ld\")")
		cmakeLists write("target_link_libraries(VM AllocatorForStack Machine Runtime Object OSKernel)\n")
		cmakeLists close
	)
	
	perform := method(
		copyCFiles
		writeCMakeLists
	)
)
