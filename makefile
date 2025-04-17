SRCS_DIR = srcs
OBJS_DIR = 
INCL_DIR = includes

SRCS = $(SRCS_DIR)/main.cpp\
		$(SRCS_DIR)/WordEntry.cpp\
		$(SRCS_DIR)/InputAnswer.cpp

OBJS = $(OBJS_DIR)wordle-bot
CC = g++




compile:
		clear
		$(CC) $(SRCS) -I $(INCL_DIR) -o $(OBJS)
		@echo -- wordle-bot.o compiled --

run:
		clear
		@./wordle-bot.o
clean:
		rm -rf $(OBJS)

.PHONY: compile clean run re
