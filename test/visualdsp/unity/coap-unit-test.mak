# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     coap-unit-test_Debug
#     coap-unit-test_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files (x86)\Analog Devices\VisualDSP 5.1.2


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "coap-unit-test_Debug" configuration
#

ifeq ($(MAKECMDGOALS),coap-unit-test_Debug)

coap-unit-test_Debug : ./Debug/coap-unit-test.dxe 

./Debug/basic.doj :../../unity/basic.cpp ../../../src/coap/header.h ../../../ext/estdlib/src/estd/cstdint.h ../../../ext/estdlib/src/estd/internal/platform.h ../../../ext/estdlib/src/estd/internal/opts.h ../../../ext/estdlib/src/estd/port/identify_platform.h ../../../ext/estdlib/src/estd/port/toolchain.h ../../../ext/estdlib/src/estd/port/toolchain/gnuc-flavor.h ../../../ext/estdlib/src/estd/port/toolchain/visualdsp.h ../../../ext/estdlib/src/estd/port/toolchain/gnuc.h ../../../ext/estdlib/src/estd/port/support_platform.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/yvals.h ../../../src/coap/platform.h ../../../ext/moducom-memory/src/mc/mem/platform.h ../../../src/mc/opts-internal.h ../../../src/mc/opts.h ../../../src/coap-features.h $(VDSP)/Blackfin/include/cplus/iostream $(VDSP)/Blackfin/include/cplus/istream $(VDSP)/Blackfin/include/cplus/ostream $(VDSP)/Blackfin/include/cplus/ios $(VDSP)/Blackfin/include/cplus/xlocnum $(VDSP)/Blackfin/include/cplus/climits $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/cplus/clocale $(VDSP)/Blackfin/include/locale.h $(VDSP)/Blackfin/include/cplus/cstdio $(VDSP)/Blackfin/include/stdio.h $(VDSP)/Blackfin/include/cplus/cstdlib $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/cplus/streambuf $(VDSP)/Blackfin/include/cplus/xiosbase $(VDSP)/Blackfin/include/cplus/cctype $(VDSP)/Blackfin/include/ctype.h $(VDSP)/Blackfin/include/cplus/stdexcept $(VDSP)/Blackfin/include/cplus/exception $(VDSP)/Blackfin/include/cplus/xstddef $(VDSP)/Blackfin/include/xsyslock.h $(VDSP)/Blackfin/include/sys/adi_rtl_sync.h $(VDSP)/Blackfin/include/stdbool.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/cplus/cstddef $(VDSP)/Blackfin/include/cplus/xstring $(VDSP)/Blackfin/include/cplus/iosfwd $(VDSP)/Blackfin/include/cplus/cstring $(VDSP)/Blackfin/include/string.h $(VDSP)/Blackfin/include/cplus/cwchar $(VDSP)/Blackfin/include/wchar.h $(VDSP)/Blackfin/include/xwcstod.h $(VDSP)/Blackfin/include/xwstr.h $(VDSP)/Blackfin/include/cplus/xdebug $(VDSP)/Blackfin/include/cplus/new ../../unity/unit-test.h $(VDSP)/Blackfin/include/math.h $(VDSP)/Blackfin/include/ymath.h $(VDSP)/Blackfin/include/math_bf.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h ../../../ext/estdlib/ext/Unity/src/unity.h ../../../ext/estdlib/ext/Unity/src/unity_internals.h $(VDSP)/Blackfin/include/setjmp.h ../../../ext/estdlib/ext/Unity/src/unity.C ../../unit-tests/test-data.h 
	@echo "..\..\unity\basic.cpp"
	$(VDSP)/ccblkfn.exe -c ..\..\unity\basic.cpp -c++ -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\basic.doj -MM

VDK.h VDK.cpp coap-unit-test.rbld :$(VDSP)/blackfin/vdk/VDK.cpp.tf $(VDSP)/blackfin/vdk/VDK.h.tf $(VDSP)/blackfin/vdk/VDKGen.exe ./coap-unit-test.vdk coap-unit-test.rbld 
	@echo ".\coap-unit-test.vdk"
	$(VDSP)/Blackfin\vdk\vdkgen.exe .\coap-unit-test.vdk -proc ADSP-BF537 -si-revision 0.3 -MM

