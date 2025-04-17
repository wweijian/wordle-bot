SRCS_DIR = srcs
OBJS_DIR = 
INCL_DIR = includes


SRCS = $(SRCS_DIR)/main.cpp\
		$(SRCS_DIR)/WordEntry.cpp
OBJS = $(OBJS_DIR)wordle-bot.o
CC = g++

compile:
		$(CC) $(SRCS) -I $(INCL_DIR) -o $(OBJS)
		@echo -- wordle-bot.o compiled --

run:
		clear
		@./wordle-bot.o
clean:
		rm -rf $(OBJS)

.PHONY: compile clean run re
