#ifndef LINE_CONTAINER
#define LINE_CONTAINER

typedef struct {
    char code[100];
    char category[20];
    char line[100];
} Line;

typedef struct {
    Line* lines;
    int amount;
} LineContainer;

Line* getRandomLine(const LineContainer* container);
Line* createLine(const char* code, const char* category, const char* line);
LineContainer* createLineContainer();
LineContainer* addLineToContainer(LineContainer* container, const Line* line);
LineContainer* getLinesByCategory(const LineContainer* container, const char* category);

#endif