./Debug/decoder.doj :../../unity/decoder.cpp ../../../src/coap/decoder.h ../../../src/coap.h ../../../src/coap/platform.h ../../../ext/moducom-memory/src/mc/mem/platform.h ../../../ext/estdlib/src/estd/internal/platform.h ../../../ext/estdlib/src/estd/internal/opts.h ../../../ext/estdlib/src/estd/port/identify_platform.h ../../../ext/estdlib/src/estd/port/toolchain.h ../../../ext/estdlib/src/estd/port/toolchain/gnuc-flavor.h ../../../ext/estdlib/src/estd/port/toolchain/visualdsp.h ../../../ext/estdlib/src/estd/port/toolchain/gnuc.h ../../../ext/estdlib/src/estd/port/support_platform.h ../../../src/mc/opts-internal.h ../../../src/mc/opts.h ../../../src/coap-features.h $(VDSP)/Blackfin/include/cplus/iostream $(VDSP)/Blackfin/include/cplus/istream $(VDSP)/Blackfin/include/cplus/ostream $(VDSP)/Blackfin/include/cplus/ios $(VDSP)/Blackfin/include/cplus/xlocnum $(VDSP)/Blackfin/include/cplus/climits $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/cplus/clocale $(VDSP)/Blackfin/include/locale.h $(VDSP)/Blackfin/include/cplus/cstdio $(VDSP)/Blackfin/include/stdio.h $(VDSP)/Blackfin/include/cplus/cstdlib $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/cplus/streambuf $(VDSP)/Blackfin/include/cplus/xiosbase $(VDSP)/Blackfin/include/cplus/cctype $(VDSP)/Blackfin/include/ctype.h $(VDSP)/Blackfin/include/cplus/stdexcept $(VDSP)/Blackfin/include/cplus/exception $(VDSP)/Blackfin/include/cplus/xstddef $(VDSP)/Blackfin/include/xsyslock.h $(VDSP)/Blackfin/include/sys/adi_rtl_sync.h $(VDSP)/Blackfin/include/stdbool.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/cplus/cstddef $(VDSP)/Blackfin/include/cplus/xstring $(VDSP)/Blackfin/include/cplus/iosfwd $(VDSP)/Blackfin/include/cplus/cstring $(VDSP)/Blackfin/include/string.h $(VDSP)/Blackfin/include/cplus/cwchar $(VDSP)/Blackfin/include/wchar.h $(VDSP)/Blackfin/include/xwcstod.h $(VDSP)/Blackfin/include/xwstr.h $(VDSP)/Blackfin/include/cplus/xdebug ../../../src/coap/option.h ../../../ext/estdlib/src/estd/cstdint.h ../../../ext/moducom-memory/src/mc/memory-chunk.h $(VDSP)/Blackfin/include/cplus/utility $(VDSP)/Blackfin/include/cplus/new ../../../ext/estdlib/src/estd/type_traits.h ../../../ext/estdlib/src/estd/internal/type_traits.h ../../../ext/estdlib/src/estd/internal/raw/type_traits.h ../../../ext/estdlib/src/estd/internal/raw/cstddef.h ../../../ext/estdlib/src/estd/internal/llvm_type_traits.h ../../../ext/estdlib/src/estd/internal/promoted_type.h ../../../ext/estdlib/src/estd/limits.h ../../../ext/estdlib/src/estd/cstddef.h ../../../src/coap/header.h ../../../src/coap.CPP ../../../ext/moducom-memory/src/mc/memory.h ../../../src/coap/decoder/simple.h ../../../src/coap/decoder/option.h ../../../ext/estdlib/src/estd/span.h ../../../ext/estdlib/src/estd/internal/buffer.h ../../../ext/estdlib/src/estd/array.h ../../../ext/estdlib/src/estd/iterator.h $(VDSP)/Blackfin/include/cplus/iterator $(VDSP)/Blackfin/include/cplus/xutility ../../../ext/estdlib/src/estd/internal/runtime_array.h ../../../ext/estdlib/src/estd/traits/allocator_traits.h ../../../ext/estdlib/src/estd/utility.h ../../../ext/estdlib/src/estd/internal/utility.h ../../../ext/estdlib/src/estd/internal/utility.CPP ../../../ext/estdlib/src/estd/memory.h ../../../ext/estdlib/src/estd/internal/value_evaporator.h ../../../ext/estdlib/src/estd/allocators/generic.h ../../../ext/estdlib/src/estd/internal/handle_with_offset.h ../../../ext/estdlib/src/estd/internal/impl/handle_desc.h $(VDSP)/Blackfin/include/cplus/memory $(VDSP)/Blackfin/include/cplus/xmemory ../../../ext/estdlib/src/estd/internal/deduce_fixed_size.h ../../../ext/estdlib/src/estd/internal/accessor.h ../../../ext/estdlib/src/estd/algorithm.h ../../../ext/estdlib/src/estd/internal/functional.h ../../../ext/estdlib/src/estd/initializer_list.h ../../../ext/estdlib/src/estd/internal/impl/allocated_array.h ../../../ext/estdlib/src/estd/allocators/handle_desc.h ../../../ext/estdlib/src/estd/allocators/fixed.h ../../../src/coap/decoder.hpp ../../../src/coap/decoder.CPP ../../../src/coap_transmission.h $(VDSP)/Blackfin/include/cplus/map $(VDSP)/Blackfin/include/cplus/xtree $(VDSP)/Blackfin/include/cplus/functional ../../../src/coap_transmission.CPP ../../../src/coap/decoder/streambuf.hpp ../../../src/coap/decoder/streambuf.h ../../../ext/estdlib/src/estd/istream.h ../../../ext/estdlib/src/estd/streambuf.h ../../../ext/estdlib/src/estd/internal/impl/streambuf.h ../../../ext/estdlib/src/estd/traits/char_traits.h $(VDSP)/Blackfin/include/cplus/string ../../../ext/estdlib/src/estd/internal/ios.h ../../../ext/estdlib/src/estd/locale.h ../../../ext/estdlib/src/estd/queue.h ../../../ext/estdlib/src/estd/vector.h ../../../ext/estdlib/src/estd/internal/dynamic_array.h ../../../ext/estdlib/src/estd/internal/impl/dynamic_array.h ../../../ext/estdlib/src/estd/functional.h ../../../ext/estdlib/src/estd/tuple.h ../../../ext/estdlib/src/estd/exp/tuple.h ../../../ext/estdlib/src/estd/internal/invoke.h ../../../ext/estdlib/src/estd/internal/priority_queue.h ../../../ext/estdlib/src/estd/exp/heap.h $(VDSP)/Blackfin/include/cplus/algorithm ../../../ext/estdlib/src/estd/internal/impl/streambuf/span.h ../../../ext/estdlib/src/estd/internal/impl/streambuf/pos.h ../../../ext/estdlib/src/estd/internal/impl/streambuf/helpers.h ../../../ext/estdlib/src/estd/port/streambuf.h ../../../ext/estdlib/src/estd/exp/streambuf-traits.h ../../../ext/estdlib/src/estd/ios.h ../../../src/coap/context.h ../../../src/coap/token.h ../../../src/coap/token.CPP ../../../src/coap/uint.h ../../../ext/moducom-memory/src/mc/objstack.h ../../unity/unit-test.h $(VDSP)/Blackfin/include/math.h $(VDSP)/Blackfin/include/ymath.h $(VDSP)/Blackfin/include/math_bf.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h ../../../ext/estdlib/ext/Unity/src/unity.h ../../../ext/estdlib/ext/Unity/src/unity_internals.h $(VDSP)/Blackfin/include/setjmp.h ../../../ext/estdlib/ext/Unity/src/unity.C ../../unit-tests/test-data.h 
	@echo "..\..\unity\decoder.cpp"
	$(VDSP)/ccblkfn.exe -c ..\..\unity\decoder.cpp -c++ -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\decoder.doj -MM

