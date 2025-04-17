SRCS_DIR = srcs
OBJS_DIR = 
INCL_DIR = includes

SRCS = $(SRCS_DIR)/main.cpp\
		$(SRCS_DIR)/Answer.cpp
OBJS = $(OBJS_DIR)wordie-bot
CC = g++




compile:
		clear
		$(CC) $(SRCS) -I $(INCL_DIR) -o $(OBJS)
		@echo -- wordie-bot compiled --

run:
		clear
		@./wordie-bot
clean:
		rm -rf $(OBJS)

.PHONY: compile clean run re
