#
# Native Activity example
# type run to execute Native Activity
# type clean to clean sources
#

TARGET = linux.so

all: $(TARGET)

NAG = $(CCTOOLSDIR)/sources/native_app_glue

CFLAGS = -Os -Wall -I$(NAG)
OBJS = linux.o $(NAG)/android_native_app_glue.o
LDFLAGS = --Wl --soname $(TARGET) -shared -Wl,--no-undefined -Wl,-z,noexecstack
LIBS = -llog -landroid -lEGL -lGLESv1_CM -lncurses -lm

$(TARGET): $(OBJS)
		gcc -o $(LDFLAGS) $(LIBS)

clean:
		rm $(OBJS) $(TARGET)

run: $(TARGET)
		run_na $(TARGET)