./Debug/encoder.doj :../../unity/encoder.cpp ../../unity/unit-test.h $(VDSP)/Blackfin/include/math.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/ymath.h $(VDSP)/Blackfin/include/math_bf.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h ../../../ext/estdlib/ext/Unity/src/unity.h ../../../ext/estdlib/ext/Unity/src/unity_internals.h $(VDSP)/Blackfin/include/setjmp.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/stdio.h ../../../ext/estdlib/ext/Unity/src/unity.C ../../unit-tests/test-data.h 
	@echo "..\..\unity\encoder.cpp"
	$(VDSP)/ccblkfn.exe -c ..\..\unity\encoder.cpp -c++ -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\encoder.doj -MM

./Debug/ExceptionHandler-BF537.doj :./ExceptionHandler-BF537.asm ./VDK.h $(VDSP)/Blackfin/include/VDK_Public.h $(VDSP)/Blackfin/include/defBF534.h $(VDSP)/Blackfin/include/defBF537.h $(VDSP)/Blackfin/include/def_LPBlackfin.h 
	@echo ".\ExceptionHandler-BF537.asm"
	$(VDSP)/easmblkfn.exe .\ExceptionHandler-BF537.asm -proc ADSP-BF537 -file-attr ProjectName=coap-unit-test -g -D_ADI_THREADS -si-revision 0.3 -o .\Debug\ExceptionHandler-BF537.doj -MM

