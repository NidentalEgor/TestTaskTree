set(GOOGLE_TEST_ROOT External/googletest/googletest)

include_directories(
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/include)

set(GOOGLE_TEST_SOURCE
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/src/gtest-all.cc)
	
foreach(_source ${GOOGLE_TEST_SOURCE})
  set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(GoogleTest ${GOOGLE_TEST_SOURCE})

#target_link_libraries(GoogleTest Tree)