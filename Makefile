OBJ=engine/core engine/input engine/render engine/sound engine/text util/list
LIB=SDL SDL_image SDL_mixer SDL_ttf m
MAIN=main
APP=app

CC=gcc
CC_FLAGS=-Wall -O2

SRC=src
OBJ_PATH=obj
OBJ_SUB=engine util
BUILD=build

OBJ_FILES=$(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(OBJ)))
LIB_FLAGS=$(addprefix -l, $(LIB))
OBJ_PATHS=$(addprefix $(OBJ_PATH)/, $(OBJ_SUB))

define cc-obj
$(CC) -c $(CC_FLAGS) $< -o $@
endef

define cc-app
$(CC) $(CC_FLAGS) $(SRC)/$(MAIN).c -o $(BUILD)/$(APP) $(OBJ_FILES) $(LIB_FLAGS)
endef

$(APP): $(OBJ_FILES) $(OBJ_PATH) $(BUILD)
	$(cc-app)
	rm -f $(OBJ_FILES)

$(BUILD):
	mkdir $(BUILD)

$(OBJ_PATH)/%.o: $(SRC)/%.c $(OBJ_PATHS)
	$(cc-obj)

$(OBJ_PATH):
	mkdir $@

$(OBJ_PATHS):
	mkdir -p $@

clean:
	rm -f $(BUILD)/$(APP) $(OBJ_FILES)
