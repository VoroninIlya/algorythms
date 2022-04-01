source_dirs := \
    main algorithms data_structures \
    threadx/common/src \
    threadx/ports/linux/gnu/src \

include_dirs := \
    main/inc algorithms/inc data_structures/inc \
    threadx/common/inc \
    threadx/ports/linux/gnu/inc \
    
wildcards := \
    ../main/*.c ../algorithms/*.c ../data_structures/*.c \
    ../threadx/common/src/*.c \
    ../threadx/ports/linux/gnu/src/*.c \

source_dirs	   := $(addprefix ../,$(source_dirs))
include_dirs   := $(addprefix ../,$(include_dirs))

# flag -lpthread is important
linux_release: $(notdir $(patsubst %.c,%.o,$(wildcard $(wildcards))))
	gcc $(compile_flags) $^ -lpthread  -o $@ 

VPATH := $(include_dirs) $(source_dirs)

%.o: %.c
	gcc $(compile_flags) -c -MD -lpthread  $(LDFLAGS) $(addprefix -I,$(include_dirs)) \
    -I/usr/include/ \
    $<

include $(wildcard *.d)
