SRCS_DIR = srcs
TARGET_DIR = 
INCL_DIR = includes

SRCS = $(SRCS_DIR)/main.cpp\
		$(SRCS_DIR)/answer.cpp\
		$(SRCS_DIR)/solver.cpp
TARGET = $(TARGET_DIR)wordie-bot
CC = g++




compile:
		clear
		$(CC) $(SRCS) -I $(INCL_DIR) -o $(TARGET)
		@echo -- wordie-bot compiled --

run:
		clear
		@./wordie-bot
clean:
		clear
		@rm -rf $(TARGET)
		@echo wordie killed

.PHONY: compile clean run re
