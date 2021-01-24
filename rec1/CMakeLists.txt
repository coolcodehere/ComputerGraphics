cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rec1)

execute_process (
    COMMAND bash -c "gcc main.c -o main -lGL -lGLU -lglut"
)
