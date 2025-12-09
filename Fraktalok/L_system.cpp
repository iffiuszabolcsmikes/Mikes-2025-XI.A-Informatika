#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define STACK_SIZE 100
#define STRING_SIZE 1000000

using namespace sf;

void stringCopy(char source[], char dest[])
{
    int i = 0;
    for(i = 0; source[i] != 0; i++)
        dest[i] = source[i];
    dest[i] = 0;
}

void replaceCharString(char *s, char mit, char *mire)
{
    char tmp[STRING_SIZE];
    stringCopy(s, tmp);

    for(char *pi = tmp; *pi != 0; pi++)
    {
        if(*pi == mit)
        {
            for(char *pj = mire; *pj != 0; pj++)
            {
                *s = *pj;
                s++;
            }
        }
        else
        {
            *s = *pi;
             s++;
        }
    }
    *s=0;
}

const float DEG_TO_RAD = 3.14159265f / 180.0f;

struct rule
{
    char what;
    char replaceWith[100];
};

rule rules[100];
int ruleCount;

struct TurtleState
{
    Vector2f position;
    float distance;
    float angle; /// fokban
};

struct Turtle {
    Vector2f position;
    float distance;
    float deltaDistance;
    float angle; /// fokban
    float turnAngle;

    Color color1;
    Color color2;

    VertexArray lines = VertexArray(Lines);

    TurtleState stack[STACK_SIZE];
    int stackSize;
};

bool stackPush(Turtle &t)
{
    if(t.stackSize == STACK_SIZE)
    {
        return 1; //hiba, a verem tele van
    }

    TurtleState state;
    state.position = t.position;
    state.angle = t.angle;
    state.distance = t.distance;

    t.stack[t.stackSize] = state;
    t.stackSize++;
    return 0;
}

bool stackEmpty(Turtle &t)
{
    return t.stackSize == 0;
}

void stackPop(Turtle &t)
{
    if(t.stackSize > 0)
    {
        t.stackSize--;
        t.position = t.stack[t.stackSize].position;
        t.angle = t.stack[t.stackSize].angle;
        t.distance = t.stack[t.stackSize].distance;
    }
}

void initTurtle(Turtle &t, Vector2f position, float distance, float deltaDistance, float angle, float turnAngle, Color color1, Color color2)
{
    t.position = position;
    t.distance = distance;
    t.deltaDistance = deltaDistance;
    t.angle = angle;

    t.color1 = color1;
    t.color2 = color2;

    t.turnAngle = turnAngle;
    t.stackSize = 0;

    ruleCount = 0;
}

void moveForward(Turtle& t)
{
    t.position.x = t.position.x + t.distance * cos(t.angle * DEG_TO_RAD);
    t.position.y = t.position.y + t.distance * sin(t.angle * DEG_TO_RAD);
}

void drawForward(Turtle& t)
{
    Vector2f oldPos = t.position;
    moveForward(t);
    t.lines.append(sf::Vertex(oldPos, t.color1));
    t.lines.append(sf::Vertex(t.position, t.color2));
}

void rotate180(Turtle& t)
{
    t.angle = t.angle + 180;
}

void turnLeft(Turtle& t)
{
    t.angle = t.angle - t.turnAngle;
}

void turnRight(Turtle& t)
{
    t.angle = t.angle + t.turnAngle;
}

void increaseLength(Turtle &t)
{
    t.distance = t.distance * (1 / t.deltaDistance);
}

void decreaseLength(Turtle &t)
{
    t.distance = t.distance * t.deltaDistance;
}

void processString(Turtle& t, char commands[])
{
    for(int i = 0; commands[i] != 0; i++)
    {
        switch(commands[i])
        {
            case 'M':
                moveForward(t);
                break;
            case 'f':
                moveForward(t);
                break;
            case 'A':
                drawForward(t);
                break;
            case 'B':
                drawForward(t);
                break;
            case 'D':
                drawForward(t);
                break;
            case 'F':
                drawForward(t);
                break;
            case 'G':
                drawForward(t);
                break;
            case 'R':
                drawForward(t);
                break;
            case 'L':
                drawForward(t);
                break;
            case '+':
                turnRight(t);
                break;
            case '-':
                turnLeft(t);
                break;
            case '|':
               rotate180(t);
               break;
            case '>':
                increaseLength(t);
                break;
            case '<':
                decreaseLength(t);
                break;
            case '[':
                stackPush(t);
                break;
            case ']':
                stackPop(t);
                break;
        }
    }
}

