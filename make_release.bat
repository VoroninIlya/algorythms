::rm -r release

mkdir release

::make compile_flags="-O2 -g -DCHECK_SORT_ALGORITHMS=1" \
::                     -DCHECK_DATA_STRUCTURES=0" \
::    --directory=release --makefile=../makefile

make compile_flags="-O2 -g -DCHECK_SORT_ALGORITHMS=0 -DCHECK_DATA_STRUCTURES=1" --directory=release --makefile=../makefile