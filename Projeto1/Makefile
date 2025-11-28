CFLAGS = -Wall -Wextra -O2 -g

PROGS = imageRGBTest test_isequal testrecur test_rotation

# Default rule: make all programs
all: $(PROGS)

imageRGBTest: imageRGBTest.o imageRGB.o instrumentation.o error.o \
              PixelCoords.o PixelCoordsQueue.o PixelCoordsStack.o

test_isequal: test_isequal.o imageRGB.o instrumentation.o error.o \
              PixelCoords.o PixelCoordsQueue.o PixelCoordsStack.o

testrecur: testrecur.o imageRGB.o instrumentation.o error.o \
          PixelCoords.o PixelCoordsQueue.o PixelCoordsStack.o

test_rotation: test_rotation.o imageRGB.o instrumentation.o error.o \
               PixelCoords.o PixelCoordsQueue.o PixelCoordsStack.o

# Object dependencies for test sources (headers)
imageRGBTest.o: imageRGB.h instrumentation.h error.h \
                PixelCoords.h PixelCoordsQueue.h PixelCoordsStack.h

test_isequal.o: imageRGB.h instrumentation.h error.h \
                PixelCoords.h PixelCoordsQueue.h PixelCoordsStack.h

testrecur.o: imageRGB.h instrumentation.h error.h \
             PixelCoords.h PixelCoordsQueue.h PixelCoordsStack.h

test_rotation.o: imageRGB.h instrumentation.h error.h \
                 PixelCoords.h PixelCoordsQueue.h PixelCoordsStack.h

# Rule to make any .o file dependent upon corresponding .h file
%.o: %.h

# Make uses builtin rule to create .o from .c files.

cleanobj:
	rm -f *.o

clean: cleanobj
	rm -f $(PROGS)