./Debug/MainThread.doj :MainThread.cpp MainThread.h VDK.h $(VDSP)/Blackfin/include/defBF537.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/defBF534.h $(VDSP)/Blackfin/include/VDK_Public.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/assert.h $(VDSP)/Blackfin/include/sys/platform.h $(VDSP)/Blackfin/include/sys/_adi_platform.h $(VDSP)/Blackfin/include/cdefBF537.h $(VDSP)/Blackfin/include/cdefBF534.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/cplus/new $(VDSP)/Blackfin/include/cplus/exception $(VDSP)/Blackfin/include/cplus/xstddef $(VDSP)/Blackfin/include/xsyslock.h $(VDSP)/Blackfin/include/sys/adi_rtl_sync.h $(VDSP)/Blackfin/include/stdbool.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/cplus/cstdlib $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/cplus/cstddef $(VDSP)/Blackfin/include/string.h ../../unity/unit-test.h $(VDSP)/Blackfin/include/math.h $(VDSP)/Blackfin/include/ymath.h $(VDSP)/Blackfin/include/math_bf.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h ../../../ext/estdlib/ext/Unity/src/unity.h ../../../ext/estdlib/ext/Unity/src/unity_internals.h $(VDSP)/Blackfin/include/setjmp.h $(VDSP)/Blackfin/include/stdio.h ../../../ext/estdlib/ext/Unity/src/unity.C ../../unit-tests/test-data.h 
	@echo ".\MainThread.cpp"
	$(VDSP)/ccblkfn.exe -c .\MainThread.cpp -c++ -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\MainThread.doj -MM

