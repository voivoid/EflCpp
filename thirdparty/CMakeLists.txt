include(ExternalProject)
include(ProcessorCount)

ProcessorCount(CoresNum)
if(CoresNum EQUAL 0)
  set(CoresNum 1)
endif()

set(MyCxxFlags ${CMAKE_CXX_FLAGS})
set(MyCFlags ${CMAKE_C_FLAGS})
set(MyLdFlags ${CMAKE_EXE_LINKER_FLAGS})

if(NOT "${CMAKE_BUILD_TYPE}" STREQUAL "")
  string(TOUPPER ${CMAKE_BUILD_TYPE} BuildTypeStr)
  set(MyCxxFlags ${MyCxxFlags} ${CMAKE_CXX_FLAGS_${BuildTypeStr}})
  set(MyCFlags ${MyCFlags} ${CMAKE_C_FLAGS_${BuildTypeStr}})
  set(MyLdFlags ${MyLdFlags} ${CMAKE_EXE_LINKER_FLAGS_${BuildTypeStr}})
endif()

message("Will build thirdparties with ${CoresNum} threads")

# --- BOOST ---

set(BoostVersion 1.63.0)
set(BoostMD5 7b493c08bc9557bbde7e29091f28b605)
set(BoostComponents filesystem system log)

foreach(Component ${BoostComponents})
  list(APPEND BoostComponentsCmdLine "--with-${Component}")
endforeach()




message("Will build boost ${BoostVersion} with components: ${BoostComponents}")

set(BoostConfigFlags                     "<cflags>\"${MyCFlags}\"")
set(BoostConfigFlags "${BoostConfigFlags} <cxxflags>\"${MyCxxFlags}\"")
set(BoostConfigFlags "${BoostConfigFlags} <linkflags>\"${MyLdFlags}\"")
set(BoostConfigFlags "${BoostConfigFlags} <archiver>\"${CMAKE_AR}\"")
set(BoostConfigFlags "${BoostConfigFlags} <ranlib>\"${CMAKE_RANLIB}\"")

set(BoostConfigFile ${CMAKE_CURRENT_BINARY_DIR}/boost-user-config.jam)
file(WRITE ${BoostConfigFile} "using gcc : tizen : ${CMAKE_CXX_COMPILER} : ${BoostConfigFlags} ;\n")

string(REPLACE . _ BoostVersionUnderscore ${BoostVersion})
ExternalProject_Add(BuildBoost
  URL http://sourceforge.net/projects/boost/files/boost/${BoostVersion}/boost_${BoostVersionUnderscore}.tar.gz/download
  URL_MD5 ${BoostMD5}
  BUILD_IN_SOURCE 1
  SOURCE_DIR ${MyDepsBoostDir}
  CONFIGURE_COMMAND ./bootstrap.sh
  BUILD_COMMAND echo ${BoostComponentsCmdLine} && ./b2 ${BoostComponentsCmdLine} link=static toolset=gcc-tizen --user-config=${BoostConfigFile} -d+2 -j ${CoresNum}
  INSTALL_COMMAND ""
  )


if(NOT TIZEN)

# --- EFL ---

set(EflVersion 1.13.0)
set(EflSHA256 7ff797d4cd01143edc1258a287be3ddfb11264f0b855878d8f5ad5129dee9357)

message("Will build EFL ${EflVersion}")
ExternalProject_Add(BuildEfl
  URL https://download.enlightenment.org/rel/libs/efl/efl-${EflVersion}.tar.gz
  URL_HASH SHA256=${EflSHA256}
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ./configure --with-crypto=none --prefix=${MyDepsEflDir} "CXXFLAGS=${MyCxxFlags}" "CFLAGS=${MyCFlags}" "LDFLAGS=${MyLdFlags}" "AR=${CMAKE_AR}" "RANLIB=${CMAKE_RANLIB}"
  BUILD_COMMAND make -j ${CoresNum}
  INSTALL_COMMAND make install
  )


# --- ELEMENTARY ---

set(ElementaryVersion ${EflVersion})
set(ElementarySHA256 52f1b4304f22156ab53d2d13b8d8f15c58a110a3bc3f31a13fc357eb9527778c)

message("Will build Elementary ${ElementaryVersion}")
ExternalProject_Add(BuildElementary
  DEPENDS BuildEfl
  URL https://download.enlightenment.org/rel/libs/elementary/elementary-${ElementaryVersion}.tar.gz
  URL_HASH SHA256=${ElementarySHA256}
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ./configure --prefix=${MyDepsElmDir} "CXXFLAGS=${MyCxxFlags}" "CFLAGS=${MyCFlags}" "LDFLAGS=${MyLdFlags}" "AR=${CMAKE_AR}" "RANLIB=${CMAKE_RANLIB}" "PKG_CONFIG_PATH=${MyDepsEflDir}/lib/pkgconfig"
  BUILD_COMMAND make -j ${CoresNum}
  INSTALL_COMMAND make install
  )

endif()