void applyRules(char *input, rule rules[], int n)
{
    char tmp[STRING_SIZE];
    stringCopy(input, tmp);

    for(char *pi = tmp; *pi != 0; pi++)
    {
        bool replaced = false;
        for(int i = 0; i < n; i++)
        {
            if(*pi == rules[i].what)
            {
                for(char *pj = rules[i].replaceWith; *pj != 0; pj++)
                {
                    *input = *pj;
                    input++;
                }
                replaced = true;
                break;
            }
        }

        if(replaced == false)
        {
            *input = *pi;
             input++;
        }
    }
    *input = 0;
}

void iterate(char *input, rule rules[], int n, int i)
{
    while(i > 0)
    {
        applyRules(input, rules, n);
        i--;
    }
}

void addRule(char what, char * rule)
{
    rules[ruleCount].what = what;
    stringCopy(rule, rules[ruleCount].replaceWith);
    ruleCount++;
}

int main()
{
    int windowWidth = 800;
    int windowHeight = 600;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "L-System");

    char input[STRING_SIZE];
    Turtle turtle;

/*
    ////haz
    initTurtle(turtle, Vector2f(50, windowHeight/2),100, 0.7, 0, 30, Color::Red, Color(255, 255, 0));
    stringCopy("D----D----D-D---D---D", input);
    processString(turtle, input);
    ///6 agu csillag
    initTurtle(turtle, Vector2f(200, windowHeight/2),100,0.7, 0, 60, Color::Red, Color(255, 255, 0));
    stringCopy("D-D++D-D++D-D++D-D++D-D++D-D", input);
    processString(turtle, input);
    ///5 agu csillag
    initTurtle(turtle, Vector2f(50, windowHeight/2 + 200),100,0.7, 0, 144, Color::Red, Color(255, 255, 0));
    stringCopy("D+D+D+D+D", input);
    processString(turtle, input);
    ///csiga vonal
    initTurtle(turtle, Vector2f(250, windowHeight/2 -100),100,0.9, 0, 30, Color::Red, Color(255, 255, 0));
    stringCopy("D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D+<D", input);
    processString(turtle, input);
    ///csigavonal rekurzivan
    initTurtle(turtle, Vector2f(250, windowHeight/2 -100),100,0.9, 0, 30, Color::Red, Color(255, 255, 0));
    addRule('D', "D+<D");
    iterate(input, rules, ruleCount, 10);
    processString(turtle, input);
    ///Koch gorbe
    initTurtle(turtle, Vector2f(100, windowHeight/2 -200),5,0.9, 0, 60, Color::Red, Color(255, 255, 0));
    stringCopy("D", input);
    addRule('D', "D-D++D-D");
    iterate(input, rules, ruleCount, 5);
    processString(turtle, input);
    ///Levy-C-gorbe
    initTurtle(turtle, Vector2f(400, windowHeight/2 -100),5,1/1.45, 0, 45, Color::Red, Color(255, 255, 0));
    stringCopy("D", input);
    addRule('D', "+D--D+");
    iterate(input, rules, ruleCount, 10);
    processString(turtle, input);
    ///sierpinski 3szog
    initTurtle(turtle, Vector2f(150, windowHeight/2),10,1, 0, 120, Color::Red, Color(255, 255, 0));
    stringCopy("F-G-G", input);
    addRule('F', "F-G+F+G-F");
    addRule('G', "GG");
    iterate(input, rules, ruleCount, 5);
    processString(turtle, input);
    ///koch gorbe90
    initTurtle(turtle, Vector2f(500, windowHeight/2+100),10,1, 0, 90, Color::Red, Color(255, 255, 0));
    stringCopy("F", input);
    addRule('F', "F+F-F-F+F");
    iterate(input, rules, ruleCount, 3);
    processString(turtle, input);
    ///sarkanygorbe
    initTurtle(turtle, Vector2f(100, windowHeight/2),6,1, 0, 90, Color::Red, Color(255, 255, 0));
    stringCopy("F", input);
    addRule('F', "F+G");
    addRule('G', "F-G");
    iterate(input, rules, ruleCount, 10);
    processString(turtle, input);
    ///haziko
    initTurtle(turtle, Vector2f(250, windowHeight/2),150,1, 0, 30, Color::Red, Color(255, 255, 0));
    stringCopy("D", input);
    addRule('D', "D---D---D---D---D---D-D----D");
    iterate(input, rules, ruleCount, 1);
    processString(turtle, input);

    initTurtle(turtle, Vector2f(300, windowHeight/2),45,1, 0, 30, Color::Red, Color(255, 255, 0));
    stringCopy("D", input);
    addRule('D', "---M+++D---D---D---D---D---D-D----D");
    iterate(input, rules, ruleCount, 1);
    processString(turtle, input);
    ///Gosper-gorbe
    initTurtle(turtle, Vector2f(550, 50),10,1/sqrt(7), 0, 60, Color::Red, Color(255, 255, 0));
    stringCopy("R", input);
    addRule('R', "R+L++L-R--RR-L+");
    addRule('R', "-R+LL++L+R--R-L");
    iterate(input, rules, ruleCount, 3);
    processString(turtle, input);
    ///penta plexity
    initTurtle(turtle, Vector2f(550, 50),10,4/(sqrt(5)+1)*(sqrt(5)+1), 0, 90, Color::Red, Color(255, 255, 0));
    stringCopy("F++F++F++F++F", input);
    addRule('F', "F++F++F|F-F++F");
    iterate(input, rules, ruleCount, 3);
    processString(turtle, input);
    ///sierpinski-szonyeg
    initTurtle(turtle, Vector2f(50, 300),3,1/3, 0, 90, Color::Red, Color(255, 255, 0));
    stringCopy("F", input);
    addRule('F', "F+F-F-FF-F-F-fF");
    addRule('f', "fff");
    iterate(input, rules, ruleCount, 4);
    processString(turtle, input);
    ///fractal binary tree
    initTurtle(turtle, Vector2f(400, 500),10,0.8, -90, 30, Color::Red, Color(255, 255, 0));
    stringCopy("A", input);
    addRule('A', "B[+A]-A");
    addRule('B', "BB");
    iterate(input, rules, ruleCount, 5);
    processString(turtle, input);

    ///fractal plant
    initTurtle(turtle, Vector2f(400, 600),5,1, -60, 30, Color::Red, Color(255, 255, 0));
    stringCopy("-X", input);
    addRule('X', "F+[[X]-X]-F[-FX]+X");
    addRule('F', "FF");
    iterate(input, rules, ruleCount, 6);
    processString(turtle, input);

    ///Penta plexity
    initTurtle(turtle, Vector2f(100, 200),10,1, -90, 36, Color::Red, Color(255, 255, 0));
    stringCopy("F++F++F++F++F", input);
    addRule('F', "F++F++F|F-F++F");
    iterate(input, rules, ruleCount, 4);
    processString(turtle, input);

    ///sierpinski haromszog vonallal
    initTurtle(turtle, Vector2f(400, 600),5,0.5, -90, 60, Color::Red, Color(255, 255, 0));
    stringCopy("A", input);
    addRule('A', "B+A+B");
    addRule('B', "A-B-A");
    iterate(input, rules, ruleCount, 6);
    processString(turtle, input);

    ///fa 1
    initTurtle(turtle, Vector2f(400, 600),3,0.5, -90, 25, Color::Red, Color(255, 255, 0));
    stringCopy("B", input);
    addRule('A', "AA");
    addRule('B', "A[[B]+B]+A[+AB]-B");
    iterate(input, rules, ruleCount, 6);
    processString(turtle, input);

    ///virag
    initTurtle(turtle, Vector2f(400, 200),3,0.5, -90, 90, Color::Red, Color(255, 255, 0));
    stringCopy("F-F-F-F", input);
    addRule('F', "FF-F-F-F-F-F+F");
    iterate(input, rules, ruleCount, 4);
    processString(turtle, input);

    ///sepru
    initTurtle(turtle, Vector2f(400, 400),30,0.5, -90, 10, Color::Red, Color(255, 255, 0));
    stringCopy("A", input);
    addRule('A', "A[-B][+B]");
    addRule('B', "A[-B]A[+A]");
    iterate(input, rules, ruleCount, 7);
    processString(turtle, input);

    initTurtle(turtle, Vector2f(400, 500),1,0.5, -90, 90, Color::Red, Color(255, 255, 0));
    stringCopy("F", input);
    addRule('F', "F+F-F-F-g+F+F+F-F");
    addRule('g', "ggg");
    iterate(input, rules, ruleCount, 5);
    processString(turtle, input);

    ///bokor
    initTurtle(turtle, Vector2f(400, 500),6,0.5, -90, 25, Color::Red, Color(255, 255, 0));
    stringCopy("F", input);
    addRule('F',"FF-[-F+F+F]+[+F-F-F]");
    iterate(input, rules, ruleCount, 4);
    processString(turtle, input);
*/
    ///kaposztalevel haromszog
    initTurtle(turtle, Vector2f(100, 500),6,0.5, 0, 85, Color::Red, Color(255, 255, 0));
    stringCopy("F", input);
    addRule('F',"F-F++F-F");
    iterate(input, rules, ruleCount, 6);
    processString(turtle, input);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                //if (event.key.code == Keyboard::Escape)
                window.close();
        }

        window.clear(Color::Black);
        window.draw(turtle.lines);
        window.clear(Color::Black);
        window.draw(turtle.lines);
        window.display();
    }

    return 0;
}