Debug/option-decoder.doj :../../../src/coap/option-decoder.cpp ../../../src/coap/decoder.h ../../../src/coap.h ../../../src/coap/platform.h ../../../ext/moducom-memory/src/mc/mem/platform.h ../../../ext/estdlib/src/estd/internal/platform.h ../../../ext/estdlib/src/estd/internal/opts.h ../../../ext/estdlib/src/estd/port/identify_platform.h ../../../ext/estdlib/src/estd/port/toolchain.h ../../../ext/estdlib/src/estd/port/toolchain/gnuc-flavor.h ../../../ext/estdlib/src/estd/port/toolchain/visualdsp.h ../../../ext/estdlib/src/estd/port/toolchain/gnuc.h ../../../ext/estdlib/src/estd/port/support_platform.h ../../../src/mc/opts-internal.h ../../../src/mc/opts.h ../../../src/coap-features.h $(VDSP)/Blackfin/include/cplus/iostream $(VDSP)/Blackfin/include/cplus/istream $(VDSP)/Blackfin/include/cplus/ostream $(VDSP)/Blackfin/include/cplus/ios $(VDSP)/Blackfin/include/cplus/xlocnum $(VDSP)/Blackfin/include/cplus/climits $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/cplus/clocale $(VDSP)/Blackfin/include/locale.h $(VDSP)/Blackfin/include/cplus/cstdio $(VDSP)/Blackfin/include/stdio.h $(VDSP)/Blackfin/include/cplus/cstdlib $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/cplus/streambuf $(VDSP)/Blackfin/include/cplus/xiosbase $(VDSP)/Blackfin/include/cplus/cctype $(VDSP)/Blackfin/include/ctype.h $(VDSP)/Blackfin/include/cplus/stdexcept $(VDSP)/Blackfin/include/cplus/exception $(VDSP)/Blackfin/include/cplus/xstddef $(VDSP)/Blackfin/include/xsyslock.h $(VDSP)/Blackfin/include/sys/adi_rtl_sync.h $(VDSP)/Blackfin/include/stdbool.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/cplus/cstddef $(VDSP)/Blackfin/include/cplus/xstring $(VDSP)/Blackfin/include/cplus/iosfwd $(VDSP)/Blackfin/include/cplus/cstring $(VDSP)/Blackfin/include/string.h $(VDSP)/Blackfin/include/cplus/cwchar $(VDSP)/Blackfin/include/wchar.h $(VDSP)/Blackfin/include/xwcstod.h $(VDSP)/Blackfin/include/xwstr.h $(VDSP)/Blackfin/include/cplus/xdebug ../../../src/coap/option.h ../../../ext/estdlib/src/estd/cstdint.h ../../../ext/moducom-memory/src/mc/memory-chunk.h $(VDSP)/Blackfin/include/cplus/utility $(VDSP)/Blackfin/include/cplus/new ../../../ext/estdlib/src/estd/type_traits.h ../../../ext/estdlib/src/estd/internal/type_traits.h ../../../ext/estdlib/src/estd/internal/raw/type_traits.h ../../../ext/estdlib/src/estd/internal/raw/cstddef.h ../../../ext/estdlib/src/estd/internal/llvm_type_traits.h ../../../ext/estdlib/src/estd/internal/promoted_type.h ../../../ext/estdlib/src/estd/limits.h ../../../ext/estdlib/src/estd/cstddef.h ../../../src/coap/header.h ../../../src/coap/decoder/simple.h ../../../src/coap/decoder/option.h ../../../ext/estdlib/src/estd/span.h ../../../ext/estdlib/src/estd/internal/buffer.h ../../../ext/estdlib/src/estd/array.h ../../../ext/estdlib/src/estd/iterator.h $(VDSP)/Blackfin/include/cplus/iterator $(VDSP)/Blackfin/include/cplus/xutility ../../../ext/estdlib/src/estd/internal/runtime_array.h ../../../ext/estdlib/src/estd/traits/allocator_traits.h ../../../ext/estdlib/src/estd/utility.h ../../../ext/estdlib/src/estd/internal/utility.h ../../../ext/estdlib/src/estd/memory.h ../../../ext/estdlib/src/estd/internal/value_evaporator.h ../../../ext/estdlib/src/estd/allocators/generic.h ../../../ext/estdlib/src/estd/internal/handle_with_offset.h ../../../ext/estdlib/src/estd/internal/impl/handle_desc.h $(VDSP)/Blackfin/include/cplus/memory $(VDSP)/Blackfin/include/cplus/xmemory ../../../ext/estdlib/src/estd/internal/deduce_fixed_size.h ../../../ext/estdlib/src/estd/internal/accessor.h ../../../ext/estdlib/src/estd/algorithm.h ../../../ext/estdlib/src/estd/internal/functional.h ../../../ext/estdlib/src/estd/initializer_list.h ../../../ext/estdlib/src/estd/internal/impl/allocated_array.h ../../../ext/estdlib/src/estd/allocators/handle_desc.h ../../../ext/estdlib/src/estd/allocators/fixed.h ../../../src/coap/decoder.hpp ../../../src/coap_transmission.h ../../../ext/moducom-memory/src/mc/memory.h $(VDSP)/Blackfin/include/cplus/map $(VDSP)/Blackfin/include/cplus/xtree $(VDSP)/Blackfin/include/cplus/functional 
	@echo "..\..\..\src\coap\option-decoder.cpp"
	$(VDSP)/ccblkfn.exe -c ..\..\..\src\coap\option-decoder.cpp -c++ -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\option-decoder.doj -MM

./Debug/unity.doj :../../../ext/estdlib/ext/Unity/src/unity.c ../../../ext/estdlib/ext/Unity/src/unity.h ../../../ext/estdlib/ext/Unity/src/unity_internals.h $(VDSP)/Blackfin/include/setjmp.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/math.h $(VDSP)/Blackfin/include/ymath.h $(VDSP)/Blackfin/include/math_bf.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/stdio.h 
	@echo "..\..\..\ext\estdlib\ext\Unity\src\unity.c"
	$(VDSP)/ccblkfn.exe -c ..\..\..\ext\estdlib\ext\Unity\src\unity.c -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\unity.doj -MM

