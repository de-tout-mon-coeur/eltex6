TARGET = abonents

SRC = abonents.c

INPUT = payload.bin

$(TARGET): $(SRC)
	gcc $(SRC) -o $(TARGET)
