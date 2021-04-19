
THORSANVIL_ROOT				?= $(realpath ../../)
COVERAGE_REQUIRED			= 70

TARGET						= ThorSerialize.lib
LINK_LIBS					= ThorsLogging
UNITTEST_LINK_LIBS			= ThorsLogging
UNITTEST_LDLIBS				= -ldl
# There is no executable code in this header. Just an enum declaration.
TEST_IGNORE					+= JsonLexemes.h

#
# Note: SERIALIZATION_EXTERN_LIBS
#▸  ▸   Is set up in the config for any external libraries that we need.
#

FILE_WARNING_FLAGS			+= $(NO_DEPRECATED_REGISTER_TEST) -Wno-unknown-pragmas $(LITERAL_WARNING)
LDLIBS_EXTERN_BUILD			+= $(yaml_ROOT_LIB)
%/JsonLexer.lex.o:			FILE_WARNING_FLAGS	+= -Wno-sign-compare -Wno-register
%/JsonLexer1.lex.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-register
%/DeprecatedTest.o:			FILE_WARNING_FLAGS	+= -Wno-deprecated-declarations

include $(THORSANVIL_ROOT)/build/tools/Makefile