./Debug/VDK.doj :VDK.cpp VDK.h $(VDSP)/Blackfin/include/defBF537.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/defBF534.h $(VDSP)/Blackfin/include/VDK_Public.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stddef.h $(VDSP)/Blackfin/include/assert.h $(VDSP)/Blackfin/include/sys/platform.h $(VDSP)/Blackfin/include/sys/_adi_platform.h $(VDSP)/Blackfin/include/cdefBF537.h $(VDSP)/Blackfin/include/cdefBF534.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/cplus/new $(VDSP)/Blackfin/include/cplus/exception $(VDSP)/Blackfin/include/cplus/xstddef $(VDSP)/Blackfin/include/xsyslock.h $(VDSP)/Blackfin/include/sys/adi_rtl_sync.h $(VDSP)/Blackfin/include/stdbool.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/cplus/cstdlib $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/cplus/cstddef $(VDSP)/Blackfin/include/string.h $(VDSP)/Blackfin/include/VDK_Internals.h $(VDSP)/Blackfin/include/sys/exception.h MainThread.h MainThread.CPP ../../unity/unit-test.h $(VDSP)/Blackfin/include/math.h $(VDSP)/Blackfin/include/ymath.h $(VDSP)/Blackfin/include/math_bf.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h ../../../ext/estdlib/ext/Unity/src/unity.h ../../../ext/estdlib/ext/Unity/src/unity_internals.h $(VDSP)/Blackfin/include/setjmp.h $(VDSP)/Blackfin/include/stdio.h ../../../ext/estdlib/ext/Unity/src/unity.C ../../unit-tests/test-data.h 
	@echo ".\VDK.cpp"
	$(VDSP)/ccblkfn.exe -c .\VDK.cpp -c++ -g -structs-do-not-overlap -no-multiline -I ../../../src -I ../../../ext/estdlib/src -I ../../../ext/embr/src -I ../../../ext/moducom-memory/src -I ../../../ext/estdlib/ext/Unity/src -double-size-32 -decls-strong -warn-protos -threads -Wsuppress 0001,0815 -si-revision 0.3 -proc ADSP-BF537 -o .\Debug\VDK.doj -MM

./Debug/coap-unit-test.dxe :./VDK-BF537.ldf ./VDK.h $(VDSP)/Blackfin/lib/bf534_rev_0.3/crtsfc532mty.doj ./Debug/basic.doj ./Debug/decoder.doj ./Debug/encoder.doj ./Debug/ExceptionHandler-BF537.doj ./Debug/MainThread.doj ./Debug/unity.doj ./Debug/VDK.doj ./Debug/option-decoder.doj $(VDSP)/BLACKFIN/lib/cplbtab537.doj $(VDSP)/Blackfin/lib/bf534_rev_0.3/crtn532mty.doj $(VDSP)/Blackfin/lib/bf534_rev_0.3/TMK-BF532.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/vdk-CORE-BF532.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/vdk-i-BF532.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libsmall532mty.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/__initsbsz532.doj $(VDSP)/Blackfin/lib/bf534_rev_0.3/libio532mty.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libc532mty.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/librt532mty.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libevent532mty.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libcpp532mty.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libf64ieee532y.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libdsp532y.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libsftflt532y.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/libetsi532y.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/Debug/libosal532_vdky.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/Debug/libssl537_vdky.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/Debug/libdrv537y.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/Debug/libusb537y.dlb $(VDSP)/Blackfin/lib/bf534_rev_0.3/idle532mty.doj $(VDSP)/Blackfin/lib/bf534_rev_0.3/librt_fileio532mty.dlb 
	@echo "Linking..."
	$(VDSP)/ccblkfn.exe .\Debug\basic.doj .\Debug\decoder.doj .\Debug\encoder.doj .\Debug\ExceptionHandler-BF537.doj .\Debug\MainThread.doj .\Debug\option-decoder.doj .\Debug\unity.doj .\Debug\VDK.doj -T .\VDK-BF537.ldf -L .\Debug -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\coap-unit-test.dxe -proc ADSP-BF537 -flags-link -MD_ADI_THREADS -si-revision 0.3 -flags-link -MM

endif

ifeq ($(MAKECMDGOALS),coap-unit-test_Debug_clean)

coap-unit-test_Debug_clean:
	-$(RM) ".\Debug\basic.doj"
	-$(RM) ".\Debug\decoder.doj"
	-$(RM) ".\Debug\encoder.doj"
	-$(RM) ".\Debug\ExceptionHandler-BF537.doj"
	-$(RM) ".\Debug\MainThread.doj"
	-$(RM) "Debug\option-decoder.doj"
	-$(RM) ".\Debug\unity.doj"
	-$(RM) ".\Debug\VDK.doj"
	-$(RM) ".\Debug\coap-unit-test.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


