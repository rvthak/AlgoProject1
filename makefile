
#--------------------------------------------------------------------------

CC=g++
CFLAGS=-Wall -Iinclude

INPUT_FILE=./datasets/input_small_id
QUERY_FILE=./datasets/query_small_id

SRCS=$(wildcard ./src/*.cpp)
OBJS=$(patsubst ./src/%.cpp, ./obj/%.o, $(SRCS))

OBJS_LSH=$(filter-out ./obj/main_Cube.o, $(OBJS))
OBJS_CUB=$(filter-out ./obj/main_LSH.o,  $(OBJS))

OUT_LSH=./bin/lsh
OUT_CUB=./bin/cube

RUNFLAGS_LSH=-o lsh_output.txt  -k 5 -L 10 -N 6 -R 450           -i $(INPUT_FILE) -q $(QUERY_FILE)
RUNFLAGS_CUB=-o cube_output.txt -k 5 -M 10 -N 6 -R 2 -probes 3 -i $(INPUT_FILE) -q $(QUERY_FILE)

VGFLAGS=--leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes

#--------------------------------------------------------------------------

all: $(OUT_LSH) $(OUT_CUB)

$(OUT_LSH): $(OBJS_LSH)
	$(CC) $(CFLAGS) $(OBJS_LSH) -o $@

$(OUT_CUB): $(OBJS_CUB)
	$(CC) $(CFLAGS) $(OBJS_CUB) -o $@

./obj/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r ./bin/* ./obj/*

init:
	mkdir obj bin

#--------------------------------------------------------------------------

lsh: $(OUT_LSH)
	$(OUT_LSH) $(RUNFLAGS_LSH)

cube: $(OUT_CUB)
	$(OUT_CUB) $(RUNFLAGS_CUB)

vg_lsh: $(OUT_LSH)
	valgrind $(OUT_LSH) $(RUNFLAGS_LSH)

vgext_lsh: $(OUT_LSH)
	valgrind $(VGFLAGS) $(OUT_LSH) $(RUNFLAGS_LSH)

vg_cube: $(OUT_CUB)
	valgrind $(OUT_CUB) $(RUNFLAGS_CUB)

vgext_cube: $(OUT_CUB)
	valgrind $(VGFLAGS) $(OUT_CUB) $(RUNFLAGS_CUB)

#--------------------------------------------------------------------------

run: lsh

vg: vg_lsh

vgext: vgext_lsh

.PHONY: clean all run lsh cube vg vgext vg_lsh vgext_lsh vg_cube vgext_cube

#--------------------------------------------------------------------------
